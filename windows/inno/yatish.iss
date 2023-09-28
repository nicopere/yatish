[Setup]
AppName=YATiSh
AppVersion=0.3
DefaultDirName={autopf}\yatish
DefaultGroupName=Yatish
AppPublisher=EIF-services
AppPublisherURL=https://www.eif-services.eu
AppSupportURL=https://www.eif-services.eu/sites/default/files/yatish/help/doc-0003.htm
AppUpdatesURL=https://www.eif-services.eu/yatish
AppCopyright=Copyright (C) 2020 EIF-services
LicenseFile=GPLv3.txt
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
OutputDir=.
OutputBaseFilename=yatish_install

[Files]
Source: "yatish.exe"; DestDir: "{app}"
Source: "yatish.ico"; DestDir: "{app}"
Source: "GPLv3.txt"; DestDir: "{app}"
Source: "README.txt"; DestDir: "{app}"; Flags: isreadme
Source: "..\help\yatish.htb"; DestDir: "{app}"
Source: "..\fr\yatish.mo"; DestDir: "{app}\fr"
Source: "..\sql\yatish.sqlite"; DestDir: "{app}\sql"
Source: "..\sql\yatish.auth"; DestDir: "{app}\sql"
Source: "dll\*"; DestDir: "{sys}"; Flags: sharedfile

[Icons]
Name: "{group}\yatish"; Filename: "{app}\yatish.exe"; IconFilename: "{app}\yatish.ico"
Name: "{group}\licence"; Filename: "{app}\GPLv3.txt"
