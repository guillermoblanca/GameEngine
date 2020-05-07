#pragma once
#include "GB.h"
#include "imgui/imgui.h"

class Editor : public GB::Application
{
public: 
	Editor()
	{
		GB_CLIENT_INFO("Initialized Game in Editor Mode");
	}

};

GB::Application* GB::CreateApplication()
{
	return new Editor();
}
