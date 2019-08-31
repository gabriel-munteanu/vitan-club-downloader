///-----------------------------------------------------------------
///
/// @file      VCDFrm.cpp
/// @author    Gabi
/// Created:   22.12.2011 00:19:00
/// @section   DESCRIPTION
///            VCDFrm class implementation
///
///------------------------------------------------------------------

#include "VCDFrm.h"
#include "AboutDlg.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// VCDFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(VCDFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(VCDFrm::OnClose)
	EVT_MENU(ID_MNU_CHANGESAVEFOLDER_1009, VCDFrm::Mnuchangesavefolder1009Click)
	EVT_MENU(ID_MNU_CLOSE_1010, VCDFrm::Mnuclose1010Click)
	EVT_MENU(ID_MNU_DESPRE_1016, VCDFrm::Mnudespre1016Click)
	EVT_MENU(ID_MNU_HOST1_1017 , VCDFrm::Mnuhost11017Click)
	EVT_MENU(ID_MNU_HOST2_1018 , VCDFrm::Mnuhost21018Click)
	EVT_MENU(ID_MNU_HOST3_1019 , VCDFrm::Mnuhost31019Click)
	EVT_MENU(ID_MNU_HOST4_1022 , VCDFrm::Mnuhost41022Click)
	EVT_TIMER(ID_TMR_DOWNLOADPROGRESS,VCDFrm::tmr_DownloadProgressTimer)
	EVT_MENU(ID_MNU_SHOWINFOLDER_1012 , VCDFrm::Mnushowinfolder1012Click)
	EVT_MENU(ID_MNU_ADAUGASIASCULTAINWINAMP_1021 , VCDFrm::Mnuadaugasiascultainwinamp1021Click)
	EVT_MENU(ID_MNU_ADAUGAINWINAMP_1020 , VCDFrm::Mnuadaugainwinamp1020Click)
	EVT_MENU(ID_MNU_STOPDL_1013 , VCDFrm::Mnustopdl1013Click)
	EVT_MENU(ID_MNU_HOST1_1001 , VCDFrm::Mnuhost11001Click)
	EVT_MENU(ID_MNU_HOST2_1003 , VCDFrm::Mnuhost21003Click)
	EVT_MENU(ID_MNU_HOST3_1004 , VCDFrm::Mnuhost31004Click)
	EVT_MENU(ID_MNU_HOST4_1007 , VCDFrm::Mnuhost41007Click)
	EVT_MENU(ID_MNU_DLPAGE_1001 , VCDFrm::Mnudlpage1001Click)
	
	EVT_LIST_ITEM_RIGHT_CLICK(ID_LIST_DOWNLOAD,VCDFrm::list_DownloadRightClick)
	EVT_BUTTON(ID_BTN_LOADM,VCDFrm::btn_LoadMClick)
	
	EVT_LIST_ITEM_ACTIVATED(ID_LIST_TRACKS,VCDFrm::list_TracksRightClick)
	EVT_LIST_ITEM_RIGHT_CLICK(ID_LIST_TRACKS,VCDFrm::list_TracksRightClick)
END_EVENT_TABLE()
////Event Table End
wxString VCDFrm::web_location = wxT("http://wyrdaprogramming.tk/vcdownloader/get/");


VCDFrm::VCDFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
	for(int i=0; i<MAX_DL_IN_LIST;i++)
	   DlS[i].active = false;
}

VCDFrm::~VCDFrm()
{
}

void VCDFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	panel_Main = new wxPanel(this, ID_PANEL_MAIN, wxPoint(0, 0), wxSize(440, 561));

	list_Tracks = new wxListCtrl(panel_Main, ID_LIST_TRACKS, wxPoint(8, 53), wxSize(430, 249), wxLC_REPORT, wxDefaultValidator, wxT("list_Tracks"));
	list_Tracks->InsertColumn(0, wxT("Nume melodie"), wxLIST_FORMAT_LEFT, 292);
	list_Tracks->InsertColumn(1, wxT("Data aparitie"), wxLIST_FORMAT_LEFT, 117);

	wxArrayString arrayStringFor_choice_MType;
	arrayStringFor_choice_MType.Add(wxT("Romaneasca"));
	arrayStringFor_choice_MType.Add(wxT("Straina"));
	choice_MType = new wxChoice(panel_Main, ID_CHOICE_MTYPE, wxPoint(68, 22), wxSize(107, 23), arrayStringFor_choice_MType, 0, wxDefaultValidator, wxT("choice_MType"));
	choice_MType->SetSelection(0);

	btn_LoadM = new wxButton(panel_Main, ID_BTN_LOADM, wxT("Incarca muzica"), wxPoint(269, 20), wxSize(98, 25), 0, wxDefaultValidator, wxT("btn_LoadM"));

	list_Download = new wxListCtrl(panel_Main, ID_LIST_DOWNLOAD, wxPoint(8, 329), wxSize(430, 115), wxLC_REPORT, wxDefaultValidator, wxT("list_Download"));
	list_Download->InsertColumn(0, wxT("Nume melodie"), wxLIST_FORMAT_LEFT, 292);
	list_Download->InsertColumn(1, wxT("Viteza"), wxLIST_FORMAT_CENTER, 72);
	list_Download->InsertColumn(2, wxT("%"), wxLIST_FORMAT_CENTER, 45);

	mnu_ListRightClick = new wxMenu(wxT(""));wxMenu *ID_MNU_DOWNLOAD_1006_Obj = new wxMenu();
	ID_MNU_DOWNLOAD_1006_Obj->Append(ID_MNU_HOST1_1001, wxT("Host1"), wxT(""), wxITEM_NORMAL);
	ID_MNU_DOWNLOAD_1006_Obj->Append(ID_MNU_HOST2_1003, wxT("Host2"), wxT(""), wxITEM_NORMAL);
	ID_MNU_DOWNLOAD_1006_Obj->Append(ID_MNU_HOST3_1004, wxT("Host3"), wxT(""), wxITEM_NORMAL);
	ID_MNU_DOWNLOAD_1006_Obj->Append(ID_MNU_HOST4_1007, wxT("Host4"), wxT(""), wxITEM_NORMAL);
	mnu_ListRightClick->Append(ID_MNU_DOWNLOAD_1006, wxT("Descarca"), ID_MNU_DOWNLOAD_1006_Obj);
	mnu_ListRightClick->Append(ID_MNU_DLPAGE_1001, wxT("Deschide pagina download"), wxT("Deschide pagina de download de pe VitanClub.net"), wxITEM_NORMAL);

	mnu_DlRightClickRun = new wxMenu(wxT(""));mnu_DlRightClickRun->Append(ID_MNU_STOPDL_1013, wxT("Opreste"), wxT(""), wxITEM_NORMAL);

	mnu_DlRightClickDone = new wxMenu(wxT(""));mnu_DlRightClickDone->Append(ID_MNU_SHOWINFOLDER_1012, wxT("Arata in folder"), wxT(""), wxITEM_NORMAL);
	mnu_DlRightClickDone->Append(ID_MNU_ADAUGASIASCULTAINWINAMP_1021, wxT("Adauga si asculta in Winamp"), wxT(""), wxITEM_NORMAL);
	mnu_DlRightClickDone->Append(ID_MNU_ADAUGAINWINAMP_1020, wxT("Adauga in Winamp"), wxT(""), wxITEM_NORMAL);

	tmr_DownloadProgress = new wxTimer();
	tmr_DownloadProgress->SetOwner(this, ID_TMR_DOWNLOADPROGRESS);
	tmr_DownloadProgress->Start(1000);

	mnu_DlRightClickErr = new wxMenu(wxT(""));wxMenu *ID_MNU_RETRYDL_1014_Obj = new wxMenu();
	ID_MNU_RETRYDL_1014_Obj->Append(ID_MNU_HOST1_1017, wxT("Host1"), wxT(""), wxITEM_NORMAL);
	ID_MNU_RETRYDL_1014_Obj->Append(ID_MNU_HOST2_1018, wxT("Host2"), wxT(""), wxITEM_NORMAL);
	ID_MNU_RETRYDL_1014_Obj->Append(ID_MNU_HOST3_1019, wxT("Host3"), wxT(""), wxITEM_NORMAL);
	ID_MNU_RETRYDL_1014_Obj->Append(ID_MNU_HOST4_1022, wxT("Host4"), wxT(""), wxITEM_NORMAL);
	mnu_DlRightClickErr->Append(ID_MNU_RETRYDL_1014, wxT("Reincearca descarcarea"), ID_MNU_RETRYDL_1014_Obj);

	mnu_Main = new wxMenuBar();
	wxMenu *ID_MNU_MENIU_1011_Mnu_Obj = new wxMenu((long)0);
	ID_MNU_MENIU_1011_Mnu_Obj->Append(ID_MNU_CHANGESAVEFOLDER_1009, wxT("Schimba folder-ul de salvare"), wxT(""), wxITEM_NORMAL);
	ID_MNU_MENIU_1011_Mnu_Obj->Append(ID_MNU_CLOSE_1010, wxT("Inchide"), wxT(""), wxITEM_NORMAL);
	mnu_Main->Append(ID_MNU_MENIU_1011_Mnu_Obj, wxT("Meniu"));
	
	wxMenu *ID_MNU_AJUTOR_1015_Mnu_Obj = new wxMenu((long)0);
	ID_MNU_AJUTOR_1015_Mnu_Obj->Append(ID_MNU_DESPRE_1016, wxT("Despre"), wxT(""), wxITEM_NORMAL);
	mnu_Main->Append(ID_MNU_AJUTOR_1015_Mnu_Obj, wxT("Ajutor"));
	SetMenuBar(mnu_Main);

	SetTitle(wxT("VitanClub Downloader"));
	SetIcon(wxNullIcon);
	SetSize(8,8,452,500);
	Center();
	
	////GUI Items Creation End
}
//-------App settings-----------------------------------------------------------

