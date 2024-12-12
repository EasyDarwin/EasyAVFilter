#ifndef __FF_STREAM_CLIENT_H__
#define __FF_STREAM_CLIENT_H__



#ifdef _WIN32
#define Easy_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#define WIN32_LEAN_AND_MEAN
#else
#define Easy_API
#define Easy_APICALL 
#endif


/* 事件类型定义 */
typedef enum __EASY_AVFILTER_STATE_T
{
	EASY_AVFILTER_STATE_PULL_CONNECTING = 1,    /* 拉流连接中 */
	EASY_AVFILTER_STATE_PULL_CONNECTED,         /* 拉流连接成功 */
	EASY_AVFILTER_STATE_PULL_CONNECT_FAILED,    /* 拉流连接失败 */
	EASY_AVFILTER_STATE_PULL_CONNECT_ABORT,     /* 拉流连接中断 */
	EASY_AVFILTER_STATE_PULL_DISCONNECTED,      /* 拉流断开连接 */
	EASY_AVFILTER_STATE_PULL_SOURCE_MEDIA_INFO,	/*输入的媒体信息*/

	EASY_AVFILTER_STATE_PUSH_CONNECTING = 10,    /* 推流连接中 */
	EASY_AVFILTER_STATE_PUSH_CONNECTED,         /* 推流连接成功 */
	EASY_AVFILTER_STATE_PUSH_CONNECT_FAILED,    /* 推流连接失败 */
	EASY_AVFILTER_STATE_PUSH_CONNECT_ABORT,     /* 推流连接中断 */
	EASY_AVFILTER_STATE_PUSHING,                /* 推流中 */
	EASY_AVFILTER_STATE_PUSH_DISCONNECTED,      /* 推流断开连接 */

	EASY_AVFILTER_STATE_EXIT,					/* 退出连接 */
	EASY_AVFILTER_STATE_PROCESSING,				/* 处理中*/
	

	EASY_AVFILTER_STATE_ERROR
} EASY_AV_FILTER_STATE_T;

typedef struct __EASY_AVFILTER_MEDIA_INFO_T
{
	int		duration;
	char	videoCodec[16];
	int		videoWidth;
	int		videoHeight;
	char	pixFmt[16];
	int		rotate;

	char	audioCodec[16];
	int		audioSamplerate;
	int		audioChannels;
}EASY_AVFILTER_MEDIA_INFO_T;

typedef int (Easy_APICALL* EasyAVFilterCallBack)(void* userPtr, EASY_AV_FILTER_STATE_T status, int progress, int errCode, const char *errMsg);

#define Easy_Handle void*

#ifdef __cplusplus
extern "C"
{
#endif

	Easy_API int Easy_APICALL EasyAVFilter_Create(Easy_Handle* handle);

	Easy_API int Easy_APICALL EasyAVFilter_SetCallback(Easy_Handle handle, EasyAVFilterCallBack callback, void* userPtr);

	Easy_API int Easy_APICALL EasyAVFilter_AddInput(Easy_Handle handle, const char *inputUrl, int connectType/*1:tcp other:udp*/);

	Easy_API int Easy_APICALL EasyAVFilter_AddFilter(Easy_Handle handle, const char *filterCommand/*添加中间参数,如叠加水印*/);

	Easy_API int Easy_APICALL EasyAVFilter_GetFilters(Easy_Handle handle, char* outFilterCommand);

	Easy_API int Easy_APICALL EasyAVFilter_SetOutput(Easy_Handle handle, const char *outputUrl, int transCodeType/*0:自动   1:强制转换为H264*/);

	Easy_API int Easy_APICALL EasyAVFilter_Start(Easy_Handle handle, int loop/* 1:循环执行  0:执行过程中如有异常或执行完成则终止*/, int connectTimeoutSecs/*连接超时时长(秒)*/, int readTimeoutSecs/*读取数据超时时长(秒)*/);
	Easy_API int Easy_APICALL EasyAVFilter_Stop(Easy_Handle handle);

	Easy_API int Easy_APICALL EasyAVFilter_Release(Easy_Handle* handle);


#ifdef __cplusplus
};
#endif


#endif
