
#include "GB.h"

class Sandbox : public GB::Application
{
public:
	Sandbox()
	{
		GB_CLIENT_INFO("Client info");
	}

	~Sandbox()
	{

	}
};

GB::Application * GB::CreateApplication()
{
	return new Sandbox();
}
