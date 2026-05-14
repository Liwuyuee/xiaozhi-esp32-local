/*
 * SPDX-FileCopyrightText: 2024-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: ESPRESSIF MIT
 */

#include <string.h>
#include <inttypes.h>
#include "hal/gpio_ll.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
#include "usb/usb_host.h"
#endif

#include "esp_sccb_i2c.h"
#include "esp_cam_sensor.h"
#include "esp_cam_sensor_detect.h"
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
#include "esp_cam_motor.h"
#include "esp_cam_motor_detect.h"
#endif
#include "esp_cam_sensor_xclk.h"

#include "esp_video_init.h"
#include "esp_video_device_internal.h"
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
#include "esp_private/esp_cam_dvp.h"
#endif
#if CONFIG_ESP_VIDEO_ENABLE_ISP_PIPELINE_CONTROLLER
#include "esp_video_pipeline_isp.h"
#endif

#if ESP_VIDEO_ENABLE_SCCB_DEVICE
#define SCCB_NUM_MAX                I2C_NUM_MAX

#define ESP_VIDEO_SPI_XCLK_NUM      ESP_VIDEO_SPI_DEVICE_NUM

typedef enum esp_video_init_port {
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
    ESP_VIDEO_INIT_DVP_SCCB,
#endif /* CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
    ESP_VIDEO_INIT_CSI_SCCB,
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
    ESP_VIDEO_INIT_MOTOR_SCCB,
#endif /* CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER */
#endif /* CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
    ESP_VIDEO_INIT_SPI_0_SCCB,
#if CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE
    ESP_VIDEO_INIT_SPI_1_SCCB,
#endif /* CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE */
#endif /* CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE */
    ESP_VIDEO_INIT_DEV_NUMS
} esp_video_init_port_t;

/**
 * @brief SCCB initialization mark
 */
#if ESP_VIDEO_ENABLE_SCCB_DEVICE
typedef struct sccb_mark {
    int i2c_ref;                                /*!< I2C reference */
    i2c_master_bus_handle_t handle;             /*!< I2C master handle */
    const esp_video_init_sccb_config_t *config; /*!< SCCB initialization config pointer */
    uint16_t dev_addr;                          /*!< Slave device address */
    esp_cam_sensor_port_t port;                 /*!< Slave device data interface */
} esp_video_init_sccb_mark_t;

typedef struct sensor_sccb_mask {
    i2c_master_bus_handle_t handle;             /*!< I2C master handle */
    esp_sccb_io_handle_t sccb_io[ESP_VIDEO_INIT_DEV_NUMS]; /*!< SCCB I/O handle */
} sensor_sccb_mask_t;
#endif /* ESP_VIDEO_ENABLE_SCCB_DEVICE */

static sensor_sccb_mask_t s_sensor_sccb_mask[SCCB_NUM_MAX];
#endif /* ESP_VIDEO_ENABLE_SCCB_DEVICE */

#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
static esp_cam_sensor_xclk_handle_t s_spi_xclk_handle[ESP_VIDEO_SPI_XCLK_NUM]; /*!< SPI XCLK handle */
#endif /* CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE */
static const char *TAG = "esp_video_init";

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
static void usb_lib_task(void *arg)
{
    ESP_LOGD(TAG, "USB Host installed");

    while (1) {
        uint32_t event_flags;

        if (usb_host_lib_handle_events(portMAX_DELAY, &event_flags) == ESP_OK) {
            if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
                if (usb_host_device_free_all() == ESP_OK) {
                    ESP_LOGI(TAG, "USB: All devices freed");
                    break;
                } else {
                    ESP_LOGD(TAG, "USB: Wait for the FLAGS_ALL_FREE");
                }
            }

            if (event_flags & USB_HOST_LIB_EVENT_FLAGS_ALL_FREE) {
                ESP_LOGD(TAG, "USB: All devices freed");
                break;
            }
        } else {
            ESP_LOGE(TAG, "Failed to handle USB events");
            break;
        }
    }

    vTaskDelay(10); // Short delay to allow clients clean-up
    if (usb_host_uninstall() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to uninstall USB Host driver");
    }
    vTaskDelete(NULL);
}
#endif

