/********************************************************************
 * Name:      yatishDBsqlite.cpp
 * Purpose:   Implements the sqlite controller
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-03-09
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#include "yatishDBsqlite.h"

/** Mainly connects to the `yatish.sqlite` database
 *
 * (initializing protected member `yatishDB::masterDB`).
 */
yatishDBsqlite::yatishDBsqlite () {
    filter = wxEmptyString;
    limitRow = false; rowLimit = 100;
    wxASSERT_MSG (masterDB == nullptr, "There can be only one instance of yatishDBsqlite.");
#ifdef NDEBUG
    wxString databasePath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFILE_SEP_PATH + "yatish.sqlite";
    databasePath.Replace ("\\", "\\\\" ); // need to escape (Windows) anti-slashes
#else
    wxString databasePath = "yatish.sqlite";
#endif
    masterDB = GetDatabase ("[SQLite]\ndatabase=" + databasePath);
    if (!masterDB) {
        wxMessageBox (_("You are probably using Yatish for the first time...\n"
                        "Please ignore error messages and read\n"
                        "\"Getting started\" in the User guide (F1)"),
                      _("Startup procedure completed?"), wxOK);
        return;
    }
    try {
        if (masterDB->GetTypeName() != "SQLITE")
            throw ( wxDatabaseException (-4, _("Master DB must be SQLite") ) );
        if ( !TablesOk (masterDB) )
            throw ( wxDatabaseException (-5, _("Yatish tables not found (SQLite)") ) );
        masterDB->RunQuery ("PRAGMA foreign_keys = ON;");
    }
    catch (wxDatabaseException& e) {
        wxLogError ( "[%d] %s", e.GetErrorCode(), e.GetErrorMessage() );
        masterDB->Close();
        delete masterDB;
        masterDB = nullptr;
    }
}

yatishDBsqlite::~yatishDBsqlite () {
    if (!masterDB) return;
    StopTimeslot(); // in case yatish is closed before stop button is pressed
    masterDB->Close();
    delete masterDB;
}

/** Fills a `wxChoice`.
 * Corresponding values of the SQL _id_ field are stored for future reference.
 * \param choices the control to fill
 * \param tid either `client_tid`, `project_tid`, `task_tid` or `tool_tid`
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::FillChoice (wxChoice * choices, tableID tid) {
    if (!masterDB) return false;
    wxArrayLong * ids;
    wxString sql ("SELECT id,name FROM yatish_");
    switch (tid) {
        case client_tid:
            sql += "client WHERE sync <> 'D' ORDER BY name;";
            ids = &clientIDs;
            break;
        case project_tid:
            sql += "project WHERE sync <> 'D' ORDER BY name;";
            ids = &projectIDs;
            break;
        case task_tid:
            sql += "task WHERE sync <> 'D' ORDER BY name;";
            ids = &taskIDs;
            break;
        case tool_tid:
            sql += "tool WHERE sync <> 'D' ORDER BY name;";
            ids = &toolIDs;
            break;
        default:
            return false;
    }
    ids->Empty();
    choices->Clear();
    try {
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            ids->Add ( results->GetResultLong (1) );
            choices->Append ( results->GetResultString (2) );
        }
        masterDB->CloseResultSet (results);
    }
    CATCH (false)
    ids->Shrink();
    return true;
}

/** Finds the proper index for selection in a `wxChoice`.
 * The selection corresponds to a given record in the refering table
 * (cf. foreign keys in the _yatish_ database schema).
 * \param tid either `client_tid`, `project_tid`, `task_tid` or `tool_tid`
 * \param id of the foreign key to read from the refering table
 * \return the `wxChoice` index (or wxNOT_FOUND in case of problem)
 */
