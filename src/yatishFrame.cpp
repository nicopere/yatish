/********************************************************************
 * Name:      yatishFrame.cpp
 * Purpose:   Implements the main Frame
 * Author:    Nicolas Pérenne (nicolas.perenne@eif-services.eu)
 * Created:   2020-02-11
 * Copyright: EIF-services (https://www.eif-services.eu/yatish)
 * License:   GPLv3
 ********************************************************************/

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
const long yatishFrame::idChoiceChart = wxNewId();
const long yatishFrame::idChoiceAggregate = wxNewId();
const long yatishFrame::idChoiceCluster = wxNewId();
const long yatishFrame::idDatePicker3 = wxNewId();
const long yatishFrame::idDatePicker4 = wxNewId();
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
const long yatishFrame::idEditSettings = wxNewId();
const long yatishFrame::idTimeToday = wxNewId();
const long yatishFrame::idTimeThisweek = wxNewId();
const long yatishFrame::idTimeThismonth = wxNewId();
const long yatishFrame::idTimeThisyear = wxNewId();
const long yatishFrame::idTimeYesterday = wxNewId();
const long yatishFrame::idTimeLastweek = wxNewId();
const long yatishFrame::idTimeLastmonth = wxNewId();
const long yatishFrame::idTimeLastyear = wxNewId();
const long yatishFrame::idHelpUser = wxNewId();
const long yatishFrame::idHelpAbout = wxNewId();
const long yatishFrame::idStatusBar = wxNewId();
const long yatishFrame::idTimer = wxNewId();
//*)

const long yatishFrame::idListActivityRecord = wxNewId();
const long yatishFrame::idListActivityListTimeslot = wxNewId();

BEGIN_EVENT_TABLE (yatishFrame, wxFrame)
    //(*EventTable(yatishFrame)
    //*)
    EVT_MENU(idListActivityRecord, yatishFrame::OnListActivityRecord)
    EVT_MENU(idListActivityListTimeslot, yatishFrame::OnListActivityListTimeslot)
    EVT_UPDATE_UI(idEditActivity, yatishFrame::OnMenuitemEditActivityUpdate)
    EVT_UPDATE_UI(idEditTable, yatishFrame::OnMenuitemEditTableUpdate)
    EVT_UPDATE_UI(idEditChart, yatishFrame::OnMenuitemEditChartUpdate)
    EVT_UPDATE_UI(idEditNew, yatishFrame::OnMenuitemEditNewUpdate)
    EVT_UPDATE_UI(idEditReset, yatishFrame::OnMenuitemEditResetUpdate)
    EVT_UPDATE_UI_RANGE(idTimeToday, idTimeLastyear, yatishFrame::OnMenuitemTimeTodayUpdate)
    EVT_UPDATE_UI(idChoiceAggregate, yatishFrame::OnChoiceAggregateUpdate)
    EVT_UPDATE_UI(idChoiceCluster, yatishFrame::OnChoiceClusterUpdate)
END_EVENT_TABLE()

