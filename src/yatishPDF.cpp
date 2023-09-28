/********************************************************************
 * Name:      yatishDB.cpp
 * Purpose:   Implements the class exporting PDF from yatish data
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2021-03-23
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#include "wx_pch.h"
#include "yatishPDF.h"

/** Prints a title then calls other member functions for the body of the PDF document.
 * \param[in] s application settings
 * \param[in] l data currently shown on panel #2*
 * \param[in] m yatish SQLite driver (master)
 * \param[in] p path to the (future) PDF file
*/
yatishPDF::yatishPDF (const Settings& s, const wxListCtrl * l, const yatishDBsqlite& m, const wxString& p)
         : sttngs (s) {
    colmax = l->GetColumnCount();
    rowmax = l->GetItemCount();
    whereToWrite = p;
    AliasNbPages();
    AddPage (wxPORTRAIT, wxPAPER_A4);
    wxString title;
    if (colmax == 6) // timeslot view
        title = _("Timesheet");
    else // other tables
        title = _("YATiSh table");
    SetFont ("Helvetica", "B", 12);  // font size: in points
    double titleWidth = GetStringWidth (title) + 6;
    SetX ( 0.5*(210 - titleWidth) ); // mm (210 = A4 paper width)
    SetLineWidth (0.4);              // mm
    Cell (titleWidth, 6, title, wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
    Ln ();
    Summary (m);
    if (s.pdfCharts) Charts (l);
    Listing (l);
}

/** Writes the PDF document to the file which was given to the constructor. */
yatishPDF::~yatishPDF () {
    SaveAsFile (whereToWrite);
}

/** A few pieces of information about the data to be shown by [Charts() and] Listing(). */
void yatishPDF::Summary (const yatishDBsqlite& mDB) {
    Cell ( 30, 4, _("Summary") );
    SetFont ("Times", "", 10);
    Cell ( 40, 4, _("Number of records:") );
    wxString info = wxString::Format ("%d", rowmax);
    if (rowmax == sttngs.rowLimit) info += _(" (limited)");
    Cell (30, 4, info, wxPDF_BORDER_NONE, 1);
    if (colmax != 6) {
        Cell (30);
        Cell ( 40, 4, _("Number of fields:") );
        info.Printf ("%d", colmax);
        Cell (30, 4, info, wxPDF_BORDER_NONE, 1);
    }
    Cell (30);
    wxString filter = mDB.GetFilter();
    if ( filter.IsEmpty() ) {
        Cell ( 40, 4, _("SQL filter:") );
        SetFont ("Times", "I");
        Cell (30, 4, _("none"), wxPDF_BORDER_NONE, 1);
        SetFont ("Times", "");
    } else {
        Cell ( 40, 4, _("SQL filter:") );
        SetFont ("Courier");
        Cell (0, 4, filter.Trim (false), wxPDF_BORDER_NONE, 1);
        SetFont ("Times");
    }
    if (colmax != 6) return;
    Cell (30);
    Cell (40, 4, _("Date range:") );
    info.Printf ( "[ %s ; %s ]", mDB.GetFirstDay().FormatDate(), mDB.GetLastDay().FormatDate() );
    Cell (0, 4, info, wxPDF_BORDER_NONE, 1);
    Cell (30);
    SetFillColour (*wxYELLOW);
    Cell (40, 4, _("Total duration (hours):"), wxPDF_BORDER_NONE, 0, wxPDF_ALIGN_LEFT, 1);
    wxTimeSpan ts;
    mDB.FilteredTotal (ts);
    info.Printf ( "%d", ts.GetHours() );
    Cell (GetStringWidth (info) + 2, 4, info, wxPDF_BORDER_NONE, 1, wxPDF_ALIGN_LEFT, 1);
}

/** Draws charts from the timeslot view only (6 columns). Moreover a maximum of 6 sectors will be drawn. */
void yatishPDF::Charts (const wxListCtrl * lst) {
    if (colmax != 6) return;
    // data from wxListCtrl: total time (in minutes) for each label
    wxString timeslot;
    unsigned long hours, minutes;
    Map4pie projects, clients, tasks, tools;
    for (int row = 0; row < rowmax; row++) {
        timeslot = lst->GetItemText (row, 1);
        if (row == 0 && timeslot.IsEmpty()) continue; // an activity is underway: don't count it
        wxStringTokenizer tkz (timeslot, ":");
        tkz.GetNextToken().ToULong (&hours);
        tkz.GetNextToken().ToULong (&minutes);
        minutes += hours*60;
        projects[lst->GetItemText (row, 2) .ToStdString()] += minutes;
        clients [lst->GetItemText (row, 3) .ToStdString()] += minutes;
        tasks   [lst->GetItemText (row, 4) .ToStdString()] += minutes;
        tools   [lst->GetItemText (row, 5) .ToStdString()] += minutes;
    }
    // no more than 6 labels
    NoMoreThan6 (projects);
    NoMoreThan6 (clients);
    NoMoreThan6 (tasks);
    NoMoreThan6 (tools);
    // plots
    SetFont ("Helvetica", "B", 12);
    Cell (30, 6, _("Charts"), wxPDF_BORDER_NONE, 1);
    double x0 = GetX() + 20, y0 = GetY();
    wxColour colors[] = { // colorbrewer2.org
        wxColour (127, 201, 127),
        wxColour (190, 174, 212),
        wxColour (253, 192, 134),
        wxColour (255, 255, 153),
        wxColour ( 56, 108, 176),
        wxColour (240,   2, 127)
    };
    PieChart (x0,      y0,      80, 30, projects, colors);
    PieChart (x0 + 80, y0,      80, 30, clients, colors);
    PieChart (x0,      y0 + 30, 80, 30, tasks,   colors);
    PieChart (x0 + 80, y0 + 30, 80, 30, tools,   colors);
    SetXY    (10,      y0 + 60); // 10: default margin
}

/** Writes a table corresponding to the current state of panel #2 (Ctrl-T). */
void yatishPDF::Listing (const wxListCtrl * lst) {
    SetFont ("Helvetica", "B", 12);
    Cell (30, 6, _("Listing"), wxBORDER_NONE, 1);
    double columnWidth = 20, offset = 0.5*(210 - columnWidth*colmax);
    SetX (offset);
    wxListItem item;
    int col, row;
    SetFont ("Times", "B", 9);
    SetLineWidth (0.2); // restore default
    for (col = 0; col < colmax; col++) {
        lst->GetColumn (col, item);
        Cell (columnWidth, 6, item.GetText(), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    Ln();
    SetFont ("Times", "", 6);
    for (row = 0; row < rowmax; row++) {
        SetX (offset);
        for (col = 0; col < colmax; col++) {
            Cell (columnWidth, 3, lst->GetItemText (row, col), wxPDF_BORDER_LEFT|wxPDF_BORDER_RIGHT);
        }
        Ln();
    }
    SetX (offset);
    Cell (columnWidth*colmax, 0, wxEmptyString, wxPDF_BORDER_TOP);
}

/** Creates the header of the PDF document, according to user preferences (Ctrl-P). */
void yatishPDF::Header () {
    SetFont ("Helvetica", "B", 12);
    if (sttngs.logo4pdf) {
        if ( wxFileName::IsFileReadable (sttngs.companyName_or_logoPath) )
            Image (sttngs.companyName_or_logoPath, 10, 8, 12);
        else
            wxLogMessage (_("Logo file not found... thus not drawn.\n"
                            "Check out your PDF settings (Ctrl-S).") );
        Cell (15, 10, wxEmptyString);
    } else {
        Cell (30, 10, sttngs.companyName_or_logoPath, wxPDF_BORDER_BOTTOM);
    }
    SetFont ("Helvetica", "I", 12);
    if (sttngs.motto4pdf)
        Cell (0, 10, sttngs.companyMotto, wxPDF_BORDER_BOTTOM, 1, wxPDF_ALIGN_RIGHT);
    else
        Cell (0, 10, wxDateTime::Now().FormatDate(), wxPDF_BORDER_BOTTOM, 1, wxPDF_ALIGN_RIGHT);
    Ln (5);
}

/** PDF footer (page count). */
void yatishPDF::Footer () {
    SetY (-15);
    SetFont ("Helvetica", "", 10);
    Cell (0, 10, wxString::Format ( "%d/{nb}", PageNo() ),
          wxPDF_BORDER_NONE, 0, wxPDF_ALIGN_CENTER);
}

/** Modified from `charting.cpp` in the _wxPdfDocument_ samples. */
void yatishPDF::PieChart (double xPage, double yPage, double width, double height,
                          const Map4pie& data, const wxColour * colors) {
    SetFont ("Helvetica", "", 8);
    double margin = 1;
    double hLegend = 3;
    // Determine maximal legend width and sum of data values
    double sum = 0;
    double wLegend = 0;
    double labelWidth;
    for (auto element : data) {
      sum = sum + element.second;
      labelWidth = GetStringWidth (element.first);
      if (labelWidth > wLegend) wLegend = labelWidth;
    }
    double radius = width - 4*margin - hLegend - wLegend;
    if (radius > height - 2*margin) radius = height - 2*margin;
    radius = floor (radius/2);
    double xDiag = xPage + margin + radius;
    double yDiag = yPage + margin + radius;
    // Sectors
    SetLineWidth (0.2);
    double angle = 0;
    double angleStart = 0;
    double angleEnd = 0;
    int color = 0;
    for (auto element : data) {
      angle = (sum != 0) ? floor ( (element.second*360)/sum ) : 0;
      if (angle != 0) {
        angleEnd = angleStart + angle;
        SetFillColour ( colors[color%6] );
        Sector (xDiag, yDiag, radius, angleStart, angleEnd);
        angleStart += angle;
        color++;
      }
    }
    if (angleEnd != 360) {
      Sector (xDiag, yDiag, radius, angleStart - angle, 360);
    }
    // Legends
    double x1 = xPage + 2*radius + 4*margin;
    double x2 = x1 + hLegend + margin;
    double y1 = yDiag - radius + ( 2*radius - data.size()*(hLegend + margin) )/2;
    color = 0;
    for (auto element : data) {
      SetFillColour ( colors[color%6] );
      Rect (x1, y1, hLegend, hLegend, wxPDF_STYLE_FILLDRAW);
      SetXY (x2, y1);
      Cell (wLegend, hLegend, element.first);
      y1 += hLegend + margin;
      color++;
    }
  }

/** Modifies its argument `map` so that there is no more than six records.
 *  Creates an `others` key if need be, which contains the _smallest_ items. */
void yatishPDF::NoMoreThan6 (Map4pie& map) {
    unsigned long mini;
    string key, others = _("others").ToStdString();
    while (map.size() > 6) {
        mini = ULONG_MAX;
        for (auto element : map) {
            if (element.first == others) continue;
            if (element.second < mini) {
                mini = element.second;
                key = element.first;
            }
        }
        map[others] += mini;
        map.erase ( map.find (key) );
    }
}
