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
		NotificationRequest = 0,
		SystemNotification = 1,
		SystemNotificationWithUserId = 2,
		SystemNotificationWithDeviceId = 3,
		SystemNotificationWithDeviceIdRelatedToUser = 4,
		SystemNotificationWithText = 5,
		SystemNotificationWithTextRelatedToUser = 6,
		SystemNotificationWithErrorCode = 7,
		SystemNotificationWithAppId = 8,
		SystemNotificationWithAppName = 9,
		SystemNotificationWithAppInfo = 9,
		SystemNotificationWithAppNameRelatedToUser = 10,
		SystemNotificationWithParams = 11,
		SendSystemNotificationWithUserName = 12,
		SystemNotificationWithUserNameInfo = 13,
		SendAddressingSystemNotification = 14,
		AddressingSystemNotificationWithDeviceId = 15,
		AddressingSystemNotificationWithUserName = 16,
		AddressingSystemNotificationWithUserId = 17,

		UNK_1 = 100,
		TrcCheckNotificationRequest = 101,
		NpDebugNotificationRequest = 102,
		UNK_2 = 102,
	};

	// Struct Credits - OSM-Made
	typedef struct
	{
		enum SceNotificationRequestType type;
		int reqId;
		int priority;
		int msgId;
		int targetId;
		int userId;
		int unk1;
		int unk2;
		int appId;
		int errorNum;
		int unk3;
		unsigned char useIconImageUri;
		char message[1024];
		char iconUri[1024];
		char unk[1024];
	} SceNotificationRequest;

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
