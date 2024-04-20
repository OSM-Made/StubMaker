#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int sceRegMgrGetStr(int optionId, char* outString, size_t stringLength);
	int sceRegMgrGetInt(int optionId, int* outInt);
	int sceRegMgrGetBin(int optionId, void* outData, size_t dataLength);
	int sceRegMgrSetBin(int optionId, const void* inData, size_t dataLength);
	int sceRegMgrSetInt(int optionId, int inInt);
	int sceRegMgrSetStr(int optionId, const char* inStirng, size_t stringLength);

#ifdef __cplusplus
}
#endif