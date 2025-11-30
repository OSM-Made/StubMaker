#pragma once

#include "Defs/HidControlDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

    int sceHidControlInit();
    int sceHidControlGetBatteryState(int deviceId, SceHidBatteryState* state);

#ifdef __cplusplus
}
#endif