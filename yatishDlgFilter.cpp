#include "wx_pch.h"
#include "yatishDlgFilter.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(yatishDlgFilter)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(yatishDlgFilter)
//*)

//(*IdInit(yatishDlgFilter)
const long yatishDlgFilter::idChoiceFilter = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishDlgFilter, wxDialog)
	//(*EventTable(yatishDlgFilter)
	//*)
END_EVENT_TABLE()

yatishDlgFilter::yatishDlgFilter (yatishDBsqlite * p_db, tableID t_id) {
	//(*Initialize(yatishDlgFilter)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxButton* buttonCancel;
	wxButton* buttonOK;

	Create(0, wxID_ANY, _("Value to display \?"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	choiceFilter = new wxChoice(this, idChoiceFilter, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceFilter"));
	BoxSizer1->Add(choiceFilter, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer2->Add(buttonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	buttonOK = new wxButton(this, wxID_OK, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	BoxSizer2->Add(buttonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgFilter::OnButtonOK);
	//*)
    pdb = p_db;
    tid = t_id;
    if ( !pdb->FillChoice (choiceFilter, tid) )
        wxLogError ("Initialization of choiceFilter failed (yatishDlgFilter)");
    choice = 0;
    choiceFilter->SetValidator ( wxGenericValidator (&choice) );
    Fit(); SetMaxSize ( GetSize() );
 // in case we get here while the database is still empty
    if ( choiceFilter->IsEmpty() ) buttonOK->Disable();
}

yatishDlgFilter::~yatishDlgFilter () {
	//(*Destroy(yatishDlgFilter)
	//*)
}

void yatishDlgFilter::OnButtonOK (wxCommandEvent& event) {
    TransferDataFromWindow();
    pdb->AddToFilter (tid, choice);
    EndModal (wxID_OK);
}
