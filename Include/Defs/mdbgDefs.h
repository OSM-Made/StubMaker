#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	struct ExceptionHandlingFrame
	{
		uint64_t HeaderAddress;	// 0x00
		size_t HeaderSize;		// 0x08
		uint64_t FrameAddress;	// 0x10
		size_t FrameSize;		// 0x18
	}; // Size = 0x20

	struct SceDebugProcessInfo
	{
		int pid;						// 0x00
		char _0x04[0xC];
		int Attribute;					// 0x10
		char Name[32];					// 0x14
		char _0x34[0x4];
		uint64_t EntryPoint;			// 0x38
		char FingerPrint[20];			// 0x40
		int ppid;						// 0x54
		uint32_t MainThreadId;			// 0x58
		char _0x58[0x4];
		ExceptionHandlingFrame EHFrame;	// 0x60
		char ExecutablePath[1024];		// 0x80
		int AffinityMask;				// 0x480
		char _0x484[0x4];
		int AppId;						// 0x488
		char _0x48C[0x4A8 - 0x48C];
	}; // Size = 0x4A8

	static_assert(sizeof(SceDebugProcessInfo) == 0x4A8, "SceDebugProcessInfo size is not correct");

	typedef enum SceDebugModuleSegmentInfoProtection 
	{
		SCE_DEBUG_PROT_CPU_READ = 0x01,
		SCE_DEBUG_PROT_CPU_RW = 0x02,
		SCE_DEBUG_PROT_CPU_EXEC = 0x04
	} SceDbgModuleSegmentInfoProtection;

	typedef enum SceDebugModuleStatus
	{
		MODULE_STATUS_LOADED = 1,
		MODULE_STATUS_STARTING = 2,
		MODULE_STATUS_LIVE = 4,
		MODULE_STATUS_STOPPING = 8,
		MODULE_STATUS_STOPPED = 16
	} SceDebugModuleStatus;

	typedef enum SceDebugModuleType
	{
		MODULE_TYPE_FIXED_ELF,
		MODULE_TYPE_DYNLIB
	} SceDebugModuleType;

	typedef enum SceDebugModuleFlags
	{
		MODULE_FLAGS_ORIGIN = 1,
		MODULE_FLAGS_SYMBOLIC = 2,
		MODULE_FLAGS_TEXT_REL = 4,
		MODULE_FLAGS_BIND_NOW = 8,
		MODULE_FLAGS_STATIC_TLS = 16
	} SceDebugModuleFlags;

	struct SceDebugModuleSegmentInfo
	{
		uint64_t StartAddress;							// 0x00
		size_t Size;									// 0x08
		SceDbgModuleSegmentInfoProtection Attributes;	// 0x10
	};	// Size = 0x18
	static_assert(sizeof(SceDebugModuleSegmentInfo) == 0x18, "SceDebugModuleInfo size is not correct");

#pragma pack(push, 8)
	struct SceDebugModuleInfo
	{
		char Name[128];							// 0x00
		uint64_t ModuleId;						// 0x80
		SceDebugModuleFlags Flags;				// 0x88
		char _0x8C[0x4];
		int SdkVersion;							// 0x90
		SceDebugModuleType Type;				// 0x94
		int ReferenceCount;						// 0x98
		char _0x9C[0x4];
		SceDebugModuleStatus Status;			// 0xA0
		char _0xA4[0x4];
		uint64_t StartFunction;					// 0xA8
		uint64_t StopFunction;					// 0xB0
		uint64_t EHFrameHDR;					// 0xB8
		uint64_t EHFrameHDRSize;				// 0xC0
		uint64_t EHFrame;						// 0xC8
		uint64_t EHFrameSize;					// 0xD0
		SceDebugModuleSegmentInfo Segments[8];	// 0xD8
		int SegmentCount;						// 0x198
		char _0x19C[0x4];
		uint64_t RequiredModules[128];			// 0x1A0
		uint64_t RequiredModuleCount;			// 0x5A0
		int Version;							// 0x5A8 - In big endian.
		char _0x5A8[0x4];
		char FingerPrint[20];					// 0x5B0
		char _0x5C4[0x4];
		char OriginalFile[128];					// 0x5C8
		int HasLoadPath;						// 0x648 - ? Not 100% sure since its zero when LoadPath is null. 
		char LoadPath[1024];					// 0x64C
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

	struct SceDebugAppInfo
	{
		int Size;				// 0x00 - Size of this struct (Always 0xE4).
		int AppId;				// 0x04
		int AppType;			// 0x08
		char TitleId[12];		// 0x0C
		char ProcessName[128];	// 0x18
		int Unk1;				// 0x98
		int Unk2;				// 0x9C
		char _0xA0[0x44];
	}; // Size = 0xE4
	static_assert(sizeof(SceDebugAppInfo) == 0xE4, "SceDebugAppInfo size is not correct");

#ifdef __cplusplus
}
#endif
