
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "EasyAVFilterAPI.h"

#ifdef _WIN32
#pragma comment(lib,"EasyAVFilter.lib")
#endif

Easy_Handle fRTSPHandle = 0;			
int Easy_APICALL __AVFilterCallBack(void* userPtr, EASY_AV_FILTER_STATE_T status, int progress, int errCode, const char *errMsg)
{
	//取流状态
	if (status == EASY_AVFILTER_STATE_PULL_CONNECTING)/* 拉流连接中 */
	{
		printf("EASY_AVFILTER_STATE_PULL_CONNECTING\n");
	}
	else if (status == EASY_AVFILTER_STATE_PULL_CONNECTED)/* 拉流连接成功 */
	{
		printf("EASY_AVFILTER_STATE_PULL_CONNECTED\n");
	}
	else if (status == EASY_AVFILTER_STATE_PULL_CONNECT_FAILED)/* 拉流连接失败 */
	{
		printf("EASY_AVFILTER_STATE_PULL_CONNECT_FAILED\n");
	}
	else if (status == EASY_AVFILTER_STATE_PULL_CONNECT_ABORT)/* 拉流连接中断 */
	{
		printf("EASY_AVFILTER_STATE_PULL_CONNECT_ABORT\n");
	}
	else if (status == EASY_AVFILTER_STATE_PULL_DISCONNECTED)/* 拉流断开连接 */
	{
		printf("EASY_AVFILTER_STATE_PULL_DISCONNECTED\n");
	}
	else if (status == EASY_AVFILTER_STATE_PULL_SOURCE_MEDIA_INFO)/*输入的媒体信息*/
	{
		if(errMsg != NULL)
		{
			printf("EASY_AVFILTER_STATE_PULL_SOURCE_MEDIA_INFO:%s", errMsg);
		}
	}
	//推流状态
	else if(status == EASY_AVFILTER_STATE_PUSH_CONNECTING)/* 推流连接中 */
	{
		printf("EASY_AVFILTER_STATE_PUSH_CONNECTING\n");
	}
	else if(status == EASY_AVFILTER_STATE_PUSH_CONNECTED)/* 推流连接成功 */
	{
		printf("EASY_AVFILTER_STATE_PUSH_CONNECTED\n");
	}
	else if(status == EASY_AVFILTER_STATE_PUSH_CONNECT_FAILED)/* 推流连接失败 */
	{
		printf("EASY_AVFILTER_STATE_PUSH_CONNECT_FAILED\n");
	}
	else if(status == EASY_AVFILTER_STATE_PUSH_CONNECT_ABORT)/* 推流连接中断 */
	{
		printf("EASY_AVFILTER_STATE_PUSH_CONNECT_ABORT\n");
	}
	else if(status == EASY_AVFILTER_STATE_PUSHING)/* 推流中 */
	{
		printf("EASY_AVFILTER_STATE_PUSHING\n");
	}
	else if(status == EASY_AVFILTER_STATE_PUSH_DISCONNECTED)/* 推流断开连接 */
	{
		printf("EASY_AVFILTER_STATE_PUSH_DISCONNECTED\n");
	}
	//转码状态
	else if(status == EASY_AVFILTER_STATE_PROCESSING)/* 处理中*/
	{
		printf("EASY_AVFILTER_STATE_PROCESSING：%d……\n", progress);
	}
	//过程结束
	else if(status == EASY_AVFILTER_STATE_EXIT)/* 退出连接 */
	{
		printf("EASY_AVFILTER_STATE_EXIT\n");
	}

	return 0;
}

