#include "wx_pch.h"
#include "yatishSettings.h"

Settings::Settings () {
    wxConfigBase * config = wxConfigBase::Get (false);
    config->SetPath ("/yatish");
    config->Read ("log2text", &log2text, false);
    config->Read ("limitRow", &limitRow, false);
    long tmp;
    config->Read ("rowLimit", &tmp, 100l);
    rowLimit = (int) tmp;
    config->Read ("lib", &tmp, 0l);
    lib = (ChartLib) tmp;
}

Settings::~Settings () {
    wxConfigBase * config = wxConfigBase::Get (false);
    config->SetPath ("/yatish");
    config->Write ("log2text", log2text);
    config->Write ("limitRow", limitRow);
    config->Write ("rowLimit", (long) rowLimit);
    config->Write ("lib", (long) lib);
}

#ifndef WX_PRECOMP
    //(*InternalHeadersPCH(yatishSettings)
    #include <wx/string.h>
    #include <wx/intl.h>
    //*)
#endif
//(*InternalHeaders(yatishSettings)
//*)

//(*IdInit(yatishSettings)
const long yatishSettings::idCheckBoxLog = wxNewId();
const long yatishSettings::idCheckBoxLimit = wxNewId();
const long yatishSettings::idSpinCtrlLimit = wxNewId();
const long yatishSettings::idChoiceLib = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishSettings, wxDialog)
    //(*EventTable(yatishSettings)
    //*)
END_EVENT_TABLE()

yatishSettings::yatishSettings () {
    //(*Initialize(yatishSettings)
    wxFlexGridSizer* FlexGridSizer1;
    wxButton* buttonOK;
    wxStaticText* StaticText1;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxButton* buttonCancel;
    wxStaticText* StaticText2;

    Create(0, wxID_ANY, _("Yatish settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(5, 2, 0, 0);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Logging:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    checkBoxLog = new wxCheckBox(this, idCheckBoxLog, _("main frame"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxLog"));
    checkBoxLog->SetValue(false);
    FlexGridSizer1->Add(checkBoxLog, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Timeslot:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    checkBoxLimit = new wxCheckBox(this, idCheckBoxLimit, _("limit list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxLimit"));
    checkBoxLimit->SetValue(false);
    FlexGridSizer1->Add(checkBoxLimit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(this, wxID_ANY, _("Row limit:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    spinCtrlLimit = new wxSpinCtrl(this, idSpinCtrlLimit, _T("100"), wxDefaultPosition, wxDefaultSize, 0, 10, 1000, 100, _T("idSpinCtrlLimit"));
    spinCtrlLimit->SetValue(_T("100"));
    FlexGridSizer1->Add(spinCtrlLimit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, wxID_ANY, _("Charts:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceLib = new wxChoice(this, idChoiceLib, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceLib"));
    choiceLib->Append(_("wxFreeChart"));
    choiceLib->Append(_("wxCharts"));
    choiceLib->Disable();
    FlexGridSizer1->Add(choiceLib, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    FlexGridSizer1->Add(buttonCancel, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    buttonOK = new wxButton(this, wxID_OK, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    FlexGridSizer1->Add(buttonOK, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(idCheckBoxLimit,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&yatishSettings::OnCheckBoxLimitClick);
    //*)
    checkBoxLog->SetValidator ( wxGenericValidator (&log2text) );
    checkBoxLimit->SetValidator ( wxGenericValidator (&limitRow) );
    spinCtrlLimit->SetValidator ( wxGenericValidator (&rowLimit) );
    choiceLib->SetValidator ( wxGenericValidator (&lib) );
    Fit(); SetMaxSize ( GetSize() );
}

yatishSettings::~yatishSettings () {
    //(*Destroy(yatishSettings)
    //*)
}

void yatishSettings::Set (Settings& s) {
    log2text = s.log2text;
    limitRow = s.limitRow;
    rowLimit = s.rowLimit;
    lib = (int) s.lib;
    spinCtrlLimit->Enable (limitRow);
}

void yatishSettings::Get (Settings& s) {
    s.log2text = log2text;
    s.limitRow = limitRow;
    s.rowLimit = rowLimit;
    s.lib = (ChartLib) lib;
}

void yatishSettings::OnCheckBoxLimitClick(wxCommandEvent& event) {
    spinCtrlLimit->Enable ( checkBoxLimit->IsChecked() );
}
