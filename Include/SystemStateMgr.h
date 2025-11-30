#pragma once

#include "Defs/SystemStateMgrDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

int sceSystemStateMgrWakeUp(TriggerCode trigger);
int sceSystemStateMgrReboot();
int sceSystemStateMgrTurnOff();
int sceSystemStateMgrEnterStandby();
int sceSystemStateMgrGetCurrentState();

#ifdef __cplusplus
}
#endif