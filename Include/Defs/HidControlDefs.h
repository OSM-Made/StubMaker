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

    struct SceHidDeviceInfo // Unfinished
    {
        int _0x00; // type ?
        int deviceId; // 0x04
        char pad_0x08[0x1F8]; // memset(SceHidDeviceInfo, 0, 0x202); in SysCore 0x05BC40
    };

#ifdef __cplusplus
}
#endif