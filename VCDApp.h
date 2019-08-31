//---------------------------------------------------------------------------
//
// Name:        VCDApp.h
// Author:      Gabi
// Created:     11.12.2011 23:24:28
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __VCDDLGApp_h__
#define __VCDDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

extern "C" void *_GdipStringFormatCachedGenericTypographic = NULL; 

class VCDDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};


#endif
