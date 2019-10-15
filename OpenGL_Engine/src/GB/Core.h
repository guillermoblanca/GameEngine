#pragma once

#ifdef GB_PLATFORM_WINDOWS
#if GB_DYNAMIC_LINK
#ifdef GB_BUILD_DLL
#define GBAPI __declspec(dllexport)
#else 
#define GBAPI __declspec(dllimport)
#endif // BUILD_DLL
#else
#define GBAPI
#endif
#else
#error "GB Only supports Windows!"
#endif

#ifdef GB_ENABLE_ASSERTS
#define GB_ASSERT(x,...) if(!x) {GB_CLIENT_ERROR("Assertion failed {0}",__VA_ARGS__); __debugbreak(); }
#define GB_CORE_ASSERT(x,...)if(!x) {GB_CORE_ERROR("Assertion failed {0}",__VA_ARGS__); __debugbreak(); }
#else
#define GB_ASSERT(x,...)
#define GB_COREASSERT(x,...)

#endif
#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(X) 1 << X

#define GB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


////////////////////////////////
// Seletec the Render to use 
////////////////////////////////

//#define GB_OPENGL
#define GB_DIRECTX