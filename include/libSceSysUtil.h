#pragma once

#include "Defs/KernelExtDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceSysUtilSendSystemNotification(int messageId);
	int sceSysUtilSendSystemNotificationWithUserId(int messageId, int userId);
	int sceSysUtilSendSystemNotificationWithDeviceId(int messageId, int deviceId);
	int sceSysUtilSendSystemNotificationWithDeviceIdRelatedToUser(int messageId, int userId, int deviceId);
	int sceSysUtilSendSystemNotificationWithText(int messageId, const char* message);
	int sceSysUtilSendSystemNotificationWithTextRelatedToUser(int messageId, int userId, const char* message);
	int sceSysUtilSendSystemNotificationWithErrorCode(int messageId, int errorCode);
	int sceSysUtilSendSystemNotificationWithAppId(int messageId, int appId);
	int sceSysUtilSendSystemNotificationWithAppName(int messageId, const char* appName);
	int sceSysUtilSendSystemNotificationWithAppInfo(int messageId, const char* arg1, const char* arg2);
	int sceSysUtilSendSystemNotificationWithAppNameRelatedToUser(int messageId, int userId, const char* appName);
	int sceSysUtilSendSystemNotificationWithParams(int messageId, ...); // Not correctly defined
	int sceSysUtilSendSystemNotificationWithUserName(int messageId, const char* userName);
	int sceSysUtilSendSystemNotificationWithUserNameInfo(int messageId, const char* arg1, const char* arg2);
	int sceSysUtilSendAddressingSystemNotification(int messageId, int targetId);
	int sceSysUtilSendAddressingSystemNotificationWithDeviceId(int messageId, int targetId, int deviceId);
	int sceSysUtilSendAddressingSystemNotificationWithUserName(int messageId, int targetId, const char* userName);
	int sceSysUtilSendAddressingSystemNotificationWithUserId(int messageId, int targetId, int userId);
	int sceSysUtilSendNotificationRequest(const char* message, bool blocking);
	int sceSysUtilSendTrcCheckNotificationRequest(const char* message, bool blocking);
	int sceSysUtilSendNpDebugNotificationRequest(const char* message, bool blocking);
	int sceSysUtilSendWebDebugNotificationRequest(const char* message, bool blocking);
	int sceSysUtilSendSystemNotificationParamInit(SceNotificationRequest* notifyBuffer, SceNotificationRequestType Type);
	int sceSysUtilSendSystemNotification2(void* input);

#ifdef __cplusplus
}
#endif