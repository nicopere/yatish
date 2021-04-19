/***************************************************************
 * Name:      yatishFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu)
 * License:   GPLv3
 **************************************************************/

#include "wx_pch.h"
#include "yatishFrame.h"
#include "yatish.xpm"
#include "yatish_recording.xpm"
// just to make sure poedit will extract the string expected by wxWidgets...
const char * not_used = _("translator-credits");
// ...when a locale is defined and wxAboutDialogInfo::AddTranslator() is not called

//(*InternalHeaders(yatishFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(yatishFrame)
const long yatishFrame::idChoiceProject = wxNewId();
const long yatishFrame::idChoiceTask = wxNewId();
const long yatishFrame::idChoiceTool = wxNewId();
const long yatishFrame::idButtonStart = wxNewId();
const long yatishFrame::idButtonStop = wxNewId();
const long yatishFrame::idPanelCurrent = wxNewId();
const long yatishFrame::idChoiceTable = wxNewId();
const long yatishFrame::idDatePicker1 = wxNewId();
const long yatishFrame::idDatePicker2 = wxNewId();
const long yatishFrame::idButtonPDF = wxNewId();
const long yatishFrame::idListCtrl = wxNewId();
const long yatishFrame::idPanelList = wxNewId();
const long yatishFrame::idPanelChart = wxNewId();
const long yatishFrame::idNotebook = wxNewId();
const long yatishFrame::idTextCtrl = wxNewId();
const long yatishFrame::idFileConnect = wxNewId();
const long yatishFrame::idFileUpdate = wxNewId();
const long yatishFrame::idFileUpload = wxNewId();
const long yatishFrame::idFileDownload = wxNewId();
const long yatishFrame::idFileQuit = wxNewId();
const long yatishFrame::idEditActivity = wxNewId();
const long yatishFrame::idEditTable = wxNewId();
const long yatishFrame::idEditChart = wxNewId();
const long yatishFrame::idEditNew = wxNewId();
const long yatishFrame::idEditReset = wxNewId();
const long yatishFrame::idEditToday = wxNewId();
const long yatishFrame::idEditThisweek = wxNewId();
const long yatishFrame::idEditThismonth = wxNewId();
const long yatishFrame::idEditYesterday = wxNewId();
const long yatishFrame::idEditLastweek = wxNewId();
const long yatishFrame::idEditLastmonth = wxNewId();
const long yatishFrame::idEditSettings = wxNewId();
const long yatishFrame::idHelpUser = wxNewId();
const long yatishFrame::idHelpAbout = wxNewId();
const long yatishFrame::idStatusBar = wxNewId();
const long yatishFrame::idTimer = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishFrame, wxFrame)
    //(*EventTable(yatishFrame)
    //*)
    EVT_UPDATE_UI(idEditActivity, yatishFrame::OnMenuitemEditActivityUpdate)
    EVT_UPDATE_UI(idEditTable, yatishFrame::OnMenuitemEditTableUpdate)
    EVT_UPDATE_UI(idEditChart, yatishFrame::OnMenuitemEditChartUpdate)
    EVT_UPDATE_UI(idEditNew, yatishFrame::OnMenuitemEditNewUpdate)
    EVT_UPDATE_UI(idEditReset, yatishFrame::OnMenuitemEditResetUpdate)
    EVT_UPDATE_UI_RANGE(idEditToday, idEditLastmonth, yatishFrame::OnMenuitemEditTodayUpdate)
END_EVENT_TABLE()

