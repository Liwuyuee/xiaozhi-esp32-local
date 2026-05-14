/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "unity_test_runner.h"
#include "unity_test_utils_memory.h"

void setUp(void)
{
    unity_utils_record_free_mem();
}

void tearDown(void)
{
    unity_utils_evaluate_leaks();
}

void app_main(void)
{
    /*
      ____ _______   _____________     __                   __
     |    |   \   \ /   /\_   ___ \  _/  |_  ____   _______/  |_
     |    |   /\   Y   / /    \  \/  \   __\/ __ \ /  ___/\   __\
     |    |  /  \     /  \     \____  |  | \  ___/ \___ \  |  |
     |______/    \___/    \______  /  |__|  \___  >____  > |__|
                                 \/             \/     \/
    */
    printf(" ____ _______   _____________     __                   __   \r\n");
    printf("|    |   \\   \\ /   /\\_   ___ \\  _/  |_  ____   _______/  |_ \r\n");
    printf("|    |   /\\   Y   / /    \\  \\/  \\   __\\/ __ \\ /  ___/\\   __\\\r\n");
    printf("|    |  /  \\     /  \\     \\____  |  | \\  ___/ \\___ \\  |  |  \r\n");
    printf("|______/    \\___/    \\______  /  |__|  \\___  >____  > |__|  \r\n");
    printf("                            \\/             \\/     \\/  \r\n");

    unity_utils_setup_heap_record(80);
    unity_utils_set_leak_level(530);
    unity_run_menu();
}
