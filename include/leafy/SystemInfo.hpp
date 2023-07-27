//
//  SystemInfo.hpp
//  Leafly
//
//  Created by Austin Horn on 7/25/23.
//

#ifndef SystemInfo_hpp
#define SystemInfo_hpp

#if WIN32
#include <windows.h>
#else
#include <CoreGraphics/CGDisplayConfiguration.h>
#endif

static void getScreenResolution(unsigned int& width, unsigned int& height) {
#if WIN32
    width = (int)GetSystemMetrics(SM_CXSCREEN);
    height = (int)GetSystemMetrics(SM_CYSCREEN);
#else
    auto mainDisplayId = CGMainDisplayID();
    width = static_cast<unsigned int>(CGDisplayPixelsWide(mainDisplayId));
    height = static_cast<unsigned int>(CGDisplayPixelsHigh(mainDisplayId));
#endif
}

#endif /* SystemInfo_hpp */
