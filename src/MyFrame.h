#ifndef __myframe__
#define __myframe__

#include "Gui.h"
#include "MyCanvas.h"
#include "CaptureManager.h"
#include "PluginBase.h"
#include "ImageJobQueue.h"
#include <wx/config.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>
#include "mathplot.h"

class CaptureManager;
class PluginBase;

//status-bar fields
enum
{
	ID_FIRST = 0,

};

/** Implementing MyFrame_ */
class MyFrame : public MyFrame_
{
	friend class PluginBase;
public:
	// Constructors
	MyFrame(const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE
		);
	MyFrame();
	~MyFrame();
	enum { //status-bar fields
		SBAR_MSG,
		SBAR_POS,
		SBAR_COUNT
	};
private:
	// Member variables
	CaptureManager *cm;
	ImageJobQueue* queue;

	// config helps in saving/loading configuration parameters in a platform-dependent way.
	wxConfigBase *config;
	wxString cwd;
	wxString imgDir;
	PluginBase *hotplug;
	bool isplaying;
	wxTimer *timer;
	bool loaded;
	int m_zslides;
	double m_deltaZ;
	double m_calibration;
	bool loadFluorescence;

	wxString getCWD();
	void EnableMenus(bool enable);
	void OnOpenMovie( wxCommandEvent &event );

public:
	void setCWD(const wxString& path);


	// File menu
	void OnOpenImages( wxCommandEvent &event );
	void OnSaveMovieAs( wxCommandEvent &event );
	void OnSaveFrameAs( wxCommandEvent &event );
	void OnPreferences( wxCommandEvent &event );
	void OpenMovie(const wxString &filename);
	void OnNewMovieOpened();
    void OnOpenConfocal( wxCommandEvent &event );

	// Image Menu
	void OnSmooth( wxCommandEvent& event );
	void OnCrop( wxCommandEvent& event );
	void OnResizeMovie( wxCommandEvent& event );
    void OnThread( wxCommandEvent& event );

	// Navigation events
	virtual void OnDeleteBefore( wxCommandEvent &event );
	virtual void OnDeleteAfter( wxCommandEvent &event );
	virtual void OnDelete( wxCommandEvent &event );
	virtual void OnPlay( wxCommandEvent &event );
	virtual void OnStop( wxCommandEvent &event );
	virtual void OnTogglePlay( wxCommandEvent &event );
	virtual void OnPrev( wxCommandEvent &event );
	virtual void OnNext( wxCommandEvent &event );
	virtual void OnFluorescence( wxCommandEvent &event );
	virtual void OnFirst( wxCommandEvent &event );
	virtual void OnLast( wxCommandEvent &event );
	virtual void OnScroll( wxScrollEvent &event );
	virtual void OnVScroll( wxScrollEvent &event );
	void OnNavigate();
	void UpdateControls();
	void OnTimer(wxTimerEvent &e);

	// Boundaries
	void OnFindContours(wxCommandEvent &event );
	void OnFilterContours(wxCommandEvent &event );
	void OnEditContours(wxCommandEvent &event );
	void OnExportContours(wxCommandEvent& e );
	void OnImportContours(wxCommandEvent& e );
	void OnImproveContours( wxCommandEvent& event );
	void OnSubtractBackground( wxCommandEvent& event );
	void OnTrackContours( wxCommandEvent& event );
	void OnLKContours( wxCommandEvent& event );
	void OnCamShift( wxCommandEvent& event );
	void OnMatchTemplate( wxCommandEvent& event );
	void OnCombinedTracking( wxCommandEvent& event );
	void OnFindFeatures( wxCommandEvent& event );
	void OnNormalizeContours( wxCommandEvent& event );
	void OnCopyContours( wxCommandEvent& event );
	void OnCorrectContours( wxCommandEvent& event );

	// Boundary View Menu
	void OnBorder( wxCommandEvent& event );
	void OnPoints( wxCommandEvent& event );
	void OnOtherBorder( wxCommandEvent& event );
	void OnOtherPoints( wxCommandEvent& event );
	void OnTopBorder( wxCommandEvent& event );
	void OnTopPoints( wxCommandEvent& event );
	void OnBottomBorder( wxCommandEvent& event );
	void OnBottomPoints( wxCommandEvent& event );

	//Analysis menu
	bool SetupCellPlot(wxString title, wxString ytitle, PlotDialog* &pd, mpWindow* &p, int &numCells);
	void OnPlotSpeed( wxCommandEvent& event );
	void OnPlotArea( wxCommandEvent& event );
	void OnPlotAreaDiff( wxCommandEvent& event );
	void OnPlotVolume( wxCommandEvent& event );
	void OnPlotVolumeDiff( wxCommandEvent& event );
	void OnPlotDeformation( wxCommandEvent& event );
	void OnViewImage(wxString title, bool (CaptureManager::*func)(wxBitmap &));
	void OnViewImage(wxString title, bool (CaptureManager::*func)(wxBitmap &, int, int));
	void OnViewTrackImage(wxCommandEvent &e);
	void OnViewTrajectoryImage(wxCommandEvent &e);
	void OnExportImage(wxString title, bool (CaptureManager::*func)(wxBitmap &));
	void OnExportImage(wxString title, bool (CaptureManager::*func)(wxBitmap &, int, int));
	void OnExportImage(wxString filename, bool (CaptureManager::*func)(wxBitmap &, int, int), int start, int end);
	void OnExportTrackImage(wxCommandEvent &e);
	void OnExportTrajectoryImage(wxCommandEvent &e);
	void OnExportSingleTrackImages(wxCommandEvent &e);
	void OnExportData(wxString title, bool (CaptureManager::*func)(const char*));
	void OnExportTrackData(wxCommandEvent &e);
	void OnExportTrajectoryData(wxCommandEvent &e);
	void OnExportSpeedData(wxCommandEvent &e);
	void OnExportAreaData(wxCommandEvent &e);
	void OnExportVolumeData(wxCommandEvent &e);
	void OnExportDeformationData(wxCommandEvent &e);
	void OnNewApproach(wxCommandEvent &e);

	void OnImportTrackData(wxCommandEvent &e);


	// Help menu
	virtual void OnAbout( wxCommandEvent &e);
	virtual void OnHelp( wxCommandEvent &e);


	// Plugin helpers
	template <class Plugin>
	void StartPlugin(Plugin *newplugin, wxWindow *parentwin);
	bool CheckPluginAlreadyHot(string pluginname);
	void OnPluginEnd(wxEvent &event );

	void SetStatusText(const wxString &text, int i=0);
	void ShowCanvas2(bool show=true);

	void OnClose(wxCloseEvent& event);
	//void OnSize(wxSizeEvent& event);

	//	void OnCanny(CannyEvent &event){		wxMessageBox("MyFrame::OnCanny: received custom event");	}
	void OnTemp( wxCommandEvent& event ){
	}
	virtual void OnKeyDown( wxKeyEvent& event );
	virtual void OnMouse( wxMouseEvent& event );
	DECLARE_EVENT_TABLE()
	DECLARE_DYNAMIC_CLASS(MyFrame)

public:
	//Testing functions
	template <class Plugin>
	void MemTestPlugin();

	void myShow(bool askLoad=false);

};

#endif // __myframe__
