#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	struct SceDebugProcessInfo
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

	static_assert(sizeof(SceDebugProcessInfo) == 0x4A8, "SceDebugProcessInfo size is not correct");

#pragma pack(push, 8)
	struct SceDebugModuleInfo
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
	static_assert(sizeof(SceDebugModuleInfo) == 0xA50, "SceDebugModuleInfo size is not correct");

	struct SceDebugVirtualQueryInfo
	{
		void* Start;		// 0x00
		void* End;			// 0x08
		char _0x10[0x8];
		int Protection;		// 0x18
		char _0x1C[0x30 - 0x1C];
		char Name[32];		// 0x30
		int unk;			// 0x50
		int unk2;			// 0x54
	}; // Size = 0x58
	static_assert(sizeof(SceDebugVirtualQueryInfo) == 0x58, "SceDebugVirtualQueryInfo size is not correct");

	struct SceDebugThreadInfo
	{
		int ThreadId;			// 0x00
		int Type;				// 0x04 ?? Might be wrong.
		char _0x08[0x4];
		char Name[32];			// 0x0C
		char _0x2C[0x38 - 0x2C];
		uint64_t StackAddress;	// 0x38
		size_t StackSize;		// 0x40
		char _0x48[0x4];
		short PriorityLevel;	// 0x4C
		short PriorityClass;	// 0x4E
		short NativePriority;	// 0x50
		short UserPriority;		// 0x52
		int AffinityMask;		// 0x54
		char _0x58[0x4];
		int SchedPolicy;		// 0x5C
		int Flags;				// 0x60
		char _0x64[0x188 - 0x64];
	}; // Size = 0x188
	static_assert(sizeof(SceDebugThreadInfo) == 0x188, "SceDebugThreadInfo size is not correct");

	enum SceDebugRegisterId
	{
		SCE_DBGP_REG_ID_RAX = 0x10000,
		SCE_DBGP_REG_ID_RCX,
		SCE_DBGP_REG_ID_RDX,
		SCE_DBGP_REG_ID_RBX,
		SCE_DBGP_REG_ID_RSP,
		SCE_DBGP_REG_ID_RBP,
		SCE_DBGP_REG_ID_RSI,
		SCE_DBGP_REG_ID_RDI,
		SCE_DBGP_REG_ID_R8,
		SCE_DBGP_REG_ID_R9,
		SCE_DBGP_REG_ID_R10,
		SCE_DBGP_REG_ID_R11,
		SCE_DBGP_REG_ID_R12,
		SCE_DBGP_REG_ID_R13,
		SCE_DBGP_REG_ID_R14,
		SCE_DBGP_REG_ID_R15,
		SCE_DBGP_REG_ID_RIP = 0x10012,
		SCE_DBGP_REG_ID_RFLAGS = 0x10015,
		SCE_DBGP_REG_ID_cw = 0x20000,
		SCE_DBGP_REG_ID_sw,
		SCE_DBGP_REG_ID_tw,
		SCE_DBGP_REG_ID_opcode = 0x20004,
		SCE_DBGP_REG_ID_FPURIP,
		SCE_DBGP_REG_ID_FPURDP,
		SCE_DBGP_REG_ID_mxcsr,
		SCE_DBGP_REG_ID_mxcsr_mask,
		SCE_DBGP_REG_ID_acc0 = 0x30000,
		SCE_DBGP_REG_ID_acc1,
		SCE_DBGP_REG_ID_acc2,
		SCE_DBGP_REG_ID_acc3,
		SCE_DBGP_REG_ID_acc4, 
		SCE_DBGP_REG_ID_acc5,
		SCE_DBGP_REG_ID_acc6,
		SCE_DBGP_REG_ID_acc7,
		SCE_DBGP_REG_ID_ymm0 = 0x40000,
		SCE_DBGP_REG_ID_ymm1,
		SCE_DBGP_REG_ID_ymm2,
		SCE_DBGP_REG_ID_ymm3,
		SCE_DBGP_REG_ID_ymm4,
		SCE_DBGP_REG_ID_ymm5,
		SCE_DBGP_REG_ID_ymm6,
		SCE_DBGP_REG_ID_ymm7,
		SCE_DBGP_REG_ID_ymm8,
		SCE_DBGP_REG_ID_ymm9,
		SCE_DBGP_REG_ID_ymm10,
		SCE_DBGP_REG_ID_ymm11,
		SCE_DBGP_REG_ID_ymm12,
		SCE_DBGP_REG_ID_ymm13,
		SCE_DBGP_REG_ID_ymm14,
		SCE_DBGP_REG_ID_ymm15,
		SCE_DBGP_REG_ID_DR0 = 0x50000,
		SCE_DBGP_REG_ID_DR1,
		SCE_DBGP_REG_ID_DR2,
		SCE_DBGP_REG_ID_DR3,
		SCE_DBGP_REG_ID_DR4,
		SCE_DBGP_REG_ID_DR5,
		SCE_DBGP_REG_ID_DR6,
		SCE_DBGP_REG_ID_DR7,
		SCE_DBGP_REG_ID_FSBASE = 0x60000,
	};

	typedef uint64_t SceDebugModuleId;
	struct SceDebugRegister
	{
		uint64_t data[4];
	};
	
	int sceDebugInit(int a1 = 1);
	int sceDebugStopChildProcesses(int pid);
	int sceDebugNoStopChildProcesses(int pid);
	int sceDebugStopOnDLLoad(int pid);
	int sceDebugNoStopOnDLLoad(int pid);
	int sceDebugAttachProcess(int pid);
	int sceDebugDetachProcess(int pid);
	int sceDebugSuspendProcess(int pid);
	int sceDebugResumeProcess(int pid, int a2 = 0);
	int sceDebugGetProcessList(int* pidList, int pidListSize, int* pidCount);
	int sceDebugGetProcessInfo(int pid, SceDebugProcessInfo* processInfo);
	int sceDebugWriteProcessMemory(int pid, uint64_t address, size_t size, uint8_t* data, size_t* sizeWritten);
	int sceDebugReadProcessMemory(int pid, uint64_t addrss, size_t size, uint8_t* data, size_t* sizeRead);
	int sceDebugGetModuleList(int pid, SceDebugModuleId* moduleIdList, int moduleIdListSize, int* moduleIdCount);
	int sceDebugGetModuleInfo(int pid, SceDebugModuleId moduleId, SceDebugModuleInfo* moduleInfo);
	int sceDebugCreateScratchExecutableAreaForPrx(int pid, size_t size, const char* name, uint64_t* addressOut);
	int sceDebugCreateScratchExecutableArea(int pid, size_t size, uint64_t* addressOut);
	int sceDebugDestroyScratchExecutableArea(int pid, uint64_t address, size_t size);
	int sceDebugGetVirtualMemoryInfo(int pid, uint64_t address, SceDebugVirtualQueryInfo* info);

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