#if ESP_VIDEO_ENABLE_SCCB_DEVICE
/**
 * @brief Create I2C master handle
 *
 * @param mark SCCB initialization make array
 * @param port Slave device data interface
 * @param init_sccb_config SCCB initialization configuration
 * @param dev_addr device address
 *
 * @return
 *      - I2C master handle on success
 *      - NULL if failed
 */
static i2c_master_bus_handle_t create_i2c_master_bus(esp_video_init_sccb_mark_t *mark,
        esp_video_init_port_t port,
        const esp_video_init_sccb_config_t *init_sccb_config,
        uint16_t dev_addr)
{
    esp_err_t ret;
    i2c_master_bus_handle_t bus_handle = NULL;
    int i2c_port = init_sccb_config->i2c_config.port;
    char *interface_name[ESP_VIDEO_INIT_DEV_NUMS] = {
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
        [ESP_VIDEO_INIT_DVP_SCCB] = "DVP",
#endif /* CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
        [ESP_VIDEO_INIT_CSI_SCCB] = "CSI",
#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
        [ESP_VIDEO_INIT_MOTOR_SCCB] = "Motor",
#endif /* CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER */
#endif /* CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
        [ESP_VIDEO_INIT_SPI_0_SCCB] = "SPI 0",
#if CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE
        [ESP_VIDEO_INIT_SPI_1_SCCB] = "SPI 1",
#endif /* CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE */
#endif /* CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE */
    };


    if (i2c_port > SCCB_NUM_MAX) {
        return NULL;
    }

    if (mark[i2c_port].handle != NULL) {
        if (init_sccb_config->i2c_config.scl_pin != mark[i2c_port].config->i2c_config.scl_pin) {
            ESP_LOGE(TAG, "Interface %s and %s: I2C port %d SCL pin is mismatched", interface_name[port],
                     interface_name[mark[i2c_port].port], i2c_port);
            return NULL;
        }

        if (init_sccb_config->i2c_config.sda_pin != mark[i2c_port].config->i2c_config.sda_pin) {
            ESP_LOGE(TAG, "Interface %s and %s: I2C port %d SDA pin is mismatched", interface_name[port],
                     interface_name[mark[i2c_port].port], i2c_port);
            return NULL;
        }

        if (dev_addr == mark[i2c_port].dev_addr) {
            ESP_LOGE(TAG, "Interface %s and %s: use same SCCB device address %d", interface_name[port],
                     interface_name[mark[i2c_port].port], dev_addr);
            return NULL;
        }

        bus_handle = mark[i2c_port].handle;
    } else {
        i2c_master_bus_config_t i2c_bus_config = {0};

        i2c_bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
        i2c_bus_config.i2c_port = init_sccb_config->i2c_config.port;
        i2c_bus_config.scl_io_num = init_sccb_config->i2c_config.scl_pin;
        i2c_bus_config.sda_io_num = init_sccb_config->i2c_config.sda_pin;
        i2c_bus_config.glitch_ignore_cnt = 7;
        i2c_bus_config.flags.enable_internal_pullup = true,

        ret = i2c_new_master_bus(&i2c_bus_config, &bus_handle);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "failed to initialize I2C master bus port %d", init_sccb_config->i2c_config.port);
            return NULL;
        }

        mark[i2c_port].handle = bus_handle;
        mark[i2c_port].config = init_sccb_config;
        mark[i2c_port].dev_addr = dev_addr;
        mark[i2c_port].port = port;
    }

    mark[i2c_port].i2c_ref++;
    assert(mark[i2c_port].i2c_ref > 0);

    return bus_handle;
}