int yatishDBsqlite::ChoiceSelector (tableID tid, long id) {
    if (!masterDB) return wxNOT_FOUND;
    wxArrayLong * ids;
    tableID refering_tid;
    switch (tid) {
        case client_tid:
            ids = &clientIDs;
            refering_tid = project_tid;
            break;
        case project_tid:
            ids = &projectIDs;
            refering_tid = activity_tid;
            break;
        case task_tid:
            ids = &taskIDs;
            refering_tid = activity_tid;
            break;
        case tool_tid:
            ids = &toolIDs;
            refering_tid = activity_tid;
            break;
        default:
            return wxNOT_FOUND;
    }
    long refered_id;
    try {
        wxString sql;
        sql.Printf ("SELECT %s_id FROM yatish_%s WHERE id = %ld;",
                    tableName[tid], tableName[refering_tid], id);
        refered_id = masterDB->GetSingleResultLong (sql, 1);
    }
    CATCH (wxNOT_FOUND)
    return ids->Index (refered_id);
}

/** Starts a new row in the timeslot table.
 * Also inserts the corresponding row in the activity table, if necessary.
 * \param project,task,tool 0-based index of the item currently selected in panel #1
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::StartTimeslot (int project, int task, int tool) {
    if (!masterDB) return false;
    int projectID = projectIDs[project],
        taskID = taskIDs[task],
        toolID = toolIDs[tool];
    wxString sql;
    sql.Printf ("SELECT id FROM yatish_activity"
                " WHERE project_id = %d AND task_id = %d AND tool_id = %d;",
                projectID, taskID, toolID);
    try {
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        if ( !results->Next() ) {
            wxString sql2;
            sql2.Printf ("INSERT INTO yatish_activity (project_id,task_id,tool_id,sync)"
                         " VALUES (%d,%d,%d,'I');",
                         projectID, taskID, toolID);
            masterDB->CloseResultSet (results);
            masterDB->RunQuery (sql2);
            results = masterDB->RunQueryWithResults (sql);
            results->Next();
        }
        long activityID = results->GetResultLong (1);
        masterDB->CloseResultSet (results);
        sql.Printf ("INSERT INTO yatish_timeslot (start,activity_id,sync)"
                    " VALUES (datetime('now'),%ld,'I');", activityID); // datetime('now'): SQLite specific (UTC)
        masterDB->RunQuery (sql);
        results = masterDB->RunQueryWithResults ("SELECT id FROM yatish_timeslot WHERE stop IS NULL;");
        results->Next(); // there should be one and only one...
        currentTimeslotID = results->GetResultLong (1);
        masterDB->CloseResultSet (results);
    }
    CATCH (false)
    return true;
}

/** Stops current timeslot.
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::StopTimeslot () {
    if (!masterDB) return false;
    try {
        wxString sql;
        sql.Printf ("UPDATE yatish_timeslot SET stop=datetime('now')"
                    " WHERE id = %ld AND stop IS NULL;", currentTimeslotID);
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}

/** Determines the number _n_ of unfinished timeslots.
 * \return -1 in case of problem (including _n_ > 1)
 */
int yatishDBsqlite::RunningTimeslots () {
    if (!masterDB) return -1;
    int n;
    try {
        wxString sql ("SELECT id,COUNT(*) FROM yatish_timeslot WHERE stop IS NULL;");
        currentTimeslotID = masterDB->GetSingleResultLong (sql, 1);
        n = masterDB->GetSingleResultInt (sql, 2);
    }
    CATCH (-1)
    return n;
}

