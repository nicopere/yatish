#include "wx_pch.h"
#include "yatishDlgProject.h"

#ifndef WX_PRECOMP
    //(*InternalHeadersPCH(yatishDlgProject)
    #include <wx/string.h>
    #include <wx/intl.h>
    //*)
#endif
//(*InternalHeaders(yatishDlgProject)
//*)

//(*IdInit(yatishDlgProject)
const long yatishDlgProject::idTextCtrlName = wxNewId();
const long yatishDlgProject::idChoiceClient = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishDlgProject, wxDialog)
    //(*EventTable(yatishDlgProject)
    //*)
END_EVENT_TABLE()

/** This constructor initializes the dialog box with data from the SQL record identified by `sql_id`. */
yatishDlgProject::yatishDlgProject (yatishDBsqlite * p_db, long sql_id) {
    BuildContent();
    pdb = p_db;
    id = sql_id;
    name = pdb->ReadName (project_tid, id);
    textCtrlName->SetValidator ( wxTextValidator (wxFILTER_ASCII, &name) );
    if ( !pdb->FillChoice (choiceClient, client_tid) )
        wxLogError ("Initialization of choiceClient failed (yatishDlgProject)");
    choice = pdb->ChoiceSelector (client_tid, id);
    choiceClient->SetValidator ( wxGenericValidator (&choice) );
    Fit(); SetMaxSize ( GetSize() );
}

/** The dialog box is initially empty and only writes NEW records (the SAVE button is cancelled). */
yatishDlgProject::yatishDlgProject (yatishDBsqlite * p_db) {
    BuildContent();
    staticBoxSizer->GetStaticBox()->SetLabel (_("New row") );
    pdb = p_db;
    buttonSave->Disable();
    name = wxEmptyString;
    textCtrlName->SetValidator ( wxTextValidator (wxFILTER_ASCII, &name) );
    if ( !pdb->FillChoice (choiceClient, client_tid) )
        wxLogError ("Initialization of choiceClient failed (yatishDlgProject)");
    choice = 0;
    choiceClient->SetValidator ( wxGenericValidator (&choice) );
    Fit(); SetMaxSize ( GetSize() );
    // in case we get here while the database is still empty
    if ( choiceClient->IsEmpty() ) buttonNew->Disable();
}

void yatishDlgProject::BuildContent() {
    //(*Initialize(yatishDlgProject)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxButton* buttonCancel;
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;

    Create(0, wxID_ANY, _("Table: yatish_project"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    staticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("(previously selected row)"));
    FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    textCtrlName = new wxTextCtrl(this, idTextCtrlName, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextCtrlName"));
    FlexGridSizer1->Add(textCtrlName, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Client:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceClient = new wxChoice(this, idChoiceClient, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceClient"));
    FlexGridSizer1->Add(choiceClient, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(wxID_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgProject::OnButtonSaveClick);
    Connect(wxID_NEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgProject::OnButtonNewClick);
    //*)
}

yatishDlgProject::~yatishDlgProject () {
    //(*Destroy(yatishDlgProject)
    //*)
}

void yatishDlgProject::OnButtonSaveClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordProject (id, name, choice) )
        EndModal (wxID_SAVE);
    else
        EndModal (wxID_CANCEL);
}

void yatishDlgProject::OnButtonNewClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordProject (wxNOT_FOUND, name, choice) )
        EndModal (wxID_NEW);
    else
        EndModal (wxID_CANCEL);
}