yatishFrame::yatishFrame (wxWindow * parent, wxWindowID id) {
    //(*Initialize(yatishFrame)
    wxBoxSizer* boxSizer2;
    wxBoxSizer* boxSizer3;
    wxBoxSizer* boxSizer4;
    wxBoxSizer* boxSizer5;
    wxBoxSizer* boxSizer7;
    wxMenu* menu1;
    wxMenu* menu2;
    wxMenu* menu3;
    wxMenu* menu4;
    wxMenuBar* menuBar;
    wxMenuItem* menuitemEditActivity;
    wxMenuItem* menuitemEditChart;
    wxMenuItem* menuitemEditLastmonth;
    wxMenuItem* menuitemEditLastweek;
    wxMenuItem* menuitemEditLastyear;
    wxMenuItem* menuitemEditNew;
    wxMenuItem* menuitemEditReset;
    wxMenuItem* menuitemEditSettings;
    wxMenuItem* menuitemEditTable;
    wxMenuItem* menuitemEditThismonth;
    wxMenuItem* menuitemEditThisweek;
    wxMenuItem* menuitemEditThisyear;
    wxMenuItem* menuitemEditToday;
    wxMenuItem* menuitemEditYesteday;
    wxMenuItem* menuitemFileQuit;
    wxMenuItem* menuitemHelpAbout;
    wxMenuItem* menuitemHelpUser;
    wxPanel* panelCurrent;
    wxPanel* panelList;
    wxStaticBoxSizer* staticBoxSizer1;
    wxStaticBoxSizer* staticBoxSizer2;
    wxStaticBoxSizer* staticBoxSizer3;
    wxStaticBoxSizer* staticBoxSizer4;
    wxStaticBoxSizer* staticBoxSizer5;

    Create(parent, wxID_ANY, _("YATiSh"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    boxSizer1 = new wxBoxSizer(wxVERTICAL);
    notebook = new wxNotebook(this, idNotebook, wxDefaultPosition, wxDefaultSize, 0, _T("idNotebook"));
    panelCurrent = new wxPanel(notebook, idPanelCurrent, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelCurrent"));
    boxSizer2 = new wxBoxSizer(wxVERTICAL);
    boxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, panelCurrent, _("Select project, task and tool"));
    choiceProject = new wxChoice(panelCurrent, idChoiceProject, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceProject"));
    staticBoxSizer1->Add(choiceProject, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    choiceTask = new wxChoice(panelCurrent, idChoiceTask, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTask"));
    staticBoxSizer1->Add(choiceTask, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    choiceTool = new wxChoice(panelCurrent, idChoiceTool, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTool"));
    staticBoxSizer1->Add(choiceTool, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    boxSizer2->Add(staticBoxSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    buttonStart = new wxButton(panelCurrent, idButtonStart, _("&RECORD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonStart"));
    boxSizer3->Add(buttonStart, 1, wxALL|wxEXPAND, 5);
    buttonStop = new wxButton(panelCurrent, idButtonStop, _("&STOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonStop"));
    boxSizer3->Add(buttonStop, 1, wxALL|wxEXPAND, 5);
    boxSizer2->Add(boxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    boxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelCurrent->SetSizer(boxSizer2);
    boxSizer2->Fit(panelCurrent);
    boxSizer2->SetSizeHints(panelCurrent);
    panelList = new wxPanel(notebook, idPanelList, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelList"));
    boxSizer4 = new wxBoxSizer(wxVERTICAL);
    boxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, panelList, _("Table"));
    choiceTable = new wxChoice(panelList, idChoiceTable, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTable"));
    choiceTable->Append(_("Client"));
    choiceTable->Append(_("Task"));
    choiceTable->Append(_("Tool"));
    choiceTable->Append(_("Project"));
    choiceTable->Append(_("Activity"));
    choiceTable->SetSelection( choiceTable->Append(_("Timeslot")) );
    staticBoxSizer2->Add(choiceTable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer5->Add(staticBoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, panelList, _("Date interval (inclusive)"));
    datePicker1 = new wxDatePickerCtrl(panelList, idDatePicker1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker1"));
    staticBoxSizer3->Add(datePicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker2 = new wxDatePickerCtrl(panelList, idDatePicker2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker2"));
    staticBoxSizer3->Add(datePicker2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer5->Add(staticBoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonPDF = new wxButton(panelList, idButtonPDF, _("E&xport PDF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonPDF"));
    boxSizer5->Add(buttonPDF, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer4->Add(boxSizer5, 0, wxALL|wxEXPAND, 5);
    listCtrl = new wxListCtrl(panelList, idListCtrl, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("idListCtrl"));
    boxSizer4->Add(listCtrl, 1, wxALL|wxEXPAND, 5);
    panelList->SetSizer(boxSizer4);
    boxSizer4->Fit(panelList);
    boxSizer4->SetSizeHints(panelList);
    panelChart = new wxPanel(notebook, idPanelChart, wxDefaultPosition, wxDefaultSize, 0, _T("idPanelChart"));
    boxSizer6 = new wxBoxSizer(wxVERTICAL);
    boxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, panelChart, _("Chart type | Temporal aggregation"));
    choiceChart = new wxChoice(panelChart, idChoiceChart, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceChart"));
    choiceChart->SetSelection( choiceChart->Append(_("Time series")) );
    choiceChart->Append(_("Pie chart"));
    staticBoxSizer4->Add(choiceChart, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    choiceAggregate = new wxChoice(panelChart, idChoiceAggregate, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceAggregate"));
    choiceAggregate->SetSelection( choiceAggregate->Append(_("Hours (total)")) );
    choiceAggregate->Append(_("Days (worked)"));
    choiceAggregate->Append(_("Hours/day (max)"));
    choiceAggregate->Append(_("Time range (max)"));
    choiceAggregate->Append(_("Minutes/timeslot (average)"));
    staticBoxSizer4->Add(choiceAggregate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer7->Add(staticBoxSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, panelChart, _("Data clustering | Date interval"));
    choiceCluster = new wxChoice(panelChart, idChoiceCluster, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceCluster"));
    choiceCluster->Append(_("Clients"));
    choiceCluster->Append(_("Projects"));
    choiceCluster->Append(_("Tasks"));
    choiceCluster->Append(_("Tools"));
    choiceCluster->SetSelection( choiceCluster->Append(_("None")) );
    staticBoxSizer5->Add(choiceCluster, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker3 = new wxDatePickerCtrl(panelChart, idDatePicker3, wxDefaultDateTime, wxPoint(-1,-1), wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker3"));
    staticBoxSizer5->Add(datePicker3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker4 = new wxDatePickerCtrl(panelChart, idDatePicker4, wxDefaultDateTime, wxPoint(-1,-1), wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker4"));
    staticBoxSizer5->Add(datePicker4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer7->Add(staticBoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    boxSizer6->Add(boxSizer7, 0, wxALL|wxEXPAND, 5);
    panelChart->SetSizer(boxSizer6);
    boxSizer6->Fit(panelChart);
    boxSizer6->SetSizeHints(panelChart);
    notebook->AddPage(panelCurrent, _("Current activity"), false);
    notebook->AddPage(panelList, _("List/Edit"), false);
    notebook->AddPage(panelChart, _("Charts"), false);
    boxSizer1->Add(notebook, 3, wxALL|wxEXPAND, 0);
    textCtrl = new wxTextCtrl(this, idTextCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("idTextCtrl"));
    boxSizer1->Add(textCtrl, 1, wxALL|wxEXPAND, 5);
    SetSizer(boxSizer1);
    menuBar = new wxMenuBar();
    menu1 = new wxMenu();
    menuitemFileConnect = new wxMenuItem(menu1, idFileConnect, _("&Connect\tCtrl-C"), _("Connect to a (remote) MySQL/MariaDB server"), wxITEM_NORMAL);
    menu1->Append(menuitemFileConnect);
    menuitemFileUpdate = new wxMenuItem(menu1, idFileUpdate, _("&Update\tCtrl-U"), _("Update remote database"), wxITEM_NORMAL);
    menu1->Append(menuitemFileUpdate);
    menuitemFileUpdate->Enable(false);
    menuitemFileUpload = new wxMenuItem(menu1, idFileUpload, _("Up&load"), _("Replace remote data (by local)"), wxITEM_NORMAL);
    menu1->Append(menuitemFileUpload);
    menuitemFileUpload->Enable(false);
    menuitemFileDownload = new wxMenuItem(menu1, idFileDownload, _("&Download"), _("Replace local data (by remote)"), wxITEM_NORMAL);
    menu1->Append(menuitemFileDownload);
    menuitemFileDownload->Enable(false);
    menu1->AppendSeparator();
    menuitemFileQuit = new wxMenuItem(menu1, idFileQuit, _("&Quit\tCtrl-Q"), wxEmptyString, wxITEM_NORMAL);
    menu1->Append(menuitemFileQuit);
    menuBar->Append(menu1, _("&File"));
    menu2 = new wxMenu();
    menuitemEditActivity = new wxMenuItem(menu2, idEditActivity, _("&Activity\tCtrl-A"), _("Start/stop current activity"), wxITEM_NORMAL);
    menu2->Append(menuitemEditActivity);
    menuitemEditTable = new wxMenuItem(menu2, idEditTable, _("&Tables\tCtrl-T"), _("Edit any table"), wxITEM_NORMAL);
    menu2->Append(menuitemEditTable);
    menuitemEditChart = new wxMenuItem(menu2, idEditChart, _("&Charts\tCtrl-G"), _("Look at various charts"), wxITEM_NORMAL);
    menu2->Append(menuitemEditChart);
    menu2->AppendSeparator();
    menuitemEditNew = new wxMenuItem(menu2, idEditNew, _("&New record...\tCtrl-N"), _("Add a record to the currently selected table"), wxITEM_NORMAL);
    menu2->Append(menuitemEditNew);
    menuitemEditReset = new wxMenuItem(menu2, idEditReset, _("&Reset filter\tCtrl-R"), _("Reset the viewing filter"), wxITEM_NORMAL);
    menu2->Append(menuitemEditReset);
    menu2->AppendSeparator();
    menuitemEditSettings = new wxMenuItem(menu2, idEditSettings, _("&Settings...\tCtrl-S"), _("Set user preferences"), wxITEM_NORMAL);
    menu2->Append(menuitemEditSettings);
    menuBar->Append(menu2, _("&Edit"));
    menu3 = new wxMenu();
    menuitemEditToday = new wxMenuItem(menu3, idTimeToday, _("Today"), _("Time interval to show: today"), wxITEM_NORMAL);
    menu3->Append(menuitemEditToday);
    menuitemEditThisweek = new wxMenuItem(menu3, idTimeThisweek, _("This week"), _("Time interval to show: this week"), wxITEM_NORMAL);
    menu3->Append(menuitemEditThisweek);
    menuitemEditThismonth = new wxMenuItem(menu3, idTimeThismonth, _("This month"), _("Time interval to show: this month"), wxITEM_NORMAL);
    menu3->Append(menuitemEditThismonth);
    menuitemEditThisyear = new wxMenuItem(menu3, idTimeThisyear, _("This year"), _("Time interval to show: this year"), wxITEM_NORMAL);
    menu3->Append(menuitemEditThisyear);
    menu3->AppendSeparator();
    menuitemEditYesteday = new wxMenuItem(menu3, idTimeYesterday, _("Yesterday"), _("Time interval to show: yesterday"), wxITEM_NORMAL);
    menu3->Append(menuitemEditYesteday);
    menuitemEditLastweek = new wxMenuItem(menu3, idTimeLastweek, _("Last week"), _("Time interval to show: last week"), wxITEM_NORMAL);
    menu3->Append(menuitemEditLastweek);
    menuitemEditLastweek->Enable(false);
    menuitemEditLastmonth = new wxMenuItem(menu3, idTimeLastmonth, _("Last month"), _("Time interval to show: last month"), wxITEM_NORMAL);
    menu3->Append(menuitemEditLastmonth);
    menuitemEditLastyear = new wxMenuItem(menu3, idTimeLastyear, _("Last year"), _("Time interval to show: last year"), wxITEM_NORMAL);
    menu3->Append(menuitemEditLastyear);
    menuBar->Append(menu3, _("&Time"));
    menu4 = new wxMenu();
    menuitemHelpUser = new wxMenuItem(menu4, idHelpUser, _("&User guide\tF1"), wxEmptyString, wxITEM_NORMAL);
    menu4->Append(menuitemHelpUser);
    menuitemHelpAbout = new wxMenuItem(menu4, idHelpAbout, _("&About..."), wxEmptyString, wxITEM_NORMAL);
    menu4->Append(menuitemHelpAbout);
    menuBar->Append(menu4, _("&Help"));
    SetMenuBar(menuBar);
    statusBar = new wxStatusBar(this, idStatusBar, 0, _T("idStatusBar"));
    int __wxStatusBarWidths_1[3] = { 65, 85, -1 };
    int __wxStatusBarStyles_1[3] = { wxSB_RAISED, wxSB_RAISED, wxSB_NORMAL };
    statusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);
    timer.SetOwner(this, idTimer);
    boxSizer1->Fit(this);
    boxSizer1->SetSizeHints(this);

    Connect(idButtonStart,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonStartClick);
    Connect(idButtonStop,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonStopClick);
    Connect(idChoiceTable,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&yatishFrame::OnChoiceTableSelect);
    Connect(idDatePicker1,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker1Changed);
    Connect(idDatePicker2,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker2Changed);
    Connect(idButtonPDF,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishFrame::OnButtonPDFClick);
    Connect(idListCtrl,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&yatishFrame::OnListItemRightClick);
    Connect(idListCtrl,wxEVT_COMMAND_LIST_KEY_DOWN,(wxObjectEventFunction)&yatishFrame::OnListKeyDown);
    Connect(idListCtrl,wxEVT_COMMAND_LIST_COL_CLICK,(wxObjectEventFunction)&yatishFrame::OnListColumnClick);
    Connect(idChoiceChart,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&yatishFrame::OnChoiceChartSelect);
    Connect(idChoiceAggregate,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&yatishFrame::OnChoiceAggregateSelect);
    Connect(idChoiceCluster,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&yatishFrame::OnChoiceClusterSelect);
    Connect(idDatePicker3,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker3Changed);
    Connect(idDatePicker4,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&yatishFrame::OnDatePicker4Changed);
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
    Connect(idEditSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemEditSettingsSelected);
    Connect(idTimeToday,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeTodaySelected);
    Connect(idTimeThisweek,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeThisweekSelected);
    Connect(idTimeThismonth,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeThismonthSelected);
    Connect(idTimeThisyear,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeThisyearSelected);
    Connect(idTimeYesterday,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeYesterdaySelected);
    Connect(idTimeLastweek,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeLastweekSelected);
    Connect(idTimeLastmonth,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeLastmonthSelected);
    Connect(idTimeLastyear,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnMenuitemTimeLastyearSelected);
    Connect(idHelpUser,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnHelp);
    Connect(idHelpAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&yatishFrame::OnAbout);
    Connect(idTimer,wxEVT_TIMER,(wxObjectEventFunction)&yatishFrame::OnTimerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&yatishFrame::OnClose);
    //*)
    datePicker1->Bind (wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu1, this);
    datePicker2->Bind (wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu2, this);
    datePicker3->Bind (wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu3, this);
    datePicker4->Bind (wxEVT_CONTEXT_MENU, &yatishFrame::OnContextMenu4, this);
    SetIcon ( wxIcon (yatish_xpm) ); // no effect in Ubuntu Jammy Jellyfish
    help.Initialize (wxStandardPaths::Get().GetDataDir() + wxFILE_SEP_PATH + "yatish");
    buttonStop->Disable(); clockStart = wxDateTime::Now();
    UpdateClock(); UpdateStatus (mysql_off); SetStatusBarPane (2);
    masterDB.SetLimit (settings.limitRow, settings.rowLimit);
    if (settings.log2text)
        defaultLog = wxLog::SetActiveTarget( new wxLogTextCtrl (textCtrl) );
    else {
        textCtrl->Hide(); boxSizer1->SetSizeHints (this);
    }
    ResetChoices(); ResetPickersT(); UpdateColumns();
    SetStatusText (wxEmptyString, 2);
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
    slaveDB  = nullptr;
    plot = nullptr;
    selectedActivityID = 0l;
    currentChartLib = wxMathPlot;
    currentPlotType = timeSeries;
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
    choiceOK = masterDB.FillChoice (choiceTask,    task_tid);
    choiceOK = masterDB.FillChoice (choiceTool,    tool_tid);
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
        choiceTask   ->SetSelection (masterDB.ChoiceSelector (task_tid,    lastActivityID) );
        choiceTool   ->SetSelection (masterDB.ChoiceSelector (tool_tid,    lastActivityID) );
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

void yatishFrame::ResetPickersT () {
    masterDB.ClearFilter();
    wxDateTime first = masterDB.First(), last = masterDB.Last();
    datePicker1->SetValue (first);
    datePicker2->SetValue (last );
    masterDB.SetFirstDay  (first);
    masterDB.SetLastDay   (last );
}
void yatishFrame::ResetPickersG () {
    masterDB.ClearFilter();
    wxDateTime first = masterDB.First(), last = masterDB.Last();
    datePicker3->SetValue (first);
    datePicker4->SetValue (last );
    plot->SetFirstDay     (first);
    plot->SetLastDay      (last );
}

void yatishFrame::NewPlot() {
    if (plot) {
        if (settings.lib == currentChartLib && choiceChart->GetSelection() == currentPlotType)
            return;
        else {
            boxSizer6->GetItem (1) ->DeleteWindows();
            boxSizer6->Detach (1);
            boxSizer6->Layout();
        }
    }
    if (settings.lib == wxMathPlot)  {
        choiceChart->SetSelection (timeSeries);
        plot = new yatishMathPlot  (panelChart, &masterDB);
        currentChartLib = wxMathPlot;
        currentPlotType = timeSeries;
    } else if (settings.lib == wxFreeChart) {
        if (choiceChart->GetSelection() == timeSeries) {
            plot = new yatishFreeSerie (panelChart, &masterDB);
            currentPlotType = timeSeries;
        } else {
            plot = new yatishFreePie (panelChart, &masterDB);
            currentPlotType = pieChart;
        }
        currentChartLib = wxFreeChart;
    } else { //settings.lib == wxCharts
        if (choiceChart->GetSelection() == timeSeries) {
            plot = new yatishChartSerie (panelChart, &masterDB);
            currentPlotType = timeSeries;
        } else {
            plot = new yatishChartPie (panelChart, &masterDB);
            currentPlotType = pieChart;
        }
        currentChartLib = wxCharts;
    }
    ResetPickersG();
    plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                     (AggregateType)choiceAggregate->GetSelection() );
    boxSizer6->Add (dynamic_cast <wxWindow *> (plot), 1, wxALL|wxEXPAND, 5);
    boxSizer6->Layout();
    boxSizer1->SetSizeHints (this);
    UNFORTUNATE_TRICK
    SetStatusText (plot->TotalFormatted(), 2);
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
        textCtrl->Show(); boxSizer1->SetSizeHints (this);
    } else {
        delete wxLog::SetActiveTarget (defaultLog);
        textCtrl->Hide(); boxSizer1->SetSizeHints (this);
    }
}

/********
 Handlers
 ********/

void yatishFrame::OnQuit (wxCommandEvent& event) {
    Close();
}

void yatishFrame::OnClose (wxCloseEvent& event) {
    if ( help.GetFrame() ) help.GetFrame()->Close (true);
    if (settings.log2text) delete wxLog::SetActiveTarget (defaultLog);
    delete slaveDB;
    delete plot;
    Destroy();
}

void yatishFrame::OnTimerTrigger (wxTimerEvent& event) {
    UpdateClock();
}

void yatishFrame::OnNotebookPageChanged (wxNotebookEvent& event) {
    switch ( event.GetSelection() ) {
        case 0:
            SetStatusText (wxEmptyString, 2);
            ResetChoices();
            break;
        case 1:
            ResetPickersT();
            UpdateRows ( (tableID) choiceTable->GetSelection() );
            break;
        case 2:
            NewPlot();
    }
}

/*************
 Menu handlers
 *************/

void yatishFrame::OnMenuitemFileConnectSelected (wxCommandEvent& event) {
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
    } else
       wxMessageBox (_("done."), _("Database update:"), wxOK);
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
    } else
       wxMessageBox (_("done."), _("Database upload:"), wxOK);
}

/** \todo wxBusyCursor and SetStatusText() off delay */
void yatishFrame::OnMenuitemFileDownloadSelected (wxCommandEvent& event) {
    if ( wxMessageBox ( _("Local data (if any) will be\noverwritten by remote ones."),
                        _("Are you sure?"),
                        wxICON_EXCLAMATION|wxOK|wxCANCEL|wxCANCEL_DEFAULT )
         == wxCANCEL ) return;
    wxBusyCursor wait; // Ubuntu: didn't work before Jammy Jellyfish
                       // (but the cursor is static until Download() has finished, and is reset when moving out of the window)
    SetStatusText (_("Please wait, working..."), 2); // applied _after_ Download() in Ubuntu Jammy Jellyfish...
    int err = slaveDB->Download();
    SetStatusText (wxEmptyString, 2);                // ...thus the message above is never seen!
    if (err == 2006 || err == 2013) {
        wxLogMessage (_("MySQL connection timed out: try to reconnect...") );
        UpdateStatus (mysql_err);
        ToggleConnect();
    } else {
        wxMessageBox (_("done."), _("Database download:"), wxOK);
        int page = notebook->GetSelection();
        if (page == 0) ResetChoices();
        if (page == 1) {
            ResetPickersT();
            UpdateRows ( (tableID) choiceTable->GetSelection() );
        }
    }
}

void yatishFrame::OnMenuitemEditActivitySelected (wxCommandEvent& event) {
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
void yatishFrame::OnMenuitemEditChartSelected (wxCommandEvent& event) {
    notebook->SetSelection (2);
}
void yatishFrame::OnMenuitemEditChartUpdate (wxUpdateUIEvent& event) {
    event.Enable (notebook->GetSelection() != 2);
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
    if (notebook->GetSelection() == 1) {
        ResetPickersT();
        UpdateRows ( (tableID) choiceTable->GetSelection() );
    } else {
        ResetPickersG();
        plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                         (AggregateType)choiceAggregate->GetSelection() );
        UNFORTUNATE_TRICK
        SetStatusText (plot->TotalFormatted(), 2);
    }
}

void yatishFrame::OnMenuitemEditResetUpdate (wxUpdateUIEvent& event) {
    bool filterTavailable = (notebook->GetSelection() == 1);
    if (filterTavailable) {
        tableID tid = (tableID) choiceTable->GetSelection();
        filterTavailable = filterTavailable && ( tid == project_tid || tid == activity_tid || tid == timeslot_tid );
    }
    event.Enable (filterTavailable || notebook->GetSelection() == 2);
}

void yatishFrame::OnMenuitemTimeTodayUpdate (wxUpdateUIEvent& event) {
    tableID tid = (tableID) choiceTable->GetSelection();
    event.Enable ( (notebook->GetSelection() == 1 && tid == timeslot_tid) || notebook->GetSelection() == 2 );
}

void yatishFrame::OnMenuitemTimeTodaySelected (wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    datePicker2->SetValue (dt);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}
void yatishFrame::OnMenuitemTimeThisweekSelected (wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    datePicker2->SetValue (dt);
    dt.SetToPrevWeekDay (wxDateTime::Mon);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}
void yatishFrame::OnMenuitemTimeThismonthSelected (wxCommandEvent& event) {
    wxDateTime dt1 = wxDateTime::Today(), dt2 = dt1;
    dt1.SetDay (1);
    if (notebook->GetSelection() == 1) {
        datePicker2->SetValue (dt2);
        datePicker1->SetValue (dt1);
        masterDB.SetFirstDay ( datePicker1->GetValue() );
        masterDB.SetLastDay  ( datePicker2->GetValue() );
        UpdateRows (timeslot_tid);
    } else {
        datePicker4->SetValue (dt2);
        datePicker3->SetValue (dt1);
        plot->SetFirstDay ( datePicker3->GetValue() );
        plot->SetLastDay  ( datePicker4->GetValue() );
        plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                         (AggregateType)choiceAggregate->GetSelection() );
        UNFORTUNATE_TRICK
        SetStatusText (plot->TotalFormatted(), 2);
    }
}
void yatishFrame::OnMenuitemTimeThisyearSelected (wxCommandEvent& event) {
    wxDateTime dt1 = wxDateTime::Today(), dt2 = dt1;
    dt1.SetMonth (wxDateTime::Jan); dt1.SetDay (1);
    if (notebook->GetSelection() == 1) {
        datePicker2->SetValue (dt2);
        datePicker1->SetValue (dt1);
        masterDB.SetFirstDay ( datePicker1->GetValue() );
        masterDB.SetLastDay  ( datePicker2->GetValue() );
        UpdateRows (timeslot_tid);
    } else {
        datePicker4->SetValue (dt2);
        datePicker3->SetValue (dt1);
        plot->SetFirstDay ( datePicker3->GetValue() );
        plot->SetLastDay  ( datePicker4->GetValue() );
        plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                         (AggregateType)choiceAggregate->GetSelection() );
        UNFORTUNATE_TRICK
        SetStatusText (plot->TotalFormatted(), 2);
    }
}

void yatishFrame::OnMenuitemTimeYesterdaySelected (wxCommandEvent& event) {
    wxDateTime dt = wxDateTime::Today();
    dt -= wxDateSpan::Day();
    datePicker2->SetValue (dt);
    datePicker1->SetValue (dt);
    masterDB.SetFirstDay ( datePicker1->GetValue() );
    masterDB.SetLastDay  ( datePicker2->GetValue() );
    UpdateRows (timeslot_tid);
}
void yatishFrame::OnMenuitemTimeLastweekSelected (wxCommandEvent& event) {
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
void yatishFrame::OnMenuitemTimeLastmonthSelected (wxCommandEvent& event) {
    wxDateTime dt1 = wxDateTime::Today(), dt2 = dt1;
    dt1 -= wxDateSpan::Month(); dt1.SetDay (1);
    dt2 -= wxDateSpan::Month(); dt2.SetToLastMonthDay();
    if (notebook->GetSelection() == 1) {
        datePicker2->SetValue (dt2);
        datePicker1->SetValue (dt1);
        masterDB.SetFirstDay ( datePicker1->GetValue() );
        masterDB.SetLastDay  ( datePicker2->GetValue() );
        UpdateRows (timeslot_tid);
    } else {
        datePicker4->SetValue (dt2);
        datePicker3->SetValue (dt1);
        plot->SetFirstDay ( datePicker3->GetValue() );
        plot->SetLastDay  ( datePicker4->GetValue() );
        plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                         (AggregateType)choiceAggregate->GetSelection() );
        UNFORTUNATE_TRICK
        SetStatusText (plot->TotalFormatted(), 2);
    }
}
void yatishFrame::OnMenuitemTimeLastyearSelected (wxCommandEvent& event) {
    wxDateTime dt1 = wxDateTime::Today(), dt2 = dt1;
    dt1 -= wxDateSpan::Year(); dt1.SetMonth (wxDateTime::Jan); dt1.SetDay (1);
    dt2 -= wxDateSpan::Year(); dt2.SetMonth (wxDateTime::Dec); dt2.SetToLastMonthDay();
    if (notebook->GetSelection() == 1) {
        datePicker2->SetValue (dt2);
        datePicker1->SetValue (dt1);
        masterDB.SetFirstDay ( datePicker1->GetValue() );
        masterDB.SetLastDay  ( datePicker2->GetValue() );
        UpdateRows (timeslot_tid);
    } else {
        datePicker4->SetValue (dt2);
        datePicker3->SetValue (dt1);
        plot->SetFirstDay ( datePicker3->GetValue() );
        plot->SetLastDay  ( datePicker4->GetValue() );
        plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                         (AggregateType)choiceAggregate->GetSelection() );
        UNFORTUNATE_TRICK
        SetStatusText (plot->TotalFormatted(), 2);
    }
}

void yatishFrame::OnContextMenu1 (wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idTimeToday, _("Today"), _("Time interval to show: today") );
    menu.Append ( idTimeThisweek, _("This week"), _("Time interval to show: this week") );
    menu.Append ( idTimeThismonth, _("This month"), _("Time interval to show: this month") );
    PopupMenu (&menu);
}
void yatishFrame::OnContextMenu3 (wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idTimeThismonth, _("This month"), _("Time interval to show: this month") );
    menu.Append ( idTimeThisyear, _("This year"), _("Time interval to show: this year") );
    PopupMenu (&menu);
}

void yatishFrame::OnContextMenu2 (wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idTimeYesterday, _("Yesterday"), _("Time interval to show: yesterday") );
    menu.Append ( idTimeLastweek, _("Last week"), _("Time interval to show: last week") );
    menu.Append ( idTimeLastmonth, _("Last month"), _("Time interval to show: last month") );
    PopupMenu (&menu);
}
void yatishFrame::OnContextMenu4 (wxContextMenuEvent& event) {
    wxMenu menu;
    menu.Append ( idTimeLastmonth, _("Last month"), _("Time interval to show: last month") );
    menu.Append ( idTimeLastyear, _("Last year"), _("Time interval to show: last year") );
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
    if (notebook->GetSelection() == 2) NewPlot();
}

void yatishFrame::OnHelp (wxCommandEvent& event) {
    help.DisplayContents();
}

void yatishFrame::OnAbout (wxCommandEvent& event) {
    wxAboutDialogInfo info;
    info.SetName ("Yatish");
    info.SetVersion ("V0.4");
    wxString what (_("Yet Another TIme SHeet\n"
                     "Time tracking for freelancers/homeworkers\n\n"
                     "Built with:\n") );
    what << wxVERSION_STRING;
    what << "\nCode::Blocks\twxSmith\nwxDatabase\twxPdfDocument\nwxMathPlot\twxFreeChart\twxCharts";
    info.SetDescription (what);
    info.SetCopyright ("(C) 2020-2023 EIF-services");
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
    "along with this program. If not, see https://www.gnu.org/licenses/");
    info.SetWebSite("https://www.eif-services.eu/yatish");
    wxString me (L"Nicolas P\u00E9renne <nicolas.perenne@eif-services.eu>");
    info.AddDeveloper (me);
    wxAboutBox (info, this);
}

/****************
 Control handlers
 ****************/

void yatishFrame::OnButtonStartClick (wxCommandEvent& event) {
    if ( !masterDB.StartTimeslot ( choiceProject->GetSelection(),
                                   choiceTask->GetSelection(),
                                   choiceTool->GetSelection() ) ) {
        wxLogError ("Timeslot could not be started");
        return;
    }
    Recording();
}

void yatishFrame::Recording () {
    clockStart = wxDateTime::Now();
    UpdateClock();
    timer.Start (1000);
    buttonStart->Disable();
    buttonStop->Enable();
    SetIcon ( wxIcon (yatish_recording_xpm) ); // no effect in Ubuntu Jammy Jellyfish
}

void yatishFrame::OnButtonStopClick (wxCommandEvent& event) {
    if ( !masterDB.StopTimeslot() ) {
        wxLogError ("Timeslot could not be stopped");
        return;
    }
    timer.Stop();
    buttonStop->Disable();
    buttonStart->Enable();
    SetIcon ( wxIcon (yatish_xpm) ); // no effect in Ubuntu Jammy Jellyfish
}

void yatishFrame::OnChoiceTableSelect (wxCommandEvent& event) {
    masterDB.ClearFilter();
    if (event.GetSelection() == timeslot_tid) {
        datePicker1->Enable();
        datePicker2->Enable();
    } else {
        datePicker1->Disable();
        datePicker2->Disable();
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
    if (ret == wxID_OK) UpdateRows (tid);
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
            if ( wxMessageBox ( _("Deleting a record..."),
                                _("Are you sure?"),
                                wxICON_EXCLAMATION|wxOK|wxCANCEL|wxCANCEL_DEFAULT )
                 == wxCANCEL ) break;
            if ( masterDB.Delete (tid, sql_id) ) UpdateRows (tid);
            break;
        default:
            event.Skip();
    }
}

void yatishFrame::OnListActivityRecord (wxCommandEvent& event) {
    wxASSERT (selectedActivityID);
    if ( buttonStop->IsEnabled() ) {
        wxMessageBox (_("Can't start a new activity\n(first close the current one)."),
                      _("Stop current activity"), wxOK);
        return;
    }
    int projectChoice = masterDB.ChoiceSelector (project_tid, selectedActivityID),
        taskChoice    = masterDB.ChoiceSelector (task_tid,    selectedActivityID),
        toolChoice    = masterDB.ChoiceSelector (tool_tid,    selectedActivityID);
    choiceProject->SetSelection (projectChoice);
    choiceTask   ->SetSelection (taskChoice);
    choiceTool   ->SetSelection (toolChoice);
    notebook->ChangeSelection (0);
    masterDB.StartTimeslot (projectChoice, taskChoice, toolChoice);
    Recording();
}
void yatishFrame::OnListActivityListTimeslot (wxCommandEvent& event) {
    wxASSERT (selectedActivityID);
    datePicker1->Enable(); datePicker2->Enable(); ResetPickersT();
    masterDB.AddToFilter (selectedActivityID);
    choiceTable->SetSelection (timeslot_tid);
    UpdateColumns();
}
void yatishFrame::OnListItemRightClick(wxListEvent& event) {
    if (choiceTable->GetSelection() != activity_tid) return;
    selectedActivityID = listCtrl->GetItemData ( event.GetIndex() );
    wxMenu menu;
    menu.Append ( idListActivityRecord, _("Record") );
    menu.Append ( idListActivityListTimeslot, _("List") );
    PopupMenu (&menu);
}

void yatishFrame::OnButtonPDFClick (wxCommandEvent& event) {
    wxFileDialog pdfDlg (this, _("Specify the PDF file to be written"),
                         wxStandardPaths::Get().GetDocumentsDir(), "yatish.pdf",
                         "PDF|*.pdf", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (pdfDlg.ShowModal() == wxID_CANCEL) return;
    yatishPDF test ( settings, listCtrl, masterDB, pdfDlg.GetPath() );
}

/**************************
 Control handlers: panel #3
 **************************/

void yatishFrame::OnChoiceChartSelect (wxCommandEvent& event) {
    PlotType plotType = (PlotType)event.GetSelection();
    if (currentChartLib == wxMathPlot && plotType == pieChart) {
        wxLogMessage (_("This plot is not provided by the current library.\n"
                        "Choose another one in the Settings (Ctrl-P).") );
        choiceChart->SetSelection (timeSeries);
        return;
    }
    if (plotType == currentPlotType) return;
    if (choiceCluster->GetCount() == 5) { // we can't wait for OnChoiceClusterUpdate() to be called
        if (choiceCluster->GetSelection() == 4) choiceCluster->Select (projectClusters);
        choiceCluster->Delete (4);
    }
    NewPlot();
}

void yatishFrame::OnChoiceAggregateUpdate (wxUpdateUIEvent& event) {
    if (choiceChart->GetSelection() == pieChart || choiceCluster->GetSelection() != none) {
        choiceAggregate->SetSelection (hoursTotal);
        event.Enable (false);
    } else
        event.Enable (true);
}
void yatishFrame::OnChoiceAggregateSelect (wxCommandEvent& event) {
    plot->PlotData ( none, (AggregateType)event.GetSelection() );
    UNFORTUNATE_TRICK
}

void yatishFrame::OnChoiceClusterUpdate (wxUpdateUIEvent& event) {
    if (choiceCluster->GetCount() == 4 && choiceChart->GetSelection() == timeSeries)
        choiceCluster->Append (_("None") );
    if (choiceCluster->GetCount() == 5 && choiceChart->GetSelection() == pieChart) {
        if (choiceCluster->GetSelection() == 4) choiceCluster->Select (projectClusters);
        choiceCluster->Delete (4);
    }
}
void yatishFrame::OnChoiceClusterSelect (wxCommandEvent& event) {
    choiceAggregate->SetSelection ( hoursTotal );
    plot->PlotData ( (ClusterType)event.GetSelection(), hoursTotal );
    UNFORTUNATE_TRICK
}

void yatishFrame::OnDatePicker3Changed (wxDateEvent& event) {
    plot->SetFirstDay ( event.GetDate() );
    plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                     (AggregateType)choiceAggregate->GetSelection() );
    UNFORTUNATE_TRICK
    SetStatusText (plot->TotalFormatted(), 2);
}
void yatishFrame::OnDatePicker4Changed (wxDateEvent& event) {
    plot->SetLastDay ( event.GetDate() );
    plot->PlotData ( (ClusterType)choiceCluster->GetSelection(),
                     (AggregateType)choiceAggregate->GetSelection() );
    UNFORTUNATE_TRICK
    SetStatusText (plot->TotalFormatted(), 2);
}
