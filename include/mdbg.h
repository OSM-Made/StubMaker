#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	
	int sceDebugInit(int a1 = 1);
	int sceDebugAttachProcess(int pid);
	int sceDebugDetachProcess(int pid);
	int sceDebugResumeProcess(int pid, int a2 = 0);


#ifdef __cplusplus
}
#endif