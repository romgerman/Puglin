#pragma once

#include <obs-module.h>

#ifdef __cplusplus
#  define EXTERNC extern "C"
#  define NOTHROW noexcept
#else
#  define EXTERNC
#  define NOTHROW
#endif

#define PUGLIN_MAX_SOURCES 16

EXTERNC void puglin_alloc_list();
EXTERNC void puglin_dealloc_list();
EXTERNC void puglin_add_info(struct obs_source_info* info);
EXTERNC struct obs_source_info* puglin_get_info(int index);