/** Fills a wxListCtrl.
 * The SQL _id_ is stored as the row data.
 * \param lst the control to fill
 * \param tid the type of data to fetch
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::FillList (wxListCtrl * lst, tableID tid) {
    if (!masterDB) return false;
    int colmin, colmax = lst->GetColumnCount();
    wxString sql ("SELECT ");
    switch (tid) {
        case client_tid:
            if (colmax != 1) return false;
            sql += "id,name FROM yatish_client WHERE sync <> 'D';";
            break;
        case project_tid:
            if (colmax != 2) return false;
            sql += "p.id,p.name,c.name FROM yatish_project AS p"
                   " INNER JOIN yatish_client AS c ON p.client_id = c.id"
                   " WHERE p.sync <> 'D'";
            sql += filter;
            sql += ";";
            break;
        case task_tid:
            if (colmax != 1) return false;
            sql += "id,name FROM yatish_task WHERE sync <> 'D';";
            break;
        case tool_tid:
            if (colmax != 1) return false;
            sql += "id,name FROM yatish_tool WHERE sync <> 'D';";
            break;
        case activity_tid:
            if (colmax != 4) return false;
            sql += "a.id,p.name,c.name,tk.name,tl.name"
                   " FROM (((yatish_activity AS a"
                   " INNER JOIN yatish_project AS p ON a.project_id = p.id)"
                   " INNER JOIN yatish_client AS c ON p.client_id = c.id)"
                   " INNER JOIN yatish_task AS tk ON a.task_id = tk.id)"
                   " INNER JOIN yatish_tool AS tl ON a.tool_id = tl.id"
                   " WHERE a.sync <> 'D'";
            sql += filter;
            sql += ";";
            break;
        case timeslot_tid:
            if (colmax != 6) return false;
            sql.Printf ("SELECT t.id,t.start,t.stop,p.name,c.name,tk.name,tl.name"
                        " FROM ((((yatish_timeslot AS t"
                        " INNER JOIN yatish_activity AS a ON t.activity_id = a.id)"
                        " INNER JOIN yatish_project AS p ON a.project_id = p.id)"
                        " INNER JOIN yatish_client AS c ON p.client_id = c.id)"
                        " INNER JOIN yatish_task AS tk ON a.task_id = tk.id)"
                        " INNER JOIN yatish_tool AS tl ON a.tool_id = tl.id"
                        " WHERE t.sync <> 'D' AND t.start BETWEEN '%s' AND '%s'"
                        , firstDay, lastDay);
            sql += filter;
            if (limitRow)
              sql += wxString::Format (" ORDER BY t.id DESC LIMIT %d;", rowLimit);
            else
              sql += " ORDER BY t.id DESC;";
            break;
        default:
            return false;
    }
    // { for timeslot_tid only...
    wxTimeSpan span;
    slotCount = 0;
    totalSpan = wxTimeSpan::Hours (0);
    // }
    try {
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        long row = 0,
             row_index; // appears to be necessary...
        while ( results->Next() ) {
            if (tid == timeslot_tid) {
                wxDateTime start = results->GetResultDate (2), stop = results->GetResultDate (3);
                start.MakeFromUTC();
                // update first item of the row
                row_index = lst->InsertItem ( row++, start.FormatISODate() );
                if ( stop.IsValid() ) {
                    stop.MakeFromUTC();
                    span = stop - start;
                    slotCount++; totalSpan += span;
                    // update second item of the row
                    lst->SetItem ( row_index, 1, span.Format ("%H:%M:%S") );
                }
                colmin = 2;
            } else {
                // update first item of the row
                row_index = lst->InsertItem ( row++, results->GetResultString (2) );
                colmin = 1;
            }
            // update remaining items
            for (int col = colmin; col < colmax; col++)
                // +1 because wxDatabase indexes are 1-based, and +1 to skip the id
                lst->SetItem ( row_index, col, results->GetResultString (col + 2) );
            // store the SQL id of the row (which is not the row index)
            lst->SetItemData ( row_index, results->GetResultLong (1) );
        }
        masterDB->CloseResultSet (results);
    }
    CATCH (false)
    return true;
}

/** Fills a `RawData` (typedefined in yatishTypes.h).
 * \param v where to write (reference)
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::FillPlotData (RawData& v) {
    if (!masterDB) return false;
    wxString sql ("SELECT t.start,t.stop,p.name,c.name,tk.name,tl.name FROM yatish_timeslot t"
                  " INNER JOIN yatish_activity a ON t.activity_id = a.id"
                  " INNER JOIN yatish_project p ON a.project_id = p.id"
                  " INNER JOIN yatish_client c ON p.client_id = c.id"
                  " INNER JOIN yatish_task tk ON a.task_id = tk.id"
                  " INNER JOIN yatish_tool tl ON a.tool_id = tl.id"
                  " WHERE stop IS NOT NULL ORDER BY start;");
    try {
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        RawRecord record;
        while ( results->Next() ) {
            record.start   = results->GetResultDate   (1);
            record.stop    = results->GetResultDate   (2);
            record.project = results->GetResultString (3);
            record.client  = results->GetResultString (4);
            record.task    = results->GetResultString (5);
            record.tool    = results->GetResultString (6);
            v.push_back (record);
        }
        masterDB->CloseResultSet (results);
    }
    CATCH (false)
    return true;
}

/** Adds a condition to the WHERE clause of FillList().
 * \param tid the table used to build the new condition
 * \param choice the item in this table (as returned from a previously filled `wxChoice`)
 */
