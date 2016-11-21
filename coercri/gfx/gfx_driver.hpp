/*
 * FILE:
 *   gfx_driver.hpp
 *
 * PURPOSE:
 *   The central "graphics driver" object -- responsible for creating
 *   Windows, Graphics, Fonts, etc., and also for dispatching events
 *   to windows.
 *
 * AUTHOR:
 *   Stephen Thompson <stephen@solarflare.org.uk>
 *
 * COPYRIGHT:
 *   Copyright (C) Stephen Thompson, 2008 - 2009.
 *
 *   This file is part of the "Coercri" software library. Usage of "Coercri"
 *   is permitted under the terms of the Boost Software License, Version 1.0, 
 *   the text of which is displayed below.
 *
 *   Boost Software License - Version 1.0 - August 17th, 2003
 *
 *   Permission is hereby granted, free of charge, to any person or organization
 *   obtaining a copy of the software and accompanying documentation covered by
 *   this license (the "Software") to use, reproduce, display, distribute,
 *   execute, and transmit the Software, and to prepare derivative works of the
 *   Software, and to permit third-parties to whom the Software is furnished to
 *   do so, all subject to the following:
 *
 *   The copyright notices in the Software and this entire statement, including
 *   the above license grant, this restriction and the following disclaimer,
 *   must be included in all copies of the Software, in whole or in part, and
 *   all derivative works of the Software, unless such copies or derivative
 *   works are solely in the form of machine-executable object code generated by
 *   a source language processor.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 *   SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 *   FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *   DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef COERCRI_GFX_DRIVER_HPP
#define COERCRI_GFX_DRIVER_HPP

#include "boost/noncopyable.hpp"
#include "boost/shared_ptr.hpp"

#include <vector>

namespace Coercri {

    class Font;
    class Graphic;
    class PixelArray;
    class Window;
    
    class GfxDriver : boost::noncopyable {
    public:
        virtual ~GfxDriver() { }

        // Find available display sizes for full screen
        struct DisplayMode {
            int width, height;
        };
        typedef std::vector<DisplayMode> DisplayModeVector;
        virtual DisplayModeVector getFullScreenModes() = 0;
        virtual DisplayMode getDesktopMode() = 0;
        
        // Create a new Window
        virtual boost::shared_ptr<Window> createWindow(int width, int height,
                                                       bool resizable, bool fullscreen,
                                                       const std::string &title) = 0;

        // Create a Graphic from a PixelArray.
        virtual boost::shared_ptr<Graphic> createGraphic(boost::shared_ptr<const PixelArray> pixels,
                                                         int hx = 0,
                                                         int hy = 0) = 0;

        // Poll for events, runs any WindowListeners that have been attached to windows
        // Returns TRUE if any events were processed.
        virtual bool pollEvents() = 0;

        // MS Windows only -- sets icon for creation of new windows
        virtual void setWindowsIcon(int resource_id) { }
    };

}

#endif