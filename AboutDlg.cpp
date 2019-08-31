///-----------------------------------------------------------------
///
/// @file      AboutDlg.cpp
/// @author    Gabi
/// Created:   04.02.2012 21:21:05
/// @section   DESCRIPTION
///            AboutDlg class implementation
///
///------------------------------------------------------------------

#include "AboutDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// AboutDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(AboutDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(AboutDlg::OnClose)
	EVT_BUTTON(ID_BTN_CLOSE,AboutDlg::btn_CloseClick)
END_EVENT_TABLE()
////Event Table End

AboutDlg::AboutDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
	btn_Close->SetFocus();
}

AboutDlg::~AboutDlg()
{
} 

void AboutDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, wxT("Copyright 2012 wyrdaprogramming"), wxPoint(4, 200), wxDefaultSize, 0, wxT("WxStaticText2"));
	WxStaticText2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	btn_Close = new wxButton(this, ID_BTN_CLOSE, wxT("Inchide"), wxPoint(192, 192), wxSize(75, 25), 0, wxDefaultValidator, wxT("btn_Close"));

	txt_About = new wxTextCtrl(this, ID_TXT_ABOUT, wxEmptyString, wxPoint(8, 80), wxSize(265, 105), wxNO_BORDER | wxTE_PROCESS_ENTER | wxTE_READONLY | wxTE_NO_VSCROLL | wxTE_NOHIDESEL | wxTE_WORDWRAP | wxTE_MULTILINE, wxDefaultValidator, wxT("txt_About"));
	txt_About->SetMaxLength(0);
	txt_About->AppendText(wxT("Aplicatia VCD are rolul de a usura descarcarea "));
	txt_About->AppendText(wxT("melodiilor de pe site-ul www.vitanclub.net.\n"));
	txt_About->AppendText(wxT("\nPentru sugestii, comentarii si alte pareri "));
	txt_About->AppendText(wxT("trimite un e-mail pe adresa "));
	txt_About->AppendText(wxT("wyrdaprogramming@gmail.com"));
	txt_About->SetFocus();
	txt_About->SetInsertionPointEnd();
	txt_About->SetForegroundColour(wxColour(wxT("BLACK")));
	txt_About->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, wxT("v 0.3"), wxPoint(112, 48), wxDefaultSize, 0, wxT("WxStaticText1"));

	lbl_Title = new wxStaticText(this, ID_LBL_TITLE, wxT("VitanClub Downloader"), wxPoint(32, 16), wxDefaultSize, 0, wxT("lbl_Title"));
	lbl_Title->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false));

	SetTitle(wxT("Despre"));
	SetIcon(wxNullIcon);
	SetSize(8,8,290,259);
	Center();
	
	////GUI Items Creation End
}

void AboutDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * btn_CloseClick
 */
void AboutDlg::btn_CloseClick(wxCommandEvent& event)
{
	Destroy();
}
