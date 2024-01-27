#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct sceShellUIUtilLaunchParam
	{
		uint32_t size;
		uint32_t userId;
	};

	// TODO: sceShellUIUtilGetDefaultQueryParameter, sceShellUIUtilGetAppUrl

	int sceShellUIUtilInitialize();
	int sceShellUIUtilLaunchByUri(const char* uri, sceShellUIUtilLaunchParam* a2);
	int sceShellUIUtilTerminate();

#ifdef __cplusplus
}
#endif