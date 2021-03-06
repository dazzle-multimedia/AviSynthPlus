// Avisynth v2.5.  Copyright 2002 Ben Rudiak-Gould et al.
// http://www.avisynth.org

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA, or visit
// http://www.gnu.org/copyleft/gpl.html .
//
// Linking Avisynth statically or dynamically with other modules is making a
// combined work based on Avisynth.  Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.
//
// As a special exception, the copyright holders of Avisynth give you
// permission to link Avisynth with independent modules that communicate with
// Avisynth solely through the interfaces defined in avisynth.h, regardless of the license
// terms of these independent modules, and to copy and distribute the
// resulting combined work under terms of your choice, provided that
// every copy of the combined work is accompanied by a complete copy of
// the source code of Avisynth (the version of Avisynth used to produce the
// combined work), being distributed under the terms of the GNU General
// Public License plus this exception.  An independent module is a module
// which is not derived from or based on Avisynth, such as 3rd-party filters,
// import and export plugins, or graphical user interfaces.


#ifndef __Color_h
#define __Color_h

#include <avisynth.h>

enum
{
    COLORYUV_RANGE_NONE,
    COLORYUV_RANGE_TV_PC,
    COLORYUV_RANGE_PC_TV,
    COLORYUV_RANGE_PC_TVY
};

struct ColorYUVPlaneData
{
    double average;
    int real_min, real_max, loose_min, loose_max;
};

struct ColorYUVPlaneConfig
{
    double gain, offset, gamma, contrast;
    int range, plane;
    bool clip_tv;
    bool changed;
};

class ColorYUV : public GenericVideoFilter
{
public:
    ColorYUV(PClip child,
             double gain_y, double offset_y, double gamma_y, double contrast_y,
             double gain_u, double offset_u, double gamma_u, double contrast_u,
             double gain_v, double offset_v, double gamma_v, double contrast_v,
             const char* level, const char* opt,
             bool colorbar, bool analyse, bool autowhite, bool autogain, bool conditional,
             IScriptEnvironment* env);

    PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);

    int __stdcall SetCacheHints(int cachehints, int frame_range) override
    {
        return cachehints == CACHE_GET_MTMODE ? MT_NICE_FILTER : 0;
    }

    static AVSValue Create(AVSValue args, void*, IScriptEnvironment* env);

private:
    ColorYUVPlaneConfig configY, configU, configV;
    bool colorbar, analyse, autowhite, autogain, conditional;
};

#endif // __Color_h
