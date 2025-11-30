#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    enum SceHidBatteryStatus
    {
        // Charging = 2 ?
    };

    struct SceHidBatteryState
    {
        SceHidBatteryStatus status; // 0x00
        int level; // 0x04
    };

#ifdef __cplusplus
}
#endif