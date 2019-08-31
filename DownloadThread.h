#ifndef __DownloadThread_H__
#define __DownloadThread_H__

#include <wx/wx.h>

#include "Downloader.h"
#include "Def.h"

class DownloadThread: public wxThread
{
private:
	virtual void* Entry();
	ThreadStruct *dl_struct;
	bool stop;
	Downloader dl;	
	void DlFileshare(string nr);
	void DlFisier(string nr);
	void DlFastUpload(string nr);
	void DlDcUpload(string nr);
	void HotFilesStep();
	static int ReportProgress(void*, double, double ,double, double);
public:
	DownloadThread(ThreadStruct *dl_str) {
		dl_struct = dl_str;
		stop = false;
		dl.SetStopVar(&stop);
	};
	void StopDL() {
        stop = true;
    };
    ~DownloadThread();
	/*void OnExit() {
        dl_struct->active = false;
    }*/
};

#endif
