#ifndef YATISHDLGNAME_H
#define YATISHDLGNAME_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishDlgName)
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/textctrl.h>
    //*)
#endif
//(*Headers(yatishDlgName)
//*)

#include "yatishDBsqlite.h"

class yatishDlgName : public wxDialog {
    public:
        yatishDlgName (yatishDBsqlite *, tableID, long);
        yatishDlgName (yatishDBsqlite *, tableID);
        ~yatishDlgName ();
    private:
        //(*Identifiers(yatishDlgName)
        static const long idTextCtrl;
        //*)
        //(*Declarations(yatishDlgName)
        wxStaticBoxSizer* staticBoxSizer;
        wxTextCtrl* textCtrl;
        wxButton* buttonSave;
        //*)
        yatishDBsqlite * pdb;
        tableID tid;
        long id;
        wxString name;
        void BuildContent ();
        //(*Handlers(yatishDlgName)
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonNewClick(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
