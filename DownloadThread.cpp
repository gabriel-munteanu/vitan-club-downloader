
#include "DownloadThread.h"

void* DownloadThread::Entry()
{
    string vt;
    string temp;
	char s[10];
	ltoa(dl_struct->track_id, s, 10);
    vt = string("http://www.vitanclub.net/dlink/") + s + string("/3.html");
	//vitan club
	int a,b,i;
	dl.SetOptions(HTTP_SET_REFERER, "http://www.vitanclub.net");
	for(i=0; i<3; i++)
	{
        vt[vt.length()-6] -= i;
        //wxMessageBox(vt);
    	dl.SetUrl(vt.c_str());   
       	
    	dl.Get();
         
    	   //wxMessageBox(dl.HtmlHeader);
    	a = dl.HtmlHeader.find("hotfil");
    	if(a != string::npos)
    	   break;
    	vt[vt.length()-6] += i;
    }
    if(i==3)//nu e filehost ca host de descarcare
    {
        dl_struct->progress = -2;
        return 0;
    }
    
    b = dl.HtmlHeader.find("\r", a);
    temp = dl.HtmlHeader.substr(a, b-a);
	a = temp.rfind("/");
	
	string nr = temp.substr(a+1);//extract id for hotfiles
	   //wxMessageBox(nr+"!");
	dl.HtmlBody.clear();
	dl.HtmlHeader.clear();
	switch(dl_struct->host)
	{
        case 1: DlFileshare(nr);break;
        case 2: DlFisier(nr);break;
        case 3: DlDcUpload(nr);break;
        case 4: DlFastUpload(nr);break;
    }
    
}
DownloadThread::~DownloadThread()
{
    if(dl_struct->progress < 0)//stop sau eroare
        unlink(dl_struct->dl_location.c_str());
}

int DownloadThread::ReportProgress(void *th, double dlt, double dln, double ult, double uln)
{
    ((DownloadThread*)th)->dl_struct->progress = (int)dln*100/dlt;
    ((DownloadThread*)th)->dl_struct->dled = dln;
    return 0;
}
void DownloadThread::HotFilesStep()
{
    int a,b;
    a = dl.HtmlBody.find("file-url");
    a = dl.HtmlBody.find("http", a+1);
    b = dl.HtmlBody.find("<", a);
    
    string dl_page_link = dl.HtmlBody.substr(a, b-a);
    //wxMessageBox(dl_page_link);
    dl.SetUrl(dl_page_link.c_str());
    dl.Get();
}

void DownloadThread::DlFileshare(string nr)
{
    int a,b;
    dl.SetUrl(("http://www.hotfiles.ro:8079/dmz/fisier/redirect/fileshare/"+nr).c_str());
	dl.SetOptions(HTTP_SET_REFERER, (char*)("http://www.hotfiles.ro/download/"+nr).c_str());
	dl.SetOptions(HTTP_FOLLOW_REDIRECT, 1);
	dl.Get();	
	
	HotFilesStep();
	   //wxMessageBox(dl.HtmlHeader);
	//cout<<x.HtmlHeader;
	
	a = dl.HtmlBody.find("action=\"http");
	   
	if(a == string::npos)
	{
        dl_struct->progress = -4;
        return;
    }
    a += 8;
	b = dl.HtmlBody.find("\"", a);
	//extract download link
	string dl_link = dl.HtmlBody.substr(a, b-a);
	//cout<<dl_link;

	//extract file extension
	string ext = dl_link.substr(dl_link.rfind('.'));
	//cout<<ext;
	//extract file link from header
	/*string cur_link;
	a = dl.HtmlHeader.find("Locati");
	a = dl.HtmlHeader.find("htt", a);
	b = dl.HtmlHeader.find("\r\n", a);
	cur_link = dl.HtmlHeader.substr(a, b-a);*/
	//cout<<cur_link<<"!";
	//download
	dl.SetUrl(dl_link.c_str());
	//wxMessageBox(dl_link);return;
	//dl.SetOptions(HTTP_SET_REFERER, (char*)cur_link.c_str());

	dl.SetProgresVars(&ReportProgress, this);
    
    //eroare in timpul descarcarii
	if(a = dl.DownloadFile((dl_struct->dl_location+=ext).c_str()))
	{   
        if(stop)
            dl_struct->progress = -1;
        else
            dl_struct->progress = -3;
        dl_struct->curl_err = a;
    }
}

void DownloadThread::DlFisier(string nr)
{
    int a,b;
    dl.SetUrl(("http://www.hotfiles.ro:8079/dmz/fisier/redirect/fisier/"+nr).c_str());
	dl.SetOptions(HTTP_SET_REFERER, (char*)("http://www.hotfiles.ro/download/"+nr).c_str());
	dl.SetOptions(HTTP_FOLLOW_REDIRECT, 1);
	dl.Get();
	HotFilesStep();
	//cout<<x.HtmlHeader;

	a = dl.HtmlBody.find("descarca\"");
	   //wxMessageBox(dl.HtmlHeader);
	if(a == string::npos){
        dl_struct->progress = -4;
        return;
    }
	
	do {
    	b = dl.HtmlBody.find("href", a);
    	if(a == string::npos){
            dl_struct->progress = -4; return;
        }
    	a = b + 6;//sar la http
    	b = dl.HtmlBody.find("\"", a);
    	//extract download link
    	string dl_link = dl.HtmlBody.substr(a, b-a);
    	a = b;
    }
    while(dl_link.find("fisier.ro"));
	//cout<<dl_link;

	//extract file extension
	string ext = dl_link.substr(dl_link.rfind('.'));
	//cout<<ext;
	//extract file link from header
	string cur_link;
	a = dl.HtmlHeader.find("Locati");
	a = dl.HtmlHeader.find("htt", a);
	b = dl.HtmlHeader.find("\r\n", a);
	cur_link = dl.HtmlHeader.substr(a, b-a);
	//cout<<cur_link<<"!";
	//download
	dl.SetUrl(dl_link.c_str());
	//wxMessageBox(dl_link);return;
	dl.SetOptions(HTTP_SET_REFERER, (char*)cur_link.c_str());

	dl.SetProgresVars(&ReportProgress, this);

    //eroare in timpul descarcarii
	if(a = dl.DownloadFile((dl_struct->dl_location+=ext).c_str()))
	{
        if(stop)
            dl_struct->progress = -1;
        else
            dl_struct->progress = -3;
        dl_struct->curl_err = a;
    }
}

