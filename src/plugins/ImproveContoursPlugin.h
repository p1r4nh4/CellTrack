#pragma once
#include "PluginBase.h"
#include "ImproveContoursSidebar.h"
#include "ImagePlus.h"
#include <cv.h>
#include <highgui.h>
#include "wxTextCtrl_double.h"

class ImproveContoursSidebar;

class ImproveContoursPlugin :
	public PluginBase
{
private:
	ImproveContoursSidebar *sidebar;
	IplImage *gray;
public:
	ImproveContoursPlugin( wxWindow* parent_, MyFrame *win_ );
	~ImproveContoursPlugin() { if(gray) cvReleaseImage( &gray ); }
	static string GetStaticName() { return "ImproveContours"; }
	virtual void OnFluorescence();
	virtual int GetScope();
	virtual int GetScope2();
	virtual bool IsPreviewOn();
	virtual void DoPreview();

	void ProcessImage( ImagePlus *img );
	static void ProcessImage_static(ImagePlus* img, IplImage* &gray, float alpha, float beta, float gamma, CvSize win, int scheme, bool useBlur, int max_iter, float epsilon);
};
