/********************************************************************
 * Name:      yatishFrame.h
 * Purpose:   Declares the main Frame
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

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
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include "yatishDBmysql.h"
#include "yatishDBsqlite.h"
#include "yatishDlgActivity.h"
#include "yatishDlgFilter.h"
#include "yatishDlgName.h"
#include "yatishDlgProject.h"
#include "yatishDlgTimeslot.h"
#include "yatishPDF.h"
#include "yatishPlot.h"
#include "yatishSettings.h"

enum mysqlStatus {
    mysql_off,
    mysql_on,
    mysql_err
};

// Need to send a wxSizeEvent with wxCharts...
#define UNFORTUNATE_TRICK if (currentChartLib == wxCharts) SetSize ( GetSize() + wxSize (0, 1) );

/** Main Yatish frame; apart from menus, status bar, etc.\ this (large!) class:
 * - is responsible for all the controls of panels #1, #2 and #3;
 * - owns the Settings and the yatishDBsqlite;
 * - creates a yatishDBmysql, a yatishPDF and a yatishPlot when needed;
 * - triggers interactions of the latter with yatishDBsqlite.
 */
class yatishFrame: public wxFrame {
    public:
        yatishFrame (wxWindow *, wxWindowID = -1);
    private:
        Settings settings;
        wxLog * defaultLog;
        wxHtmlHelpController help;
        wxDateTime clockStart;
        yatishDBsqlite masterDB;
        yatishDBmysql * slaveDB;
        yatishPlot * plot;
        ChartLib currentChartLib;
        PlotType currentPlotType;
        long selectedActivityID;
        void UpdateClock ();
        void UpdateStatus (mysqlStatus);
        void ResetChoices ();
        void UpdateColumns ();
        void UpdateRows (tableID);
        void ResetPickersT ();
        void ResetPickersG ();
        void NewPlot ();
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
        void OnMenuitemEditActivitySelected(wxCommandEvent& event);
        void OnMenuitemEditChartSelected(wxCommandEvent& event);
        void OnButtonPDFClick(wxCommandEvent& event);
        void OnChoiceChartSelect(wxCommandEvent& event);
        void OnChoiceAggregateSelect(wxCommandEvent& event);
        void OnChoiceClusterSelect(wxCommandEvent& event);
        void OnDatePicker3Changed(wxDateEvent& event);
        void OnDatePicker4Changed(wxDateEvent& event);
        void OnListItemRightClick(wxListEvent& event);
        void OnMenuitemTimeTodaySelected(wxCommandEvent& event);
        void OnMenuitemTimeThisweekSelected(wxCommandEvent& event);
        void OnmenuitemTimeThismonthSelected(wxCommandEvent& event);
        void OnMenuitemTimeThisyearSelected(wxCommandEvent& event);
        void OnMenuitemTimeYesterdaySelected(wxCommandEvent& event);
        void OnMenuitemTimeLastweekSelected(wxCommandEvent& event);
        void OnMenuitemTimeLastmonthSelected(wxCommandEvent& event);
        void OnMenuitemTimeLastyearSelected(wxCommandEvent& event);
        void OnMenuitemTimeThismonthSelected(wxCommandEvent& event);
        //*)
        void OnListActivityRecord (wxCommandEvent& event);
        void OnListActivityListTimeslot (wxCommandEvent& event);
        void OnMenuitemEditActivityUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditTableUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditChartUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditNewUpdate (wxUpdateUIEvent&);
        void OnMenuitemEditResetUpdate (wxUpdateUIEvent&);
        void OnMenuitemTimeTodayUpdate (wxUpdateUIEvent&);
        void OnChoiceAggregateUpdate (wxUpdateUIEvent&);
        void OnChoiceClusterUpdate (wxUpdateUIEvent&);
        void OnContextMenu1 (wxContextMenuEvent&);
        void OnContextMenu2 (wxContextMenuEvent&);
        void OnContextMenu3 (wxContextMenuEvent&);
        void OnContextMenu4 (wxContextMenuEvent&);
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
        static const long idChoiceChart;
        static const long idChoiceAggregate;
        static const long idChoiceCluster;
        static const long idDatePicker3;
        static const long idDatePicker4;
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
        static const long idEditSettings;
        static const long idTimeToday;
        static const long idTimeThisweek;
        static const long idTimeThismonth;
        static const long idTimeThisyear;
        static const long idTimeYesterday;
        static const long idTimeLastweek;
        static const long idTimeLastmonth;
        static const long idTimeLastyear;
        static const long idHelpUser;
        static const long idHelpAbout;
        static const long idStatusBar;
        static const long idTimer;
        //*)
        static const long idListActivityRecord;
        static const long idListActivityListTimeslot;
        //(*Declarations(yatishFrame)
        wxBoxSizer* boxSizer1;
        wxBoxSizer* boxSizer6;
        wxButton* buttonPDF;
        wxButton* buttonStart;
        wxButton* buttonStop;
        wxChoice* choiceAggregate;
        wxChoice* choiceChart;
        wxChoice* choiceCluster;
        wxChoice* choiceProject;
        wxChoice* choiceTable;
        wxChoice* choiceTask;
        wxChoice* choiceTool;
        wxDatePickerCtrl* datePicker1;
        wxDatePickerCtrl* datePicker2;
        wxDatePickerCtrl* datePicker3;
        wxDatePickerCtrl* datePicker4;
        wxListCtrl* listCtrl;
        wxMenuItem* menuitemFileConnect;
        wxMenuItem* menuitemFileDownload;
        wxMenuItem* menuitemFileUpdate;
        wxMenuItem* menuitemFileUpload;
        wxNotebook* notebook;
        wxPanel* panelChart;
        wxStatusBar* statusBar;
        wxTextCtrl* textCtrl;
        wxTimer timer;
        //*)
        DECLARE_EVENT_TABLE()
};

#endif // YATISHMAIN_H
