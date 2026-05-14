/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <catch2/catch_test_macros.hpp>
#include "mock_add_usb_device.h"
#include "test_fixtures.hpp"

extern "C" {
#include "Mockusb_host.h"
}

esp_err_t test_uvc_host_install(const uvc_host_driver_config_t *driver_config)
{
    // Allocation of CTRL transfer (common for all devices)
    usb_host_transfer_alloc_ExpectAndReturn(64, 0, nullptr, ESP_OK);
    usb_host_transfer_alloc_IgnoreArg_transfer();
    // usb_host_transfer_alloc_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_transfer_alloc_AddCallback(usb_host_transfer_alloc_mock_callback);

    // Client registration
    usb_host_client_register_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_client_register_AddCallback(usb_host_client_register_mock_callback);

    // Client processing
    usb_host_client_handle_events_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_client_handle_events_AddCallback(usb_host_client_handle_events_mock_callback);

    // Call the real function
    return uvc_host_install(driver_config);
}

esp_err_t test_uvc_host_uninstall(void)
{
    usb_host_client_unblock_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_client_unblock_AddCallback(usb_host_client_unblock_mock_callback);

    usb_host_client_deregister_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_client_deregister_AddCallback(usb_host_client_deregister_mock_callback);

    // Free the common CTRL transfer
    usb_host_transfer_free_ExpectAnyArgsAndReturn(ESP_OK);
    usb_host_transfer_free_AddCallback(usb_host_transfer_free_mock_callback);

    // Call the real function
    return uvc_host_uninstall();
}

esp_err_t test_uvc_host_stream_open(const uvc_host_stream_config_t *stream_config, int timeout, uvc_host_stream_hdl_t *stream_hdl_ret, bool is_isoc)
{
    /* **Setup callbacks** */

    // This will setup or mocking framework
    usb_host_device_open_Stub(usb_host_device_open_mock_callback);
    usb_host_get_device_descriptor_Stub(usb_host_get_device_descriptor_mock_callback);
    usb_host_device_close_Stub(usb_host_device_close_mock_callback);
    usb_host_get_active_config_descriptor_Stub(usb_host_get_active_config_descriptor_mock_callback);
    usb_host_device_addr_list_fill_Stub(usb_host_device_addr_list_fill_mock_callback);
    usb_host_device_info_Stub(usb_host_device_info_mock_callback);

    /* **Testing starts here** */

    usb_host_transfer_submit_control_AddCallback(usb_host_transfer_submit_control_success_mock_callback);
    usb_host_interface_claim_ExpectAnyArgsAndReturn(ESP_OK);         // Claim interface
    if (is_isoc) {                                                   // Set interface only for ISOC cameras)
        usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK);
    }

    // Negotiation
    // The UVC driver compares 'GET format' with the 'SET format'
    // Since our mock does not change the negotiated data, it will always succeed
    // Pros: The mock is trivial to implement
    // Cons: We will succeed even when the camera does not support required FPS
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Get current
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Set current
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Get current
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Get max
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Get min
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Set current
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Get current
    usb_host_transfer_submit_control_ExpectAnyArgsAndReturn(ESP_OK); // Commit

    // IN transfers allocation
    for (int i = 0; i < stream_config->advanced.number_of_urbs; i++) {
        usb_host_transfer_alloc_ExpectAnyArgsAndReturn(ESP_OK);
    }
    usb_host_transfer_alloc_AddCallback(usb_host_transfer_alloc_mock_callback);

    return uvc_host_stream_open(stream_config, timeout, stream_hdl_ret);
}

esp_err_t test_uvc_host_stream_close(uvc_host_stream_hdl_t stream_hdl)
{
    usb_host_interface_release_ExpectAnyArgsAndReturn(ESP_OK); // Release data interface
    usb_host_transfer_free_Stub(usb_host_transfer_free_mock_callback); // Free all transfers
    usb_host_device_close_ExpectAnyArgsAndReturn(ESP_OK);      // Close the device

    return uvc_host_stream_close(stream_hdl);
}
