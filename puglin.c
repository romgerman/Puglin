#include <obs-module.h>

#include "puglin_list.h"

OBS_DECLARE_MODULE()

#include "SamplePlugin.h"

/*#include <Windows.h>

void* create_modeless(void* object, void* ui_data)
{
	return CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"OK",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		GetActiveWindow(),     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(GetActiveWindow(), GWL_HINSTANCE),
		NULL);      // Pointer not needed.
}*/

bool obs_module_load(void)
{
	puglin_alloc_list();

	/*struct obs_modeless_ui mdui = {
		.id = "mybutton",
		.task = "mytask",
		.target = "win32",
		.create = create_modeless
	};*/

	//obs_register_modeless_ui(&mdui);

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
