#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int sceSystemServiceGetAppIdOfBigApp();
	int sceSystemServiceGetAppIdOfMiniApp();
	int sceSystemServiceAddLocalProcess(int appId, const char* executablePath, int args, const char* argsv[]);
	int sceSystemServiceIsAppSuspended(int appId, int* state);
	int sceSystemServiceKillApp(int, int, int, int);
	int sceSystemServiceKillLocalProcess(int appId, int appLocalPid);
	int sceSystemServiceLaunchApp(const char* titleId, char* args, int* appParam);

#ifdef __cplusplus
}
#endif