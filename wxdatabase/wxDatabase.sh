#!/bin/bash
cd include/wx/database/mysql
mv mysql_preparedStatement_resultset.h mysql_preparedstatement_resultset.h
cd ../../../..
patch -p0 <wxDatabase.patch
