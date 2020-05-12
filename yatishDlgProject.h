#ifndef YATISHDLGPROJECT_H
#define YATISHDLGPROJECT_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishDlgProject)
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/textctrl.h>
    #include <wx/choice.h>
    //*)
#endif
//(*Headers(yatishDlgProject)
//*)

#include <wx/valgen.h>
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
        wxStaticBoxSizer* staticBoxSizer;
        wxTextCtrl* textCtrlName;
        wxButton* buttonSave;
        wxChoice* choiceClient;
        wxButton* buttonNew;
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
