/********************************************************************
 * Name:      yatishDBsqlite.h
 * Purpose:   Declares a sqlite controller
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-03-09
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHDBSQLITE_H
#define YATISHDBSQLITE_H

#include "wx_pch.h"
#include "yatishDB.h"
#include "yatishTypes.h"

/** Interacts with _yatish_ tables in a SQLite database.
 * Cf. the application example distributed with the wxDatabase library.
 *
 * ### [Database schema](../../sql/yatish_tables.pdf)
 * The _sync_ field of each table only exists in the local (SQlite) database,
 * with values among:
 * - __S__ the row is _synchronized_ with the remote (MySQL/MariaDB) database
 * - __I__ the row was _inserted_ in the local table (and needs publishing to the remote DB)
 * - __U__ the row was _updated_ in the local table (and needs publishing to the remote DB)
 * - __D__ the row was _deleted_ in the local table (and needs publishing to the remote DB)
 *
 * ### Timezone management
 * - The timestamps are generated locally by SQLite's `date(`'`now`'`)`.
 * Such timestamps are stored by SQLite as TEXT fields in the UTC timezone
 * (i.e. we don't use `date(`'`now`'`,`'`localtime`'`)`).
 * - The SQL datatype used for the MySQL/MariaDB server is DATETIME: thus a timestamp
 * is not modified by the timezone the server is running in
 * (as would be the case with the TIMESTAMP type).
 * - This choice means that the application does not need to be in the same timezone
 * as the server and can also move from a timezone to another one.
 * The drawback is that formatting a timestamp in local time (if need be)
 * must be performed by the application itself. \sa ReadDates()
 */
class yatishDBsqlite : public yatishDB {
    public:
        yatishDBsqlite ();
        ~yatishDBsqlite ();
        bool FillChoice (wxChoice *, tableID);
        int ChoiceSelector (tableID, long);
        bool StartTimeslot (int, int, int);
        bool StopTimeslot ();
        int RunningTimeslots ();
        void SetLimit (bool b, int i) { limitRow = b; rowLimit = i; }
        bool FillList (wxListCtrl *, tableID);
        bool FillPlotData (RawData&);
        void AddToFilter (tableID, int);
        void AddToFilter (long);
        wxString GetFilter () const { return filter; };
        void ClearFilter () { filter.Clear(); }
        long FilteredTotal (wxTimeSpan &) const;
        wxString FilteredTotalFormatted ();
        void SetFirstDay (const wxDateTime&);
        void SetLastDay (const wxDateTime&);
        wxDateTime GetFirstDay () const { return wxFirstDay; }
        wxDateTime GetLastDay () const { return wxLastDay; }
        wxDateTime First ();
        wxDateTime Last ();
        long LastActivity ();
        long Activity (long);
        bool Delete (tableID, long);
        wxString ReadName (tableID, long);
        bool ReadDates (long, wxDateTime&, wxDateTime&);
        bool RecordName (tableID, long, const wxString&);
        bool RecordProject (long, const wxString&, int);
        bool RecordActivity (long, int, int, int);
        bool RecordTimeslot (long, const wxDateTime&, const wxDateTime&, int, int, int);
    private:
        bool limitRow;
        int rowLimit;
        long currentTimeslotID, slotCount;
        wxArrayLong clientIDs, projectIDs, taskIDs, toolIDs;
        wxString firstDay, lastDay, filter;
        wxDateTime wxFirstDay, wxLastDay;
        wxTimeSpan totalSpan;
};

#endif // YATISHDBSQLITE_H
