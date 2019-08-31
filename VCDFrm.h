///-----------------------------------------------------------------
///
/// @file      VCDFrm.h
/// @author    Gabi
/// Created:   22.12.2011 00:19:00
/// @section   DESCRIPTION
///            VCDFrm class declaration
///
///------------------------------------------------------------------

#ifndef __VCDFRM_H__
#define __VCDFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
////Header Include End

#include <wx/msw/registry.h>
#include "Def.h"
#include "DownloadThread.h"
#include "Downloader.h"

#define MAX_DL_IN_LIST 5

////Dialog Style Start
#undef VCDFrm_STYLE
#define VCDFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class VCDFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		VCDFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("VCD"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = VCDFrm_STYLE);
		virtual ~VCDFrm();
		void LoadSettings();
        void CheckInternet();		
        void StartDownload(int host);
        void RestartDownload(int host);
		void btn_LoadMClick(wxCommandEvent& event);
		//void Mnudownload1006Click(wxCommandEvent& event);
		void list_TracksRightClick(wxListEvent& event);
		void tmr_DownloadProgressTimer(wxTimerEvent& event);
		void Mnuchangesavefolder1009Click(wxCommandEvent& event);
		void Mnuclose1010Click(wxCommandEvent& event);
		void Mnudlpage1001Click(wxCommandEvent& event);
		void Mnushowinfolder1012Click(wxCommandEvent& event);
		void list_DownloadRightClick(wxListEvent& event);
		void Mnustopdl1013Click(wxCommandEvent& event);
		//void Mnuretrydl1014Click(wxCommandEvent& event);
		void Mnudespre1016Click(wxCommandEvent& event);
		void Mnuhost11001Click(wxCommandEvent& event);
		void Mnuhost21003Click(wxCommandEvent& event);
		void Mnuhost31004Click(wxCommandEvent& event);
		void Mnuhost11017Click(wxCommandEvent& event);
		void Mnuhost21018Click(wxCommandEvent& event);
		void Mnuhost31019Click(wxCommandEvent& event);		
		void Mnuadaugainwinamp1020Click(wxCommandEvent& event);
		void Mnuadaugasiascultainwinamp1021Click(wxCommandEvent& event);
		void Mnuhost41007Click(wxCommandEvent& event);
		void Mnuhost41022Click(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenuBar *mnu_Main;
		wxMenu *mnu_DlRightClickErr;
		wxTimer *tmr_DownloadProgress;
		wxMenu *mnu_DlRightClickDone;
		wxMenu *mnu_DlRightClickRun;
		wxMenu *mnu_ListRightClick;
		wxListCtrl *list_Download;
		wxButton *btn_LoadM;
		wxChoice *choice_MType;
		wxListCtrl *list_Tracks;
		wxPanel *panel_Main;
		////GUI Control Declaration End


		void DlError(wxString, int, int);
		wxString DlSpeed(int);
		
		//Settings
		wxString SaveFolder;
		//Other vars
		static wxString web_location;
		Track tracks[70];
		ThreadStruct *Th;//ptr pentru lista de download la click dreapta
		DlStruct DlS[MAX_DL_IN_LIST];//vector pentru melodiile active la descarcare
		const static int stack_size = 1024*1024;
		
		bool internet_acces;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_MENIU_1011 = 1026,
			ID_MNU_CHANGESAVEFOLDER_1009 = 1025,
			ID_MNU_CLOSE_1010 = 1024,
			ID_MNU_AJUTOR_1015 = 1023,
			ID_MNU_DESPRE_1016 = 1022,
			
			ID_MNU_RETRYDL_1014 = 1021,
			ID_MNU_HOST1_1017 = 1020,
			ID_MNU_HOST2_1018 = 1019,
			ID_MNU_HOST3_1019 = 1018,
			ID_MNU_HOST4_1022 = 1017,
			
			ID_TMR_DOWNLOADPROGRESS = 1016,
			ID_MNU_SHOWINFOLDER_1012 = 1015,
			ID_MNU_ADAUGASIASCULTAINWINAMP_1021 = 1014,
			ID_MNU_ADAUGAINWINAMP_1020 = 1013,
			
			ID_MNU_STOPDL_1013 = 1012,
			
			ID_MNU_DOWNLOAD_1006 = 1011,
			ID_MNU_HOST1_1001 = 1010,
			ID_MNU_HOST2_1003 = 1009,
			ID_MNU_HOST3_1004 = 1008,
			ID_MNU_HOST4_1007 = 1007,
			ID_MNU_DLPAGE_1001 = 1006,
			
			ID_LIST_DOWNLOAD = 1005,
			ID_BTN_LOADM = 1004,
			ID_CHOICE_MTYPE = 1003,
			ID_LIST_TRACKS = 1002,
			ID_PANEL_MAIN = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
