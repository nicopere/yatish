#ifndef YATISHDLGACTIVITY_H
#define YATISHDLGACTIVITY_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishDlgActivity)
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/choice.h>
    //*)
#endif
//(*Headers(yatishDlgActivity)
//*)

#include <wx/valgen.h>
#include "yatishDBsqlite.h"

class yatishDlgActivity: public wxDialog {
    public:
        yatishDlgActivity (yatishDBsqlite *, long);
        yatishDlgActivity (yatishDBsqlite *);
        ~yatishDlgActivity ();
    private:
        //(*Identifiers(yatishDlgActivity)
        static const long idChoiceProject;
        static const long idChoiceTask;
        static const long idChoiceTool;
        //*)
        //(*Declarations(yatishDlgActivity)
        wxChoice* choiceProject;
        wxChoice* choiceTask;
        wxStaticBoxSizer* staticBoxSizer;
        wxChoice* choiceTool;
        wxButton* buttonSave;
        wxButton* buttonNew;
        //*)
        yatishDBsqlite * pdb;
        long id;
        int project, task, tool;
        void BuildContent ();
        //(*Handlers(yatishDlgActivity)
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonNewClick(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
