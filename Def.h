#ifndef __Def_h__
#define __Def_h__
#include <string>
using namespace std;
#define VCD_VERSION "0.4"

struct Track
{
    wxString id;
    wxString name;
    wxString date;
};

struct ThreadStruct
{
    long track_id;
    wxThread *thread;
    int progress;
    string dl_location;  
    int curl_err;
    double dled;
    double dled_lst;
    int host;
};
struct DlStruct
{
    ThreadStruct *data;
    bool active;
};

//Mesaje cu erori de descarcare
#define ERROR_NO_HOST 0 // val = -2
#define ERROR_DURING_DL 1 // val = -3
#define ERROR_HOST_PROBLEM 2 // val = -4

static char error_dl[][45]={
    "Nu am gasit host cunoscut pentru descarcare",
    "Eroare(%d) la descarcare",
    "Probleme la descarcarea de pe acest host"};

#endif
