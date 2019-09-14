#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "driver/uart.h"
#include "esp_vfs_dev.h"

void app_main()
{
    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    char str[100],ch[100];
    int num = 0,i=0,temp=0,j=0;

    while(1) {
      goto6:
      while(1)
      {
        printf("toggle mode \n");
        goto1: gets(str);
        if(str[0]=='t'&& str[1]=='\0')
        {
          printf("Read: %s \n",str);
          goto goto1;
        }
        else if(str[0]=='s'&& str[1]=='\0')
        {
          printf("Read: %s \n",str);
          goto goto2;
        }
      }
      goto2:
      while(1)
      {
        printf("echo mode \n");
        goto3:gets(str);
        if(str[0]=='s'&& str[1]=='\0')
        {
          printf("echo: %s \n",str);
          goto goto4;
        }
        else
        {
          printf("echo: %s \n",str);
          goto goto3;
        }
      }
      goto4:
      while(1)
      {
        printf("echo dec to hex mode \n");
        goto5: printf("Enter a integer: \n");
        for(i=0;i<100;i++)
          ch[i]='\0';
        gets(ch);
        if(ch[0]=='s'&& ch[1]=='\0')
        {
          goto goto6;
        }
        else
        {
          for(i=0;ch[i]!='\0';i++)
          {
            num=num*10+(ch[i]-'0');
          }
          for(i=0;i<100;i++)
            str[i]='\0';
          i=0;
          while(num!=0)
          {
            temp=0;
            temp=num%16;
            if(temp<10)
            {
              str[i]=temp+48;
              i++;
            }
            else
            {
              str[i]=temp+55;
              i++;
            }
            num=num/16;
          }
          for(j=i-1;j>=0;j--)
          {
            printf("%c",str[j]);
          }
          printf("\n");
          goto goto5;
        }
      }
     vTaskDelay(50 / portTICK_RATE_MS);
    }
}
