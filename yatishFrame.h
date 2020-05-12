/***************************************************************
 * Name:      yatishFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#ifndef YATISHMAIN_H
#define YATISHMAIN_H

//(*Headers(yatishFrame)
#include <wx/sizer.h>
#include <wx/datectrl.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/dateevt.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/timer.h>
//*)

#include <wx/aboutdlg.h>
#include <wx/help.h>
//#include "yatishApp.h"
#include "yatishDBsqlite.h"
#include "yatishDBmysql.h"
#include "yatishDlgName.h"
#include "yatishDlgProject.h"
#include "yatishDlgActivity.h"
#include "yatishDlgTimeslot.h"
#include "yatishDlgFilter.h"
#include "yatishSettings.h"

enum mysqlStatus {
    mysql_off,
    mysql_on,
    mysql_err
};

class yatishFrame: public wxFrame {
    public:
        yatishFrame (wxWindow *, wxWindowID = -1);
        ~yatishFrame ();
    private:
        Settings settings;
        wxLog * defaultLog;
        wxHtmlHelpController yatishHelp;
        wxDateTime clockStart;
        yatishDBsqlite masterDB;
        yatishDBmysql * slaveDB;
        void UpdateClock ();
        void UpdateStatus (mysqlStatus);
        void ResetChoices ();
        void UpdateColumns ();
        void UpdateRows (tableID);
        void ResetPickers ();
        void ToggleConnect ();
        void ToggleLog ();
        void Recording ();
        //(*Handlers(yatishFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTimerTrigger(wxTimerEvent& event);
        void OnButtonStartClick(wxCommandEvent& event);
        void OnButtonStopClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnChoiceTableSelect(wxCommandEvent& event);
        void OnNotebookPageChanged(wxNotebookEvent& event);
        void OnDatePicker1Changed(wxDateEvent& event);
        void OnDatePicker2Changed(wxDateEvent& event);
        void OnListColumnClick(wxListEvent& event);
        void OnListKeyDown(wxListEvent& event);
        void OnMenuitemEditTableSelected(wxCommandEvent& event);
        void OnMenuitemFileConnectSelected(wxCommandEvent& event);
        void OnMenuitemFileUpdateSelected(wxCommandEvent& event);
        void OnMenuitemEditNewSelected(wxCommandEvent& event);
        void OnMenuitemEditResetSelected(wxCommandEvent& event);
        void OnMenuitemFileUploadSelected(wxCommandEvent& event);
        void OnMenuitemFileDownloadSelected(wxCommandEvent& event);
        void OnMenuitemEditSettingsSelected(wxCommandEvent& event);
        void OnHelp(wxCommandEvent& event);
        //*)
        void OnMenuitemEditTableUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditNewUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditResetUpdate (wxUpdateUIEvent&);
        void OnContextMenu (wxContextMenuEvent&);
        //(*Identifiers(yatishFrame)
        static const long idChoiceProject;
        static const long idChoiceTask;
        static const long idChoiceTool;
        static const long idButtonStart;
        static const long idButtonStop;
        static const long idPanelCurrent;
        static const long idChoiceTable;
        static const long idDatePicker1;
        static const long idDatePicker2;
        static const long idButtonPDF;
        static const long idListCtrl;
        static const long idPanelList;
        static const long idPanelChart;
        static const long idNotebook;
        static const long idTextCtrl;
        static const long idFileConnect;
        static const long idFileUpdate;
        static const long idFileUpload;
        static const long idFileDownload;
        static const long idFileQuit;
        static const long idEditTable;
        static const long idEditNew;
        static const long idEditReset;
        static const long idEditSettings;
        static const long idHelpUser;
        static const long idHelpAbout;
        static const long idStatusBar;
        static const long idTimer;
        //*)
        //(*Declarations(yatishFrame)
        wxTimer timer;
        wxDatePickerCtrl* datePicker1;
        wxStatusBar* statusBar;
        wxChoice* choiceProject;
        wxChoice* choiceTask;
        wxMenuItem* menuitemFileDownload;
        wxChoice* choiceTable;
        wxMenuItem* menuitemFileConnect;
        wxNotebook* notebook;
        wxButton* buttonStop;
        wxMenuItem* menuitemFileUpload;
        wxTextCtrl* textCtrl;
        wxButton* buttonPDF;
        wxMenuItem* menuitemEditReset;
        wxChoice* choiceTool;
        wxListCtrl* listCtrl;
        wxMenuItem* menuitemEditNew;
        wxBoxSizer* BoxSizer1;
        wxDatePickerCtrl* datePicker2;
        wxMenuItem* menuitemFileUpdate;
        wxButton* buttonStart;
        //*)
        DECLARE_EVENT_TABLE()
};

#endif // YATISHMAIN_H
