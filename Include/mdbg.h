#pragma once
#include "Defs/mdbgDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceDebugInit(int a1 = 1);
	int sceDebugStopChildProcesses(int pid);
	int sceDebugNoStopChildProcesses(int pid);
	int sceDebugStopOnDLLoad(int pid);
	int sceDebugNoStopOnDLLoad(int pid);
	int sceDebugKillProcess(int pid);
	int sceDebugAttachProcess(int pid);
	int sceDebugDetachProcess(int pid);
	int sceDebugSuspendProcess(int pid);
	int sceDebugResumeProcess(int pid, int a2 = 0);
	int sceDebugProcessSpawn(int context, void* argv, int flags, size_t stackSize, const char* workdir, const char* pathFile);
	int sceDebugGetProcessList(int* pidList, int pidListSize, int* pidCount);
	int sceDebugGetProcessInfo(int pid, SceDebugProcessInfo* processInfo);
	int sceDebugWriteProcessMemory(int pid, uint64_t address, size_t size, uint8_t* data, size_t* sizeWritten);
	int sceDebugReadProcessMemory(int pid, uint64_t addrss, size_t size, uint8_t* data, size_t* sizeRead);
	int sceDebugGetModuleList(int pid, SceDebugModuleId* moduleIdList, int moduleIdListSize, int* moduleIdCount);
	int sceDebugGetModuleInfo(int pid, SceDebugModuleId moduleId, SceDebugModuleInfo* moduleInfo);
	int sceDebugGetModuleMetaData(int pid, SceDebugModuleId moduleId, void* metaData, size_t metaDataSize, size_t** actualMetaData);
	int sceDebugCreateScratchExecutableAreaForPrx(int pid, size_t size, const char* name, uint64_t* addressOut);
	int sceDebugCreateScratchExecutableArea(int pid, size_t size, uint64_t* addressOut);
	int sceDebugDestroyScratchExecutableArea(int pid, uint64_t address, size_t size);
	int sceDebugGetVirtualMemoryInfo(int pid, uint64_t address, SceDebugVirtualQueryInfo* info);
	int sceDebugGetApplicationIdByTitleId(char titleId[10], int* appId);
	int sceDebugGetApplicationList(int* appIds, int maxAppIds, int* actualAppIds);
	int sceDebugGetApplicationInfo(int appId, SceDebugAppInfo* info);
	int sceDebugKillApplication(int context, int appid);
	int sceDebugSuspendApplication(int context, int appid);
	int sceDebugResumeApplication(int context, int appId);
	int sceDebugSpawnApplication(int context, char titleId[10], void* argv, int flags, int mountFlags);
	int sceDebugGetEventList(int pid, uint64_t sid, SceKernelEvent* dataPtr, uint64_t a4, size_t** actualEvents);

	int sceDebugWriteThreadRegister(int tid, SceDebugRegisterId reg, SceDebugRegister value);
	int sceDebugReadThreadRegister(int tid, SceDebugRegisterId reg, SceDebugRegister* value);

	int sceDebugClearStepThread(int tid);
	int sceDebugSetStepThread(int tid);
	int sceDebugResumeThread(int tid);
	int sceDebugSuspendThread(int tid);
	int sceDebugGetThreadList(int pid, int* tidList, int tidListSize, int* tidCount);
	int sceDebugGetThreadInfo(int pid, int tid, SceDebugThreadInfo* info);

#ifdef __cplusplus
}
#endif