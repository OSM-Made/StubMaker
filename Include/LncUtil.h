#pragma once
#include "Defs/LncUtilDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceLncUtilInitialize();
	int sceLncUtilTerminate();

	int sceLncUtilBlockAppSuspend(const char* tileId);
	int sceLncUtilUnblockAppSuspend(const char* tileId);

	int sceLncUtilGetAppIdOfBigApp();
	int sceLncUtilGetAppIdOfMiniApp();
	int sceLncUtilGetAppId(const char* tileId);
	int sceLncUtilIsAppLaunched(const char* tileId, bool* isLaunched);
	int sceLncUtilIsAppSuspended(int appId, bool* isSuspended);
	int sceLncUtilKillApp(int appId);
	int sceLncUtilResumeApp(int appId, int flag);
	int sceLncUtilSuspendApp(int appId, int flag);
	int sceLncUtilSetAppFocus(int appId, int flag);
	int sceLncUtilLaunchApp(const char* titleId, char** args, LaunchAppParam* appParam);

#ifdef __cplusplus
}
#endif