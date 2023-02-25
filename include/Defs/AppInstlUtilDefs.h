#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	enum SceAppInstUtilDelete {
		SCE_APP_INST_UTIL_DELETE_PATCH = (1u << 0),
		SCE_APP_INST_UTIL_DELETE_ADDCONT_EXTRA_DATA = (1u << 1),
		SCE_APP_INST_UTIL_DELETE_TEMP_DATA = (1u << 2),
		SCE_APP_INST_UTIL_DELETE_DOWNLOAD_DATA = (1u << 3),
		SCE_APP_INST_UTIL_DELETE_USERS_SAVE_DATA = (1u << 4),
		SCE_APP_INST_UTIL_DELETE_ALL_USERS_SAVE_DATA = (1u << 5),
	};

#ifdef __cplusplus
}
#endif
