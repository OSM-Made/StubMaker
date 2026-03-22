#pragma once
#include <stdint.h>
#include <kernel.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Enum Credits - OSM-Made
	enum SceNotificationRequestType
	{
		Message = 0,
		MessageMsgId = 1,
		MessageUserId = 2,
		MessageDeviceId = 3,
		MessageDeviceIdRelatedToUser = 4,
		MessageText = 5,
		MessageTextRelatedToUser = 6,
		MessageErrorCode = 7,
		MessageAppId = 8,
		MessageAppInfo = 9,
		MessageTitleRelatedToUser = 10,
		MessageParams = 11,
		MessageUserName = 12,
		MessageUserNameInfo = 13,
		MessageAddressing = 14,
		MessageAddressingDeviceId = 15,
		MessageAddressingUserName = 16,
		MessageAddressingUserId, = 17,

		DebugMessage = 100,
		TrcCheckMessage = 101,
		NpDebugMessage = 102,
		WebDebugMessage = 102,
		UNK_103 = 103,
	};

	enum SystemNotificationPriority
	{
		Default = 0,
		High = 1,
		Special = -1
	};

	enum SystemNotificationAttribute
	{
		ShowVideoPlayback = 1,
		ShowVR = 2,
		ShowKratos = 4,
		All = 7,
	};

	enum NotificationAPI
	{
		ToastPopup = 0,
		NotifyDatabase = 1,
	};

	// Struct Credits - OSM-Made
#pragma pack(push, 1)
	struct SceNotificationRequest
	{
		enum SceNotificationRequestType Type;   // 0x00
		uint32_t ReqId;            				// 0x04
		uint32_t Priority;						// 0x08
		uint32_t MsgId;            				// 0x0C
		uint32_t TargetId;						// 0x10
		uint32_t UserId;						// 0x14
		uint32_t DeviceId;						// 0x18
		uint32_t AddressingUserId;				// 0x1C
		uint32_t AppId;            				// 0x20
		uint32_t ErrorNumber;					// 0x24
		uint32_t Attribute;						// 0x28
		uint8_t  HasIcon;						// 0x2C
		union
		{
			struct
			{
				char Message[0x400];			// 0x2D
				char IconImageUri[0x800];		// 0x42D
			};

			struct
			{
				char arg1[180];					// 0x2D
				char arg2[180];					// 0xE1
				char arg3[180];					// 0x195

			};

			struct	// Ensure proper size.
			{
				char buffer[0xC03];				// 0x2D
			};
		};
	};
#pragma pack(pop)
	static_assert(sizeof(SceNotificationRequest) == 0xC30, "Size of SceNotificationRequest is not 0xC30");

	typedef struct
	{
		int AppId;
		int Unk;
		char unk0x8[0x4];
		int AppType;
		char TitleId[10];
		char unk0x1A[0x2E];
	} SceAppInfo;

	typedef struct SceKernelModuleSegmentInfo
	{
		void* address;
		uint32_t size;
		int32_t prot;
	} SceKernelModuleSegmentInfo;

	typedef struct SceKernelModuleInfo
	{
		size_t size;
		char name[256];
		SceKernelModuleSegmentInfo segmentInfo[4];
		uint32_t segmentCount;
		uint8_t fingerprint[20];
	} SceKernelModuleInfo;

	enum BuzzerType
	{
		RingOnce = 1,
		RingThree,
		LongRing,
		ThreeLongRing,
		ThreeLongDoubleBeeps,
	};

	typedef struct {
		size_t Size;                // 0x0
		char VersionString[0x1C];   // 0x8 (e.g. " 6.720.001" padded with leading zeros)
		uint32_t Version;           // 0xe.g. 0x06720001
	} SceKernelSwVersion;

	typedef struct __mcontext {
		__register_t	mc_onstack;
		__register_t	mc_rdi;
		__register_t	mc_rsi;
		__register_t	mc_rdx;
		__register_t	mc_rcx;
		__register_t	mc_r8;
		__register_t	mc_r9;
		__register_t	mc_rax;
		__register_t	mc_rbx;
		__register_t	mc_rbp;
		__register_t	mc_r10;
		__register_t	mc_r11;
		__register_t	mc_r12;
		__register_t	mc_r13;
		__register_t	mc_r14;
		__register_t	mc_r15;
		__uint32_t	mc_trapno;
		__uint16_t	mc_fs;
		__uint16_t	mc_gs;
		__register_t	mc_addr;
		__uint32_t	mc_flags;
		__uint16_t	mc_es;
		__uint16_t	mc_ds;
		__register_t	mc_err;
		__register_t	mc_rip;
		__register_t	mc_cs;
		__register_t	mc_rflags;
		__register_t	mc_rsp;
		__register_t	mc_ss;
		long	mc_len;
		long	mc_fpformat;
		long	mc_ownedfp;
		long	mc_fpstate[104] __aligned(64);
		__register_t	mc_fsbase;
		__register_t	mc_gsbase;
		long	mc_spare[6];
	} mcontext_t;
	typedef struct __ucontext {
		sigset_t	uc_sigmask;
		mcontext_t	uc_mcontext;
		struct __ucontext* uc_link;
		stack_t		uc_stack;
		int		uc_flags;
		int		__spare__[4];
	} ucontext_t;
	typedef ucontext_t SceDbgUcontext;
	typedef void (*SceDbgExceptionHandler)(int, SceDbgUcontext*);
	struct pthread_attr
	{
		int	sched_policy;
		int	sched_inherit;
		int	prio;
		int	suspend;
#define	THR_STACK_USER		0x100	/* 0xFF reserved for <pthread.h> */
		int	flags;
		void* stackaddr_attr;
		size_t	stacksize_attr;
		size_t	guardsize_attr;
		cpuset_t* cpuset;
		size_t	cpusetsize;
	};
	struct thread
	{
		int tid;
		char _0x04[0x34];
		thread* next;
		char _0x40[0x40];
		void* (*routine)(void*);
		void* arg;
		pthread_attr attr;
	};

#ifdef __cplusplus
}
#endif
