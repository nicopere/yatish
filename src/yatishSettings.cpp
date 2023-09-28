#include "wx_pch.h"
#include "yatishSettings.h"

/** The `Settings` constructor retrieves itself from the configuration file
 *
 *  (set up by yatishApp::OnInit()).
 */
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
    config->Read ("logo4pdf", &logo4pdf, false);
    config->Read ("companyName_or_logoPath", &companyName_or_logoPath, wxEmptyString);
    config->Read ("motto4pdf", &motto4pdf, true);
    config->Read ("companyMotto", &companyMotto, wxEmptyString);
    config->Read ("pdfCharts", &pdfCharts, true);
}

/** The `Settings` destructor saves itself to the configuration file
 *
 *  (set up by yatishApp::OnInit()).
 */
Settings::~Settings () {
    wxConfigBase * config = wxConfigBase::Get (false);
    config->SetPath ("/yatish");
    config->Write ("log2text", log2text);
    config->Write ("limitRow", limitRow);
    config->Write ("rowLimit", (long) rowLimit);
    config->Write ("lib", (long) lib);
    config->Write ("logo4pdf", logo4pdf);
    config->Write ("companyName_or_logoPath", companyName_or_logoPath);
    config->Write ("motto4pdf", motto4pdf);
    config->Write ("companyMotto", companyMotto);
    config->Write ("pdfCharts", pdfCharts);
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
const long yatishSettings::ID_STATICTEXT1 = wxNewId();
const long yatishSettings::idCheckBoxLog = wxNewId();
const long yatishSettings::ID_STATICTEXT2 = wxNewId();
const long yatishSettings::idCheckBoxLimit = wxNewId();
const long yatishSettings::ID_STATICTEXT3 = wxNewId();
const long yatishSettings::idSpinCtrlLimit = wxNewId();
const long yatishSettings::ID_STATICTEXT4 = wxNewId();
const long yatishSettings::idChoiceLib = wxNewId();
const long yatishSettings::idPanelGUI = wxNewId();
const long yatishSettings::idRadioButtonName = wxNewId();
const long yatishSettings::idTextCtrlName = wxNewId();
const long yatishSettings::idRadioButtonLogo = wxNewId();
const long yatishSettings::idButtonLogo = wxNewId();
const long yatishSettings::idCheckBoxMotto = wxNewId();
const long yatishSettings::idTextCtrlMotto = wxNewId();
const long yatishSettings::idCheckBoxPDFcharts = wxNewId();
const long yatishSettings::idPanelPDF = wxNewId();
const long yatishSettings::idNotebook = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishSettings, wxDialog)
    //(*EventTable(yatishSettings)
    //*)
    EVT_UPDATE_UI(idSpinCtrlLimit, yatishSettings::OnSpinCtrlLimitUpdate)
    EVT_UPDATE_UI(idButtonLogo, yatishSettings::OnButtonLogoUpdate)
    EVT_UPDATE_UI(idTextCtrlName, yatishSettings::OnTextCtrlNameUpdate)
    EVT_UPDATE_UI(idTextCtrlMotto, yatishSettings::OnTextCtrlMottoUpdate)
END_EVENT_TABLE()

