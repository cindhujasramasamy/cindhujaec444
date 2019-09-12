/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO1 13
#define BLINK_GPIO2 12
#define BLINK_GPIO3 33
#define BLINK_GPIO4 27


void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO1);
    gpio_pad_select_gpio(BLINK_GPIO2);
    gpio_pad_select_gpio(BLINK_GPIO3);
    gpio_pad_select_gpio(BLINK_GPIO4);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO3, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO4, GPIO_MODE_OUTPUT);

    int temp[4]={0};

    while(1) {
        for(int i=0;i<=15;i++)
        {
          temp[0]=0;temp[1]=0;temp[2]=0;temp[3]=0;
          int num=i;
          while(num>0)
          {
            if(num>=8)
            {
              temp[0]=1; num-=8;
            }
            else if(num>=4)
            {
              temp[1]=1;num-=4;
            }
            else if(num>=2)
            {
              temp[2]=1;num-=2;
            }
            else if(num>=1)
            {
              temp[3]=1;num-=1;
            }
          }
          gpio_set_level(BLINK_GPIO1, temp[0]);
          gpio_set_level(BLINK_GPIO2, temp[1]);
          gpio_set_level(BLINK_GPIO3, temp[2]);
          gpio_set_level(BLINK_GPIO4, temp[3]);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
  /*Sample Blink code
        //Blink off (output low)
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        //Blink on (output high)
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
  */
    }
}

void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
