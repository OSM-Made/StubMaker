#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int sceShellCoreUtilShowErrorDialog(int error_code);
	int sceShellCoreUtilExitMiniApp(void);
	int sceShellCoreUtilExitMiniAppWithValue(const char* value);
	int sceShellCoreUtilGetFreeSizeOfUserPartition(uint64_t* free, uint64_t* total);

#ifdef __cplusplus
}
#endif