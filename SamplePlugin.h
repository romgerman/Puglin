
#ifdef __cplusplus
#  define EXTERNC extern "C"
#  define NOTHROW noexcept
#else
#  define EXTERNC
#  define NOTHROW
#endif

EXTERNC void NewSamplePlugin() NOTHROW;
EXTERNC void DeleteSamplePlugin() NOTHROW;