yatishSettings::yatishSettings () {
    //(*Initialize(yatishSettings)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxButton* buttonCancel;
    wxButton* buttonOK;
    wxFlexGridSizer* FlexGridSizer1;
    wxNotebook* notebook;
    wxPanel* panelGUI;
    wxPanel* panelPDF;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(0, wxID_ANY, _("Yatish settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetExtraStyle( GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY );
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    notebook = new wxNotebook(this, idNotebook, wxDefaultPosition, wxDefaultSize, 0, _T("idNotebook"));
    panelGUI = new wxPanel(notebook, idPanelGUI, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelGUI"));
    FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
    StaticText1 = new wxStaticText(panelGUI, ID_STATICTEXT1, _("Logging:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    checkBoxLog = new wxCheckBox(panelGUI, idCheckBoxLog, _("main frame"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxLog"));
    checkBoxLog->SetValue(false);
    FlexGridSizer1->Add(checkBoxLog, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(panelGUI, ID_STATICTEXT2, _("Timeslot:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    checkBoxLimit = new wxCheckBox(panelGUI, idCheckBoxLimit, _("limit list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxLimit"));
    checkBoxLimit->SetValue(false);
    FlexGridSizer1->Add(checkBoxLimit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(panelGUI, ID_STATICTEXT3, _("Row limit:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    spinCtrlLimit = new wxSpinCtrl(panelGUI, idSpinCtrlLimit, _T("100"), wxDefaultPosition, wxSize(125,-1), 0, 10, 1000, 100, _T("idSpinCtrlLimit"));
    spinCtrlLimit->SetValue(_T("100"));
    FlexGridSizer1->Add(spinCtrlLimit, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(panelGUI, ID_STATICTEXT4, _("Charts:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    choiceLib = new wxChoice(panelGUI, idChoiceLib, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceLib"));
    choiceLib->SetSelection( choiceLib->Append(_("wxFreeChart")) );
    choiceLib->Append(_("wxCharts"));
    choiceLib->Disable();
    FlexGridSizer1->Add(choiceLib, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    panelGUI->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(panelGUI);
    FlexGridSizer1->SetSizeHints(panelGUI);
    panelPDF = new wxPanel(notebook, idPanelPDF, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelPDF"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, panelPDF, _("Company"));
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    radioButtonName = new wxRadioButton(panelPDF, idRadioButtonName, _("Name"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("idRadioButtonName"));
    BoxSizer4->Add(radioButtonName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    textCtrlName = new wxTextCtrl(panelPDF, idTextCtrlName, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, wxDefaultValidator, _T("idTextCtrlName"));
    BoxSizer4->Add(textCtrlName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer4, 1, wxALL|wxEXPAND, 0);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    radioButtonLogo = new wxRadioButton(panelPDF, idRadioButtonLogo, _("Logo"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idRadioButtonLogo"));
    BoxSizer5->Add(radioButtonLogo, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonLogo = new wxButton(panelPDF, idButtonLogo, _("File..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonLogo"));
    BoxSizer5->Add(buttonLogo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer5, 1, wxALL|wxEXPAND, 0);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    checkBoxMotto = new wxCheckBox(panelPDF, idCheckBoxMotto, _("Motto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxMotto"));
    checkBoxMotto->SetValue(false);
    BoxSizer6->Add(checkBoxMotto, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    textCtrlMotto = new wxTextCtrl(panelPDF, idTextCtrlMotto, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, wxDefaultValidator, _T("idTextCtrlMotto"));
    BoxSizer6->Add(textCtrlMotto, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer6, 1, wxALL|wxEXPAND, 0);
    BoxSizer3->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    checkBoxPDFcharts = new wxCheckBox(panelPDF, idCheckBoxPDFcharts, _("with charts"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idCheckBoxPDFcharts"));
    checkBoxPDFcharts->SetValue(false);
    BoxSizer3->Add(checkBoxPDFcharts, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelPDF->SetSizer(BoxSizer3);
    BoxSizer3->Fit(panelPDF);
    BoxSizer3->SetSizeHints(panelPDF);
    notebook->AddPage(panelGUI, _("GUI"), false);
    notebook->AddPage(panelPDF, _("PDF"), false);
    BoxSizer1->Add(notebook, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer2->Add(buttonCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonOK = new wxButton(this, wxID_OK, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    BoxSizer2->Add(buttonOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(idButtonLogo,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishSettings::OnButtonLogoClick);
    //*)
    checkBoxLog->SetValidator ( wxGenericValidator (&log2text) );
    checkBoxLimit->SetValidator ( wxGenericValidator (&limitRow) );
    spinCtrlLimit->SetValidator ( wxGenericValidator (&rowLimit) );
    choiceLib->SetValidator ( wxGenericValidator (&lib) );
    radioButtonLogo->SetValidator ( wxGenericValidator (&logo4pdf) );
    textCtrlName->SetValidator ( wxTextValidator (wxFILTER_NONE, &companyName_or_logoPath) );
    checkBoxMotto->SetValidator ( wxGenericValidator (&motto4pdf) );
    textCtrlMotto->SetValidator ( wxTextValidator (wxFILTER_NONE, &companyMotto) );
    checkBoxPDFcharts->SetValidator ( wxGenericValidator (&pdfCharts) );
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
    logo4pdf = s.logo4pdf;
    companyName_or_logoPath = s.companyName_or_logoPath;
    motto4pdf = s.motto4pdf;
    companyMotto = s.companyMotto;
    pdfCharts = s.pdfCharts;
}

void yatishSettings::Get (Settings& s) {
    s.log2text = log2text;
    s.limitRow = limitRow;
    s.rowLimit = rowLimit;
    s.lib = (ChartLib) lib;
    s.logo4pdf = logo4pdf;
    s.companyName_or_logoPath = companyName_or_logoPath;
    s.motto4pdf = motto4pdf;
    s.companyMotto = companyMotto;
    s.pdfCharts = pdfCharts;
}

void yatishSettings::OnSpinCtrlLimitUpdate (wxUpdateUIEvent& event) {
    event.Enable ( checkBoxLimit->IsChecked() );
}
void yatishSettings::OnButtonLogoUpdate (wxUpdateUIEvent& event) {
    event.Enable ( radioButtonLogo->GetValue() );
}
void yatishSettings::OnTextCtrlNameUpdate (wxUpdateUIEvent& event) {
    event.Enable ( radioButtonName->GetValue() );
}
void yatishSettings::OnTextCtrlMottoUpdate (wxUpdateUIEvent& event) {
    event.Enable ( checkBoxMotto->IsChecked() );
}

void yatishSettings::OnButtonLogoClick(wxCommandEvent& event) {
    wxFileDialog logoDlg (this, _("Select the logo file"),
                          wxStandardPaths::Get().GetDocumentsDir(), wxEmptyString,
                          "PNG|*.png|GIF|*.gif|JPEG|*.jpg", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (logoDlg.ShowModal() == wxID_CANCEL) return;
    textCtrlName->SetValue ( logoDlg.GetPath() );
}
