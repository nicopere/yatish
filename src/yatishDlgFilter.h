#ifndef YATISHDLGFILTER_H
#define YATISHDLGFILTER_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(yatishDlgFilter)
	#include <wx/button.h>
	#include <wx/choice.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	//*)
#endif
//(*Headers(yatishDlgFilter)
//*)

#include "yatishDBsqlite.h"

class yatishDlgFilter: public wxDialog {
    public:
        yatishDlgFilter (yatishDBsqlite *, tableID);
        ~yatishDlgFilter ();
    private:
        //(*Identifiers(yatishDlgFilter)
        static const long idChoiceFilter;
        //*)
        //(*Declarations(yatishDlgFilter)
        wxChoice* choiceFilter;
        //*)
        yatishDBsqlite * pdb;
        tableID tid;
        int choice;
        //(*Handlers(yatishDlgFilter)
        void OnButtonOK(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
