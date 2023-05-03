#pragma once 
#include <rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

	int sceRtcSetCurrentTick(SceRtcTick* pTick);
	int sceRtcSetCurrentNetworkTick(SceRtcTick* pTick);

#ifdef __cplusplus
}
#endif