/**
 * @brief Create SCCB device
 *
 * @param mark SCCB initialization make array
 * @param port Slave device data interface
 * @param init_sccb_config SCCB initialization configuration
 * @param dev_addr device address
 *
 * @return
 *      - SCCB handle on success
 *      - NULL if failed
 */
static esp_sccb_io_handle_t create_sccb_device(esp_video_init_sccb_mark_t *mark,
        esp_video_init_port_t port,
        const esp_video_init_sccb_config_t *init_sccb_config,
        uint16_t dev_addr)
{
    esp_err_t ret;
    esp_sccb_io_handle_t sccb_io;
    sccb_i2c_config_t sccb_config = {0};
    i2c_master_bus_handle_t bus_handle;
    int i2c_port = init_sccb_config->i2c_config.port;
    int sccb_io_num = port;

    if (init_sccb_config->init_sccb) {
        bus_handle = create_i2c_master_bus(mark, port, init_sccb_config, dev_addr);
    } else {
        bus_handle = init_sccb_config->i2c_handle;
    }

    if (!bus_handle) {
        return NULL;
    }

    sccb_config.dev_addr_length = I2C_ADDR_BIT_LEN_7,
    sccb_config.device_address = dev_addr,
    sccb_config.scl_speed_hz = init_sccb_config->freq,
    ret = sccb_new_i2c_io(bus_handle, &sccb_config, &sccb_io);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to initialize SCCB");
        return NULL;
    }

    if (init_sccb_config->init_sccb) {
        s_sensor_sccb_mask[i2c_port].handle = bus_handle;
        s_sensor_sccb_mask[i2c_port].sccb_io[sccb_io_num] = sccb_io;
    } else {
        for (int i = 0; i < SCCB_NUM_MAX; i++) {
            if (!s_sensor_sccb_mask[i].sccb_io[sccb_io_num]) {
                s_sensor_sccb_mask[i].sccb_io[sccb_io_num] = sccb_io;
                break;
            }
        }
    }

    return sccb_io;
}

/**
 * @brief Destroy SCCB device
 *
 * @param handle SCCB handle
 * @param mark SCCB initialization make array
 *
 * @return None
 */
static void destroy_sccb_device(esp_sccb_io_handle_t handle, esp_video_init_sccb_mark_t *mark,
                                const esp_video_init_sccb_config_t *init_sccb_config)
{
    esp_sccb_del_i2c_io(handle);
    if (init_sccb_config->init_sccb) {
        int i2c_port = init_sccb_config->i2c_config.port;

        if (mark[i2c_port].handle) {
            assert(mark[i2c_port].i2c_ref > 0);
            mark[i2c_port].i2c_ref--;
            if (!mark[i2c_port].i2c_ref) {
                i2c_del_master_bus(mark[i2c_port].handle);
                mark[i2c_port].handle = NULL;

                s_sensor_sccb_mask[i2c_port].handle = NULL;
                for (int j = 0; j < ESP_VIDEO_INIT_DEV_NUMS; j++) {
                    s_sensor_sccb_mask[i2c_port].sccb_io[j] = NULL;
                }
            }
        }
    } else {
        for (int i = 0; i < SCCB_NUM_MAX; i++) {
            for (int j = 0; j < ESP_VIDEO_INIT_DEV_NUMS; j++) {
                if (s_sensor_sccb_mask[i].sccb_io[j] == handle) {
                    s_sensor_sccb_mask[i].sccb_io[j] = NULL;
                    break;
                }
            }
        }
    }
}

static bool sensor_is_detected(esp_cam_sensor_detect_fn_t *p, esp_cam_sensor_device_t *cam_dev)
{
    return true;
}
#endif

/**
 * @brief Initialize video hardware and software, including I2C, MIPI CSI and so on.
 *
 * @param config video hardware configuration
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_init(const esp_video_init_config_t *config)
{
    esp_err_t ret = ESP_OK;
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
    bool csi_inited = false;
#endif /* CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
    bool dvp_inited = false;
#endif /* CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE */
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
    bool spi_inited[ESP_VIDEO_SPI_DEVICE_NUM] = {false};
