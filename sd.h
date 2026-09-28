#include "xil_printf.h"
#include "stdio.h"
#include "xparameters.h"
#include "ff.h"

//读写文件名字，使用前需要更改
#define FILE_NAME "rd.txt"
//读取数据长度，使用前需更改
#define LEN 12

void sd_init();

//格式化sd卡，init失败时使用,格式为FM_FAT32
void sd_mount();
//读数据
void sd_read_data(char *file_name, char rd_data[]);
