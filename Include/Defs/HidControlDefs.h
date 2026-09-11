#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    enum SceHidBatteryStatus
    {
        BATTERY_STATUS_CHARGING = 1,
        BATTERY_STATUS_FULLCHARGED = 2,
    };

    struct SceHidBatteryState
    {
        SceHidBatteryStatus status; // 0x00
        int level; // 0x04
    };

#pragma pack(push, 1)
    struct SceHidDeviceInfo
    {
        int _0x00; // type ?
        int deviceId; // 0x04
        char pad_0x08[0x1FA]; // memset(SceHidDeviceInfo, 0, 0x202); in SysCore 0x05BC40
    };
#pragma pack(pop)

#ifdef __cplusplus
}
#endif