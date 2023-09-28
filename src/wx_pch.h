/********************************************************************
 * Name:      wx_pch.h
 * Purpose:   Header to create Pre-Compiled Header (PCH)
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef WX_PCH_H_INCLUDED
#define WX_PCH_H_INCLUDED

// basic wxWidgets headers
#include <wx/wxprec.h>

#include <wx/aboutdlg.h>
#include <wx/fs_zip.h>
#include <wx/html/helpctrl.h>
#include <wx/listctrl.h>
#include <wx/snglinst.h>
#include <wx/spinctrl.h>
#include <wx/sstream.h>
#include <wx/stdpaths.h>
#include <wx/tokenzr.h>
#include <wx/valgen.h>
#include <wx/wfstream.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#ifdef WX_PRECOMP
    // put here all your rarely-changing header files

    #include <wx/database/wxprec.h>

    #include <wx/pdfdoc.h>

    #include <mathplot.h>

    #include <wx/category/categorysimpledataset.h>
    #include <wx/chartpanel.h>
    #include <wx/pie/pieplot.h>
    #include <wx/xy/xylinerenderer.h>
    #include <wx/xy/xyplot.h>
    #include <wx/xy/xysimpledataset.h>

    #include <wxcharts/wx/charts/wxcharts.h>

#endif // WX_PRECOMP

#endif // WX_PCH_H_INCLUDED
