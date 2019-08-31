//---------------------------------------------------------------------------
//
// Name:        VCDApp.cpp
// Author:      Gabi
// Created:     11.12.2011 23:24:28
// Description: 
//
//---------------------------------------------------------------------------

#include "VCDApp.h"
#include "VCDFrm.h"



IMPLEMENT_APP(VCDDlgApp)

bool VCDDlgApp::OnInit()
{
	VCDFrm* frame = new VCDFrm(NULL);
	SetTopWindow(frame);
	frame->SetIcon(wxICON(VCD_ICON));
	frame->Show(true);
	frame->LoadSettings();
	frame->CheckInternet();
    	
	return true;
}
 
int VCDDlgApp::OnExit()
{
	return 0;
}
