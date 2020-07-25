#include "wx_pch.h"
#include "yatishDlgTimeslot.h"

/** Simplified from the [wxWidgets Wiki](https://wiki.wxwidgets.org/WxValidator):
 * - "try dynamic cast" did not appear to prevent segmentation fault
 *   when SetValidator was called on a wxChoice...
 * - Validate() always returns true, i.e. we rely on wx(Date|Time)PickerCtrl
 *   (style wxDP_ALLOWNONE __not__ set)
 * \todo
 * - fix RTTI
 * - try template?
 */
class DateValidator : public wxValidator {
    public:
        DateValidator () { pdt = nullptr; }
        DateValidator (wxDateTime * p) { pdt = p; }
        DateValidator ( const DateValidator& v ) : wxValidator() { pdt = v.pdt; }
        wxObject * Clone () const { return new DateValidator (*this); }
        bool TransferFromWindow ();
        bool TransferToWindow ();
        bool Validate (wxWindow *) { return true; }
    private:
        wxDateTime * pdt;
 };
bool DateValidator::TransferFromWindow () {
    wxDatePickerCtrl * date = (wxDatePickerCtrl *) m_validatorWindow;
    *pdt = date->GetValue();
    return true;
}
bool DateValidator::TransferToWindow () {
    wxDatePickerCtrl * date = (wxDatePickerCtrl *) m_validatorWindow;
    date->SetValue (*pdt);
    return true;
}
/** \sa DateValidator
 */
class TimeValidator : public wxValidator {
    public:
        TimeValidator () { pdt = nullptr; }
        TimeValidator (wxDateTime * p) { pdt = p; }
        TimeValidator ( const TimeValidator& v ) : wxValidator() { pdt = v.pdt; }
        wxObject * Clone () const { return new TimeValidator (*this); }
        bool TransferFromWindow ();
        bool TransferToWindow ();
        bool Validate (wxWindow *) { return true; }
    private:
        wxDateTime * pdt;
 };
bool TimeValidator::TransferFromWindow () {
    wxTimePickerCtrl * date = (wxTimePickerCtrl *) m_validatorWindow;
    *pdt = date->GetValue();
    return true;
}
bool TimeValidator::TransferToWindow () {
    wxTimePickerCtrl * date = (wxTimePickerCtrl *) m_validatorWindow;
    date->SetValue (*pdt);
    return true;
}

#ifndef WX_PRECOMP
    //(*InternalHeadersPCH(yatishDlgTimeslot)
    #include <wx/string.h>
    #include <wx/intl.h>
    //*)
#endif
//(*InternalHeaders(yatishDlgTimeslot)
//*)

//(*IdInit(yatishDlgTimeslot)
const long yatishDlgTimeslot::idDatePicker1 = wxNewId();
const long yatishDlgTimeslot::idTimePicker1 = wxNewId();
const long yatishDlgTimeslot::idDatePicker2 = wxNewId();
const long yatishDlgTimeslot::idTimePicker2 = wxNewId();
const long yatishDlgTimeslot::idChoiceProject = wxNewId();
const long yatishDlgTimeslot::idChoiceTask = wxNewId();
const long yatishDlgTimeslot::idChoiceTool = wxNewId();
//*)

BEGIN_EVENT_TABLE (yatishDlgTimeslot, wxDialog)
    //(*EventTable(yatishDlgTimeslot)
    //*)
END_EVENT_TABLE()

/** This constructor initializes the dialog box with data from the SQL record identified by `sql_id`. */
yatishDlgTimeslot::yatishDlgTimeslot (yatishDBsqlite * p_db, long sql_id) {
    BuildContent();
    pdb = p_db;
    id = sql_id;
    bool choiceOK;
    choiceOK = pdb->FillChoice (choiceProject, project_tid);
    choiceOK = pdb->FillChoice (choiceTask, task_tid);
    choiceOK = pdb->FillChoice (choiceTool, tool_tid);
    if (!choiceOK) wxLogError ("Initialization of choices failed (yatishDlgTimeslot)");
    long activity_id = pdb->Activity (id);
    project = pdb->ChoiceSelector (project_tid, activity_id);
    task    = pdb->ChoiceSelector (task_tid, activity_id);
    tool    = pdb->ChoiceSelector (tool_tid, activity_id);
    choiceProject->SetValidator ( wxGenericValidator (&project) );
    choiceTask   ->SetValidator ( wxGenericValidator (&task) );
    choiceTool   ->SetValidator ( wxGenericValidator (&tool) );
    if ( pdb->ReadDates (id, date1, date2) ) {
        datePicker1->SetValidator ( DateValidator (&date1) );
        datePicker2->SetValidator ( DateValidator (&date2) );
        time1 = date1; time2 = date2; // date part not used
        timePicker1->SetValidator ( TimeValidator (&time1) );
        timePicker2->SetValidator ( TimeValidator (&time2) );
    } else
        wxLogError ("Initialization of dates failed (yatishDlgTimeslot)");
    Fit(); SetMaxSize ( GetSize() ); // Fit() really needed here !
    /** \todo TAB traversal broken by wx[Date|Time]PickerCtrl... (idem panel #2) [no problem on Windows]*/
}

