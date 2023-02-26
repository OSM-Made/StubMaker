#pragma once 

#include "Defs/NetExtDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceNetGetIfList(SceNetIfName ifName_num, SceNetIfEntry* out, int size);

#ifdef __cplusplus
}
#endif