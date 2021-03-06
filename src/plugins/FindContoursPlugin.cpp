#include "FindContoursPlugin.h"
#include "Util.h"

FindContoursPlugin::FindContoursPlugin( wxWindow* parent_, MyFrame *win_ )
: PluginBase(GetStaticName(), parent_, win_, true, true),
gray(NULL), edge(NULL)
{
	sidebar =  new FindContoursSidebar(parent_, this);
	sidebarw = sidebar;
	if (cm->viewFluorescence)
        sidebar->scope2->SetSelection(1);
	DoPreview();
}

void FindContoursPlugin::ReleaseTemps()
{
	if (gray) cvReleaseImage(&gray);
	if (edge) cvReleaseImage(&edge);
}

int FindContoursPlugin::GetScope() {	return sidebar->scope->GetSelection(); }
int FindContoursPlugin::GetScope2() {	return sidebar->scope2->GetSelection(); }
bool FindContoursPlugin::IsPreviewOn(){ return sidebar->preview->GetValue(); }
void FindContoursPlugin::DoPreview()
{
	if (!IsPreviewOn())
		return;
	if (!sidebar->clean->GetValue())
		cm->ReloadCurrentFrameContours(false);
	ProcessImage(&cm->img);
	cm->Redraw(false);
}
#include <vector>
void FindContoursPlugin::ProcessImage( ImagePlus *img )
{
	ProcessImage_static(img, gray, edge, sidebar->thresh1->GetValue(), sidebar->thresh2->GetValue(), wxStringToLong(sidebar->aperture->GetStringSelection()), sidebar->dilate->GetValue(), sidebar->erode->GetValue(), sidebar->clean->GetValue(), sidebar->intra->GetSelection(), sidebar->approx->GetValue(), sidebar->autoThresh->GetValue() );
}

void FindContoursPlugin::ProcessImage_static( ImagePlus *img, IplImage* &gray, IplImage* &edge, double thresh1, double thresh2, int aperture, int dilate, int erode, bool clean, bool all, bool approx, bool autoThreshold )
{
	IplImage *orig = img->orig;
	if (!gray)
		gray = cvCreateImage( cvSize(orig->width, orig->height), IPL_DEPTH_8U, 1 );
	if (!edge)
		edge = cvCreateImage( cvSize(orig->width, orig->height), IPL_DEPTH_8U, 1 );
	cvCvtColor(orig, gray, CV_BGR2GRAY);
	if (autoThreshold)
	{
        thresh2 = cvThreshold(gray, edge, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        thresh1 = (255+thresh2)/2;
        //std::cout << thresh1 << " " << thresh2 << std::endl;
	}
	cvCanny( gray, edge, thresh1, thresh2, aperture );
	cvDilate( edge, edge, NULL, dilate );
	cvErode( edge, edge, NULL, erode );
	CvSeq *seq;
	cvFindContours( edge, img->CreateContoursStorageOnDemand(clean), &seq, sizeof(CvContour),
		all ? CV_RETR_LIST : CV_RETR_EXTERNAL,  approx ? CV_CHAIN_APPROX_SIMPLE : CV_CHAIN_APPROX_NONE , cvPoint(0,0) );
	img->AddContours(seq);
}

void FindContoursPlugin::OnFluorescence()
{
    if (cm->viewFluorescence && GetScope2() == 0)
    {
        sidebar->scope2->SetSelection(1);
    }
    else if (!cm->viewFluorescence && GetScope2() == 1)
    {
        sidebar->scope2->SetSelection(0);
    }
}
