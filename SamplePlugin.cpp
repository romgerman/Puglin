#include "OBSPlugin.h"
#include "SamplePlugin.h"

#include <Windows.h> // testing

using namespace Puglin;

class SamplePlugin : public OBSPlugin
{
public:
	SamplePlugin() : OBSPlugin("buttplug", "Butt Plug", obs_source_type::OBS_SOURCE_TYPE_FILTER, OBS_SOURCE_VIDEO)
	{
		RegisterPlugin(OptionalPluginCallback::OPCLoad | OptionalPluginCallback::OPCSave);
	}

	void* OnCreate(obs_data_t* settings, obs_source_t* source) override
	{
		MessageBox(0, "ONCREATE WRKS", "", 0);
		return nullptr;
	}
};

SamplePlugin* buttplug;

EXTERNC void NewSamplePlugin() NOTHROW
{
	buttplug = new SamplePlugin();
}

EXTERNC void DeleteSamplePlugin() NOTHROW
{
	delete buttplug;
}
