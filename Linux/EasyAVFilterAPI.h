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


/* �¼����Ͷ��� */
typedef enum __EASY_AVFILTER_STATE_T
{
	EASY_AVFILTER_STATE_PULL_CONNECTING = 1,    /* ���������� */
	EASY_AVFILTER_STATE_PULL_CONNECTED,         /* �������ӳɹ� */
	EASY_AVFILTER_STATE_PULL_CONNECT_FAILED,    /* ��������ʧ�� */
	EASY_AVFILTER_STATE_PULL_CONNECT_ABORT,     /* ���������ж� */
	EASY_AVFILTER_STATE_PULL_DISCONNECTED,      /* �����Ͽ����� */
	EASY_AVFILTER_STATE_PULL_SOURCE_MEDIA_INFO,	/*�����ý����Ϣ*/

	EASY_AVFILTER_STATE_PUSH_CONNECTING = 10,    /* ���������� */
	EASY_AVFILTER_STATE_PUSH_CONNECTED,         /* �������ӳɹ� */
	EASY_AVFILTER_STATE_PUSH_CONNECT_FAILED,    /* ��������ʧ�� */
	EASY_AVFILTER_STATE_PUSH_CONNECT_ABORT,     /* ���������ж� */
	EASY_AVFILTER_STATE_PUSHING,                /* ������ */
	EASY_AVFILTER_STATE_PUSH_DISCONNECTED,      /* �����Ͽ����� */

	EASY_AVFILTER_STATE_EXIT,					/* �˳����� */
	EASY_AVFILTER_STATE_PROCESSING,				/* ������*/
	

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

	Easy_API int Easy_APICALL EasyAVFilter_AddFilter(Easy_Handle handle, const char *filterCommand/*����м����,�����ˮӡ*/);

	Easy_API int Easy_APICALL EasyAVFilter_GetFilters(Easy_Handle handle, char* outFilterCommand);

	Easy_API int Easy_APICALL EasyAVFilter_SetOutput(Easy_Handle handle, const char *outputUrl, int transCodeType/*0:�Զ�   1:ǿ��ת��ΪH264*/);

	Easy_API int Easy_APICALL EasyAVFilter_Start(Easy_Handle handle, int loop/* 1:ѭ��ִ��  0:ִ�й����������쳣��ִ���������ֹ*/, int connectTimeoutSecs/*���ӳ�ʱʱ��(��)*/, int readTimeoutSecs/*��ȡ���ݳ�ʱʱ��(��)*/);
	Easy_API int Easy_APICALL EasyAVFilter_Stop(Easy_Handle handle);

	Easy_API int Easy_APICALL EasyAVFilter_Release(Easy_Handle* handle);


#ifdef __cplusplus
};
#endif


#endif