#endif /* CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE */
#if ESP_VIDEO_ENABLE_SCCB_DEVICE
    esp_video_init_sccb_mark_t sccb_mark[SCCB_NUM_MAX] = {0};
#endif /* ESP_VIDEO_ENABLE_SCCB_DEVICE */

    if (config == NULL) {
        ESP_LOGW(TAG, "Please validate camera config");
        return ESP_ERR_INVALID_ARG;
    }

#if CONFIG_ESP_VIDEO_ENABLE_ISP_VIDEO_DEVICE
    ret = esp_video_create_isp_video_device();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to create hardware ISP video device");
        return ret;
    }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
    if (config->usb_uvc) {
        if (config->usb_uvc->usb.init_usb_host_lib) {
            TaskHandle_t usb_lib_task_handler = NULL;
            BaseType_t usb_task_created = pdFALSE;
            int task_affinity = config->usb_uvc->usb.task_affinity >= 0 ? config->usb_uvc->usb.task_affinity : tskNO_AFFINITY;

            ESP_LOGD(TAG, "Installing USB Host");

            usb_host_config_t host_config = {
                .skip_phy_setup = false,
                .intr_flags = ESP_INTR_FLAG_LEVEL1,
            };
            if (usb_host_install(&host_config) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to install USB Host driver");
                return ESP_FAIL;
            }

            usb_task_created = xTaskCreatePinnedToCore(
                                   usb_lib_task,
                                   "usb_lib",
                                   config->usb_uvc->usb.task_stack,
                                   NULL,
                                   config->usb_uvc->usb.task_priority,
                                   &usb_lib_task_handler,
                                   task_affinity);
            if (usb_task_created != pdTRUE) {
                ESP_LOGE(TAG, "Failed to create USB host library task");
                return ESP_FAIL;
            }
        }

        esp_video_usb_uvc_device_config_t cfg = {
            .uvc_dev_num = config->usb_uvc->uvc.uvc_dev_num,
            .task_stack = config->usb_uvc->uvc.task_stack,
            .task_priority = config->usb_uvc->uvc.task_priority,
            .task_affinity = config->usb_uvc->uvc.task_affinity,
        };

        ESP_RETURN_ON_ERROR(esp_video_install_usb_uvc_driver(&cfg), TAG, "Failed to install USB UVC driver");
    }
