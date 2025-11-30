#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    enum SystemState
    {
        InvalidSystemState = 0,
        INITIALIZING = 10,
        SHUTDOWN_ON_GOING = 100,
        POWER_SAVING = 200,
        SUSPEND_ON_GOING = 300,
        MAIN_ON_STANDBY = 500,
        WORKING = 1000
    };

	enum TriggerCode
	{
		InvalidTrigger,
		MISC,
		HDMI_CEC,
		REMOTE_PLAY = 100,
		COMPANION_APP,
		REMOTE_PLAY_NP_PUSH,
		UPDATER_SERVICE,
		BGFT,
		BG_DAILY_CHECK,
		NP_EVENT_JOIN,
		NP_EVENT_INFO_UPDATE,
		SP_CONNECT
	};

#ifdef __cplusplus
}
#endif
