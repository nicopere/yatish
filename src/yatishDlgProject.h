#ifndef YATISHDLGPROJECT_H
#define YATISHDLGPROJECT_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishDlgProject)
    #include <wx/button.h>
    #include <wx/choice.h>
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/textctrl.h>
    //*)
#endif
//(*Headers(yatishDlgProject)
//*)

#include "yatishDBsqlite.h"

class yatishDlgProject: public wxDialog {
    public:
        yatishDlgProject (yatishDBsqlite *, long);
        yatishDlgProject (yatishDBsqlite *);
        ~yatishDlgProject ();
    private:
        //(*Identifiers(yatishDlgProject)
        static const long idTextCtrlName;
        static const long idChoiceClient;
        //*)
        //(*Declarations(yatishDlgProject)
        wxButton* buttonNew;
        wxButton* buttonSave;
        wxChoice* choiceClient;
        wxStaticBoxSizer* staticBoxSizer;
        wxTextCtrl* textCtrlName;
        //*)
        yatishDBsqlite * pdb;
        long id;
        wxString name;
        int choice;
        void BuildContent ();
        //(*Handlers(yatishDlgProject)
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonNewClick(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
