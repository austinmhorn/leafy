//
//  SystemInfo.hpp
//  leafy
//
//  Created by Austin Horn on 7/25/23.
//

#ifndef SystemInfo_hpp
#define SystemInfo_hpp

#if WIN32 || WIN64
#include <windows.h>
#elif LINUX || linux || __linux__
#include <X11/Xlib.h>
#elif APPLE || MACH || __APPLE__ || __MACH__
#include <CoreGraphics/CGDisplayConfiguration.h>
#else
#endif

static void getScreenResolution(unsigned int& width, unsigned int& height) {
#if WIN32 || WIN64
    width = (int)GetSystemMetrics(SM_CXSCREEN);
    height = (int)GetSystemMetrics(SM_CYSCREEN);
#elif LINUX || linux || __linux__
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    width = s->width;
    height = s->height;
#elif APPLE || MACH || __APPLE__ || __MACH__
    auto mainDisplayId = CGMainDisplayID();
    width = static_cast<unsigned int>(CGDisplayPixelsWide(mainDisplayId));
    height = static_cast<unsigned int>(CGDisplayPixelsHigh(mainDisplayId));
#else
#endif
}

#endif /* SystemInfo_hpp */
