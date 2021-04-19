#include "wx_pch.h"
#include "yatishDlgName.h"

#ifndef WX_PRECOMP
    //(*InternalHeadersPCH(yatishDlgName)
    #include <wx/string.h>
    #include <wx/intl.h>
    //*)
#endif
//(*InternalHeaders(yatishDlgName)
//*)

//(*IdInit(yatishDlgName)
const long yatishDlgName::idTextCtrl = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishDlgName, wxDialog)
    //(*EventTable(yatishDlgName)
    //*)
END_EVENT_TABLE()

/** This constructor initializes the dialog box with data from the SQL record identified by `sql_id`. */
yatishDlgName::yatishDlgName (yatishDBsqlite * p_db, tableID t_id, long sql_id) {
    BuildContent();
    pdb = p_db;
    tid = t_id;
    id = sql_id;
    name = pdb->ReadName (tid, id);
    textCtrl->SetValidator ( wxTextValidator (wxFILTER_ASCII, &name) );
    SetLabel ( wxString(_("Table: yatish_") ) + yatishDB::tableName[tid] );
    Fit(); SetMaxSize ( GetSize() );
}

/** The dialog box is initially empty and only writes NEW records (the SAVE button is cancelled). */
yatishDlgName::yatishDlgName (yatishDBsqlite * p_db, tableID t_id) {
    BuildContent();
    staticBoxSizer->GetStaticBox()->SetLabel (_("New row") );
    pdb = p_db;
    tid = t_id;
    buttonSave->Disable();
    name = wxEmptyString;
    textCtrl->SetValidator ( wxTextValidator (wxFILTER_ASCII, &name) );
    SetLabel ( wxString(_("Table: yatish_") ) + yatishDB::tableName[tid] );
    Fit(); SetMaxSize ( GetSize() );
}

void yatishDlgName::BuildContent () {
    //(*Initialize(yatishDlgName)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxButton* buttonCancel;
    wxButton* buttonNew;
    wxStaticText* StaticText;

    Create(0, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    staticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("(previously selected row)"));
    StaticText = new wxStaticText(this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    staticBoxSizer->Add(StaticText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textCtrl = new wxTextCtrl(this, idTextCtrl, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextCtrl"));
    textCtrl->SetMaxLength(20);
    staticBoxSizer->Add(textCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(wxID_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgName::OnButtonSaveClick);
    Connect(wxID_NEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgName::OnButtonNewClick);
    //*)
}

yatishDlgName::~yatishDlgName () {
    //(*Destroy(yatishDlgName)
    //*)
}

void yatishDlgName::OnButtonSaveClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordName (tid, id, name) )
        EndModal (wxID_SAVE);
    else
        EndModal (wxID_CANCEL);
}

void yatishDlgName::OnButtonNewClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    if ( pdb->RecordName (tid, wxNOT_FOUND, name) )
        EndModal (wxID_NEW);
    else
        EndModal (wxID_CANCEL);
}
