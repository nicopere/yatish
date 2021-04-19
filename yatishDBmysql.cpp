/***************************************************************
 * Name:      yatishDBmysql.cpp
 * Purpose:   Code for the mysql controller
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-04-16
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#include "wx_pch.h"
#include "yatishDBmysql.h"

#undef CATCH // avoids a warning before redefining
#define CATCH(returnValue) catch (wxDatabaseException& e) {\
 errorCode = e.GetErrorCode();\
 wxLogError ( "[%d] %s", errorCode, e.GetErrorMessage() );\
 return returnValue; }

wxDatabase * yatishDBmysql::slaveDB = nullptr;

/** Mainly connects to the MySQL database specified in `yatish.auth`
 *
 * (initializing private member `slaveDB`).
 *
 */
yatishDBmysql::yatishDBmysql () {
    wxASSERT_MSG (slaveDB == nullptr, "There can be only one instance of yatishDBmysql.");
    slaveDB = GetDatabase ("");
    if (!slaveDB) return;
    try {
        if (slaveDB->GetTypeName() != "MYSQL")
            throw ( wxDatabaseException (-4, _("Slave DB must be MySQL") ) );
        if ( !TablesOk (slaveDB) && !NewTables() )
            throw ( wxDatabaseException (-5, _("Yatish tables not created (MySQL)") ) );
    }
    catch (wxDatabaseException& e) {
        wxLogError ( "[%d] %s", e.GetErrorCode(), e.GetErrorMessage() );
        slaveDB->Close();
        delete slaveDB;
        slaveDB = nullptr;
    }
    errorCode = 0;
}

/** Creates the _yatish_ tables.
 * Warning! If any of the tables was already there, it is emptied.
 * \return `false` if something went wrong
 */
bool yatishDBmysql::NewTables () {
    if (!slaveDB) return false;
    try {
        if ( slaveDB->TableExists ("yatish_client") )
            slaveDB->RunQuery ("DELETE FROM yatish_client;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_client ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "name VARCHAR (20) NOT NULL UNIQUE,"
                               "PRIMARY KEY (id));");
        if ( slaveDB->TableExists ("yatish_project") )
            slaveDB->RunQuery ("DELETE FROM yatish_project;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_project ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "name VARCHAR (20) NOT NULL UNIQUE,"
                               "client_id INT NOT NULL,"
                               "PRIMARY KEY (id),"
                               "FOREIGN KEY (client_id) REFERENCES yatish_client (id)"
                               "ON DELETE CASCADE ON UPDATE CASCADE);");
        if ( slaveDB->TableExists ("yatish_task") )
            slaveDB->RunQuery ("DELETE FROM yatish_task;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_task ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "name VARCHAR (20) NOT NULL UNIQUE,"
                               "PRIMARY KEY (id));");
        if ( slaveDB->TableExists ("yatish_tool") )
            slaveDB->RunQuery ("DELETE FROM yatish_tool;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_tool ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "name VARCHAR (20) NOT NULL UNIQUE,"
                               "PRIMARY KEY (id));");
        if ( slaveDB->TableExists ("yatish_activity") )
            slaveDB->RunQuery ("DELETE FROM yatish_activity;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_activity ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "project_id INT NOT NULL,"
                               "task_id INT NOT NULL,"
                               "tool_id INT NOT NULL,"
                               "PRIMARY KEY (id),"
                               "UNIQUE (project_id,task_id,tool_id),"
                               "FOREIGN KEY (project_id) REFERENCES yatish_project (id)"
                               "ON DELETE CASCADE ON UPDATE CASCADE,"
                               "FOREIGN KEY (task_id) REFERENCES yatish_task (id)"
                               "ON DELETE CASCADE ON UPDATE CASCADE,"
                               "FOREIGN KEY (tool_id) REFERENCES yatish_tool (id)"
                               "ON DELETE CASCADE ON UPDATE CASCADE);");
        if ( slaveDB->TableExists ("yatish_timeslot") )
            slaveDB->RunQuery ("DELETE FROM yatish_timeslot;");
        else
            slaveDB->RunQuery ("CREATE TABLE yatish_timeslot ("
                               "id INT NOT NULL AUTO_INCREMENT,"
                               "start DATETIME,"
                               "stop DATETIME,"
                               "activity_id INT NOT NULL,"
                               "PRIMARY KEY (id),"
                               "FOREIGN KEY (activity_id) REFERENCES yatish_activity (id)"
                               "ON DELETE CASCADE ON UPDATE CASCADE);");
    }
    CATCH (false);
    return true;
}

