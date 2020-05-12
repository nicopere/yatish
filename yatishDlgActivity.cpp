#include "wx_pch.h"
#include "yatishDlgActivity.h"

#ifndef WX_PRECOMP
    //(*InternalHeadersPCH(yatishDlgActivity)
    #include <wx/string.h>
    #include <wx/intl.h>
    //*)
#endif
//(*InternalHeaders(yatishDlgActivity)
//*)

//(*IdInit(yatishDlgActivity)
const long yatishDlgActivity::idChoiceProject = wxNewId();
const long yatishDlgActivity::idChoiceTask = wxNewId();
const long yatishDlgActivity::idChoiceTool = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishDlgActivity, wxDialog)
    //(*EventTable(yatishDlgActivity)
    //*)
END_EVENT_TABLE()

/** This constructor initializes the dialog box with data from the SQL record identified by `sql_id`. */
yatishDlgActivity::yatishDlgActivity (yatishDBsqlite * p_db, long sql_id) {
    BuildContent();
    pdb = p_db;
    id = sql_id;
    bool choiceOK;
    choiceOK = pdb->FillChoice (choiceProject, project_tid);
    choiceOK = pdb->FillChoice (choiceTask, task_tid);
    choiceOK = pdb->FillChoice (choiceTool, tool_tid);
    if (!choiceOK) wxLogError ("Initialization of choices failed (yatishDlgActivity)");
    project = pdb->ChoiceSelector (project_tid, id);
    task    = pdb->ChoiceSelector (task_tid, id);
    tool    = pdb->ChoiceSelector (tool_tid, id);
    choiceProject->SetValidator ( wxGenericValidator (&project) );
    choiceTask   ->SetValidator ( wxGenericValidator (&task) );
    choiceTool   ->SetValidator ( wxGenericValidator (&tool) );
    Fit(); SetMaxSize ( GetSize() );
}

/** The dialog box is initially empty and only writes NEW records (the SAVE button is cancelled). */
yatishDlgActivity::yatishDlgActivity (yatishDBsqlite * p_db) {
    BuildContent();
    staticBoxSizer->GetStaticBox()->SetLabel (_("New row") );
    pdb = p_db;
    buttonSave->Disable();
    bool choiceOK;
    choiceOK = pdb->FillChoice (choiceProject, project_tid);
    choiceOK = pdb->FillChoice (choiceTask, task_tid);
    choiceOK = pdb->FillChoice (choiceTool, tool_tid);
    if (!choiceOK) wxLogError ("Initialization of choices failed (yatishDlgActivity)");
    project = 0;
    task    = 0;
    tool    = 0;
    choiceProject->SetValidator ( wxGenericValidator (&project) );
    choiceTask   ->SetValidator ( wxGenericValidator (&task) );
    choiceTool   ->SetValidator ( wxGenericValidator (&tool) );
    Fit(); SetMaxSize ( GetSize() );
    if ( choiceProject->IsEmpty() || choiceTask->IsEmpty() || choiceTool->IsEmpty() )
      buttonNew->Disable(); // in case we get here while some tables are still empty
}

void yatishDlgActivity::BuildContent () {
    //(*Initialize(yatishDlgActivity)
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer2;
    wxStaticText* StaticText1;
    wxStaticText* StaticText3;
    wxBoxSizer* BoxSizer1;
    wxButton* buttonCancel;
    wxStaticText* StaticText2;

    Create(0, wxID_ANY, _("Table: yatish_activity"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    staticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("(previously selected row)"));
    FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Project:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceProject = new wxChoice(this, idChoiceProject, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceProject"));
    FlexGridSizer1->Add(choiceProject, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Task:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceTask = new wxChoice(this, idChoiceTask, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTask"));
    FlexGridSizer1->Add(choiceTask, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(this, wxID_ANY, _("Tool:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceTool = new wxChoice(this, idChoiceTool, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTool"));
    FlexGridSizer1->Add(choiceTool, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    staticBoxSizer->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(staticBoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer2->Add(buttonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonSave = new wxButton(this, wxID_SAVE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_SAVE"));
    BoxSizer2->Add(buttonSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonNew = new wxButton(this, wxID_NEW, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_NEW"));
    BoxSizer2->Add(buttonNew, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(wxID_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgActivity::OnButtonSaveClick);
    Connect(wxID_NEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgActivity::OnButtonNewClick);
    //*)
}

yatishDlgActivity::~yatishDlgActivity () {
    //(*Destroy(yatishDlgActivity)
    //*)
}

void yatishDlgActivity::OnButtonSaveClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordActivity (id, project, task, tool) )
        EndModal (wxID_SAVE);
    else
        EndModal (wxID_CANCEL);
}

void yatishDlgActivity::OnButtonNewClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordActivity (wxNOT_FOUND, project, task, tool) )
        EndModal (wxID_NEW);
    else
        EndModal (wxID_CANCEL);
}
