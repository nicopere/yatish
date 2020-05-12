/***************************************************************
 * Name:      yatishApp.h
 * Purpose:   Defines Application Class
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#ifndef YATISHAPP_H
#define YATISHAPP_H

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/stdpaths.h>
#include <wx/config.h>
#include <wx/fs_zip.h>

class yatishApp : public wxApp {
    public:
        bool OnInit ();
        int OnExit ();
    private:
#ifdef NDEBUG
        wxSingleInstanceChecker checker;
#endif
        wxLocale * yatishLocale;
};

//wxDECLARE_APP (yatishApp);

#endif // YATISHAPP_H
