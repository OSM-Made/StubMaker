#pragma once 

#ifdef __cplusplus
extern "C" {
#endif

	enum SceNetIfName
	{
		SCE_NET_IF_NAME_UNKNOWN = -2,
		SCE_NET_IF_NAME_NONE,
		SCE_NET_IF_NAME_LO0,
		SCE_NET_IF_NAME_PHYSICAL,
		SCE_NET_IF_NAME_ETH0 = 1,
		SCE_NET_IF_NAME_ETH1,
		SCE_NET_IF_NAME_DBG0,
		SCE_NET_IF_NAME_WLAN0,
		SCE_NET_IF_NAME_WLAN1,
		SCE_NET_IF_NAME_GBE0,
		SCE_NET_IF_NAME_BT0,
		SCE_NET_IF_NAME_PHONE0,
		SCE_NET_IF_NAME_VIRTUAL,
		SCE_NET_IF_NAME_PPPOE0 = 9,
		SCE_NET_IF_NAME_MAX
	};

	typedef struct SceNetIfEntry
	{
		char Name[0x10];				// 0x00
		char padding0[0x18];			// 0x10
		int IPAddress;					// 0x28
		char padding1[0x24];			// 0x2C
		unsigned char MacAddress[6];	// 0x50
		char padding2[0x192];			// 0x56
	} SceNetIfEntry; //0x1E8

#ifdef __cplusplus
}
#endif

