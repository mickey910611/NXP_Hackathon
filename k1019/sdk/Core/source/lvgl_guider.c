/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"

#include "fsl_debug_console.h"
#include "lvgl_support.h"
#include "pin_mux.h"
#include "board.h"
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include <stdio.h>
#include "widgets_init.h"
#include "lvgl_demo_utils.h"
#include "lvgl_freertos.h"


//以下wifi預備
/*
#include "FreeRTOS.h"
#include "task.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "wpl.h"
#include "lwip/sockets.h"  // LWIP sockets
#include "lwip/netif.h"    // LWIP network interface
#include "lwip/init.h"     // LWIP initialization
#include "lwip/netdb.h"
#include <stdlib.h>
#include "fsl_device_registers.h"
#include "fsl_gpio.h"
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile bool s_lvgl_initialized = false;
lv_ui guider_ui;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


// 以下wifi預備
/*
static volatile bool ap_started = false;

#define AP_SSID "My_NXP_AP"
#define AP_PASSWORD "12345678"
#define AP_CHANNEL 6
#define TCP_SERVER_PORT 8080
#define TCP_BUFFER_SIZE 256

#define main_task_PRIORITY 1
#define main_task_STACK_DEPTH 800

#define RED_PIN 20U
#define YELLOW_PIN 27U
#define GREEN_PIN 26U

static volatile bool wlan_connected = false;

static void LinkStatusChangeCallback(bool linkState)
{
    if (linkState == false)
    {
        PRINTF("-------- LINK LOST --------\r\n");
    }
    else
    {
        PRINTF("-------- LINK REESTABLISHED --------\r\n");
    }
}


void start_access_point(void) {
    wpl_ret_t err;
    err = WPL_Init();
 if (err != WPLRET_SUCCESS)
 {
  PRINTF("[!] WPL Init failed: %d\r\n", (uint32_t)err);
  __BKPT(0);
 }

 err = WPL_Start(LinkStatusChangeCallback);
 if (err != WPLRET_SUCCESS)
 {
  PRINTF("[!] WPL Start failed %d\r\n", (uint32_t)err);
  __BKPT(0);
 }
//    // 初始化 WLAN 模組
//    err = WPL_Init();
//    if (err != WPLRET_SUCCESS) {
//        PRINTF("WPL_Init failed: %d\r\n", err);
//        return;
//    }

    // 設置 AP 配置 (SSID, 密碼, 頻道)
//    err = WPL_SetAP_Config(AP_SSID, AP_PASSWORD, AP_CHANNEL);
//    if (err != WPLRET_SUCCESS) {
//        PRINTF("WPL_SetAPConfig failed: %d\r\n", err);
//        return;
//    }

    // 啟動 AP 模式
    err = WPL_Start_AP(AP_SSID, AP_PASSWORD, AP_CHANNEL);
    if (err != WPLRET_SUCCESS) {
        PRINTF("WPL_StartAP failed: %d\r\n", err);
        return;
    }

    ap_started = true;
    PRINTF("Access Point started: %s\r\n", AP_SSID);
}


void tcp_server_task(void *arg) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[TCP_BUFFER_SIZE];

    // Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        PRINTF("Failed to create socket\r\n");
        vTaskDelete(NULL);
        return;
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        PRINTF("Bind failed\r\n");
        close(server_socket);
        vTaskDelete(NULL);
        return;
    }

    // Start listening
    listen(server_socket, 1);
    PRINTF("TCP server listening on port %d\r\n", TCP_SERVER_PORT);

    while (1) {
        // Accept client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            PRINTF("Accept failed\r\n");
            continue; // Continue to listen for new connections
        }
        PRINTF("Client connected\r\n");

        // Process incoming messages
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            int recv_len = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (recv_len > 0) {
                PRINTF("Received: %s\r\n", buffer);

                // Convert received string to integer array
                int array[4] = {0}; // Assume storing 4 integers
                char *token = strtok(buffer, " "); // Split string by space
                int i = 0;
                while (token != NULL && i < 4) {
                    array[i] = atoi(token); // Convert string to integer
                    token = strtok(NULL, " "); // Get next token
                    i++;
                }
                PRINTF("array[0] = %d\r\n", array[0]);
                if (array[0] == 0) {
                    // 打開綠燈
                    GPIO_PinWrite(GPIO1, RED_PIN, 0);
                    GPIO_PinWrite(GPIO1, YELLOW_PIN, 0);
                    GPIO_PinWrite(GPIO1, GREEN_PIN, 1);  // 打開綠燈
                } else if (array[0] == 1) {
                    // 打開黃燈
                    GPIO_PinWrite(GPIO1, RED_PIN, 0);
                    GPIO_PinWrite(GPIO1, YELLOW_PIN, 1); // 打開黃燈
                    GPIO_PinWrite(GPIO1, GREEN_PIN, 0);
                } else if (array[0] == 2) {
                    // 打開紅燈
                    GPIO_PinWrite(GPIO1, RED_PIN, 1);    // 打開紅燈
                    GPIO_PinWrite(GPIO1, YELLOW_PIN, 0);
                    GPIO_PinWrite(GPIO1, GREEN_PIN, 0);
                }

                // Display converted integer array
                PRINTF("Converted to array: [%d, %d, %d, %d]\r\n", array[0], array[1], array[2], array[3]);

                // Control lights based on the first value of the array

                // Send confirmation to client
                send(client_socket, "Message received\n", 16, 0);
            } else {
                PRINTF("Client disconnected\r\n");
                break; // Exit inner loop, wait for the next connection
            }
        }

        close(client_socket); // Close client connection
    }

    close(server_socket); // Close server socket
    vTaskDelete(NULL);
}



void task_main(void *param) {
    PRINTF("Starting AP and TCP server...\r\n");

    // 啟動接入點 (AP)
    start_access_point();
    if (ap_started) {
        // 啟動 TCP 伺服器任務
        xTaskCreate(tcp_server_task, "tcp_server_task", main_task_STACK_DEPTH, NULL, main_task_PRIORITY, NULL);
    }

    vTaskDelete(NULL);
}
*/




