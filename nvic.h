#ifndef NVIC_H
#define NVIC_H

#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

static XScuGic GicInst;    // GIC实例

#define GIC_DEV_ID XPAR_SCUGIC_SINGLE_DEVICE_ID  //GIC设备名，根据自己程序更改

void Gic_Init(void);

int Gic_IntConfig(u32 IntrId, u8 Priority, u8 Trigger, Xil_InterruptHandler Handler);

#endif
