#include "sd.h"

FATFS fs;
TCHAR *Path = "0:";
FRESULT status;

void sd_init()
{
	status = f_mount(&fs, Path, 0);
	if(status == FR_OK)
	{
		xil_printf("SD card init success\r\n");
	}
	else
	{
		xil_printf("SD card init fail\r\n");
	}
}

void sd_mount()
{
	BYTE work[FF_MAX_SS];
	f_mkfs("", FM_FAT32,0,work,sizeof work);
	status = f_mount(&fs, Path, 0);
	if(status == FR_OK)
	{
		xil_printf("SD card FM_FAT32 success\r\n");
	}
}

void sd_read_data(char *file_name, char rd_data[])
{
	FIL fil;
	UINT br;

	f_open(&fil, file_name, FA_READ);
	f_lseek(&fil,0);
	f_read(&fil,rd_data,LEN,&br);
}
