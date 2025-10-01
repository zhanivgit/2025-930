# Project Instructions for Copilot

## 1. 核心技术栈 (Core Technologies)

这是一个基于 **STM32F1xx 微控制器**的固件项目。
* **语言:** C 语言 (C99/C11 标准)。
* **库:** 使用 **STM32 HAL 库**进行硬件抽象和操作。
* **操作系统:** 使用 **FreeRTOS** 进行任务调度和并发管理。

## 2. 架构与编码规范 (Architecture and Conventions)

* **任务管理:** 所有主要的应用程序逻辑必须定义在 **FreeRTOS 任务（Task）**中。
    * 任务应使用 `osDelay()` 或其他 FreeRTOS 同步机制来避免忙等待。
    * 任务创建示例：`xTaskCreate(StartDefaultTask, "Default", 128, NULL, 1, NULL);`
* **硬件操作:** 禁止直接访问硬件寄存器。所有 IO 和外设操作必须通过 **HAL 函数**完成（例如 `HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)`）。
* **驱动文件:** 自定义的驱动（例如 OLED, 传感器）位于 `Drivers/MCU/` 目录。函数命名遵循 `模块名_功能描述` 的格式（如 `OLED_ShowString`, `LED_Toggle`）。
* **中断处理:** 中断服务程序 (ISR) 位于 `stm32f1xx_it.c`。在 ISR 中，对 RTOS API 的调用必须使用 **FromISR 后缀**版本（如 `xSemaphoreGiveFromISR`）。

## 3. 工作流 (Workflow)

* **编译环境:** 使用 **Keil uVision (MDK-ARM)** 或 **STM32CubeIDE** 进行编译。
    * **Keil uVision 编译命令示例:** `UV4.exe -f <project_path>.uvprojx -j0 -t <target_name>`
* **部署:** 代码通过 **ST-Link** 烧录到目标板。

## 4. 关键文件参考 (Key Files Reference)

* `main.c`: 包含所有 HAL 初始化、时钟配置 (`SystemClock_Config`) 和 FreeRTOS 任务启动代码。
* `Core/Src/freertos.c`: 包含 RTOS 调度器相关的配置和钩子函数，以及 FreeRTOS 任务的定义。
* `Drivers/MCU/`: 包含自定义的硬件驱动文件，如 `OLED.c`, `Led.c`, `buzzer.c` 等。
* `FreeRTOSConfig.h`: FreeRTOS 的配置头文件。