//Incarca setarile din registry iar daca nu exista(prima rulare) forteaza
//setarea celor necesare(dl location)
void VCDFrm::LoadSettings()
{
    wxRegKey *pRegKey = new wxRegKey("HKEY_CURRENT_USER\\Software\\wyrdaprogramming");

    if( !pRegKey->Exists() )
        pRegKey->Create();
        
    if( pRegKey->HasValue("defaultSaveFolder") )
        pRegKey->QueryValue("defaultSaveFolder", SaveFolder);
    else
    {
        wxDirDialog *DirDglSaveLoc = new wxDirDialog(this, "Unde salvez muzica?");
        while(SaveFolder.IsEmpty())
        {
            DirDglSaveLoc->ShowModal();
            SaveFolder = DirDglSaveLoc->GetPath();
        }
        SaveFolder += "\\";
        pRegKey->SetValue("defaultSaveFolder", SaveFolder);
        
        delete DirDglSaveLoc;
    }
    delete pRegKey;
}

//-------Utilities--------------------------------------------------------------
// Verifica daca avem conexiune la internet si vitanclub e online
void VCDFrm::CheckInternet()
{
    Downloader x;
    x.SetUrl("http://wyrdaprogramming.tk/version/vcdownloader.txt");
	x.Get();
	if(x.HtmlBody.find("vcdownloader:")==string::npos)
	{
        internet_acces = false;
        wxMessageBox("Nu esti conectat la internet");
    }
    else
    {    
        internet_acces = true;
        
        string ver = x.HtmlBody.substr(13);
        if((ver.length() < 6) &&
         (ver.compare(VCD_VERSION)))
            wxMessageBox("Versiunea "+ver+" este disponibila pe http://wyrdaprogramming.tk!", "Versiune noua");
        
        x.SetUrl("http://www.vitanclub.net");
	    x.Get();
	    if(x.HtmlBody.find("Romaneasca")==string::npos)
	        wxMessageBox("Nu vei putea descarca melodii, www.vitanclub.ro este offline!");
    }
}


//-------Controls events--------------------------------------------------------
//-------Main frame controls----------------------------------------------------

// Mnuchangesavefolder1009Click

