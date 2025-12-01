#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	int sceKernelInitializeDipsw();
	int sceKernelSetDipsw(short sw);
	int sceKernelUnsetDipsw(short sw);
	int sceKernelCheckDipsw(short sw);
	int sceKernelReadDipswData(uint64_t a1, uint64_t a2);
	int sceKernelWriteDipswData(uint64_t a1, uint64_t a2);
	int sceKernelIsDevelopmentMode();
	int sceKernelIsAssistMode();
	int sceKernelIsDisableRazor();

#ifdef __cplusplus
}
#endif