yatishDBmysql::~yatishDBmysql () {
    if (!slaveDB) return;
    slaveDB->Close();
    delete slaveDB;
    slaveDB = nullptr;
}

/** Updates `slaveDB` with records of `masterDB` where the _sync_ field is not `'S'`.
 * Also sets the (local) _sync_ field to `'S'` when (remote) data were updated with no error.
 * \return wxDatabase error code if something went wrong (otherwise 0)
 */
int yatishDBmysql::Commit () {
    if (!slaveDB || !masterDB) return 0;
    Insert() && InsertProject() && InsertActivity() && InsertTimeslot() &&
    Update() && UpdateProject() && UpdateActivity() && UpdateTimeslot() &&
    Delete();
    return errorCode;
}

/** Uploads `masterDB` into `slaveDB`.
 * Warning! Former data in `slaveDB` (if any) are erased.
 * \return wxDatabase error code if something went wrong (otherwise 0)
 */
int yatishDBmysql::Upload () {
    if (!slaveDB || !masterDB) return 0;
    Commit() && //  first ensure that any locally modified records are cleared out (including local CASCADE...)
    EmptySlaveTables() && OutdateMasterTables() &&
    Insert() && InsertProject() && InsertActivity() && InsertTimeslot();
    return errorCode;
}

/** Downloads `slaveDB` into `masterDB`.
 * Warning! Former data in `masterDB` (if any) are erased.
 * \return wxDatabase error code if something went wrong (otherwise 0)
 */
int yatishDBmysql::Download () {
    if (!slaveDB || !masterDB) return 0;
    EmptyMasterTables() &&
    DownloadNames() && DownloadProject() && DownloadActivity() && DownloadTimeslot();
    return errorCode;
}

/** Empties all _yatish_ tables in `slaveDB`.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::EmptySlaveTables () {
    if (!slaveDB) return false;
    try {
        slaveDB->RunQuery ("DELETE FROM yatish_client;");
        slaveDB->RunQuery ("DELETE FROM yatish_project;");
        slaveDB->RunQuery ("DELETE FROM yatish_task;");
        slaveDB->RunQuery ("DELETE FROM yatish_tool;");
        slaveDB->RunQuery ("DELETE FROM yatish_activity;");
        slaveDB->RunQuery ("DELETE FROM yatish_timeslot;");
    }
    CATCH (false);
    errorCode = 0;
    return true;
}

/** Empties all _yatish_ tables in `masterDB`.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::EmptyMasterTables () {
    if (!masterDB) return false;
    try {
        masterDB->RunQuery ("DELETE FROM yatish_client;");
        masterDB->RunQuery ("DELETE FROM yatish_project;");
        masterDB->RunQuery ("DELETE FROM yatish_task;");
        masterDB->RunQuery ("DELETE FROM yatish_tool;");
        masterDB->RunQuery ("DELETE FROM yatish_activity;");
        masterDB->RunQuery ("DELETE FROM yatish_timeslot;");
    }
    CATCH (false);
    errorCode = 0;
    return true;
}

/** Sets the _sync_ field to 'I' in all records of all _yatish_ tables in `masterDB`.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::OutdateMasterTables () {
    if (!masterDB) return false;
    try {
        masterDB->RunQuery ("UPDATE yatish_client   SET sync = 'I';");
        masterDB->RunQuery ("UPDATE yatish_project  SET sync = 'I';");
        masterDB->RunQuery ("UPDATE yatish_task     SET sync = 'I';");
        masterDB->RunQuery ("UPDATE yatish_tool     SET sync = 'I';");
        masterDB->RunQuery ("UPDATE yatish_activity SET sync = 'I';");
        masterDB->RunQuery ("UPDATE yatish_timeslot SET sync = 'I';");
    }
    CATCH (false);
    errorCode = 0;
    return true;
}

/** Takes care of DELETEs in _yatish_ tables.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 *
 * N.B. We rely on the fact that the _id_ of a record is the same in both RDBMS (cf. Insert()).
 */
