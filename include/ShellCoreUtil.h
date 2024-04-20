#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct sceShellCoreUtilLaunchParam
	{
		uint32_t size;
		uint32_t userId;
	};

	int sceShellCoreUtilShowErrorDialog(int error_code);
	int sceShellCoreUtilExitMiniApp(void);
	int sceShellCoreUtilExitMiniAppWithValue(const char* value);
	int sceShellCoreUtilGetFreeSizeOfUserPartition(uint64_t* free, uint64_t* total);
	int sceShellCoreUtilLaunchByUri(const char* uri, sceShellCoreUtilLaunchParam* a2);

#ifdef __cplusplus
}
#endif