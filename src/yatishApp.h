/********************************************************************
 * Name:      yatishApp.h
 * Purpose:   Declares the Application class
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHAPP_H
#define YATISHAPP_H

/** Usual wxWidgets application class, taking care of:
 * - wxConfig
 * - wxLocale
 */
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