bool yatishDBmysql::Delete () {
    if (!slaveDB || !masterDB) return false;
    wxString sql;
    long id;
    for (int i = 0; i < 6; i++) {
        try {
            const char * n = tableName[i];
            sql.Printf("SELECT id FROM yatish_%s WHERE sync = 'D';", n);
            wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
            while ( results->Next() ) {
                id = results->GetResultLong (1);
                sql.Printf ("DELETE FROM yatish_%s WHERE id = %ld;", n, id);
                slaveDB->RunQuery (sql);
            }
            masterDB->CloseResultSet (results);
            sql.Printf("DELETE FROM yatish_%s WHERE sync = 'D';", n);
            masterDB->RunQuery (sql);
        }
        CATCH (false)
    }
    errorCode = 0;
    return true;
}

/** Takes care of INSERTs in _yatish_ tables with a single _name_ column.
 * The _id_ is also copied (we do not use remote AUTO_INCREMENT).
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 *
 * N.B. This function assumes `tableName` was defined with "simple" tables first.
 * \sa InsertProject() InsertActivity() InsertTimeslot()
 */
bool yatishDBmysql::Insert () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id;
    for (int i = 0; i < 3; i++) {
        try {
            const char * n = tableName[i];
            sql.Printf("SELECT id,name FROM yatish_%s WHERE sync = 'I';", n);
            wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
            while ( results->Next() ) {
                id = results->GetResultLong (1);
                name = results->GetResultString (2);
                sql.Printf ("INSERT INTO yatish_%s (id,name) VALUES (%ld,'%s');", n, id, name);
                slaveDB->RunQuery (sql);
            }
            masterDB->CloseResultSet (results);
            sql.Printf("UPDATE yatish_%s SET sync='S' WHERE sync = 'I';", n);
            masterDB->RunQuery (sql);
        }
        CATCH (false)
    }
    errorCode = 0;
    return true;
}

/** Downloads _yatish_ tables with a single _name_ column.
 * The _id_ is also copied (we do not use local AUTO_INCREMENT).
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 *
 * N.B. This function assumes `tableName` was defined with "simple" tables first.
 * \sa DownloadProject() DownloadActivity() DownloadTimeslot()
 */
bool yatishDBmysql::DownloadNames () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id;
    for (int i = 0; i < 3; i++) {
        try {
            const char * n = tableName[i];
            sql.Printf("SELECT id,name FROM yatish_%s;", n);
            wxDatabaseResultSet * results = slaveDB->RunQueryWithResults (sql);
            while ( results->Next() ) {
                id = results->GetResultLong (1);
                name = results->GetResultString (2);
                sql.Printf ("INSERT INTO yatish_%s (id,name,sync) VALUES (%ld,'%s','S');", n, id, name);
                masterDB->RunQuery (sql);
            }
            slaveDB->CloseResultSet (results);
        }
        CATCH (false)
    }
    errorCode = 0;
    return true;
}

/** Takes care of UPDATEs in _yatish_ tables with a single _name_ column.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 *
 * N.B. This function assumes `tableName` was defined with "simple" tables first.
 *
 * N.B. We rely on the fact that the _id_ of a record is the same in both RDBMS (cf. Insert()).
 * \sa UpdateProject() UpdateActivity() UpdateTimeslot()
 */
