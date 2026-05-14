# SSCMA Client

[![Component Registry](https://components.espressif.com/components/wvirgil123/sscma_client/badge.svg)](https://components.espressif.com/components/wvirgil123/sscma_client)

## Quick Start

Below is a minimal example for initializing and using the SSCMA Client component via UART, with English comments and no project-specific dependencies.

```c
#include "sscma_client_io.h"
#include "sscma_client_ops.h"
#include "driver/uart.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static sscma_client_io_handle_t io = NULL;
sscma_client_handle_t client = NULL;

// Callback for inference result
typedef void (*sscma_client_event_cb_t)(sscma_client_handle_t, const sscma_client_reply_t *, void *);
void on_event(sscma_client_handle_t client, const sscma_client_reply_t *reply, void *user_ctx)
{
    printf("on_event: %s\n", reply->data);
}

void on_log(sscma_client_handle_t client, const sscma_client_reply_t *reply, void *user_ctx)
{
    printf("log: %s\n", reply->data);
}

void on_connect(sscma_client_handle_t client, const sscma_client_reply_t *reply, void *user_ctx)
{
    printf("on_connect\n");
}

void app_main(void)
{
    // 1. Initialize UART for SSCMA communication
    uart_config_t uart_config = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;
    ESP_ERROR_CHECK(uart_driver_install(1, 8 * 1024, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(1, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(1, 21, 20, -1, -1));

    // 2. Create SSCMA client UART IO
    sscma_client_io_uart_config_t io_uart_config = {
        .user_ctx = NULL,
    };
    sscma_client_new_io_uart_bus((sscma_client_uart_bus_handle_t)1, &io_uart_config, &io);

    // 3. Configure SSCMA client
    sscma_client_config_t sscma_client_config = SSCMA_CLIENT_CONFIG_DEFAULT();
    sscma_client_config.reset_gpio_num = GPIO_NUM_5; // Set your reset GPIO
    sscma_client_new(io, &sscma_client_config, &client);

    // 4. Register callbacks
    const sscma_client_callback_t callback = {
        .on_connect = on_connect,
        .on_event = on_event,
        .on_log = on_log,
    };
    sscma_client_register_callback(client, &callback, NULL);

    // 5. Initialize SSCMA client
    sscma_client_init(client);

    // 6. Set model and get info
    sscma_client_set_model(client, 1);
    sscma_client_info_t *info;
    if (sscma_client_get_info(client, &info, true) == ESP_OK) {
        printf("ID: %s\n", info->id ? info->id : "NULL");
        // ... print other info fields ...
    }

    // 7. Run inference
    if (sscma_client_invoke(client, -1, false, false) != ESP_OK) {
        printf("invoke failed\n");
    }

    // 8. Main loop
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
```
