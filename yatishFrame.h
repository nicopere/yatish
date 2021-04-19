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
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include <wx/aboutdlg.h>
#include <wx/help.h>
#include <wx/html/helpctrl.h>
//#include "yatishApp.h"
#include "yatishDBmysql.h"
#include "yatishDBsqlite.h"
#include "yatishDlgActivity.h"
#include "yatishDlgFilter.h"
#include "yatishDlgName.h"
#include "yatishDlgProject.h"
#include "yatishDlgTimeslot.h"
#include "yatishPDF.h"
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
        void OnMenuitemEditTodaySelected(wxCommandEvent& event);
        void OnMenuitemEditThisweekSelected(wxCommandEvent& event);
        void OnMenuitemEditThismonthSelected(wxCommandEvent& event);
        void OnMenuitemEditYestedaySelected(wxCommandEvent& event);
        void OnMenuitemEditLastweekSelected(wxCommandEvent& event);
        void OnMenuitemEditLastmonthSelected(wxCommandEvent& event);
        void OnMenuitemEditActivitySelected(wxCommandEvent& event);
        void OnMenuitemEditChartSelected(wxCommandEvent& event);
        void OnButtonPDFClick(wxCommandEvent& event);
        //*)
        void OnMenuitemEditActivityUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditTableUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditChartUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditNewUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditResetUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditTodayUpdate (wxUpdateUIEvent&);
        void OnContextMenu1 (wxContextMenuEvent&);
        void OnContextMenu2 (wxContextMenuEvent&);
        void OnContextMenu3 (wxContextMenuEvent&);
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
        static const long idEditActivity;
        static const long idEditTable;
        static const long idEditChart;
        static const long idEditNew;
        static const long idEditReset;
        static const long idEditToday;
        static const long idEditThisweek;
        static const long idEditThismonth;
        static const long idEditYesterday;
        static const long idEditLastweek;
        static const long idEditLastmonth;
        static const long idEditSettings;
        static const long idHelpUser;
        static const long idHelpAbout;
        static const long idStatusBar;
        static const long idTimer;
        //*)
        //(*Declarations(yatishFrame)
        wxBoxSizer* BoxSizer1;
        wxButton* buttonPDF;
        wxButton* buttonStart;
        wxButton* buttonStop;
        wxChoice* choiceProject;
        wxChoice* choiceTable;
        wxChoice* choiceTask;
        wxChoice* choiceTool;
        wxDatePickerCtrl* datePicker1;
        wxDatePickerCtrl* datePicker2;
        wxListCtrl* listCtrl;
        wxMenuItem* menuitemFileConnect;
        wxMenuItem* menuitemFileDownload;
        wxMenuItem* menuitemFileUpdate;
        wxMenuItem* menuitemFileUpload;
        wxNotebook* notebook;
        wxStatusBar* statusBar;
        wxTextCtrl* textCtrl;
        wxTimer timer;
        //*)
        DECLARE_EVENT_TABLE()
};

#endif // YATISHMAIN_H
