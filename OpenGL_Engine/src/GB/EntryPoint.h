#pragma once
#include "Application.h"

#ifdef GB_PLATFORM_WINDOWS

extern GB::Application * GB::CreateApplication();

int main(int argc, char** argv)
{
	GB::Log::Init();
	auto app = GB::CreateApplication();
	app->Run();
	return 0;
}

#endif

