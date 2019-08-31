///-----------------------------------------------------------------
///
/// @file      AboutDlg.h
/// @author    Gabi
/// Created:   04.02.2012 21:21:05
/// @section   DESCRIPTION
///            AboutDlg class declaration
///
///------------------------------------------------------------------

#ifndef __ABOUTDLG_H__
#define __ABOUTDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
////Header Include End


////Dialog Style Start
#undef AboutDlg_STYLE
#define AboutDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class AboutDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		AboutDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = AboutDlg_STYLE);
		virtual ~AboutDlg();
		void btn_CloseClick(wxCommandEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticText *WxStaticText2;
		wxButton *btn_Close;
		wxTextCtrl *txt_About;
		wxStaticText *WxStaticText1;
		wxStaticText *lbl_Title;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXSTATICTEXT2 = 1011,
			ID_BTN_CLOSE = 1004,
			ID_TXT_ABOUT = 1010,
			ID_WXSTATICTEXT1 = 1002,
			ID_LBL_TITLE = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
