
#ifdef _WIN32
#include <winsock2.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EasyAVFilterAPI.h"


int Easy_APICALL __EasyAVFilterCallBack(void* userPtr, EASY_AV_FILTER_STATE_T status, int progress, int errCode, const char *errMsg)
{
    
    printf("__EasyAVFilterCallBack status: %d  errCode:%d  errMsg:%s\n", __EasyAVFilterCallBack, errCode,  errMsg);
    
    return 0;
}


int main(int argc, char** argv)
{
    printf("main...\n");
    
	Easy_Handle avFilterHandle = NULL;

	EasyAVFilter_Create(&avFilterHandle);
        EasyAVFilter_SetCallback(avFilterHandle, __EasyAVFilterCallBack, avFilterHandle);
#if 0
	// 用法1
	EasyAVFilter_AddInput(avFilterHandle[i], "rtsp://admin:12345@192.168.1.100", 1);
	EasyAVFilter_AddFilter(avFilterHandle[i], "-vcodec copy -acodec aac");
	EasyAVFilter_SetOutput(avFilterHandle[i], "rtmp://192.168.1.200:1935/live/ch1", 0);
#else
	// 用法2
	//const char* pCommand = "-rtsp_transport tcp -i rtsp://admin:12345@192.168.1.100 -vcodec copy -acodec copy -f flv rtmp://192.168.1.200:1935/live/ch1";
	char command[512] = { 0 };
	char* pCommand = (char*)command;
	for (int i = 1; i < argc; i++)
	{
		pCommand += sprintf(pCommand, " %s", argv[i]);
	}

	EasyAVFilter_AddFilter(avFilterHandle, command);
#endif

	char filterCommand[256] = { 0 };
	EasyAVFilter_GetFilters(avFilterHandle, filterCommand);
	printf("command: %s\n", filterCommand);

	EasyAVFilter_Start(avFilterHandle, 1, 30, 20);

        printf("Press Enter key to exit...\n");
	getchar();

	EasyAVFilter_Stop(avFilterHandle);

	EasyAVFilter_Release(&avFilterHandle);
        
        
        
        return 0;
}