void yatishDBsqlite::AddToFilter (tableID tid, int choice) {
    wxString sqlAnd;
    switch (tid) {
        case client_tid:
            sqlAnd.Printf (" AND c.id = %ld", clientIDs[choice]);
            break;
        case project_tid:
            sqlAnd.Printf (" AND p.id = %ld", projectIDs[choice]);
            break;
        case task_tid:
            sqlAnd.Printf (" AND tk.id = %ld", taskIDs[choice]);
            break;
        case tool_tid:
            sqlAnd.Printf (" AND tl.id = %ld", toolIDs[choice]);
            break;
      default:
            return;
    }
    filter += sqlAnd;
}

/** Adds a condition to the WHERE clause of FillList().
 * \param activityID the foreign key
 * \note This overload is relevant to the _timeslot_ table only (SQL error otherwise).
 */
void yatishDBsqlite::AddToFilter (long activityID) {
    wxString sqlAnd;
    sqlAnd.Printf (" AND activity_id = %ld", activityID);
    filter += sqlAnd;
}

/** Returns the total duration of currently viewed timeslots (and their count).
 * \param[out] ts where the total duration shall be written
 * \return the timeslot count
 */
long yatishDBsqlite::FilteredTotal (wxTimeSpan& ts) const {
    if (slotCount)
        ts = totalSpan;
    else
        ts = wxTimeSpan::Hours (0);
    return slotCount;
}

/** Writes the total and average durations of currently viewed timeslots.
 * One work day amounts to 7 hours.
 * \return a properly formatted `wxString`, or `wxEmptyString`
 *         if the currently viewed table is not _yatish_timeslot_
 */
wxString yatishDBsqlite::FilteredTotalFormatted () {
    if (!slotCount) return wxEmptyString;
    double totalSeconds = totalSpan.GetSeconds().ToDouble();
    double totalDays, averageHours;
    totalDays = totalSeconds / 3600.; // hours still...
    averageHours = totalDays / slotCount;
    totalDays /= 7.;                  // ...nowadays!
    return wxString::Format(_("SUM: %.1f days | AVG: %.1f hours (x%ld)"),
                            totalDays, averageHours, slotCount);
}

/** Sets private member `firstDay` (for future SQL queries).
 * `firstDay` is a UTC time string in ISO format.
 * \sa SetLastDay()
 */
void yatishDBsqlite::SetFirstDay (const wxDateTime& dt) {
    firstDay = dt.ToUTC().FormatISOCombined();
    wxFirstDay = dt; // stores a copy in case somebody needs it (yatishPDF...)
}

/** Sets private member `lastDay` (for future SQL queries).
 * `lastDay` is a UTC time string in ISO format.
 * \sa SetFirstDay()
 */
void yatishDBsqlite::SetLastDay (const wxDateTime& dt) {
    wxLastDay = dt; // stores a copy in case somebody needs it (yatishPDF...)
    lastDay = ( dt + wxDateSpan::Day() ).ToUTC().FormatISOCombined();
}

/** Obtains the minimum time in column _start_ from currently selected rows of table _yatish_timeslot_.
 * This time is provided in the local timezone.
 * \return `Now()` if something went wrong
 */
