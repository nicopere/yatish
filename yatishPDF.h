/***************************************************************
 * Name:      yatishDB.h
 * Purpose:   Defines the class exporting PDF from yatish data
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2021-03-23
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#ifndef YATISHPDF_H
#define YATISHPDF_H

#include <map>
#include <wx/listctrl.h>
#include <wx/pdfdoc.h>
#include <wx/tokenzr.h>
#include "yatishDBsqlite.h"
#include "yatishSettings.h"

/** Exports a PDF reflecting the current state of panel #2.
 * \todo optionally export a non-localized (English) PDF
 */
class yatishPDF : public wxPdfDocument {
    public:
        yatishPDF (const Settings&, const wxListCtrl *, const yatishDBsqlite&,
                   const wxString& = "yatish.pdf");
        ~yatishPDF ();
    private:
        const Settings& sttngs; // for Header()
        int colmax, rowmax;
        wxString whereToWrite; // for ~yatishPDF()
        void Summary (const yatishDBsqlite&);
        void Charts (const wxListCtrl *);
        void Listing (const wxListCtrl *);
        void Header ();
        void Footer ();
        void PieChart (double, double, double, double,
                       const std::map <std::string, long>&, const wxColour *);
        void NoMoreThan6 (std::map <std::string, long>&);
};

#endif // YATISHPDF_H
