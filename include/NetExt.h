#pragma once 

#include "Defs/NetExtDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceNetGetIfList(SceNetIfName ifName_num, SceNetIfEntry* out, int size);
	int sceNetConfigEtherGetLinkMode(SceNetIfName name, void* a2);

#ifdef __cplusplus
}
#endif