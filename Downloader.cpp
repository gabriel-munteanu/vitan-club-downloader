#include "Downloader.h"

string Downloader::UserAgent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/533.4 (KHTML, like Gecko) Chrome/5.0.375.86 Safari/533.4";

//initializez functiile pentru cur l
//setez UserAgent-ul
Downloader::Downloader()
{
	curl = curl_easy_init();
	ProgressFct = NULL;
	ProgressData = NULL;
	stop = NULL;
	post_data = NULL;
	
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3l);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, UserAgent.c_str());
	//for get		 	
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)this);
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void *)this);
	
}

void Downloader::SetUrl(const char *url)
{
	curl_easy_setopt(curl, CURLOPT_URL, url);
}

void Downloader::SetProgresVars(int (*ProgF)(void*,double, double, double, double), void* ProgD)
{
	ProgressFct = ProgF;
	ProgressData = ProgD;
}

int Downloader::Get(int HTTP_FLAGS)
{
	HtmlBody.clear();
	HtmlHeader.clear();
	//curl_easy_reset(curl);
	if(HTTP_FLAGS & HTTP_POST)
	   curl_easy_setopt(curl, CURLOPT_POST, 1L);
	else
	   curl_easy_setopt(curl, CURLOPT_POST, 0L);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetHtmlCallback); 	
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, GetHtmlHeaderCallback);
	
	res = curl_easy_perform(curl);
	return res;
}

void Downloader::SetStopVar(bool *stop_var)
{
    stop = stop_var;
}

void Downloader::SetOptions(int FLAGS,const char *option)
{
	if(FLAGS & HTTP_SET_REFERER)
		curl_easy_setopt(curl, CURLOPT_REFERER, option);
	if(FLAGS & HTTP_SET_COOKIE)
		curl_easy_setopt(curl, CURLOPT_COOKIE, option);
	if(FLAGS & HTTP_SET_POST_DATA)
	{
        if(post_data)
            delete post_data;
        post_data = strdup(option);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (void*)post_data);
    }
}
void Downloader::SetOptions(int FLAGS, int option)
{
	if(FLAGS & HTTP_FOLLOW_REDIRECT)
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, option);
	if(FLAGS &  HTTP_RESET_COOKIE)
		curl_easy_setopt(curl, CURLOPT_COOKIESESSION, option);
}

int Downloader::DownloadFile(const char* save_location)
{	
	DownloadHeader.clear();
	//curl_easy_reset(curl);
	
	if(ProgressFct)
	{
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressFct);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, ProgressData);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DlFileCallback); 	
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, DlHeaderCallback);
	
	fout_dl.open(save_location, ios::binary);
	if(!fout_dl.is_open())
	   return 777;
		
	res = curl_easy_perform(curl);
	
	fout_dl.close();
		
	return res;
}

size_t Downloader::GetHtmlCallback(void *data, size_t size, size_t nmemb, Downloader *dl)
{
	dl->HtmlBody.append((char*)data, size*nmemb);
	if(dl->stop)
	if(*(dl->stop))
	   return 0;
	
	return (size_t)(size * nmemb);
}

size_t Downloader::GetHtmlHeaderCallback(void *data, size_t size, size_t nmemb, Downloader *dl)
{
	dl->HtmlHeader.append((char*)data, size*nmemb);
	if(dl->stop)
	if(*(dl->stop))
	   return 0;
	
    return (size_t)(size * nmemb);
}

//Callback descarcare fisier
size_t Downloader::DlFileCallback(void *data, size_t size, size_t nmemb, Downloader *dl)
{
	//dl->HtmlHeader.append((char*)data, size*nmemb);
	dl->fout_dl.write((char*)data, size * nmemb);
	if(dl->stop)
	if(*(dl->stop))
	   return 0;
	
    return (size_t)(size * nmemb);
}
//Callback header descarcare fisier
size_t Downloader::DlHeaderCallback(void *data, size_t size, size_t nmemb, Downloader *dl)
{
	dl->DownloadHeader.assign((char*)data, size*nmemb);
	if(dl->stop)
	if(*(dl->stop))
	   return 0;
	
	return (size_t)(size * nmemb);
}

Downloader::~Downloader()
{
    if(post_data)
            delete post_data;
	curl_easy_cleanup(curl);
}
