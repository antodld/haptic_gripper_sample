#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define Test_grasping_DLLIMPORT __declspec(dllimport)
#  define Test_grasping_DLLEXPORT __declspec(dllexport)
#  define Test_grasping_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define Test_grasping_DLLIMPORT __attribute__((visibility("default")))
#    define Test_grasping_DLLEXPORT __attribute__((visibility("default")))
#    define Test_grasping_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define Test_grasping_DLLIMPORT
#    define Test_grasping_DLLEXPORT
#    define Test_grasping_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef Test_grasping_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define Test_grasping_DLLAPI
#  define Test_grasping_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef Test_grasping_EXPORTS
#    define Test_grasping_DLLAPI Test_grasping_DLLEXPORT
#  else
#    define Test_grasping_DLLAPI Test_grasping_DLLIMPORT
#  endif // Test_grasping_EXPORTS
#  define Test_grasping_LOCAL Test_grasping_DLLLOCAL
#endif // Test_grasping_STATIC