int main(int argc, char** argv)
{
	Easy_Handle avFilterHandle = NULL;

	EasyAVFilter_Create(&avFilterHandle);

	EasyAVFilter_SetCallback(avFilterHandle,__AVFilterCallBack,0);
#if 1
	// 用法1
	// 将网络流录制成本地MP4或者HLS录像,参考命令：./ffmpeg.exe -re -rtsp_transport tcp -i rtsp://admin:admin12345@124.112.228.212:554/ch1/main/av_stream -c:v copy -c:a aac -f segment -segment_list ./20230829150000.m3u8 -segment_time 300 -strftime 1 rec_%Y-%m-%d_%H-%M-%S.ts
	EasyAVFilter_AddInput(avFilterHandle, "rtsp://admin:admin12345@124.112.228.212:554/ch1/main/av_stream", 1);
	EasyAVFilter_AddFilter(avFilterHandle, "-vcodec copy -acodec aac");
	EasyAVFilter_AddFilter(avFilterHandle, "-f segment -segment_time 8 -reset_timestamps 1 -strftime 1");
	//EasyAVFilter_AddFilter(avFilterHandle, "-segment_list C://temp/20230829150000.m3u8");//是否需要列表文件，可要可不要
	EasyAVFilter_SetOutput(avFilterHandle, "C://temp/output_%Y-%m-%d_%H-%M-%S.mp4", 0);

	//// 将本地视频文件转成格式化的MP4或者HLS提供点播，参考命令：./ffmpeg.exe -fflags +genpts -hide_banner -vcodec copy -acodec aac -ac 2 -strict -2 -f hls -hls_time 16 -hls_list_size 0 C://temp/La_Isla_Bonita.m3u8
	//EasyAVFilter_AddInput(avFilterHandle, "C://temp/La_Isla_Bonita.avi", 1);
	//EasyAVFilter_AddFilter(avFilterHandle, "-fflags +genpts -hide_banner -vcodec copy -acodec aac -ac 2 -strict -2");
	//EasyAVFilter_AddFilter(avFilterHandle, "-f hls -hls_time 16 -hls_list_size 0");
	//EasyAVFilter_SetOutput(avFilterHandle, "C://temp/La_Isla_Bonita.m3u8", 0);

	//// 将本地视频文件转成格式化的MP4或者HLS提供点播，参考命令：./ffmpeg.exe -re -rtsp_transport tcp -i rtsp://admin:admin12345@124.112.228.212:554/ch1/main/av_stream -vcodec copy -acodec aac -ac 2 -strict -2 -f flv rtmp://172.81.216.155:3519/live/IbMkUXeVR?sign=SxMk8X6VRz
	//EasyAVFilter_AddInput(avFilterHandle, "rtsp://admin:admin12345@124.112.228.212:554/ch1/main/av_stream", 1);
	//EasyAVFilter_AddFilter(avFilterHandle, "-vcodec copy -acodec aac -ac 2 -strict -2");
	//EasyAVFilter_AddFilter(avFilterHandle, "-f flv");
	//EasyAVFilter_SetOutput(avFilterHandle, "rtmp://172.81.216.155:3519/live/IbMkUXeVR?sign=SxMk8X6VRz", 0);

#else
	// 用法2
	const char* command = "-rtsp_transport tcp -i rtsp://admin:admin12345@124.112.228.212:554/ch1/main/av_stream -vcodec copy -acodec copy -f flv rtmp://192.168.1.200:1935/live/ch1";
	//char command[512] = { 0 };
	//char* pCommand = (char*)command;
	//for (int i = 1; i < argc; i++)
	//{
	//	pCommand += sprintf(pCommand, " %s", argv[i]);
	//}

	EasyAVFilter_AddFilter(avFilterHandle, command);
#endif

	char filterCommand[256] = { 0 };
	EasyAVFilter_GetFilters(avFilterHandle, filterCommand);
	printf("command: %s\n", filterCommand);

	getchar();
	EasyAVFilter_Start(avFilterHandle, 0, 8, 10);//注意，文件转码不需要循环读取，第二个参数从1改成0

	getchar();
	EasyAVFilter_Stop(avFilterHandle);

	getchar();
	EasyAVFilter_Release(&avFilterHandle);

	return 0;
}