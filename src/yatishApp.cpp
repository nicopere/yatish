/** \mainpage Time tracking desktop application for freelancers/homeworkers
  * __Features:__
  * - Cross-platform (Linux, Windows).
  * - SQLite based: no connection needed but...
  * - ...can sync to a MySQL/MariaDB server.
  * - PDF export of selected listings (to be appended to invoices).
  * - 3 charting toolsets available.
  * - GUI in English or French.
  * - Integrated user guide (not translated though).
  * - Doxygen source code documentation (obviously) e.g. our yatishDBsqlite class.
  * - Privacy: _yatish_ will not publish anything unless you do mean it,
  * and then only in a privately owned database.
  *
  * This file:
> * Name:      yatishApp.cpp
> * Purpose:   Implements the Application class
> * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
> * Created:   2020-02-11
> * Copyright: EIF-services (https://www.eif-services.eu/yatish)
> * License:   GPLv3
  */

#include "wx_pch.h"
#include "yatishApp.h"

//(*AppHeaders
#include "yatishFrame.h"
#include <wx/image.h>
//*)

wxIMPLEMENT_APP (yatishApp);

bool yatishApp::OnInit () {
    if ( !wxApp::OnInit() ) return false;
    wxConfig::Set ( new wxConfig ("yatish", "EIF-services",
                                  wxEmptyString, wxEmptyString,
                                  wxCONFIG_USE_LOCAL_FILE|wxCONFIG_USE_SUBDIR) );
#ifdef __WXGTK__
    wxStandardPaths::Get().SetInstallPrefix ("/usr/local"); // should be already there according to the wxwidgets doc...
#endif
    yatishLocale = new wxLocale ( wxLANGUAGE_DEFAULT );
    yatishLocale->AddCatalog ("yatish");
#ifdef NDEBUG
    if ( checker.IsAnotherRunning() ) {
        wxLogError(_("Another program instance is already running, aborting this one.") );
        return false;
    }
#endif
    wxFileSystem::AddHandler(new wxZipFSHandler);
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        yatishFrame* Frame = new yatishFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;
}

int yatishApp::OnExit () {
    delete yatishLocale;
    delete wxConfig::Set (nullptr);
    return wxApp::OnExit();
}