#if LV_USE_LOG
static void print_cb(const char *buf)
{
    PRINTF("\r%s\n", buf);
}
#endif

static uint32_t get_idle_time_cb(void)
{
    return (getIdleTaskTime() / 1000);
}

static void reset_idle_time_cb(void)
{
    resetIdleTaskTime();
}

static void AppTask(void *param)
{
#if LV_USE_LOG
    lv_log_register_print_cb(print_cb);
#endif

    lv_timer_register_get_idle_cb(get_idle_time_cb);
    lv_timer_register_reset_idle_cb(reset_idle_time_cb);
    lv_port_pre_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    s_lvgl_initialized = true;

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

#if LV_USE_VIDEO
    Video_InitPXP();
#endif

    for (;;)
    {
        lv_task_handler();
        vTaskDelay(2);
    }
}

#if LV_USE_VIDEO
static void VideoTask(void *param)
{
    for( ;; )
    {
        video_play(&guider_ui);
    }
}
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
	// 以下wifi預備部分
	/*
	;66666666    BaseType_t result = 0;
	    (void)result;

	    BOARD_ConfigMPU();
	    BOARD_InitPins();
	    BOARD_InitBootPins();
	    BOARD_InitBootClocks();
	    BOARD_InitDebugConsole();

	    gpio_pin_config_t gpio_output_config = {
	        kGPIO_DigitalOutput, 0,  // 配置為數字輸出，並且初始值為 0（燈關閉）
	    };

	    GPIO_PinInit(GPIO1, RED_PIN, &gpio_output_config);
	    GPIO_PinInit(GPIO1, YELLOW_PIN, &gpio_output_config);
	    GPIO_PinInit(GPIO1, GREEN_PIN, &gpio_output_config);
	    result = xTaskCreate(task_main, "main", main_task_STACK_DEPTH, NULL, main_task_PRIORITY, NULL);
	    assert(pdPASS == result);

	    vTaskStartScheduler();
	    for (;;)
	        ;
	*/


    BaseType_t stat;

    /* Init board hardware. */
    /* Set the eLCDIF read_qos priority high, to make sure eLCDIF
     * can fetch data in time when PXP is used.
     */
    *((volatile uint32_t *)0x41044100) = 5;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_InitI2C1Pins();
    BOARD_InitSemcPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    DEMO_InitUsTimer();


    stat = xTaskCreate(AppTask, "lvgl", configMINIMAL_STACK_SIZE + 8000, NULL, configMAX_PRIORITIES - 1, NULL);

    if (pdPASS != stat)
    {
        PRINTF("Failed to create lvgl task");
        while (1)
            ;
    }

#if LV_USE_VIDEO
    if (xTaskCreate(VideoTask, "Video", configMINIMAL_STACK_SIZE + 8000, NULL, configMAX_PRIORITIES -3, NULL) != pdPASS)
    {
        PRINTF("Failed to create video task");
        while (1)
            ;
    }
#endif


    vTaskStartScheduler();

    for (;;)
    {
    } /* should never get here */
}

/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    PRINTF("Malloc failed. Increase the heap size.");

    for (;;)
        ;
}

/*!
 * @brief FreeRTOS tick hook.
 */
void vApplicationTickHook(void)
{
    if (s_lvgl_initialized)
    {
        lv_tick_inc(1);
    }
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    for (;;)
        ;
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize)
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
