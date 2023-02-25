#pragma once

#ifdef __cplusplus 
extern "C" {
#endif

enum AppType
{
	AppTypeInvalid = -1,
	Unknown,
	ShellUI,
	Daemon,
	CDLG,
	MiniApp,
	BigApp,
	ShellCore,
	ShellApp
};

struct AppStatus
{
	int AppId;
	int LaunchRequestAppId;
	char AppType;
};

enum Flag
{
	Flag_None = 0,
	SkipLaunchCheck = 1,
	SkipResumeCheck = 1,
	SkipSystemUpdateCheck = 2,
	RebootPatchInstall = 4,
	VRMode = 8,
	NonVRMode = 16
};

struct LaunchAppParam
{
	unsigned int size;      //0x00
	int userId;             //0x04
	int appAttr;            //0x08
	int enableCrashReport;  //0x0C
	uint64_t checkFlag;     //0x10
};

#ifdef __cplusplus
}
#endif