#endif

    for (esp_cam_sensor_detect_fn_t *p = &__esp_cam_sensor_detect_fn_array_start; p < &__esp_cam_sensor_detect_fn_array_end; ++p) {
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
        if (!csi_inited && p->port == ESP_CAM_SENSOR_MIPI_CSI && config->csi != NULL) {
            esp_cam_sensor_config_t cfg;
            esp_cam_sensor_device_t *cam_dev;

            cfg.sccb_handle = create_sccb_device(sccb_mark, ESP_VIDEO_INIT_CSI_SCCB, &config->csi->sccb_config, p->sccb_addr);
            if (!cfg.sccb_handle) {
                return ESP_FAIL;
            }

            cfg.reset_pin = config->csi->reset_pin,
            cfg.pwdn_pin = config->csi->pwdn_pin,
            cam_dev = (*(p->detect))((void *)&cfg);
            if (!cam_dev) {
                destroy_sccb_device(cfg.sccb_handle, sccb_mark, &config->csi->sccb_config);
                ESP_LOGE(TAG, "failed to detect MIPI-CSI camera sensor with address=%x", p->sccb_addr);
                continue;
            }

            ret = esp_video_create_csi_video_device(cam_dev);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to create MIPI-CSI video device");
                return ret;
            }

#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
            if (config->cam_motor) {
                for (esp_cam_motor_detect_fn_t *p = &__esp_cam_motor_detect_fn_array_start; p < &__esp_cam_motor_detect_fn_array_end; p++) {
                    esp_cam_motor_config_t cfg = {0};
                    esp_cam_motor_device_t *motor_dev;
                    const esp_video_init_cam_motor_config_t *cm = config->cam_motor;
                    cfg.sccb_handle = create_sccb_device(sccb_mark, ESP_VIDEO_INIT_MOTOR_SCCB, &cm->sccb_config, p->sccb_addr);
                    if (!cfg.sccb_handle) {
                        return ESP_FAIL;
                    }

                    cfg.reset_pin = cm->reset_pin,
                    cfg.pwdn_pin = cm->pwdn_pin,
                    cfg.signal_pin = cm->signal_pin,
                    motor_dev = (*(p->detect))((void *)&cfg);
                    if (!motor_dev) {
                        destroy_sccb_device(cfg.sccb_handle, sccb_mark, &config->csi->sccb_config);
                        ESP_LOGE(TAG, "failed to detect sensor motor with address=%x", p->sccb_addr);
                        continue;
                    }

                    ret = esp_video_csi_video_device_add_motor(motor_dev);
                    if (ret != ESP_OK) {
                        ESP_LOGE(TAG, "failed to add motor device to CSI video device");
                        return ret;
                    }
                    break;
                }
            }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_ISP_PIPELINE_CONTROLLER
            if (cam_dev->cur_format && cam_dev->cur_format->isp_info) {
                const esp_ipa_config_t *ipa_config = esp_ipa_pipeline_get_config(cam_dev->name);
                if (ipa_config) {
                    esp_video_isp_config_t isp_config = {
                        .cam_dev = ESP_VIDEO_MIPI_CSI_DEVICE_NAME,
                        .isp_dev = ESP_VIDEO_ISP1_DEVICE_NAME,
                        .ipa_config = ipa_config
                    };

                    ret = esp_video_isp_pipeline_init(&isp_config);
                    if (ret != ESP_OK) {
                        ESP_LOGE(TAG, "failed to create ISP pipeline controller");
                        return ret;
                    }
                } else {
                    ESP_LOGW(TAG, "failed to get configuration to initialize ISP controller");
                }
            }
#endif
            csi_inited = true;
        }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
        if (!dvp_inited && p->port == ESP_CAM_SENSOR_DVP && config->dvp != NULL) {
            int dvp_ctlr_id = 0;
            esp_cam_sensor_config_t cfg;
            esp_cam_sensor_device_t *cam_dev;

            ret = esp_cam_ctlr_dvp_init(dvp_ctlr_id, CAM_CLK_SRC_DEFAULT, &config->dvp->dvp_pin);
            if (ret != ESP_OK) {
                return ret;
            }

            if (config->dvp->dvp_pin.xclk_io >= 0 && config->dvp->xclk_freq > 0) {
                ret = esp_cam_ctlr_dvp_output_clock(dvp_ctlr_id, CAM_CLK_SRC_DEFAULT, config->dvp->xclk_freq);
                if (ret != ESP_OK) {
                    return ret;
                }
            }

            cfg.sccb_handle = create_sccb_device(sccb_mark, ESP_VIDEO_INIT_DVP_SCCB, &config->dvp->sccb_config, p->sccb_addr);
            if (!cfg.sccb_handle) {
                return ESP_FAIL;
            }

            cfg.reset_pin = config->dvp->reset_pin,
            cfg.pwdn_pin = config->dvp->pwdn_pin,
            cam_dev = (*(p->detect))((void *)&cfg);
            if (!cam_dev) {
                destroy_sccb_device(cfg.sccb_handle, sccb_mark, &config->dvp->sccb_config);
                esp_cam_ctlr_dvp_deinit(dvp_ctlr_id);
                ESP_LOGE(TAG, "failed to detect DVP camera with address=%x", p->sccb_addr);
                continue;
            }

            ret = esp_video_create_dvp_video_device(cam_dev);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "failed to create DVP video device");
                return ret;
            }

            dvp_inited = true;
        }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
        if (p->port == ESP_CAM_SENSOR_SPI && config->spi != NULL) {
            for (uint8_t i = 0; i < ESP_VIDEO_SPI_DEVICE_NUM; i++) {
                if (spi_inited[i]) {
                    continue;
                }

                esp_cam_sensor_config_t cfg;
                esp_cam_sensor_device_t *cam_dev;
                esp_cam_sensor_xclk_handle_t xclk_handle = NULL;
                const esp_video_init_spi_config_t *spi_config = &config->spi[i];

                if (spi_config->xclk_pin >= 0 && spi_config->xclk_freq > 0) {
                    esp_cam_sensor_xclk_config_t cam_xclk_config = {0};

#if CONFIG_CAMERA_XCLK_USE_ESP_CLOCK_ROUTER
                    if (spi_config->xclk_source == ESP_CAM_SENSOR_XCLK_ESP_CLOCK_ROUTER) {
                        cam_xclk_config.esp_clock_router_cfg.xclk_pin = spi_config->xclk_pin;
                        cam_xclk_config.esp_clock_router_cfg.xclk_freq_hz = spi_config->xclk_freq;
                    }
#endif

#if CONFIG_CAMERA_XCLK_USE_LEDC
                    if (spi_config->xclk_source == ESP_CAM_SENSOR_XCLK_LEDC) {
                        cam_xclk_config.ledc_cfg.timer = spi_config->xclk_ledc_cfg.timer;
                        cam_xclk_config.ledc_cfg.clk_cfg = spi_config->xclk_ledc_cfg.clk_cfg;
                        cam_xclk_config.ledc_cfg.channel = spi_config->xclk_ledc_cfg.channel;
                        cam_xclk_config.ledc_cfg.xclk_freq_hz = spi_config->xclk_freq;
                        cam_xclk_config.ledc_cfg.xclk_pin = spi_config->xclk_pin;

                        ESP_LOGD(TAG, "SPI CAM%d:pin=%d, freq=%" PRIu32 ", timer=%d, channel=%d", i, spi_config->xclk_pin,
                                 spi_config->xclk_freq, spi_config->xclk_ledc_cfg.timer, spi_config->xclk_ledc_cfg.channel);
                    }
#endif
                    if (esp_cam_sensor_xclk_allocate(spi_config->xclk_source, &xclk_handle) != ESP_OK) {
                        ESP_LOGE(TAG, "SPI %d xclk allocate failed.", i);
                        return ESP_FAIL;
                    }

                    if (esp_cam_sensor_xclk_start(xclk_handle, &cam_xclk_config) != ESP_OK) {
                        ESP_LOGE(TAG, "SPI xclk start failed.");
                        esp_cam_sensor_xclk_free(xclk_handle);
                        return ESP_FAIL;
                    }
                }

#if CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE
                esp_video_init_port_t init_port = i == 0 ? ESP_VIDEO_INIT_SPI_0_SCCB : ESP_VIDEO_INIT_SPI_1_SCCB;
#else
                esp_video_init_port_t init_port = ESP_VIDEO_INIT_SPI_0_SCCB;
#endif /* CONFIG_ESP_VIDEO_ENABLE_THE_SECOND_SPI_VIDEO_DEVICE */
                cfg.sccb_handle = create_sccb_device(sccb_mark, init_port, &spi_config->sccb_config, p->sccb_addr);
                if (!cfg.sccb_handle) {
                    if (xclk_handle) {
                        esp_cam_sensor_xclk_stop(xclk_handle);
                        esp_cam_sensor_xclk_free(xclk_handle);
                    }
                    return ESP_FAIL;
                }

                cfg.reset_pin = spi_config->reset_pin;
                cfg.pwdn_pin = spi_config->pwdn_pin;
                cam_dev = (*(p->detect))((void *)&cfg);
                if (!cam_dev) {
                    destroy_sccb_device(cfg.sccb_handle, sccb_mark, &spi_config->sccb_config);
                    if (xclk_handle) {
                        esp_cam_sensor_xclk_stop(xclk_handle);
                        esp_cam_sensor_xclk_free(xclk_handle);
                    }
                    ESP_LOGE(TAG, "failed to detect SPI camera %d with address=%x", i, p->sccb_addr);
                    continue;
                }

                esp_video_spi_device_config_t spi_dev_config = {
                    .spi_port = spi_config->spi_port,
                    .spi_cs_pin = spi_config->spi_cs_pin,
                    .spi_sclk_pin = spi_config->spi_sclk_pin,
                    .spi_data0_io_pin = spi_config->spi_data0_io_pin
                };
                ret = esp_video_create_spi_video_device(cam_dev, &spi_dev_config, i);
                if (ret != ESP_OK) {
                    ESP_LOGE(TAG, "failed to create SPI video device");
                    return ret;
                }

                s_spi_xclk_handle[i] = xclk_handle;
                spi_inited[i] = true;
            }
        }