bool yatishDBmysql::Update () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id;
    for (int i = 0; i < 3; i++) {
        try {
            const char * n = tableName[i];
            sql.Printf("SELECT id,name FROM yatish_%s WHERE sync = 'U';", n);
            wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
            while ( results->Next() ) {
                id = results->GetResultLong (1);
                name = results->GetResultString (2);
                sql.Printf ("UPDATE yatish_%s SET name='%s' WHERE id = %ld;", n, name, id);
                slaveDB->RunQuery (sql);
            }
            masterDB->CloseResultSet (results);
            sql.Printf ("UPDATE yatish_%s SET sync='S' WHERE sync = 'U';", n);
            masterDB->RunQuery (sql);
        }
        CATCH (false)
    }
    errorCode = 0;
    return true;
}

/** Takes care of INSERTs in _yatish_project_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::InsertProject () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id, client_id;
    try {
        sql.Printf("SELECT id,name,client_id FROM yatish_project WHERE sync = 'I';");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            name = results->GetResultString (2);
            client_id = results->GetResultLong (3);
            sql.Printf ("INSERT INTO yatish_project (id,name,client_id)"
                        " VALUES (%ld,'%s',%ld);", id, name, client_id);
            slaveDB->RunQuery (sql);
        }
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_project SET sync='S' WHERE sync = 'I';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Downloads _yatish_project_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::DownloadProject () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id, client_id;
    try {
        sql.Printf("SELECT id,name,client_id FROM yatish_project;");
        wxDatabaseResultSet * results = slaveDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            name = results->GetResultString (2);
            client_id = results->GetResultLong (3);
            sql.Printf ("INSERT INTO yatish_project (id,name,client_id,sync)"
                        " VALUES (%ld,'%s',%ld,'S');", id, name, client_id);
            masterDB->RunQuery (sql);
        }
        slaveDB->CloseResultSet (results);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Takes care of UPDATEs in _yatish_project_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::UpdateProject () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, name;
    long id, client_id;
    try {
        sql.Printf("SELECT id,name,client_id FROM yatish_project WHERE sync = 'U';");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            name = results->GetResultString (2);
            client_id = results->GetResultLong (3);
            sql.Printf ("UPDATE yatish_project SET name='%s',client_id=%ld"
                        " WHERE id = %ld;", name, client_id, id);
            slaveDB->RunQuery (sql);
        }
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_project SET sync='S' WHERE sync = 'U';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Takes care of INSERTs in _yatish_activity_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::InsertActivity () {
    if (!slaveDB || !masterDB) return false;
    wxString sql;
    long id1, id2, id3, id4;
    try {
        sql.Printf("SELECT id,project_id,task_id,tool_id FROM yatish_activity WHERE sync = 'I';");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id1 = results->GetResultLong (1);
            id2 = results->GetResultLong (2);
            id3 = results->GetResultLong (3);
            id4 = results->GetResultLong (4);
            sql.Printf ("INSERT INTO yatish_activity (id,project_id,task_id,tool_id)"
                        " VALUES (%ld,%ld,%ld,%ld);", id1, id2, id3, id4);
            slaveDB->RunQuery (sql);
        }
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_activity SET sync='S' WHERE sync = 'I';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Downloads _yatish_activity_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::DownloadActivity () {
    if (!slaveDB || !masterDB) return false;
    wxString sql;
    long id1, id2, id3, id4;
    try {
        sql.Printf("SELECT id,project_id,task_id,tool_id FROM yatish_activity;");
        wxDatabaseResultSet * results = slaveDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id1 = results->GetResultLong (1);
            id2 = results->GetResultLong (2);
            id3 = results->GetResultLong (3);
            id4 = results->GetResultLong (4);
            sql.Printf ("INSERT INTO yatish_activity (id,project_id,task_id,tool_id,sync)"
                        " VALUES (%ld,%ld,%ld,%ld,'S');", id1, id2, id3, id4);
            masterDB->RunQuery (sql);
        }
        slaveDB->CloseResultSet (results);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Takes care of UPDATEs in _yatish_activity_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::UpdateActivity () {
    if (!slaveDB || !masterDB) return false;
    wxString sql;
    long id1, id2, id3, id4;
    try {
        sql.Printf("SELECT id,project_id,task_id,tool_id FROM yatish_activity WHERE sync = 'U';");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id1 = results->GetResultLong (1);
            id2 = results->GetResultLong (2);
            id3 = results->GetResultLong (3);
            id4 = results->GetResultLong (4);
            sql.Printf ("UPDATE yatish_activity SET project_id=%ld,task_id=%ld,tool_id=%ld"
                        " WHERE id = %ld;", id2, id3, id4, id1);
            slaveDB->RunQuery (sql);
        }
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_activity SET sync='S' WHERE sync = 'U';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Takes care of INSERTs in _yatish_timeslot_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::InsertTimeslot () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, start, stop;
    long id, activity_id;
    try {
        sql.Printf("SELECT id,start,stop,activity_id FROM yatish_timeslot WHERE sync = 'I';");
        // masterDB->RunQueryWithResults before the loop
        // is much faster than
        // masterDB->RunQuery inside the loop
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        wxPreparedStatement * prepareSlave = slaveDB->PrepareStatement (
            "INSERT INTO yatish_timeslot (id,start,stop,activity_id) VALUES (?,?,?,?);" );
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            start = results->GetResultString (2);
            stop = results->GetResultString (3);
            activity_id = results->GetResultLong (4);
            prepareSlave->SetParamLong (1, id);          // my wxDatabase
            prepareSlave->SetParamString (2, start);
            prepareSlave->SetParamString (3, stop);
            prepareSlave->SetParamLong (4, activity_id); // my wxDatabase
            prepareSlave->RunQuery();
        }
        slaveDB->CloseStatement (prepareSlave);
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_timeslot SET sync='S' WHERE sync='I';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Download _yatish_timeslot_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::DownloadTimeslot () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, start, stop;
    long id, activity_id;
    try {
        masterDB->BeginTransaction();
        sql.Printf("SELECT id,start,stop,activity_id FROM yatish_timeslot;");
        wxDatabaseResultSet * results = slaveDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            start = results->GetResultDate (2) .FormatISOCombined (' ');
            stop = results->GetResultDate (3) .FormatISOCombined (' ');
            activity_id = results->GetResultLong (4);
            sql.Printf ("INSERT INTO yatish_timeslot (id,start,stop,activity_id,sync)"
                        " VALUES (%ld,'%s','%s',%ld,'S');", id, start, stop, activity_id);
            masterDB->RunQuery (sql);
        }
        slaveDB->CloseResultSet (results);
        masterDB->Commit();
    }
    CATCH (false)
    errorCode = 0;
    return true;
}

/** Takes care of UPDATEs in _yatish_timeslot_.
 * The error code from the wxDatabase library (if any) is stored in `errorCode` (private member).
 * \return `false` if something went wrong
 */
bool yatishDBmysql::UpdateTimeslot () {
    if (!slaveDB || !masterDB) return false;
    wxString sql, start, stop;
    long id, activity_id;
    try {
        sql.Printf("SELECT id,start,stop,activity_id FROM yatish_timeslot WHERE sync = 'U';");
        wxDatabaseResultSet * results = masterDB->RunQueryWithResults (sql);
        while ( results->Next() ) {
            id = results->GetResultLong (1);
            start = results->GetResultString (2);
            stop = results->GetResultString (3);
            activity_id = results->GetResultLong (4);
            sql.Printf ("UPDATE yatish_timeslot SET start='%s',stop='%s',activity_id=%ld"
                        " WHERE id = %ld;", start, stop, activity_id, id);
            slaveDB->RunQuery (sql);
        }
        masterDB->CloseResultSet (results);
        sql.Printf ("UPDATE yatish_timeslot SET sync='S' WHERE sync = 'U';");
        masterDB->RunQuery (sql);
    }
    CATCH (false)
    errorCode = 0;
    return true;
}
