# YATiSh

Yatish is a desktop time tracking application for freelancers and homeworkers; it is an advantageous alternative to classic spreadsheet-made time sheets. Yatish allows in particular to justify the time spent for a client, or for an employee to control her/his (tele)work time. The application can also prove useful in the context of long-term hobbies: model makers or wooden ship builders, for instance, often quote the number of hours spent on a particular project. It is not an ERP, however, meaning that Yatish is suited to individual workers (standalone application), not to enterprises (no collaborative use, no shared database).

The name of the application is an acronym: **Y**et **A**nother **Ti**me **Sh**eet. Indeed this program does not claim to provide revolutionary features but rather a minimal set which I found helpful when using YATiSh (nearly every day since 2020, by the way ensuring a thorough testing ;-). These features include:

* Cross-platform application (Linux, Windows);
* SQLite based: Internet access not needed but...
* ...can sync to a MySQL/MariaDB server (optional);
* PDF export of selected listings (to be appended to invoices, for instance);
* three third-party graphic toolsets available;
* GUI in English or French;
* in-app user guide;
* Doxygen source code documentation;
* free software: GPLv3;
* privacy: YATiSh will not publish anything unless you do mean it, and then only to a privately owned database.

## Source code

The development of YATiSh is first recorded in the public area of a Subversion server:
```
svn checkout svn://eif-services.eu/eif/yatish/trunk --username anonymous yatish
```

Then last stable version of the code (currently V0.4) is also published here on GitHub.

The C++ (documented) code now amounts to 5261 non-empty lines (`grep -v ^$ src/* | wc -l`).

## Compilation

There is no longer a Windows installer nor Debian package.

As far as Windows is concerned, an Inno Setup configuration and some compilation hints are still there (dating back from V0.3): look into the `windows/` subdirectory.

YATiSh is developed on Linux though; a Makefile is provided (typically `make yatish; sudo make install; sudo make install-help`) which relies on a Code::Blocks project, and a checklist of necessary packages is also given in `prerequisites.sh`.

Cmake will be considered for the next release (V0.5); that will apply to Windows also.

## Use cases and *roadmap*

### one user / one PC

* The "master" database is a SQLite (local) file; we suggest to back-up/reset the file once a year.

### one user / several PCs

* Add a "slave" MySQL database (typically on a remote server); use `File>Update (Ctrl-U)` liberally (optimized for speed).
* Upload/download database (full content): robust, but upload slower than update and be careful! (overwrites previous content)
* *Sync status and new timeslots download.*

### one user (read/write) + multiple, customized read accesses

* *Dedicated viewer*, in case you want to instantly publish (part of) your timetable to some of your clients.

### one user with MySQL "slave" + Android smartphone

* *Log activities without a PC* (only edit allowed: adding a timeslot).