void VCDFrm::Mnuchangesavefolder1009Click(wxCommandEvent& event)
{
	wxRegKey *pRegKey = new wxRegKey("HKEY_CURRENT_USER\\Software\\wyrdaprogramming");

    wxDirDialog *DirDglSaveLoc = new wxDirDialog(this, "Unde salvez muzica?");
    DirDglSaveLoc->SetPath(SaveFolder);

    if( DirDglSaveLoc->ShowModal() == wxID_OK )
    {
        SaveFolder = DirDglSaveLoc->GetPath();
        SaveFolder += "\\";
        pRegKey->SetValue("defaultSaveFolder", SaveFolder);
    }
    delete DirDglSaveLoc;
    delete pRegKey;
}

// Mnuclose1010Click

void VCDFrm::Mnuclose1010Click(wxCommandEvent& event)
{
	Destroy();
}

// Mnudespre1016Click
void VCDFrm::Mnudespre1016Click(wxCommandEvent& event)
{
	AboutDlg *about = new AboutDlg(GetCapture());
	about->SetIcon(wxICON(VCD_ICON));
	about->ShowModal();
	delete about;
}


//Timer-ul folosit la update-ul progresului si vitezei melodiilor ce se descarca
void VCDFrm::tmr_DownloadProgressTimer(wxTimerEvent& event)
{
    for(int i=0; i<MAX_DL_IN_LIST;i++)
        if(DlS[i].active == true)
        {
            int itmIndex = list_Download->FindItem(-1, (wxUIntPtr)DlS[i].data);
            if(DlS[i].data->progress < 0)//daca avem erori
            {
                if(DlS[i].data->progress == -1)
                    list_Download->SetItem(itmIndex, 1, "Stop");
                else
                    list_Download->SetItem(itmIndex, 1, "Eroare");
                DlS[i].active = false;

                DlError(list_Download->GetItemText(itmIndex), DlS[i].data->progress, DlS[i].data->curl_err);
                continue;
            }
            if(DlS[i].data->progress == 0)//daca nu a descarcat nimic sa nu modifice mesajul initial
                continue;
            //wxMessageBox(wxString::Format(wxT("%i %%"),ThS[i].progress));
            list_Download->SetItem(itmIndex, 1, DlSpeed(i));
            list_Download->SetItem(itmIndex, 2, wxString::Format(wxT("%d %%"),DlS[i].data->progress));
            DlS[i].data->dled_lst = DlS[i].data->dled;//update download last
            if(DlS[i].data->progress == 100)
                DlS[i].active = false;
        }
}
//-------Auxiliar functions-----------------------------------------------------
//Calculeaza viteza de descarcare a melodiei ThS[ i ]
wxString VCDFrm::DlSpeed(int i)
{
    double dl = (DlS[i].data->dled - DlS[i].data->dled_lst)/1024;// kb/s

    if(dl > 1024)
        return wxString::Format(wxT("%.1f Mb/s"),dl/1024);
    return wxString::Format(wxT("%.1f Kb/s"),dl);
}

//Afiseaza pentru o melodie ce nu a putut fi descarcata
void VCDFrm::DlError(wxString mel, int cod, int curl_err)
{
    switch(cod)
    {// -1  - download oprit manual
        case -1: break;
        case -2:
            wxMessageBox(error_dl[ERROR_NO_HOST], mel);break;
        case -3:
            char er[20];
            sprintf(er, error_dl[ERROR_DURING_DL], curl_err);
            wxMessageBox(er, mel);break;
        case -4:
            wxMessageBox(error_dl[ERROR_HOST_PROBLEM], mel);break;
        default:
            wxMessageBox(wxString::Format(wxT("Cod eroare necunoscut(%d)(%d)"),cod, curl_err), "Eroare");
    }
}

void VCDFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

//-------Music list functions---------------------------------------------------
//Butonul de "Incarca muzica" ce populeaza lista de melodii in functie de tip-ul
//ales

