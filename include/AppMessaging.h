#pragma once

#include "Defs/AppMessagingDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceAppMessagingSendMsgToShellCore(uint32_t msgType, const void* payload, uint32_t payloadSize, uint32_t flags);
	int sceAppMessagingSendMsgToShellUI(uint32_t msgType, const void* payload, uint32_t payloadSize, uint32_t flags);
	int sceAppMessagingSendMsg(int destAppId, uint32_t msgType, const void* payload, uint32_t payloadSize, uint32_t flags);
	int sceAppMessagingReceiveMsg(AppMessage* message);
	int sceAppMessagingTryReceiveMsg(AppMessage* message);

	int sceAppMessagingClearEventFlag(int destAppId, uint64_t bitsToClear);
	int sceAppMessagingSetEventFlag(int destAppId, uint64_t bitPattern);
	int sceAppMessagingTryGetEventFlag(uint64_t bitsToGet, uint64_t* resultPat, bool clearObtainedBits);

#ifdef __cplusplus
}
#endif