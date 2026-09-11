#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    int scePadGetDeviceId(int handle, int* deviceId);
    int scePadGetDeviceInfo(int a1, char* a2);
    int scePadGetVersionInfo(int a1, char* a2);

#ifdef __cplusplus
}
#endif