void VCDFrm::btn_LoadMClick(wxCommandEvent& event)
{
    //check if we have internet connection
    if(!internet_acces)
        CheckInternet();
    if(!internet_acces)
        return;
    
    //create the link for the trak list
    wxString link = web_location + choice_MType->GetStringSelection().Lower();

    //get the http response
	Downloader x;
	//x.SetUrl(link.mb_str(wxConvUTF8));
	x.SetUrl(link.c_str() );
	x.Get();

	//wxMessageBox(x.HtmlHeader);

	//display thsults in the list control
	char delim = '\n';
	int a=0;
	int b;
	list_Tracks->DeleteAllItems();
	for(int i=0; i<=60;i++)
	{
		b = x.HtmlBody.find(delim, a);
		tracks[i].id = x.HtmlBody.substr(a,b-a);
		a = b + 1;
		b = x.HtmlBody.find(delim, a);
		tracks[i].name = x.HtmlBody.substr(a,b-a);
		//wxMessageBox(tracks[i].name);
		a = b + 1;
		b = x.HtmlBody.find(delim, a);
		tracks[i].date = x.HtmlBody.substr(a,b-a);
		a = b + 1;

        list_Tracks->InsertItem(i, tracks[i].name);
        list_Tracks->SetItem(i, 1,tracks[i].date);

	}
}

//Event-ul de click dreapta de pe lista cu melodii

void VCDFrm::list_TracksRightClick(wxListEvent& event)
{
	PopupMenu(mnu_ListRightClick);
}

//Butonul de download din meniul ce apare cand dai click dreapta pe o melodie
//ce vrei sa o descarci

void VCDFrm::StartDownload(int host)
{
	long itemIndex = -1;
	itemIndex = list_Tracks->GetNextItem(itemIndex,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);
    if(itemIndex == -1)
        return;
    //verific daca melodia e deja in lista de la descarcare
    wxString name = list_Tracks->GetItemText(itemIndex);
    if(list_Download->FindItem(-1, name) != -1)
    {
        wxMessageBox("Melodia exista in lista de download!");
        return;
    }
    //wxMessageBox(list_Tracks->GetItemText(itemIndex));
    int i;
    for(i=0; i<MAX_DL_IN_LIST; i++)
	   if(DlS[i].active == false)
	       break;
	if(i == MAX_DL_IN_LIST)
	{
        wxMessageBox(wxString("Limita maxima de downloaduri active este de ") + 
                   wxString::Format(wxT("%i"),MAX_DL_IN_LIST));
        return;
    }
    
    //setup for new download
    DlS[i].data = new ThreadStruct;
    DlS[i].data->track_id = atol(tracks[itemIndex].id.c_str());
    DlS[i].data->dl_location = string(SaveFolder + tracks[itemIndex].name);
    DlS[i].data->progress = 0;    
    DlS[i].data->host = host;
    DlS[i].data->dled_lst = DlS[i].data->dled = 0; 
    DownloadThread *th = new DownloadThread(DlS[i].data);
    DlS[i].data->thread = th;
    th->Create(stack_size);
    
    list_Download->InsertItem(0, tracks[itemIndex].name);
    list_Download->SetItem(0, 1,"Se pregateste");
    //list_Download->SetItemData(0, ThS[i].track_id);
    list_Download->SetItemPtrData(0, (wxUIntPtr)DlS[i].data);
    //wxMessageBox(tracks[itemIndex].name);
    th->Run();
    DlS[i].active = true;    
}
//Click pt Host1
void VCDFrm::Mnuhost11001Click(wxCommandEvent& event)
{
	StartDownload(1);
}

//Click pt Host2
void VCDFrm::Mnuhost21003Click(wxCommandEvent& event)
{
	StartDownload(2);
}

//Click pt Host3
void VCDFrm::Mnuhost31004Click(wxCommandEvent& event)
{
	StartDownload(3);
}

//Click pt Host4
void VCDFrm::Mnuhost41007Click(wxCommandEvent& event)
{
	StartDownload(4);
}
//Deschide pagina de download a melodiei de pe vitanclub.net
void VCDFrm::Mnudlpage1001Click(wxCommandEvent& event)
{
	long itemIndex = -1;
	itemIndex = list_Tracks->GetNextItem(itemIndex,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);
    wxString link = tracks[itemIndex].name;
    for(int i=0; i< link.Length(); i++)
    {
            if(link[i] == ' ' || 
                link[i] == '.'  || 
                link[i] == '&'||
                link[i] == '('||
                link[i] == ')')
                link[i] = '-';
            
    }
    link = "http://www.vitanclub.net/download-" + 
            choice_MType->GetStringSelection().Lower() + "/" + link + "_" +
            tracks[itemIndex].id + ".html";
    ShellExecute(NULL,_("open"), link.wc_str(), _(""), NULL, SW_SHOWNORMAL);
            
}

