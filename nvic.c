#include "nvic.h"

void Gic_Init(void)
{
    XScuGic_Config *GicCfgPtr;
    int status;

    // 1. 初始化ARM异常向量
    Xil_ExceptionInit();

    // 2. 查找GIC配置
    GicCfgPtr = XScuGic_LookupConfig(GIC_DEV_ID);
    if(GicCfgPtr == NULL)
    {
        xil_printf("Gic LookupConfig NULL!\r\n");
        return;
    }

    // 3. 初始化GIC驱动
    status = XScuGic_CfgInitialize(&GicInst, GicCfgPtr, GicCfgPtr->CpuBaseAddress);
    if(status != XST_SUCCESS)
    {
        xil_printf("GIC CfgInitialize Failed\r\n");
        return;
    }
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 &GicInst);

    // 打开CPU全局IRQ总开关
    Xil_ExceptionEnable();
    xil_printf("GIC Init OK\r\n");
}

/*
 * IntrId：中断号（SPI/PPI编号，如XPAR_UART0_INTR、PL中断61）
 * Priority：优先级 0~0xFF，数值越小优先级越高，A9只用高4bit
 * Trigger：触发类型 0=高电平 3=上升沿
 * Handler：中断回调函数
 * 返回：XST_SUCCESS / XST_FAILURE
 */
int Gic_IntConfig(u32 IntrId, u8 Priority, u8 Trigger, Xil_InterruptHandler Handler)
{
    int status;
    XScuGic_SetPriorityTriggerType(&GicInst, IntrId, Priority, Trigger);

    status = XScuGic_Connect(&GicInst, IntrId, Handler, &GicInst);
    if(status != XST_SUCCESS)
    {
        xil_printf("Gic Connect Id:%d failed\r\n", IntrId);
        return XST_FAILURE;
    }
    xil_printf("%d IntConfig success\r\n", IntrId);
    XScuGic_Enable(&GicInst, IntrId);
    return XST_SUCCESS;
}

