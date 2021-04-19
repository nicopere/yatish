#ifndef YATISHSETTINGS_H
#define YATISHSETTINGS_H

#ifndef WX_PRECOMP
    //(*HeadersPCH(yatishSettings)
    #include <wx/button.h>
    #include <wx/checkbox.h>
    #include <wx/choice.h>
    #include <wx/dialog.h>
    #include <wx/panel.h>
    #include <wx/radiobut.h>
    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/textctrl.h>
    //*)
#endif
//(*Headers(yatishSettings)
#include <wx/notebook.h>
#include <wx/spinctrl.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/valgen.h>

enum ChartLib {
    wxFreeChart, // 0
    wxCharts
};

/** Defines the application settings. Defined here but instantiated in yatishFrame
 * (private member there).
 */
struct Settings {
    bool log2text, /**< If `True`, error/warning messages will be forwarded
                        to the bottom of the main frame. */
         limitRow; /**< If `True`, the listing in panel #2 will be limited... */
    int rowLimit;  /**< ...to `rowLimit` lines. */
    ChartLib lib;  /**< A `ChartLib` enumerates the graphic libraries
                        available for panel #3 (not used yet). */
    bool logo4pdf; /**< If `True` the company name is replaced by its logo
                        in the PDF header. Also determines the meaning of `companyName_or_logoPath`. */
    wxString companyName_or_logoPath; /**< Either the company name or its logo.
                                           Can be left empty if `logo4pdf` is `False`. */
    bool motto4pdf; /**< Print the company motto in the PDF header? */
    wxString companyMotto; /**< Slogan or short description of the purpose. */
    bool pdfCharts; /**< PDF charts? */
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
        static const long ID_STATICTEXT1;
        static const long idCheckBoxLog;
        static const long ID_STATICTEXT2;
        static const long idCheckBoxLimit;
        static const long ID_STATICTEXT3;
        static const long idSpinCtrlLimit;
        static const long ID_STATICTEXT4;
        static const long idChoiceLib;
        static const long idPanelGUI;
        static const long idRadioButtonName;
        static const long idTextCtrlName;
        static const long idRadioButtonLogo;
        static const long idButtonLogo;
        static const long idCheckBoxMotto;
        static const long idTextCtrlMotto;
        static const long idCheckBoxPDFcharts;
        static const long idPanelPDF;
        static const long idNotebook;
        //*)
        //(*Declarations(yatishSettings)
        wxButton* buttonLogo;
        wxCheckBox* checkBoxLimit;
        wxCheckBox* checkBoxLog;
        wxCheckBox* checkBoxMotto;
        wxCheckBox* checkBoxPDFcharts;
        wxChoice* choiceLib;
        wxRadioButton* radioButtonLogo;
        wxRadioButton* radioButtonName;
        wxSpinCtrl* spinCtrlLimit;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxTextCtrl* textCtrlMotto;
        wxTextCtrl* textCtrlName;
        //*)
        bool log2text, limitRow, logo4pdf, motto4pdf, pdfCharts;
        int rowLimit, lib;
        wxString companyName_or_logoPath, companyMotto;
        //(*Handlers(yatishSettings)
        void OnCheckBoxLimitClick(wxCommandEvent& event);
        void OnButtonLogoClick(wxCommandEvent& event);
        //*)
        void OnSpinCtrlLimitUpdate (wxUpdateUIEvent&);
        void OnButtonLogoUpdate (wxUpdateUIEvent&);
        void OnTextCtrlNameUpdate (wxUpdateUIEvent&);
        void OnTextCtrlMottoUpdate (wxUpdateUIEvent&);
        DECLARE_EVENT_TABLE()
};

#endif
