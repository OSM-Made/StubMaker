#pragma once 

#include "Defs/KernelExtDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceApplicationInitialize();

	void _sceApplicationGetAppId(int Pid, int* AppId);
	void sceApplicationContinue(int appId);
	bool sceApplicationIsResumable(int appId);
	int sceApplicationResume(int appId);
	int sceApplicationSuspend(int AppId);
	int sceApplicationGetAppInfoByAppId(int appId, SceAppInfo* info);
	int sceApplicationSetApplicationFocus(int AppId);

	void sceApplicationSystemReboot();

#ifdef __cplusplus
}
#endif