void DownloadThread::DlFastUpload(string nr)
{
    int a,b;
    dl.SetUrl(("http://www.hotfiles.ro:8079/dmz/fisier/redirect/fastupload/"+nr).c_str());
	dl.SetOptions(HTTP_SET_REFERER, (char*)("http://www.hotfiles.ro/download/"+nr).c_str());
	dl.SetOptions(HTTP_FOLLOW_REDIRECT, 1);
	dl.Get();
	HotFilesStep();
	//cout<<x.HtmlHeader;
        //wxMessageBox(dl.HtmlBody);
        //wxMessageBox(dl.HtmlHeader);
        
	a = dl.HtmlBody.find("buton_descarcare\"");//wxMessageBox(dl.HtmlBody.substr(a, 20));
	a = dl.HtmlBody.find("buton_descarcare\"", a+10);
	       //wxMessageBox(wxString::Format(wxT("%d"),a));
	       
	if(a == string::npos)
	{
        dl_struct->progress = -4;
        return;
    }
    
	b = dl.HtmlBody.find("href", a);
	a = b + 6;//sar la http
	b = dl.HtmlBody.find("\"", a);
	//extract download link
	string dl_link = dl.HtmlBody.substr(a, b-a);
	//cout<<dl_link;
                                        //wxMessageBox(dl_link);
	//extract file extension
	string ext = dl_link.substr(dl_link.rfind('.'));
	//cout<<ext;
	//extract file link from header
	string cur_link;
	a = dl.HtmlHeader.rfind("Locati");
	a = dl.HtmlHeader.find("htt", a);
	b = dl.HtmlHeader.find("\r\n", a);
	cur_link = dl.HtmlHeader.substr(a, b-a);
	//cout<<cur_link<<"!";
	//download
	dl.SetUrl(dl_link.c_str());
	//wxMessageBox(dl_link);return;
	dl.SetOptions(HTTP_SET_REFERER, (char*)cur_link.c_str());

	dl.SetProgresVars(&ReportProgress, this);

    //eroare in timpul descarcarii
	if(a = dl.DownloadFile((dl_struct->dl_location+=ext).c_str()))
	{                          //wxMessageBox(wxString::Format(wxT("%d %d"),a, stop));
        if(stop)
            dl_struct->progress = -1;
        else
            dl_struct->progress = -3;
        dl_struct->curl_err = a;
    }
}

void DownloadThread::DlDcUpload(string nr)
{
    int a,b;
    dl.SetUrl(("http://www.hotfiles.ro:8079/dmz/fisier/redirect/dcupload/"+nr).c_str());
	dl.SetOptions(HTTP_SET_REFERER, (char*)("http://www.hotfiles.ro/download/"+nr).c_str());
	dl.SetOptions(HTTP_FOLLOW_REDIRECT, 1);
	dl.Get();
	HotFilesStep();
	//cout<<x.HtmlHeader;
        //wxMessageBox(dl.HtmlBody);
        //wxMessageBox(dl.HtmlHeader);

	if(dl.HtmlHeader.find("myuplbox") == string::npos)
	{
        dl_struct->progress = -4;
        return;
    }
	string cookie;
	a = dl.HtmlHeader.find("Set-Cookie") + 1;//sar peste primul
	while((a = dl.HtmlHeader.find("Set-Cookie", a+1))!=string::npos)
	{
		a += 11;
		b = dl.HtmlHeader.find("; ", a+1);			
		cookie += dl.HtmlHeader.substr(a, b-a+1);
		a = b+1;
	}
		
	dl.SetOptions(HTTP_SET_COOKIE, cookie.c_str());
	//extract file extension
	string dl_link = "http://www.myuplbox.com/file/go";
	string ext = ".mp3";
	//cout<<ext;
	//extract file link from header
	string cur_link;
	a = dl.HtmlHeader.rfind("Locati");
	a = dl.HtmlHeader.find("htt", a);
	b = dl.HtmlHeader.find("\r\n", a);
	cur_link = dl.HtmlHeader.substr(a, b-a);
	//cout<<cur_link<<"!";
	//download
	dl.SetUrl(dl_link.c_str());
	//wxMessageBox(dl_link);return;
	dl.SetOptions(HTTP_SET_REFERER, (char*)cur_link.c_str());

	dl.SetProgresVars(&ReportProgress, this);

    //eroare in timpul descarcarii
	if(a = dl.DownloadFile((dl_struct->dl_location+=ext).c_str()))
	{                          //wxMessageBox(wxString::Format(wxT("%d %d"),a, stop));
        if(stop)
            dl_struct->progress = -1;
        else
            dl_struct->progress = -3;
        dl_struct->curl_err = a;
    }
}