yatishFrame::yatishFrame (wxWindow* parent, wxWindowID id) {
    //(*Initialize(yatishFrame)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenu* Menu3;
    wxMenuBar* menuBar;
    wxMenuItem* menuitemEditActivity;
    wxMenuItem* menuitemEditChart;
    wxMenuItem* menuitemEditLastmonth;
    wxMenuItem* menuitemEditLastweek;
    wxMenuItem* menuitemEditNew;
    wxMenuItem* menuitemEditReset;
    wxMenuItem* menuitemEditSettings;
    wxMenuItem* menuitemEditTable;
    wxMenuItem* menuitemEditThismonth;
    wxMenuItem* menuitemEditThisweek;
    wxMenuItem* menuitemEditToday;
    wxMenuItem* menuitemEditYesteday;
    wxMenuItem* menuitemFileQuit;
    wxMenuItem* menuitemHelpAbout;
    wxMenuItem* menuitemHelpUser;
    wxPanel* panelChart;
    wxPanel* panelCurrent;
    wxPanel* panelList;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticText* StaticText1;

    Create(parent, wxID_ANY, _("YATiSh"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    notebook = new wxNotebook(this, idNotebook, wxDefaultPosition, wxDefaultSize, 0, _T("idNotebook"));
    panelCurrent = new wxPanel(notebook, idPanelCurrent, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelCurrent"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, panelCurrent, _("Select project, task and tool"));
    choiceProject = new wxChoice(panelCurrent, idChoiceProject, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceProject"));
    StaticBoxSizer1->Add(choiceProject, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    choiceTask = new wxChoice(panelCurrent, idChoiceTask, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTask"));
    StaticBoxSizer1->Add(choiceTask, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    choiceTool = new wxChoice(panelCurrent, idChoiceTool, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTool"));
    StaticBoxSizer1->Add(choiceTool, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer2->Add(StaticBoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    buttonStart = new wxButton(panelCurrent, idButtonStart, _("&RECORD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonStart"));
    BoxSizer3->Add(buttonStart, 1, wxALL|wxEXPAND, 5);
    buttonStop = new wxButton(panelCurrent, idButtonStop, _("&STOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonStop"));
    BoxSizer3->Add(buttonStop, 1, wxALL|wxEXPAND, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelCurrent->SetSizer(BoxSizer2);
    BoxSizer2->Fit(panelCurrent);
    BoxSizer2->SetSizeHints(panelCurrent);
    panelList = new wxPanel(notebook, idPanelList, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelList"));
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, panelList, _("Table"));
    choiceTable = new wxChoice(panelList, idChoiceTable, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTable"));
    choiceTable->Append(_("Client"));
    choiceTable->Append(_("Task"));
    choiceTable->Append(_("Tool"));
    choiceTable->Append(_("Project"));
    choiceTable->Append(_("Activity"));
    choiceTable->SetSelection( choiceTable->Append(_("Timeslot")) );
    StaticBoxSizer2->Add(choiceTable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, panelList, _("Date interval (inclusive)"));
    datePicker1 = new wxDatePickerCtrl(panelList, idDatePicker1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker1"));
    StaticBoxSizer3->Add(datePicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker2 = new wxDatePickerCtrl(panelList, idDatePicker2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker2"));
    StaticBoxSizer3->Add(datePicker2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticBoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonPDF = new wxButton(panelList, idButtonPDF, _("E&xport PDF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonPDF"));
    BoxSizer5->Add(buttonPDF, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer5, 0, wxALL|wxEXPAND, 5);
    listCtrl = new wxListCtrl(panelList, idListCtrl, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("idListCtrl"));
    BoxSizer4->Add(listCtrl, 1, wxALL|wxEXPAND, 5);
    panelList->SetSizer(BoxSizer4);
    BoxSizer4->Fit(panelList);
    BoxSizer4->SetSizeHints(panelList);
    panelChart = new wxPanel(notebook, idPanelChart, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelChart"));
    StaticText1 = new wxStaticText(panelChart, wxID_ANY, _("Coming soon..."), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    notebook->AddPage(panelCurrent, _("Current activity"), false);
    notebook->AddPage(panelList, _("List/Edit"), false);
    notebook->AddPage(panelChart, _("Charts"), false);
    BoxSizer1->Add(notebook, 3, wxALL|wxEXPAND, 0);
    textCtrl = new wxTextCtrl(this, idTextCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("idTextCtrl"));
    BoxSizer1->Add(textCtrl, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    menuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    menuitemFileConnect = new wxMenuItem(Menu1, idFileConnect, _("&Connect\tCtrl-C"), _("Connect to a (remote) MySQL/MariaDB server"), wxITEM_NORMAL);
    Menu1->Append(menuitemFileConnect);
    menuitemFileUpdate = new wxMenuItem(Menu1, idFileUpdate, _("&Update\tCtrl-U"), _("Update remote database"), wxITEM_NORMAL);
    Menu1->Append(menuitemFileUpdate);
    menuitemFileUpdate->Enable(false);
    menuitemFileUpload = new wxMenuItem(Menu1, idFileUpload, _("Up&load"), _("Replace remote data (by local)"), wxITEM_NORMAL);
    Menu1->Append(menuitemFileUpload);
    menuitemFileUpload->Enable(false);
    menuitemFileDownload = new wxMenuItem(Menu1, idFileDownload, _("&Download"), _("Replace local data (by remote)"), wxITEM_NORMAL);
    Menu1->Append(menuitemFileDownload);
    menuitemFileDownload->Enable(false);
    Menu1->AppendSeparator();
    menuitemFileQuit = new wxMenuItem(Menu1, idFileQuit, _("&Quit\tCtrl-Q"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(menuitemFileQuit);
    menuBar->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    menuitemEditActivity = new wxMenuItem(Menu2, idEditActivity, _("&Activity\tCtrl-A"), _("Start/stop current activity"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditActivity);
    menuitemEditTable = new wxMenuItem(Menu2, idEditTable, _("&Tables\tCtrl-T"), _("Edit any table"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditTable);
    menuitemEditChart = new wxMenuItem(Menu2, idEditChart, _("&Charts\tCtrl-G"), _("Look at various charts"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditChart);
    Menu2->AppendSeparator();
    menuitemEditNew = new wxMenuItem(Menu2, idEditNew, _("&New record...\tCtrl-N"), _("Add a record to the currently selected table"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditNew);
    menuitemEditReset = new wxMenuItem(Menu2, idEditReset, _("&Reset filter\tCtrl-R"), _("Reset the viewing filter"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditReset);
    Menu2->AppendSeparator();
    menuitemEditToday = new wxMenuItem(Menu2, idEditToday, _("Today"), _("Time interval to show: today"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditToday);
    menuitemEditThisweek = new wxMenuItem(Menu2, idEditThisweek, _("This week"), _("Time interval to show: this week"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditThisweek);
    menuitemEditThismonth = new wxMenuItem(Menu2, idEditThismonth, _("This month"), _("Time interval to show: this month"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditThismonth);
    menuitemEditYesteday = new wxMenuItem(Menu2, idEditYesterday, _("Yesterday"), _("Time interval to show: yesterday"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditYesteday);
    menuitemEditLastweek = new wxMenuItem(Menu2, idEditLastweek, _("Last week"), _("Time interval to show: last week"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditLastweek);
    menuitemEditLastweek->Enable(false);
    menuitemEditLastmonth = new wxMenuItem(Menu2, idEditLastmonth, _("Last month"), _("Time interval to show: last month"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditLastmonth);
    Menu2->AppendSeparator();
    menuitemEditSettings = new wxMenuItem(Menu2, idEditSettings, _("&Settings...\tCtrl-S"), _("Set user preferences"), wxITEM_NORMAL);
    Menu2->Append(menuitemEditSettings);
    menuBar->Append(Menu2, _("&Edit"));
    Menu3 = new wxMenu();
    menuitemHelpUser = new wxMenuItem(Menu3, idHelpUser, _("&User guide\tF1"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(menuitemHelpUser);
    menuitemHelpAbout = new wxMenuItem(Menu3, idHelpAbout, _("&About..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(menuitemHelpAbout);
    menuBar->Append(Menu3, _("&Help"));
    SetMenuBar(menuBar);
    statusBar = new wxStatusBar(this, idStatusBar, 0, _T("idStatusBar"));
    int __wxStatusBarWidths_1[3] = { 65, 85, -1 };
    int __wxStatusBarStyles_1[3] = { wxSB_RAISED, wxSB_RAISED, wxSB_NORMAL };
    statusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);
    timer.SetOwner(this, idTimer);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(idButtonStart,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonStartClick);
    Connect(idButtonStop,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonStopClick);
    Connect(idChoiceTable,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&yatishFrame::OnChoiceTableSelect);
    Connect(idDatePicker1,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker1Changed);
    Connect(idDatePicker2,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker2Changed);
    Connect(idButtonPDF,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonPDFClick);
    Connect(idListCtrl,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&yatishFrame::OnListKeyDown);
    Connect(idListCtrl,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&yatishFrame::OnListColumnClick);
    Connect(idNotebook,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnNotebookPageChanged);
    Connect(idFileConnect,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemFileConnectSelected);
    Connect(idFileUpdate,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemFileUpdateSelected);
    Connect(idFileUpload,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemFileUploadSelected);
    Connect(idFileDownload,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemFileDownloadSelected);
    Connect(idFileQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnQuit);
    Connect(idEditActivity,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditActivitySelected);
    Connect(idEditTable,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditTableSelected);
    Connect(idEditChart,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditChartSelected);
    Connect(idEditNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditNewSelected);
    Connect(idEditReset,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditResetSelected);
    Connect(idEditToday,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditTodaySelected);
    Connect(idEditThisweek,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditThisweekSelected);
    Connect(idEditThismonth,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditThismonthSelected);
    Connect(idEditYesterday,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditYestedaySelected);
    Connect(idEditLastweek,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditLastweekSelected);
    Connect(idEditLastmonth,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditLastmonthSelected);
    Connect(idEditSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditSettingsSelected);
    Connect(idHelpUser,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnHelp);
    Connect(idHelpAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnAbout);
    Connect(idTimer,wxEVT_TIMER,(wxObjectEventFunction)&yatishFrame::OnTimerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&yatishFrame::OnClose);
    //*)
    datePicker1->Bind(wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu1, this);
    datePicker2->Bind(wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu2, this);
    listCtrl->Bind(wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu3, this);
    SetIcon ( wxIcon (yatish_xpm) );
    yatishHelp.Initialize (wxStandardPaths::Get().GetDataDir() + wxFILE_SEP_PATH + "yatish");
    buttonStop->Disable(); clockStart = wxDateTime::Now();
    UpdateClock(); UpdateStatus (mysql_off); SetStatusBarPane (2);
    masterDB.SetLimit (settings.limitRow, settings.rowLimit);
    if (settings.log2text)
        defaultLog = wxLog::SetActiveTarget( new wxLogTextCtrl (textCtrl) );
    else {
        textCtrl->Hide(); BoxSizer1->Fit (this); BoxSizer1->SetSizeHints (this);
    }
    ResetChoices(); ResetPickers(); UpdateColumns();
    SetStatusText (wxEmptyString, 2); // don't show SUM|AVG on startup
    // take care of previously ill-terminated yatish jobs
    switch ( masterDB.RunningTimeslots() ) {
        case -1:
        case 0:
            break;
        case 1:
            Recording();
            break;
        default:
            wxLogError (_("Several yatish were inappropriately terminated!") );
    }
    panelChart->Hide(); // Coming soon...
    slaveDB = nullptr;
}

yatishFrame::~yatishFrame () {
    //(*Destroy(yatishFrame)
    //*)
}

void yatishFrame::UpdateClock () {
    wxDateTime now = wxDateTime::Now();
    wxTimeSpan elapsed = now - clockStart;
    SetStatusText ( elapsed.Format() );
}

void yatishFrame::UpdateStatus (mysqlStatus status) {
    switch (status) {
        case mysql_on:
            SetStatusText ("MySQL  ON", 1);
            break;
        case mysql_off:
            SetStatusText ("MySQL OFF", 1);
            break;
        default:
            SetStatusText ("MySQL ERR", 1);
    }
}

void yatishFrame::ResetChoices () {
    bool choiceOK;
    choiceOK = masterDB.FillChoice (choiceProject, project_tid);
    choiceOK = masterDB.FillChoice (choiceTask, task_tid);
    choiceOK = masterDB.FillChoice (choiceTool, tool_tid);
    if (!choiceOK) wxLogError ("Reset of choices failed for panel #1");
    if ( choiceProject->IsEmpty() || choiceTask->IsEmpty() || choiceTool->IsEmpty() )
        buttonStart->Disable(); // in case the database is not populated yet
    else
        buttonStart->Enable ( !buttonStop->IsEnabled() );
    long lastActivityID = masterDB.LastActivity();
    if (lastActivityID == wxNOT_FOUND) {
        choiceProject->SetSelection (0);
        choiceTask   ->SetSelection (0);
        choiceTool   ->SetSelection (0);
    } else {
        choiceProject->SetSelection (masterDB.ChoiceSelector (project_tid, lastActivityID) );
        choiceTask   ->SetSelection (masterDB.ChoiceSelector (task_tid, lastActivityID) );
        choiceTool   ->SetSelection (masterDB.ChoiceSelector (tool_tid, lastActivityID) );
    }
}

void yatishFrame::UpdateColumns () {
    listCtrl->DeleteAllColumns();
 // Now we rely on the fact that choiceTable was initialized
 // in the same order as tableID is defined:
    tableID tid = (tableID) choiceTable->GetSelection();
 // (same assumption each time we will use the trick).
    switch (tid) {
        case timeslot_tid:
            listCtrl->AppendColumn(_("Date") );
            listCtrl->AppendColumn(_("Duration") );
            listCtrl->AppendColumn(_("Project") );
            listCtrl->AppendColumn(_("Client") );
            listCtrl->AppendColumn(_("Task") );
            listCtrl->AppendColumn(_("Tool") );
            break;
        case activity_tid:
            listCtrl->AppendColumn(_("Project") );
            listCtrl->AppendColumn(_("Client") );
            listCtrl->AppendColumn(_("Task") );
            listCtrl->AppendColumn(_("Tool") );
            break;
        case project_tid:
            listCtrl->AppendColumn(_("Name") );
            listCtrl->AppendColumn(_("Client") );
            break;
        default:
            listCtrl->AppendColumn(_("Name") );
    }
    UpdateRows (tid);
}

void yatishFrame::UpdateRows (tableID tid) {
    listCtrl->Freeze(); // or Hide()...
    listCtrl->DeleteAllItems();
    if ( !masterDB.FillList (listCtrl, tid) )
        wxLogError ("Updating listCrl failed (panel #2)");
    for (int col = 0; col < listCtrl->GetColumnCount(); col++)
        listCtrl->SetColumnWidth (col, wxLIST_AUTOSIZE_USEHEADER);
    listCtrl->Thaw();   // or Show()...
    SetStatusText (masterDB.FilteredTotalFormatted(), 2);
}

void yatishFrame::ResetPickers () {
    datePicker1->SetValue ( masterDB.First() );
    datePicker2->SetValue ( masterDB.Last() );
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
}

void yatishFrame::ToggleConnect () {
    bool b = menuitemFileConnect->IsEnabled();
    menuitemFileConnect ->Enable (!b);
    menuitemFileUpdate  ->Enable ( b);
    menuitemFileUpload  ->Enable ( b);
    menuitemFileDownload->Enable ( b);
}

void yatishFrame::ToggleLog () {
    if (settings.log2text) {
        defaultLog = wxLog::SetActiveTarget( new wxLogTextCtrl (textCtrl) );
        textCtrl->Show(); BoxSizer1->Fit (this); BoxSizer1->SetSizeHints (this);
    } else {
        delete wxLog::SetActiveTarget (defaultLog);
        textCtrl->Hide(); BoxSizer1->Fit (this); BoxSizer1->SetSizeHints (this);
    }
}

// Handlers...

void yatishFrame::OnQuit (wxCommandEvent& event) {
    Close();
}

void yatishFrame::OnClose (wxCloseEvent& event) {
    if ( yatishHelp.GetFrame() ) yatishHelp.GetFrame()->Close (true);
    if (settings.log2text) delete wxLog::SetActiveTarget (defaultLog);
    delete slaveDB;
    Destroy();
}

void yatishFrame::OnTimerTrigger (wxTimerEvent& event) {
    UpdateClock();
}

// ...menus

void yatishFrame::OnMenuitemFileConnectSelected(wxCommandEvent& event) {
    delete slaveDB;
    slaveDB = new yatishDBmysql;
    if ( slaveDB->IsOk() ) {
        ToggleConnect();
        UpdateStatus (mysql_on);
    } else
        UpdateStatus (mysql_err);
}

void yatishFrame::OnMenuitemFileUpdateSelected (wxCommandEvent& event) {
    if ( buttonStop->IsEnabled() ) {
        wxMessageBox (_("Please stop the current activity"),
                      _("Update refused"), wxOK);
        return;
    }
    int err = slaveDB->Commit();
    if (err == 2006 || err == 2013) {
        wxLogMessage (_("MySQL connection timed out: try to reconnect...") );
        UpdateStatus (mysql_err);
        ToggleConnect();
    }
}

void yatishFrame::OnMenuitemFileUploadSelected (wxCommandEvent& event) {
    if ( wxMessageBox ( _("Remote data (if any) will be\noverwritten by local ones."),
                        _("Are you sure?"),
                        wxICON_EXCLAMATION|wxOK|wxCANCEL|wxCANCEL_DEFAULT )
         == wxCANCEL ) return;
    SetStatusText (_("Please wait, working..."), 2);
    int err = slaveDB->Upload();
    SetStatusText (wxEmptyString, 2);
    if (err == 2006 || err == 2013) {
        wxLogMessage (_("MySQL connection timed out: try to reconnect...") );
        UpdateStatus (mysql_err);
        ToggleConnect();
    }
}

void yatishFrame::OnMenuitemFileDownloadSelected (wxCommandEvent& event) {
    if ( wxMessageBox ( _("Local data (if any) will be\noverwritten by remote ones."),
                        _("Are you sure?"),
                        wxICON_EXCLAMATION|wxOK|wxCANCEL|wxCANCEL_DEFAULT )
         == wxCANCEL ) return;
    SetStatusText (_("Please wait, working..."), 2);
    int err = slaveDB->Download();
    SetStatusText (wxEmptyString, 2);
    if (err == 2006 || err == 2013) {
        wxLogMessage (_("MySQL connection timed out: try to reconnect...") );
        UpdateStatus (mysql_err);
        ToggleConnect();
    } else {
        int page = notebook->GetSelection();
        if (page == 0) ResetChoices();
        if (page == 1) {
            ResetPickers();
            UpdateRows ( (tableID) choiceTable->GetSelection() );
        }
    }
}

void yatishFrame::OnMenuitemEditActivitySelected(wxCommandEvent& event) {
    notebook->SetSelection (0);
}
void yatishFrame::OnMenuitemEditActivityUpdate (wxUpdateUIEvent& event) {
    event.Enable (notebook->GetSelection() != 0);
}
void yatishFrame::OnMenuitemEditTableSelected (wxCommandEvent& event) {
    notebook->SetSelection (1);
}
void yatishFrame::OnMenuitemEditTableUpdate (wxUpdateUIEvent& event) {
    event.Enable (notebook->GetSelection() != 1);
}
void yatishFrame::OnMenuitemEditChartSelected(wxCommandEvent& event) {
    notebook->SetSelection (2);
}
void yatishFrame::OnMenuitemEditChartUpdate (wxUpdateUIEvent& event) {
  //event.Enable (notebook->GetSelection() != 2); // Coming soon...
    event.Enable (false);
}

void yatishFrame::OnMenuitemEditNewSelected (wxCommandEvent& event) {
    int dlgEnd = wxID_CANCEL;
    tableID tid = (tableID) choiceTable->GetSelection();
    if (tid == client_tid || tid == task_tid || tid == tool_tid) {
        yatishDlgName dlg (&masterDB, tid);
        dlgEnd = dlg.ShowModal();
    } else if (tid == project_tid) {
        yatishDlgProject dlg (&masterDB);
        dlgEnd = dlg.ShowModal();
    } else if (tid == activity_tid) {
        yatishDlgActivity dlg (&masterDB);
        dlgEnd = dlg.ShowModal();
    } else { // tid == timeslot_tid
        yatishDlgTimeslot dlg (&masterDB);
        dlgEnd = dlg.ShowModal();
    }
    if (dlgEnd != wxID_CANCEL) {
        datePicker2->SetValue ( masterDB.Last() );
        masterDB.SetLastDay ( datePicker2->GetValue() );
        UpdateRows (tid);
    }
}

void yatishFrame::OnMenuitemEditNewUpdate (wxUpdateUIEvent& event) {
    event.Enable (notebook->GetSelection() == 1);
}

void yatishFrame::OnMenuitemEditResetSelected (wxCommandEvent& event) {
    masterDB.ClearFilter();
    ResetPickers();
    UpdateRows ( (tableID) choiceTable->GetSelection() );
}

void yatishFrame::OnMenuitemEditResetUpdate (wxUpdateUIEvent& event) {
    tableID tid = (tableID) choiceTable->GetSelection();
    bool filterAvailable = ( tid == project_tid || tid == activity_tid || tid == timeslot_tid );
    event.Enable (notebook->GetSelection() == 1 && filterAvailable);
}

void yatishFrame::OnMenuitemEditTodaySelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    datePicker2->SetValue (dt);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnMenuitemEditTodayUpdate (wxUpdateUIEvent& event) {
    tableID tid = (tableID) choiceTable->GetSelection();
    event.Enable (notebook->GetSelection() == 1 && tid == timeslot_tid);
}

void yatishFrame::OnMenuitemEditThisweekSelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    datePicker2->SetValue (dt);
    dt.SetToPrevWeekDay (wxDateTime::Mon);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnMenuitemEditThismonthSelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    datePicker2->SetValue (dt);
    dt.SetDay (1);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnMenuitemEditYestedaySelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    dt -= wxDateSpan::Day();
    datePicker2->SetValue (dt);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnMenuitemEditLastweekSelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    dt -= wxDateSpan::Week();
    dt.SetToNextWeekDay (wxDateTime::Sun);
    datePicker2->SetValue (dt);
    dt.SetToPrevWeekDay (wxDateTime::Mon);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnMenuitemEditLastmonthSelected(wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    dt -= wxDateSpan::Month();
    dt.SetToLastMonthDay();
    datePicker2->SetValue (dt);
    dt.SetDay (1);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnContextMenu1(wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idEditToday, _("Today"), _("Time interval to show: today") );
    menu.Append ( idEditThisweek, _("This week"), _("Time interval to show: this week") );
    menu.Append ( idEditThismonth, _("This month"), _("Time interval to show: this month") );
    PopupMenu (&menu);
}

void yatishFrame::OnContextMenu2(wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idEditYesterday, _("Yesterday"), _("Time interval to show: yesterday") );
    menu.Append ( idEditLastweek, _("Last week"), _("Time interval to show: last week") );
    menu.Append ( idEditLastmonth, _("Last month"), _("Time interval to show: last month") );
    PopupMenu (&menu);
}

void yatishFrame::OnContextMenu3(wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idEditNew, _("New record..."), _("Add a record to the currently selected table") );
    menu.Append ( idEditReset, _("Reset filter"), _("Reset the viewing filter") );
  //wxPoint pos = ScreenToClient ( event.GetPosition() );
  //PopupMenu (&menu, pos);
    PopupMenu (&menu);
}

void yatishFrame::OnMenuitemEditSettingsSelected (wxCommandEvent& event) {
    yatishSettings dlg;
    dlg.Set (settings);
    if (dlg.ShowModal() == wxID_CANCEL) return;
    bool oldLog = settings.log2text;
    dlg.Get (settings);
    if (settings.log2text != oldLog) ToggleLog();
    masterDB.SetLimit (settings.limitRow, settings.rowLimit);
    tableID tid = (tableID) choiceTable->GetSelection();
    if (notebook->GetSelection() == 1) UpdateRows (tid);
}

void yatishFrame::OnHelp (wxCommandEvent& event) {
    yatishHelp.DisplayContents();
}

void yatishFrame::OnAbout (wxCommandEvent& event) {
    wxAboutDialogInfo info;
    info.SetName ("Yatish");
    info.SetVersion ("V0.3");
    wxString what (_("Yet Another TIme SHeet\n"
                     "Time tracking for freelancers/homeworkers\n\n"
                     "Built with:\n") );
    what << wxVERSION_STRING;
    what << "\nCode::Blocks\twxSmith\nwxDatabase\twxPdfDocument";
    info.SetDescription (what);
    info.SetCopyright ("(C) 2020-2021 EIF-services");
    info.SetLicence ("This program is free software:\n"
    "you can redistribute it and/or modify it\n"
    "under the terms of the GNU General Public License\n"
    "as published by the Free Software Foundation,\n"
    "either version 3 of the License, or (at your option) any later version.\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty\n"
    "of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
    "See the GNU General Public License for more details.\n"
    "You should have received a copy of the GNU General Public License\n"
    "along with this program.  If not, see https://www.gnu.org/licenses/");
    info.SetWebSite("https://www.eif-services.eu/yatish");
    wxString me (L"Nicolas P\u00E9renne <nicolas.perenne@eif-services.eu>");
    info.AddDeveloper (me);
    wxAboutBox (info, this);
}

// ...controls

void yatishFrame::OnNotebookPageChanged (wxNotebookEvent& event) {
    if (event.GetSelection() == 0) {
        SetStatusText (wxEmptyString, 2); // don't show SUM|AVG
        ResetChoices();
    }
    if (event.GetSelection() == 1) {
        masterDB.ClearFilter();
        ResetPickers();
        UpdateRows ( (tableID) choiceTable->GetSelection() );
    }
}

void yatishFrame::OnButtonStartClick (wxCommandEvent& event) {
    if ( !masterDB.StartTimeslot ( choiceProject->GetSelection(),
                                   choiceTask->GetSelection(),
                                   choiceTool->GetSelection() ) ) {
        wxLogError ("Timeslot could not be started");
        return;
    }
    Recording();
}

/** \todo `SetIcon()` not applied when `yatish.desktop` is installed (Linux issue) */
void yatishFrame::Recording () {
    clockStart = wxDateTime::Now();
    UpdateClock();
    timer.Start (1000);
    buttonStart->Disable();
    buttonStop->Enable();
    SetIcon ( wxIcon (yatish_recording_xpm) );
}

void yatishFrame::OnButtonStopClick (wxCommandEvent& event) {
    if ( !masterDB.StopTimeslot() ) {
        wxLogError ("Timeslot could not be stopped");
        return;
    }
    timer.Stop();
    buttonStop->Disable();
    buttonStart->Enable();
    SetIcon ( wxIcon (yatish_xpm) );
}

void yatishFrame::OnChoiceTableSelect (wxCommandEvent& event) {
    masterDB.ClearFilter();
    if (event.GetSelection() == timeslot_tid) {
        datePicker1->Enable();
        datePicker2->Enable();
        //buttonPDF->Enable();
    } else {
        datePicker1->Disable();
        datePicker2->Disable();
        //buttonPDF->Disable();
    }
    UpdateColumns();
}

void yatishFrame::OnDatePicker1Changed (wxDateEvent& event) {
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnDatePicker2Changed (wxDateEvent& event) {
    masterDB.SetLastDay ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}

void yatishFrame::OnListColumnClick (wxListEvent& event) {
    tableID tid = (tableID) choiceTable->GetSelection();
    if (tid == client_tid || tid == task_tid || tid == tool_tid)
        return;
    int project_col = -1,
        client_col  = -1,
        task_col    = -1,
        tool_col    = -1;
    if (tid == timeslot_tid) {
        project_col = 2;
        client_col = 3;
        task_col = 4;
        tool_col = 5;
    }
    if (tid == activity_tid) {
        project_col = 0;
        client_col = 1;
        task_col = 2;
        tool_col = 3;
    }
    if (tid == project_tid)
        client_col = 1;
    int col = event.GetColumn();
    int ret = wxID_CANCEL;
    if (col == project_col) {
        yatishDlgFilter dlg (&masterDB, project_tid);
        ret = dlg.ShowModal();
    }
    if (col == client_col) {
        yatishDlgFilter dlg (&masterDB, client_tid);
        ret = dlg.ShowModal();
    }
    if (col == task_col) {
        yatishDlgFilter dlg (&masterDB, task_tid);
        ret = dlg.ShowModal();
    }
    if (col == tool_col) {
        yatishDlgFilter dlg (&masterDB, tool_tid);
        ret = dlg.ShowModal();
    }
    if (ret == wxID_OK) {
        UpdateRows (tid);
        //ResetPickers();
    }
}

void yatishFrame::OnListKeyDown (wxListEvent& event) {
    if ( !wxGetKeyState (WXK_SHIFT) ) {
        event.Skip();
        return;
    }
    tableID tid = (tableID) choiceTable->GetSelection();
    long row_id = event.GetIndex(), sql_id = listCtrl->GetItemData (row_id);
    switch ( event.GetKeyCode() ) {
        case 'E':
          { int dlgEnd = wxID_CANCEL;
            if (tid == client_tid || tid == task_tid || tid == tool_tid) {
                yatishDlgName dlg (&masterDB, tid, sql_id);
                dlgEnd = dlg.ShowModal();
            } else if (tid == project_tid) {
                yatishDlgProject dlg (&masterDB, sql_id);
                dlgEnd = dlg.ShowModal();
            } else if (tid == activity_tid) {
                yatishDlgActivity dlg (&masterDB, sql_id);
                dlgEnd = dlg.ShowModal();
            } else { // tid == timeslot_tid
                if ( listCtrl->GetItemText (row_id, 1) .IsEmpty() ) {
                    wxMessageBox (_("Won't edit the current activity\n(first close it)."),
                                  _("Change selection"), wxOK);
                } else {
                    yatishDlgTimeslot dlg (&masterDB, sql_id);
                    dlgEnd = dlg.ShowModal();
                }
            }
            if (dlgEnd != wxID_CANCEL) UpdateRows (tid); }
            break;
        case 'D':
            if ( masterDB.Delete (tid, sql_id) ) UpdateRows (tid);
            break;
        default:
            event.Skip();
    }
}

void yatishFrame::OnButtonPDFClick(wxCommandEvent& event) {
    wxFileDialog pdfDlg (this, _("Specify the PDF file to be written"),
                         wxStandardPaths::Get().GetDocumentsDir(), "yatish.pdf",
                         "PDF|*.pdf", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (pdfDlg.ShowModal() == wxID_CANCEL) return;
    yatishPDF test ( settings, listCtrl, masterDB, pdfDlg.GetPath() );
}