wxDateTime yatishDBsqlite::First () {
    wxDateTime dt = wxDateTime::Now();
    if (!masterDB) return dt;
    wxString ans;
    try {
        wxString sql ("SELECT MIN(start) FROM ((((yatish_timeslot AS t"
                      " INNER JOIN yatish_activity AS a ON t.activity_id = a.id)"
                      " INNER JOIN yatish_project AS p ON a.project_id = p.id)"
                      " INNER JOIN yatish_client AS c ON p.client_id = c.id)"
                      " INNER JOIN yatish_task AS tk ON a.task_id = tk.id)"
                      " INNER JOIN yatish_tool AS tl ON a.tool_id = tl.id"
                      " WHERE t.sync <> 'D'");
        sql += filter;
        sql += ";";
        ans = masterDB->GetSingleResultString (sql, 1);
    }
    CATCH (dt)
    dt.ParseISOCombined (ans, ' ');
    return dt.MakeFromUTC();
}

/** Obtains the maximum time in column _start_ from currently selected rows of table _yatish_timeslot_.
 * This time is provided in the local timezone.
 * \return `Now()` if something went wrong
 */
wxDateTime yatishDBsqlite::Last () {
    wxDateTime dt = wxDateTime::Now();
    if (!masterDB) return dt;
    wxString ans;
    try {
         wxString sql ("SELECT MAX(start) FROM ((((yatish_timeslot AS t"
                      " INNER JOIN yatish_activity AS a ON t.activity_id = a.id)"
                      " INNER JOIN yatish_project AS p ON a.project_id = p.id)"
                      " INNER JOIN yatish_client AS c ON p.client_id = c.id)"
                      " INNER JOIN yatish_task AS tk ON a.task_id = tk.id)"
                      " INNER JOIN yatish_tool AS tl ON a.tool_id = tl.id"
                      " WHERE t.sync <> 'D'");
        sql += filter;
        sql += ";";
        ans = masterDB->GetSingleResultString (sql, 1);
    }
    CATCH (dt)
    dt.ParseISOCombined (ans, ' ');
    return dt.MakeFromUTC();
}

/** Reads the last _activity_id_ in _yatish_timeslot_.
 * \return wxNOT_FOUND if table is empty
 */
long yatishDBsqlite::LastActivity () {
    long id = wxNOT_FOUND;
    if (!masterDB) return id;
    try {
        wxString sql ("SELECT activity_id FROM yatish_timeslot ORDER BY start DESC LIMIT 1;");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        if ( results->Next() ) id = results->GetResultLong (1);
        masterDB->CloseResultSet (results);
    }
    CATCH (id)
    return id;
}

/** Reads the _activity_id_ in a record of _yatish_timeslot_.
 * \param id the record to read
 * \return wxNOT_FOUND if table is empty
 */
long yatishDBsqlite::Activity (long id) {
    long rid = wxNOT_FOUND;
    if (!masterDB) return rid;
    try {
        wxString sql = wxString::Format("SELECT activity_id FROM yatish_timeslot WHERE id=%ld;", id);
        rid = masterDB->GetSingleResultLong (sql, 1);
    }
    CATCH (rid)
    return rid;
}

/** Marks a local record for deletion.
 * Actually deletes it if its _sync_ status was 'I'.
 * \param tid Which table?
 * \param id Which record?
 * \return `false` if something went wrong or deletion was cancelled
 */
