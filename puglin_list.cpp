#include "puglin_list.h"

bool puglin_sources_allocated = false;
struct obs_source_info** puglin_sources_list;
static int puglin_current_source_index = 0;

EXTERNC void puglin_alloc_list()
{
	if (!puglin_sources_allocated)
	{
		//puglin_sources_list = (obs_source_info**)malloc(sizeof(struct obs_source_info*) * PUGLIN_MAX_SOURCES);
		puglin_sources_list = new obs_source_info*[PUGLIN_MAX_SOURCES];
		puglin_sources_allocated = true;
	}
}

EXTERNC void puglin_dealloc_list()
{
	if (puglin_sources_allocated)
		//free(puglin_sources_list);
		delete[] puglin_sources_list;
}

EXTERNC void puglin_add_info(struct obs_source_info* info)
{
	puglin_sources_list[puglin_current_source_index] = info;
	puglin_current_source_index++;
}

EXTERNC struct obs_source_info* puglin_get_info(int index)
{
	return puglin_sources_list[index];
}
