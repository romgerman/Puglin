#include "OBSPlugin.h"
#include "SamplePlugin.h"

#include <Windows.h> // testing

using namespace Puglin;

class SamplePlugin : public OBSPlugin
{
public:
	SamplePlugin() : OBSPlugin("buttplug", "Butt Plug", obs_source_type::OBS_SOURCE_TYPE_FILTER, OBS_SOURCE_VIDEO)
	{
		RegisterPlugin(OptionalPluginCallback::OPCProperties | OptionalPluginCallback::OPCDefaults);
	}

	void* OnCreate(obs_data_t* settings, obs_source_t* source) override
	{
		void* handle = obs_create_ui("mybutton", "mytask", "win32", 0, 0);
		
		if (!handle)
			MessageBox(0, "NOPE", "", 0);
		else
		{
			MessageBox(0, "OK", "", 0);
		}

		return nullptr;
	}

	obs_properties_t* GetProperties() override
	{
		obs_properties_t* props = obs_properties_create();

		obs_properties_add_float_slider(props, "test", "Description?", 0.0, 100.0, 10.0);

		MessageBox(0, "Props got called", "", 0); // TODO: Doesn't get called
		
		return props;
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
