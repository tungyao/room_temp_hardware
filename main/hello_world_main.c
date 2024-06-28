/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include "myi2c.h"
#include "gxhtc3.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static const char *TAG =  "main";
void app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    esp_err_t ret = gxhtc3_read_id();
    while(ret != ESP_OK)
    {
         ret = gxhtc3_read_id();
         ESP_LOGI(TAG,"GXHTC3 READ ID");
         vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG,"GXHTC3 OK");

    xTaskCreate(gxhtc3_task, "gxhtc3_task", 4096, NULL, 6, NULL);
}