//-------Download list functions------------------------------------------------

//Event-ul de click dreapta in lista de download-uri
void VCDFrm::list_DownloadRightClick(wxListEvent& event)
{
    long itemIndex = -1;
	itemIndex = list_Download->GetNextItem(itemIndex,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);                
	Th = (ThreadStruct*)list_Download->GetItemData(itemIndex);
	if( Th->progress == 100)//terminat
	{
        PopupMenu(mnu_DlRightClickDone);
        return;
    }
    if( Th->progress < 0 || Th->progress > 100)//eroare sau oprit intentionat
	{
        PopupMenu(mnu_DlRightClickErr);
        return;
    }
    if( Th->progress >= 0 && Th->progress < 100)//ruleaza
    {
        PopupMenu(mnu_DlRightClickRun);
        return;
    }
}

//Arata fisierul descarcat 100% in folder
void VCDFrm::Mnushowinfolder1012Click(wxCommandEvent& event)
{
	ShellExecute(NULL, _("open"), _("explorer.exe"), wxString("/select,"+Th->dl_location).wc_str(), NULL, SW_SHOWNORMAL);
}

//Adauga melodia in winamp
void VCDFrm::Mnuadaugainwinamp1020Click(wxCommandEvent& event)
{
	ShellExecute(NULL, _("open"), _("winamp"), wxString("/ADD \""+Th->dl_location+"\"").wc_str(), NULL, SW_SHOWNORMAL);
}

//Adauga melodia si ii da play in winamp
void VCDFrm::Mnuadaugasiascultainwinamp1021Click(wxCommandEvent& event)
{
	ShellExecute(NULL, _("open"), _("winamp"), wxString("/ADD \\\\QUEUE \""+Th->dl_location+"\"").wc_str(), NULL, SW_SHOWNORMAL);
}
//Opreste download-ul
void VCDFrm::Mnustopdl1013Click(wxCommandEvent& event)
{
	((DownloadThread*)Th->thread)->StopDL();
	//Th->thread = NULL;
	//Th->progress = -1;	
}
//Porneste descarcarea pentru un download oprit(eroare sau intentionat)
void VCDFrm::RestartDownload(int host)
{
    int i;
    for(i=0; i<MAX_DL_IN_LIST; i++)
	   if(DlS[i].active == false)
	       break;
	if(i == MAX_DL_IN_LIST)
	{
        wxMessageBox(wxString("Limita maxima de downloaduri active este de ") +
                   wxString::Format(wxT("%i"),MAX_DL_IN_LIST));
        return;
    }
    //wxMessageBox("test");
	Th->dl_location.resize( Th->dl_location.find_last_of('.') );
	Th->dled = 0;
	Th->dled_lst = 0;
	Th->progress = 0;
	Th->host = host;
	//if(Th->thread)
	//   delete Th->thread;
	Th->thread = new DownloadThread(Th);
	Th->thread->Create(stack_size);
	Th->thread->Run();
    DlS[i].active = true;
    
    int itemIndex = list_Download->FindItem(-1, (wxUIntPtr)Th);
    if(itemIndex != -1)
    {
        list_Download->SetItem(itemIndex, 1,"Se pregateste");
        list_Download->SetItem(itemIndex, 2,"0 %");
}
}

//Click pt Host1
void VCDFrm::Mnuhost11017Click(wxCommandEvent& event)
{
	RestartDownload(1);
}

//Click pt Host2
void VCDFrm::Mnuhost21018Click(wxCommandEvent& event)
{
	RestartDownload(2);
}

//Click pt Host3
void VCDFrm::Mnuhost31019Click(wxCommandEvent& event)
{
	RestartDownload(3);
}

//Click pt Host4
void VCDFrm::Mnuhost41022Click(wxCommandEvent& event)
{
	RestartDownload(4);
}
//------------------------------------------------------------------------------