bool yatishDBsqlite::Delete (tableID tid, long id) {
    if (!masterDB) return false;
    if ( tid != timeslot_tid &&
         wxMessageBox ( _("Owing to foreign key constraints\nin the Yatish database,"
                         "\nrecords refering to this item\nwill also be deleted."),
                        _("Confirm deletion"),
                        wxICON_EXCLAMATION|wxOK|wxCANCEL|wxCANCEL_DEFAULT )
         == wxCANCEL ) return false;
    wxString sql, status;
    try {
        sql.Printf ("SELECT sync FROM yatish_%s WHERE id = %ld;", tableName[tid], id);
        status = masterDB->GetSingleResultString(sql, 1);
    }
    CATCH (false)
    if (status == 'I')
        sql.Printf ("DELETE FROM yatish_%s WHERE id = %ld;", tableName[tid], id);
    else
        sql.Printf ("UPDATE yatish_%s SET sync='D' WHERE id = %ld;", tableName[tid], id);
    try {
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}

/** Reads a `wxString` from the _name_ column.
 * \param tid Which table?
 * \param id Which record?
 * \return "" if something went wrong
 */
wxString yatishDBsqlite::ReadName (tableID tid, long id) {
    if (!masterDB) return "";
    try {
        wxString sql;
        sql.Printf ("SELECT name FROM yatish_%s WHERE id = %ld;", tableName[tid], id);
        return masterDB->GetSingleResultString (sql, 1);
    }
    CATCH ("")
}

/** Reads the _start_ and _stop_ fields of a _yatish_timeslot_ record.
 * \param id Which record?
 * \param dt1 where to write the _start_ value
 * \param dt2 where to write the _stop_ value
 * \return `false` if something went wrong (or activity still running)
 */
bool yatishDBsqlite::ReadDates (long id, wxDateTime& dt1, wxDateTime& dt2) {
    if (!masterDB) return false;
    try {
        wxString sql;
        sql.Printf ("SELECT start,stop FROM yatish_timeslot WHERE id = %ld;", id);
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        if ( !results->Next() ) {
            masterDB->CloseResultSet (results);
            return false;
        }
        dt1 = results->GetResultDate (1); dt2 = results->GetResultDate (2);
        masterDB->CloseResultSet (results);
    }
    CATCH (false)
    dt1.MakeFromUTC();
    if ( !dt2.IsValid() ) return false;
    dt2.MakeFromUTC();
    return true;
}

/** Modifies or creates a record with only one field (called _name_).
 * \param tid Which table?
 * \param id Which record? __A new record is created if `id == wxNOT_FOUND`.__
 * \param str the new _name_
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::RecordName (tableID tid, long id, const wxString& str) {
    if (!masterDB) return false;
    if (tid == project_tid || tid == activity_tid || tid == timeslot_tid) return false;
    try {
        wxString sql, tbl = tableName[tid], sync;
        if (id == wxNOT_FOUND)
            sql.Printf ("INSERT INTO yatish_%s (name,sync) VALUES ('%s','I');", tbl, str);
        else {
            sql.Printf ("SELECT sync FROM yatish_%s WHERE id = %ld", tbl, id);
            sync = masterDB->GetSingleResultString (sql, 1);
            if (sync == 'I')  // don't switch to 'U' state before it is synchronized
                sql.Printf ("UPDATE yatish_%s SET name='%s'"
                            " WHERE id = %ld;", tbl, str, id);
            else
                sql.Printf ("UPDATE yatish_%s SET name='%s',sync='U'"
                            "WHERE id = %ld;", tbl, str, id);
        }
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}

/** Modifies or creates a record in the _yatish_project_ table.
 * \param id Which record? __A new record is created if `id == wxNOT_FOUND`.__
 * \param str the new _name_
 * \param client_choice index selected in a previously filled `wxChoice`
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::RecordProject (long id, const wxString& str, int client_choice) {
    if (!masterDB) return false;
    try {
        wxString sql, sync;
        int clientID = clientIDs[client_choice];
        if (id == wxNOT_FOUND)
            sql.Printf ("INSERT INTO yatish_project (name,client_id,sync) VALUES ('%s',%d,'I');",
                        str, clientID);
        else {
            sql.Printf ("SELECT sync FROM yatish_project WHERE id = %ld", id);
            sync = masterDB->GetSingleResultString (sql, 1);
            if (sync == 'I')  // don't switch to 'U' state before it is synchronized
              sql.Printf ("UPDATE yatish_project SET name='%s',client_id=%d"
                          " WHERE id = %ld;", str, clientID, id);
            else
              sql.Printf ("UPDATE yatish_project SET name='%s',client_id=%d,sync='U'"
                          " WHERE id = %ld;", str, clientID, id);
        }
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}

/** Modifies or creates a record in the _yatish_activity_ table.
 * \param id Which record? __A new record is created if `id == wxNOT_FOUND`.__
 * \param project,task,tool indexes selected in previously filled `wxChoice`s
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::RecordActivity (long id, int project, int task, int tool) {
    if (!masterDB) return false;
    try {
        wxString sql, sync;
        int projectID = projectIDs[project],
            taskID    = taskIDs[task],
            toolID    = toolIDs[tool];
        if (id == wxNOT_FOUND)
            sql.Printf ("INSERT INTO yatish_activity (project_id,task_id,tool_id,sync)"
                        " VALUES (%d,%d,%d,'I');", projectID, taskID, toolID);
        else {
            sql.Printf ("SELECT sync FROM yatish_activity WHERE id = %ld", id);
            sync = masterDB->GetSingleResultString (sql, 1);
            if (sync == 'I')  // don't switch to 'U' state before it is synchronized
              sql.Printf ("UPDATE yatish_activity SET project_id=%d,task_id=%d,tool_id=%d"
                          " WHERE id = %ld;", projectID, taskID, toolID, id);
            else
              sql.Printf ("UPDATE yatish_activity SET project_id=%d,task_id=%d,tool_id=%d,sync='U'"
                          " WHERE id = %ld;", projectID, taskID, toolID, id);
        }
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}

/** Modifies or creates a record in the _yatish_timeslot_ table.
 * Also inserts the corresponding row in the activity table, if necessary.
 * \sa StartTimeslot()
 * \param id Which record? __A new record is created if `id == wxNOT_FOUND`.__
 * \param dt1,dt2 the new _start_ and _stop_
 * \param project,task,tool indexes selected in previously filled `wxChoice`s
 * \return `false` if something went wrong
 */
bool yatishDBsqlite::RecordTimeslot (long id,
                                     const wxDateTime& dt1, const wxDateTime& dt2,
                                     int project, int task, int tool) {
    if (!masterDB) return false;
    wxString start = dt1.ToUTC().FormatISOCombined(' ');
    wxString stop  = dt2.ToUTC().FormatISOCombined(' ');
    int projectID = projectIDs[project],
        taskID = taskIDs[task],
        toolID = toolIDs[tool];
    wxString sql, sync;
    sql.Printf ("SELECT id FROM yatish_activity"
                " WHERE project_id = %d AND task_id = %d AND tool_id = %d;",
                projectID, taskID, toolID);
    try {
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        if ( !results->Next() ) {
            wxString sql2;
            sql2.Printf ("INSERT INTO yatish_activity (project_id,task_id,tool_id,sync)"
                         " VALUES (%d,%d,%d,'I');",
                         projectID, taskID, toolID);
            masterDB->CloseResultSet (results);
            masterDB->RunQuery (sql2);
            results = masterDB->RunQueryWithResults (sql);
            results->Next();
        }
        long activityID = results->GetResultLong (1);
        masterDB->CloseResultSet (results);
        if (id == wxNOT_FOUND)
            sql.Printf ("INSERT INTO yatish_timeslot (start,stop,activity_id,sync)"
                        " VALUES ('%s','%s',%ld,'I');", start, stop, activityID);
        else {
            sql.Printf ("SELECT sync FROM yatish_timeslot WHERE id = %ld", id);
            sync = masterDB->GetSingleResultString (sql, 1);
            if (sync == 'I')  // don't switch to 'U' state before it is synchronized
                sql.Printf ("UPDATE yatish_timeslot SET start='%s',stop='%s',activity_id=%ld"
                            " WHERE id = %ld;", start, stop, activityID, id);
            else
                sql.Printf ("UPDATE yatish_timeslot SET start='%s',stop='%s',activity_id=%ld,sync='U'"
                           " WHERE id = %ld;", start, stop, activityID, id);
        }
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    return true;
}
