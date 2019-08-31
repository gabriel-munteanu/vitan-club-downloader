#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>

#ifndef __Downloader_h__
#define __Downloader_h__

using namespace std;
//HTTP_REQUEST_FLAGS	
	#define HTTP_REFERER (1<<0)    //use referer in request	
	#define HTTP_RESET_COOKIE (1<<2)    //reset all cookies from curl
	//#define HTTP_GET_HEADER (1<<3)   //get only the header without content
	#define HTTP_POST (1<<4)    //use POST in request, not GET	
	#define HTTP_SET_COOKIE (1<<5)    //set curl a cookie
	#define HTTP_FOLLOW_REDIRECT (1<<6)    //set curl to follor redirects
	#define HTTP_SET_REFERER (1<<7)    //set a value for referer
	#define HTTP_SET_POST_DATA (1<<8)    //set a value for post_data	
	//END OF: HTTP_REQUEST_FLAGS
class Downloader
{
protected:
	static string UserAgent;
	string Url;
	
	ofstream fout_dl;	
	
	CURL *curl;
	CURLcode res;	
	
	int (*ProgressFct)(void*, double, double, double, double);
	void *ProgressData;
	bool *stop;
	
	char *post_data;
	
	static size_t GetHtmlCallback(void *, size_t, size_t, Downloader*);
	static size_t GetHtmlHeaderCallback(void *, size_t, size_t,Downloader*);
	static size_t DlFileCallback(void *, size_t, size_t, Downloader*);
	static size_t DlHeaderCallback(void *, size_t, size_t, Downloader*);
public:
	string HtmlBody;
	string HtmlHeader;	
	string DownloadHeader;	
	Downloader();
	void SetUrl(const char *);
	void SetOptions(int,const char*);
	void SetOptions(int, int);
	int Get(int HTTP_FLAGS=0);
	void SetProgresVars(int (*)(void*, double, double, double, double), void*);
	int DownloadFile(const char*);
	void SetStopVar(bool *stop_var);
	~Downloader();
	
};
#endif
