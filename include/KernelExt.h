#pragma once 

#include "Defs/KernelExtDefs.h"
#include "Defs/PtraceDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceKernelSendNotificationRequest(int device, SceNotificationRequest* req, size_t size, int blocking);
	int sceKernelGetAppInfo(int pid, SceAppInfo* info);
	int sceKernelSetAppInfo(int pid, SceAppInfo* info);
	int sceKernelSetProcessName(const char* name);
	int sceKernelGetThreadName(uint32_t tid, char* out);
	int sceKernelDebugOutText(int dbg_channel, const char* text, ...);
	int sceKernelGetProcessName(int pid, char* out);
	int sysKernelGetUpdVersion(int* vers);
	int sceKernelGetCompiledSdkVersion(int* vers);
	int sceKernelGetModuleList(int* arr, size_t size, size_t* available);
	int sceKernelGetModuleInfo(int handle, SceKernelModuleInfo* info);
	int sceKernelGetPageTableStats(int* cpuTotal, int* cpuAvailable, int* gpuTotal, int* gpuAvailable);
	void sceKernelIccIndicatorBootDone();
	void sceKernelIccIndicatorShutdown();
	void sceKernelIccIndicatorStandby();
	void sceKernelIccIndicatorStandbyBoot();
	void sceKernelIccIndicatorStandbyShutdown();
	void sceKernelIccSetBuzzer(enum BuzzerType mode);
	int sceKernelGetCpuTemperature(int* Temperature);
	int sceKernelGetSocSensorTemperature(int, int* Temperature);
	const char* sceKernelGetFsSandboxRandomWord();
	int sceKernelGetSystemSwVersion(SceKernelSwVersion* version);

	int get_page_table_stats(int vm, unsigned long long Table, int* totalOut, int* AvailableOut);
	int sysctlbyname(const char* name, void* oldp, size_t* oldlenp, const void* newp, size_t newlen);
	int sysctl(int* name, unsigned int namelen, void* oldp, size_t* oldlenp, void* newp, size_t newlen);
	int ptrace(int request, int pid, void* addr, int data);
	int wait4(int wpid, int* status, int options, struct rusage* rusage);
	int waitpid(int wpid, int* status, int options);
	int ioctl(int fd, unsigned long request, ...);
	int getpid(void);
	int sceDbgInstallExceptionHandler(int en, SceDbgExceptionHandler handler);
	int sceDbgRemoveExceptionHandler(int en);
	int sigaction(int, struct sigaction*, struct sigaction*);
	int sigemptyset(sigset_t* set);

	// thread
	int pthread_suspend_user_context_np(thread* thr);
	int pthread_resume_user_context_np(thread* thr);
	int pthread_get_user_context_np(thread* thr, SceDbgUcontext* context);
	int pthread_set_user_context_np(thread* thr, SceDbgUcontext* context);
	int pthread_suspend_np(thread* thr);
	int pthread_resume_np(thread* thr);
	int pthread_suspend_all_np();
	int pthread_resume_all_np();

	int scePthreadSuspend(thread* thr);
	int scePthreadResume(thread* thr);
	int scePthreadSuspendAll();
	int scePthreadResumeAll();

#ifdef __cplusplus
}
#endif
