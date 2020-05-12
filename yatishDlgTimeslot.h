#ifndef YATISHDLGTIMESLOT_H
#define YATISHDLGTIMESLOT_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishDlgTimeslot)
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/choice.h>
    //*)
#endif
//(*Headers(yatishDlgTimeslot)
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/timectrl.h>
//*)

#include <wx/valgen.h>
#include "yatishDBsqlite.h"

class yatishDlgTimeslot: public wxDialog {
    public:
        yatishDlgTimeslot (yatishDBsqlite *, long);
        yatishDlgTimeslot (yatishDBsqlite *);
        ~yatishDlgTimeslot ();
    private:
        //(*Identifiers(yatishDlgTimeslot)
        static const long idDatePicker1;
        static const long idTimePicker1;
        static const long idDatePicker2;
        static const long idTimePicker2;
        static const long idChoiceProject;
        static const long idChoiceTask;
        static const long idChoiceTool;
        //*)
        //(*Declarations(yatishDlgTimeslot)
        wxDatePickerCtrl* datePicker1;
        wxChoice* choiceProject;
        wxChoice* choiceTask;
        wxStaticBoxSizer* staticBoxSizer;
        wxTimePickerCtrl* timePicker1;
        wxTimePickerCtrl* timePicker2;
        wxChoice* choiceTool;
        wxButton* buttonSave;
        wxDatePickerCtrl* datePicker2;
        wxButton* buttonNew;
        //*)
        yatishDBsqlite * pdb;
        long id;
        int project, task, tool;
        wxDateTime date1, date2, time1, time2;
        void BuildContent ();
        //(*Handlers(yatishDlgTimeslot)
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonNewClick(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
