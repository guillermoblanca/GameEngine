#pragma once
#include "Application.h"

extern GB::Application * GB::CreateApplication();

int main(int argc, char** argv)
{
	GB::Log::Init();
	auto app = GB::CreateApplication();
	app->Run();
	return 0;
}



