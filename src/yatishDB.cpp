/***************************************************************
 * Name:      yatishDB.cpp
 * Purpose:   Code for the base class of yatish database controllers
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-04-15
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#include "yatishDB.h"

/** Must be defined in the same order as `enum tableID`.
 * Furthermore this order is consistent with the _yatish_ foreign key constraints
 * for SQL CREATE (DROP on the contrary, should be performed in reverse order).
 */
const char * yatishDB::tableName [] = {
    "client",
    "task",
    "tool",
    "project",
    "activity",
    "timeslot"
};

wxDatabase * yatishDB::masterDB = nullptr;

/** Sets up a (configuration) flux using its argument then calls `wxDatabase::GetDatabase()`.
 * \param configString
 * - if empty (""), the database credentials are read from the file `yatish.auth`
 * - otherwise they are read from the string itself
 * \return pointer to a `wxDatabase`, or `nullptr` if something went wrong
 *
 * If `configString = ""`, the function uses the _last_ valid credentials
 * found in `yatish.auth`; for instance:
 * ~~~
 * [SQLite]
 * database=yatish.sqlite
 * ;[MySQL]
 * ;server=<domain name or IP address>
 * ;database=<yatish database>
 * ;user=<MySQL/MariaDB user>
 * ;password=********
 * ~~~
 * is equivalent to calling the function with the non-empty argument
 * `"[SQLite]\ndatabase=yatish.sqlite"` because the MySQL account is commented out.
 */
wxDatabase * yatishDB::GetDatabase (const wxString& configString) {
    wxInputStream * configStream;
    wxDatabase * pDatabase;
    try {
        if ( configString.IsEmpty() ) {
            wxString configPath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFILE_SEP_PATH + "yatish.auth";
            if ( !wxFileName::FileExists (configPath) ) {
                wxString msg;
                msg.Printf (_("Authentication file '%s' not found"), configPath);
                throw ( wxDatabaseException (-1, msg) );
            }
            configStream = new wxFileInputStream (configPath);
            if ( !configStream->IsOk() ) {
                wxString msg;
                msg.Printf (_("Authentication file '%s' cannot be opened"), configPath);
                throw ( wxDatabaseException (-2, msg) );
            }
        } else {
            configStream = new wxStringInputStream (configString);
        }
        wxFileConfig config (*configStream);
        wxString err = wxEmptyString;
        pDatabase = wxDatabase::GetDatabase (config, &err);
        if (!pDatabase) {
            wxString msg;
            msg.Printf (_("Error while reading the authentication file:\n%s"), err);
            throw ( wxDatabaseException (-3, msg) );
        }
    }
    CATCH (nullptr)
    delete configStream;
    return pDatabase;
}

/** Returns `false` if any of the _yatish_ table is missings. */
bool yatishDB::TablesOk (wxDatabase * pDatabase) {
    return pDatabase->TableExists ("yatish_client")  &&
           pDatabase->TableExists ("yatish_project") &&
           pDatabase->TableExists ("yatish_task")    &&
           pDatabase->TableExists ("yatish_tool")    &&
           pDatabase->TableExists ("yatish_activity")&&
           pDatabase->TableExists ("yatish_timeslot");
}
