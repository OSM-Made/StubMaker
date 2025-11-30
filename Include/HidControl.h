#pragma once

#include "Defs/HidControlDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

    int sceHidControlInit();
    int sceHidControlGetBatteryState(int deviceId, SceHidBatteryState* state);
    int sceHidControlGetDeviceName(int deviceId, char* out);

#ifdef __cplusplus
}
#endif