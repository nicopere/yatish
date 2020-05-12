#ifndef YATISHSETTINGS_H
#define YATISHSETTINGS_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishSettings)
    #include <wx/checkbox.h>
    #include <wx/dialog.h>
    #include <wx/sizer.h>
    #include <wx/button.h>
    #include <wx/stattext.h>
    #include <wx/choice.h>
    //*)
#endif
//(*Headers(yatishSettings)
#include <wx/spinctrl.h>
//*)

#include <wx/valgen.h>
#include <wx/config.h>

enum ChartLib {
    wxFreeChart, // 0
    wxCharts
};

struct Settings {
    bool log2text, limitRow;
    int rowLimit;
    ChartLib lib;
    Settings ();
    ~Settings ();
};

class yatishSettings: public wxDialog {
    public:
        yatishSettings ();
        ~yatishSettings ();
        void Set (Settings&);
        void Get (Settings&);
    private:
        //(*Identifiers(yatishSettings)
        static const long idCheckBoxLog;
        static const long idCheckBoxLimit;
        static const long idSpinCtrlLimit;
        static const long idChoiceLib;
        //*)
        //(*Declarations(yatishSettings)
        wxCheckBox* checkBoxLog;
        wxCheckBox* checkBoxLimit;
        wxChoice* choiceLib;
        wxSpinCtrl* spinCtrlLimit;
        //*)
        bool log2text, limitRow;
        int rowLimit, lib;
        //(*Handlers(yatishSettings)
        void OnCheckBoxLimitClick(wxCommandEvent& event);
        //*)
        DECLARE_EVENT_TABLE()
};

#endif
