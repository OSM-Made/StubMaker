#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	struct DebugProcessInfo
	{
		int pid;					// 0x00
		uint64_t unk;				// 0x04
		int flags;					// 0x10
		char Name[32];				// 0x14
		char _0x34[0x80 - 0x34];
		char ExecutablePath[1024];	// 0x80
		char _0x480[0x8];
		int AppId;					// 0x488
		char _0x48C[0x4A8 - 0x48C];
	}; // Size = 0x4A8

	static_assert(sizeof(DebugProcessInfo) == 0x4A8, "DebugProcessInfo size is not correct");

#pragma pack(push, 8)
	struct DebugModuleInfo
	{
		char Name[128];					// 0x00
		uint64_t ModuleId;				// 0x80
		char _0x88[0x8];
		int SdkVersion;					// 0x90
		int SomeFlagThing;				// 0x94
		int RefCount;					// 0x98
		char _0x9C[0x4];
		int status;						// 0xA0
		char _0xA4[0x4];
		uint64_t init;					// 0xA8
		uint64_t fini;					// 0xB0
		uint64_t EHFrameHDR;			// 0xB8
		uint64_t EHFrameHDRSize;		// 0xC0
		uint64_t EHFrame;				// 0xC8
		uint64_t EHFrameSize;			// 0xD0
		uint64_t MapBase;				// 0xD8
		size_t TextSize;				// 0xE0
		char _0xE8[0x8];
		uint64_t DataBase;				// 0xF0
		size_t DataSize;				// 0xF8
		char _0x100[0xA0];
		uint64_t RequiredModules[128];	// 0x1A0
		uint64_t RequiredModuleCount;	// 0x5A0
		char _0x5A8[0x8];
		char FingerPrint[20];			// 0x5B0
		char _0x5C4[0x4];
		char OriginalName[128];			// 0x5C8
		int TlsIndex;					// 0x648
		char Path[1024];				// 0x64C
	}; // Size = 0xA50
#pragma pack(pop)
	static_assert(sizeof(DebugModuleInfo) == 0xA50, "DebugModuleInfo size is not correct");
	
	int sceDebugInit(int a1 = 1);
	int sceDebugAttachProcess(int pid);
	int sceDebugDetachProcess(int pid);
	int sceDebugResumeProcess(int pid, int a2 = 0);
	int sceDebugGetProcessList(int* pidList, int pidListSize, int* pidCount);
	int sceDebugGetProcessInfo(int pid, DebugProcessInfo* processInfo);

	int sceDebugGetModuleList(int pid, uint64_t* moduleIdList, int moduleIdListSize, int* moduleIdCount);
	int sceDebugGetModuleInfo(int pid, uint64_t moduleId, DebugModuleInfo* moduleInfo);

#ifdef __cplusplus
}
#endif