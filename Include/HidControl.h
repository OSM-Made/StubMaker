#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int sceHidControlInit();
    int sceHidControlGetBatteryState(int deviceId, ...);
    // Can we use sceHidControlGetBatteryState to get the battery level of the controller ?

#ifdef __cplusplus
}
#endif