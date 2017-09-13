#include <obs-module.h>

#include "puglin_list.h"

OBS_DECLARE_MODULE()

#include "SamplePlugin.h"

bool obs_module_load(void)
{
	puglin_alloc_list();

	NewSamplePlugin(); // TODO: this sucks. Need an automated way to do it. Macros?
	
	//for (int i = 0; i < PUGLIN_MAX_SOURCES; i++)
	//{
		//if (puglin_get_info(i))
			obs_register_source(puglin_get_info(0)); // TODO: Why i not working here?
	//}

	return true;
}

void obs_module_unload(void)
{
	DeleteSamplePlugin();
	puglin_dealloc_list();
}
