#pragma once

#include "Defs/SysmoduleInternalDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

	int sceSysmoduleLoadModuleInternal(uint32_t id);
	int sceSysmoduleUnloadModuleInternal(uint32_t id);

#ifdef __cplusplus
}
#endif