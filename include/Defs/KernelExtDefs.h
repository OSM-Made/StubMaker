#pragma once
#include <stdint.h>

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


#ifdef __cplusplus
}
#endif
