################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/nxp/GUI-Guider-Projects/k1019/sdk/Core/lvgl/lvgl/src/extra/widgets/chart/lv_chart.c 

C_DEPS += \
./lvgl/lvgl/src/extra/widgets/chart/lv_chart.d 

OBJS += \
./lvgl/lvgl/src/extra/widgets/chart/lv_chart.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/extra/widgets/chart/lv_chart.o: C:/nxp/GUI-Guider-Projects/k1019/sdk/Core/lvgl/lvgl/src/extra/widgets/chart/lv_chart.c lvgl/lvgl/src/extra/widgets/chart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__NEWLIB__ -DCPU_MIMXRT1062DVL6B -DCPU_MIMXRT1062DVL6B_cm7 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DSKIP_SYSCLK_INIT -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DSD_ENABLED -DLV_CONF_INCLUDE_SIMPLE=1 -D__NXP_MSDK__ -DMCUXPRESSO_SDK -DSDK_I2C_BASED_COMPONENT_USED=1 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\source" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\video" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\drivers" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\utilities" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\component\gpio" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\sdmmc\inc" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\sdmmc\host" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\fatfs\source" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\fatfs\source\fsl_sd_disk" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\openh264\codec\decoder\core\inc" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\openh264\codec\decoder\plus\inc" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\device" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\component\uart" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\component\lists" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\xip" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\CMSIS" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\sdmmc\osa" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\component\osa" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\freertos\freertos-kernel\include" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\openh264\codec\api\svc" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\openh264\codec\common\inc" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\board" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\source\freertos_libraries\abstractions\posix\include" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\source\freertos_libraries\freertos_plus\standard\freertos_plus_posix\include" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\source\freertos_libraries\c_sdk\standard\common\include\private" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\touchpanel" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\lvgl\lvgl" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\lvgl\lvgl\src" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\lvgl" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\lvgl\lvgl\src\font" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\component\serial_manager" -I"C:\nxp\GUI-Guider-Projects\k1019\custom" -I"C:\nxp\GUI-Guider-Projects\k1019\generated" -I"C:\nxp\GUI-Guider-Projects\k1019\generated\guider_customer_fonts" -I"C:\nxp\GUI-Guider-Projects\k1019\generated\guider_fonts" -I"C:\nxp\GUI-Guider-Projects\k1019\sdk\Core\rlottie" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -Wno-format -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-chart

clean-lvgl-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-chart:
	-$(RM) ./lvgl/lvgl/src/extra/widgets/chart/lv_chart.d ./lvgl/lvgl/src/extra/widgets/chart/lv_chart.o

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-chart

