/***************************************************************
 * Name:      yatishDBmysql.h
 * Purpose:   Defines a mysql controller
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-04-16
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#ifndef YATISHDBMYSQL_H
#define YATISHDBMYSQL_H

#include <wx/listctrl.h>
#include "yatishDB.h"

/** Interacts with _yatish_ tables in a MySQL/MariaDB database.
 * \sa yatishDBsqlite
 */
class yatishDBmysql : public yatishDB {
    public:
        yatishDBmysql ();
        ~yatishDBmysql ();
        bool IsOk () { return slaveDB != nullptr; }
        int Commit ();
        int Upload ();
        int Download ();
    private:
        static wxDatabase * slaveDB;
        int errorCode;
        bool NewTables ();
        bool EmptySlaveTables ();
        bool EmptyMasterTables ();
        bool OutdateMasterTables ();
        bool Delete ();
        bool Insert ();
        bool InsertProject ();
        bool InsertActivity ();
        bool InsertTimeslot ();
        bool Update ();
        bool UpdateProject ();
        bool UpdateActivity ();
        bool UpdateTimeslot ();
        bool DownloadNames ();
        bool DownloadProject ();
        bool DownloadActivity ();
        bool DownloadTimeslot ();
};

#endif // YATISHDBMYSQL_H
