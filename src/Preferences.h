#ifndef __Preferences__
#define __Preferences__

/**
@file
Subclass of PreferencesDialog_, which is generated by wxFormBuilder.
*/

#include "Gui.h"
#include <wx/config.h>
#include <cxcore.h>

#define DEFINE_PREF_VARIABLE(TYPE,NAME)	\
	private: static TYPE NAME; \
	public: static TYPE Get##NAME();

/** Implementing PreferencesDialog_ */
class Preferences : public PreferencesDialog_
{
private:
	static wxConfigBase *config;
	static bool initialized;

public:
	/** Constructor */
	Preferences( wxWindow* parent, bool keepDefaults=false );
	void OnRestoreDefaults(wxCommandEvent &e);
	void OnCancel(wxCommandEvent &e);
	void OnSave(wxCommandEvent &e);

	//call this function first to initialize other static variables.
	// TODO: move this to private: and remove call in myApp when all the
	// member variables have a corresponding Get..
	static void InitializeOnDemand(); 
	static long GetSavingCodec();
	static CvSize GetSavingSize();

	DEFINE_PREF_VARIABLE(bool, SavingCodecUseCombo)
	DEFINE_PREF_VARIABLE(int, SavingCodecCombo)
	DEFINE_PREF_VARIABLE(bool, SavingCodecUseFOURCC)
	DEFINE_PREF_VARIABLE(wxString, SavingCodecFOURCC)
	DEFINE_PREF_VARIABLE(bool, SavingSizeOverride)
	DEFINE_PREF_VARIABLE(wxString, SavingSizeWidth)
	DEFINE_PREF_VARIABLE(wxString, SavingSizeHeight)
	DEFINE_PREF_VARIABLE(int, SavingFpsDefault)
	DEFINE_PREF_VARIABLE(bool, SavingFpsOverride)
	DEFINE_PREF_VARIABLE(bool, ColorContourBorderDraw)
	DEFINE_PREF_VARIABLE(wxString, ColorContourBorderColor)
	DEFINE_PREF_VARIABLE(int, ColorContourBorderWidth)
	DEFINE_PREF_VARIABLE(bool, ColorContourCornerDraw)
	DEFINE_PREF_VARIABLE(wxString, ColorContourCornerColor)
	DEFINE_PREF_VARIABLE(int, ColorContourCornerWidth)
	DEFINE_PREF_VARIABLE(bool, ColorContourPolygonFill)
	DEFINE_PREF_VARIABLE(wxString, ColorContourPolygonColor)
	DEFINE_PREF_VARIABLE(int, Notebook)
	DEFINE_PREF_VARIABLE(wxString, ColorContourSelectedColor)
	DEFINE_PREF_VARIABLE(wxString, ColorFeatureColor)

};
#endif // __PreferencesDialog__