/** The dialog box is initially empty and only writes NEW records (the SAVE button is cancelled). */
yatishDlgTimeslot::yatishDlgTimeslot (yatishDBsqlite * p_db) {
    BuildContent();
    staticBoxSizer->GetStaticBox()->SetLabel (_("New row") );
    pdb = p_db;
    buttonSave->Disable();
    bool choiceOK;
    choiceOK = pdb->FillChoice (choiceProject, project_tid);
    choiceOK = pdb->FillChoice (choiceTask, task_tid);
    choiceOK = pdb->FillChoice (choiceTool, tool_tid);
    if (!choiceOK) wxLogError ("Initialization of choices failed (yatishDlgTimeslot)");
    project = 0;
    task    = 0;
    tool    = 0;
    choiceProject->SetValidator ( wxGenericValidator (&project) );
    choiceTask   ->SetValidator ( wxGenericValidator (&task) );
    choiceTool   ->SetValidator ( wxGenericValidator (&tool) );
    date1 = wxDateTime::Now(); date2 = date1;
    datePicker1->SetValidator ( DateValidator (&date1) );
    datePicker2->SetValidator ( DateValidator (&date2) );
    time1 = date1; time2 = date2;
    timePicker1->SetValidator ( TimeValidator (&time1) );
    timePicker2->SetValidator ( TimeValidator (&time2) );
    Fit(); SetMaxSize ( GetSize() );
    if ( choiceProject->IsEmpty() || choiceTask->IsEmpty() || choiceTool->IsEmpty() )
      buttonNew->Disable(); // in case we get here while some tables are still empty
}

void yatishDlgTimeslot::BuildContent() {
    //(*Initialize(yatishDlgTimeslot)
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer2;
    wxStaticText* StaticText1;
    wxBoxSizer* BoxSizer1;
    wxButton* buttonCancel;
    wxStaticText* StaticText2;

    Create(0, wxID_ANY, _("Table: yatish_timeslot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    staticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("(previously selected row)"));
    FlexGridSizer1 = new wxFlexGridSizer(3, 3, 0, 0);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Start:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker1 = new wxDatePickerCtrl(this, idDatePicker1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker1"));
    FlexGridSizer1->Add(datePicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timePicker1 = new wxTimePickerCtrl(this,idTimePicker1,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT,wxDefaultValidator,_T("idTimePicker1"));
    FlexGridSizer1->Add(timePicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Stop:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePicker2 = new wxDatePickerCtrl(this, idDatePicker2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("idDatePicker2"));
    FlexGridSizer1->Add(datePicker2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    timePicker2 = new wxTimePickerCtrl(this,idTimePicker2,wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT,wxDefaultValidator,_T("idTimePicker2"));
    FlexGridSizer1->Add(timePicker2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    choiceProject = new wxChoice(this, idChoiceProject, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceProject"));
    FlexGridSizer1->Add(choiceProject, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    choiceTask = new wxChoice(this, idChoiceTask, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTask"));
    FlexGridSizer1->Add(choiceTask, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    choiceTool = new wxChoice(this, idChoiceTool, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("idChoiceTool"));
    FlexGridSizer1->Add(choiceTool, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(wxID_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgTimeslot::OnButtonSaveClick);
    Connect(wxID_NEW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&yatishDlgTimeslot::OnButtonNewClick);
    //*)
}

yatishDlgTimeslot::~yatishDlgTimeslot () {
    //(*Destroy(yatishDlgTimeslot)
    //*)
}

void yatishDlgTimeslot::OnButtonSaveClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    wxDateTime dt1 = date1 + ( time1 - time1.GetDateOnly() ); // The date of the wxDateTime returned by a
    wxDateTime dt2 = date2 + ( time2 - time2.GetDateOnly() ); // wxTimePickerCtrl is Jan 1st, current year!
    if ( pdb->RecordTimeslot (id, dt1, dt2, project, task, tool) )
        EndModal (wxID_SAVE);
    else
        EndModal (wxID_CANCEL);
}

void yatishDlgTimeslot::OnButtonNewClick (wxCommandEvent& event) {
    TransferDataFromWindow();
    wxDateTime dt1 = date1 + ( time1 - time1.GetDateOnly() );
    wxDateTime dt2 = date2 + ( time2 - time2.GetDateOnly() );
    if ( pdb->RecordTimeslot (wxNOT_FOUND, dt1, dt2, project, task, tool) )
        EndModal (wxID_NEW);
    else
        EndModal (wxID_CANCEL);
}
