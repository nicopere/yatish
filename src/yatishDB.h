/********************************************************************
 * Name:      yatishDB.h
 * Purpose:   Declares the base class of yatish database controllers
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-04-15
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

#ifndef YATISHDB_H
#define YATISHDB_H

enum tableID {
    client_tid,
    task_tid,
    tool_tid,
    project_tid,
    activity_tid,
    timeslot_tid
};

#define CATCH(returnValue) catch (wxDatabaseException& e) {\
 wxLogError ( "[%d] %s", e.GetErrorCode(), e.GetErrorMessage() );\
 return returnValue; }

/** Provides a few basic methods and (static) members to interact with _yatish_ tables.
 * `yatishDB` and its daugters potentially raise `wxDatabaseException`s.
 * The list of _yatish_ error codes is centralized here for reference:
 *
 * Error code | Raised by | Error message
 * :--------: | --------: | :------------
 * -1 | yatishDB::GetDatabase | Authentication file not found
 * -2 | yatishDB::GetDatabase | Authentication file cannot be opened
 * -3 | yatishDB::GetDatabase | Error while reading the authentication file
 * -4 | yatishDBsqlite::yatishDBsqlite | Master DB must be SQLite
 * -4 | yatishDBmysql::yatishDBmysql | Slave DB must be MySQL
 * -5 | yatishDBsqlite::yatishDBsqlite | Yatish tables not found
 * -5 | yatishDBmysql::yatishDBmysql | Yatish tables not created
 *
 * (error codes from the wxDatabase library itself are positive...).
 */
class yatishDB {
    public:
        static const char * tableName [];
    protected:
        static wxDatabase * masterDB;
        wxDatabase * GetDatabase (const wxString&);
        bool TablesOk (wxDatabase *);
};

#endif // YATISHDB_H
