/********************************************************************
 * Name:      yatishDB.h
 * Purpose:   Declares the class exporting PDF from yatish data
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2021-03-23
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHPDF_H
#define YATISHPDF_H

#include "yatishDBsqlite.h"
#include "yatishSettings.h"
#include "yatishTypes.h"

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
                       const Map4pie&, const wxColour *);
        void NoMoreThan6 (Map4pie&);
};

#endif // YATISHPDF_H
