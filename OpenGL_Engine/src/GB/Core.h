#pragma once


#ifdef GB_BUILD_DLL
#define GBAPI __declspec(dllexport)
#else 
#define GBAPI __declspec(dllimport)
#endif // BUILD_DLL


#ifdef GB_ENABLE_ASSERTS
#define GB_ASSERT(x,...) if(!x) {GB_ERROR("Assertion failed {0}",__VA_ARGS__); __debugbreak(); }
#define GB_CORE_ASSERT(x,...)if(!x) {GB_CORE_ERROR("Assertion failed {0}",__VA_ARGS__); __debugbreak(); }
#else
#define GB_ASSERT(x,...)
#define GB_COREASSERT(x,...)

#endif
#define BIT(X) 1 << X

#define GB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)