#endif
    }

#if CONFIG_ESP_VIDEO_ENABLE_HW_H264_VIDEO_DEVICE
    ret = esp_video_create_h264_video_device(true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to create hardware H.264 video device");
        return ret;
    }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
    jpeg_encoder_handle_t handle = NULL;

    if (config->jpeg) {
        handle = config->jpeg->enc_handle;
    }

    ret = esp_video_create_jpeg_video_device(handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to create hardware JPEG video device");
        return ret;
    }
#endif

    return ret;
}

/**
 * @brief Deinitialize video hardware and software, including I2C, MIPI CSI and so on.
 *
 * @param None
 *
 * @return
 *      - ESP_OK on success
 *      - Others if failed
 */
esp_err_t esp_video_deinit(void)
{
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
    bool csi_deinited = false;
#endif
#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
    bool dvp_deinited = false;
#endif
#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
    bool spi_deinited[ESP_VIDEO_SPI_DEVICE_NUM] = {false};
#endif

#if CONFIG_ESP_VIDEO_ENABLE_HW_JPEG_VIDEO_DEVICE
    ESP_RETURN_ON_ERROR(esp_video_destroy_jpeg_video_device(), TAG, "Failed to destroy JPEG video device");
#endif

#if CONFIG_ESP_VIDEO_ENABLE_HW_H264_VIDEO_DEVICE
    ESP_RETURN_ON_ERROR(esp_video_destroy_h264_video_device(true), TAG, "Failed to destroy H.264 video device");
#endif

    for (esp_cam_sensor_detect_fn_t *p = &__esp_cam_sensor_detect_fn_array_start; p < &__esp_cam_sensor_detect_fn_array_end; ++p) {
#if CONFIG_ESP_VIDEO_ENABLE_MIPI_CSI_VIDEO_DEVICE
        if (!csi_deinited && p->port == ESP_CAM_SENSOR_MIPI_CSI) {
            esp_cam_sensor_device_t *cam_dev;

            cam_dev = esp_video_get_csi_video_device_sensor();
            if (!cam_dev) {
                continue;
            }

            if (!sensor_is_detected(p, cam_dev)) {
                continue;
            }

#if CONFIG_ESP_VIDEO_ENABLE_CAMERA_MOTOR_CONTROLLER
            esp_cam_motor_device_t *motor_dev = esp_video_get_csi_video_device_motor();
            if (motor_dev) {
                ESP_RETURN_ON_ERROR(esp_cam_motor_del_dev(motor_dev), TAG, "Failed to delete CSI motor");
            }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_ISP_PIPELINE_CONTROLLER
            if (esp_video_isp_pipeline_is_initialized()) {
                ESP_RETURN_ON_ERROR(esp_video_isp_pipeline_deinit(), TAG, "Failed to destroy ISP controller");
            }
#endif

            ESP_RETURN_ON_ERROR(esp_video_destroy_csi_video_device(), TAG, "Failed to destroy CSI video device");
            ESP_RETURN_ON_ERROR(esp_cam_sensor_del_dev(cam_dev), TAG, "Failed to delete CSI sensor");

            csi_deinited = true;
        }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_DVP_VIDEO_DEVICE
        if (!dvp_deinited && p->port == ESP_CAM_SENSOR_DVP) {
            int dvp_ctlr_id = 0;
            esp_cam_sensor_device_t *cam_dev;

            cam_dev = esp_video_get_dvp_video_device_sensor();
            if (!cam_dev) {
                continue;
            }

            if (!sensor_is_detected(p, cam_dev)) {
                continue;
            }

            ESP_RETURN_ON_ERROR(esp_video_destroy_dvp_video_device(), TAG, "Failed to destroy DVP video device");
            ESP_RETURN_ON_ERROR(esp_cam_sensor_del_dev(cam_dev), TAG, "Failed to delete DVP sensor");
            ESP_RETURN_ON_ERROR(esp_cam_ctlr_dvp_deinit(dvp_ctlr_id), TAG, "Failed to deinit DVP port");

            dvp_deinited = true;
        }
#endif

#if CONFIG_ESP_VIDEO_ENABLE_SPI_VIDEO_DEVICE
        if (p->port == ESP_CAM_SENSOR_SPI) {
            for (uint8_t i = 0; i < ESP_VIDEO_SPI_DEVICE_NUM; i++) {
                if (spi_deinited[i]) {
                    continue;
                }

                esp_cam_sensor_device_t *cam_dev;

                cam_dev = esp_video_get_spi_video_device_sensor(i);
                if (!cam_dev) {
                    continue;
                }

                if (!sensor_is_detected(p, cam_dev)) {
                    continue;
                }

                ESP_RETURN_ON_ERROR(esp_video_destroy_spi_video_device(i), TAG, "Failed to destroy SPI CAM%d video device", i);
                ESP_RETURN_ON_ERROR(esp_cam_sensor_del_dev(cam_dev), TAG, "Failed to delete SPI CAM%d sensor", i);
                if (s_spi_xclk_handle[i]) {
                    ESP_RETURN_ON_ERROR(esp_cam_sensor_xclk_stop(s_spi_xclk_handle[i]), TAG, "Failed to stop SPI CAM%d XCLK", i);
                    ESP_RETURN_ON_ERROR(esp_cam_sensor_xclk_free(s_spi_xclk_handle[i]), TAG, "Failed to free SPI CAM%d XCLK", i);
                    s_spi_xclk_handle[i] = NULL;
                }
                spi_deinited[i] = true;
            }
        }
#endif
    }

#if ESP_VIDEO_ENABLE_SCCB_DEVICE
    for (int i = 0; i < SCCB_NUM_MAX; i++) {
        sensor_sccb_mask_t *m = &s_sensor_sccb_mask[i];

        for (int j = 0; j < ESP_VIDEO_INIT_DEV_NUMS; j++) {
            if (m->sccb_io[j]) {
                esp_sccb_del_i2c_io(m->sccb_io[j]);
            }
        }

        if (m->handle) {
            i2c_del_master_bus(m->handle);
        }
    }
    memset(s_sensor_sccb_mask, 0, sizeof(s_sensor_sccb_mask));
#endif /* ESP_VIDEO_ENABLE_SCCB_DEVICE */

#if CONFIG_ESP_VIDEO_ENABLE_USB_UVC_VIDEO_DEVICE
    ESP_RETURN_ON_ERROR(esp_video_uninstall_usb_uvc_driver(), TAG, "Failed to uninstall USB UVC driver");
#endif

#if CONFIG_ESP_VIDEO_ENABLE_ISP_VIDEO_DEVICE
    ESP_RETURN_ON_ERROR(esp_video_destroy_isp_video_device(), TAG, "Failed to destroy ISP video device");
#endif

    return ESP_OK;
}
