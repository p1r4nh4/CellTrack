#include "ImproveContoursPlugin.h"
#include "Util.h"

ImproveContoursPlugin::ImproveContoursPlugin( wxWindow* parent_, MyFrame *win_ ): PluginBase(GetStaticName(), parent_, win_, true, true), gray(NULL)
{
	sidebar =  new ImproveContoursSidebar(parent_, this);
	sidebarw = sidebar;
	DoPreview();
}

int ImproveContoursPlugin::GetScope() {	return sidebar->scope->GetSelection(); }
int ImproveContoursPlugin::GetScope2() { return sidebar->scope2->GetSelection(); }
bool ImproveContoursPlugin::IsPreviewOn(){ return sidebar->preview->GetValue(); }

void ImproveContoursPlugin::OnFluorescence()
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

void ImproveContoursPlugin::DoPreview()
{
	if (!IsPreviewOn())
		return;
	cm->ReloadCurrentFrameContours(false);
	ProcessImage(&cm->img);
	cm->Redraw(false);
}

void ImproveContoursPlugin::ProcessImage( ImagePlus *img )
{
	CvSeq *seq;
	CvPoint* ps;
	float alpha=sidebar->alpha->GetValue();
	float beta= sidebar->beta->GetValue();
	float gamma=sidebar->gamma->GetValue();
	CvSize win=cvSize(2*sidebar->width->GetValue()-1, 2*sidebar->height->GetValue()-1);
	int scheme = sidebar->gradient->GetValue();

	if (!gray)
		gray = cvCreateImage( cvSize(img->orig->width, img->orig->height), IPL_DEPTH_8U, 1 );
	cvCvtColor(img->orig, gray, CV_BGR2GRAY);
	if (sidebar->use_blur->GetValue())
    {
        IplImage* temp = cvCreateImage( cvSize(gray->width, gray->height), IPL_DEPTH_8U, 1 );
        cvCopyImage(gray, temp);
        cvSmooth(temp, gray, CV_MEDIAN, 3);
        cvReleaseImage(&temp);
    }
	for (int i=(int)img->contourArray.size()-1; i>=0; i--)
	{
		seq = img->contourArray[i];
		int np = seq->total;
		ps = (CvPoint*)malloc( np*sizeof(CvPoint) );
		cvCvtSeqToArray(seq, ps);
		CvTermCriteria term=cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, sidebar->max_iter->GetValue(), sidebar->epsilon->GetValue()*np);
		cvSnakeImage( gray, ps, np, &alpha, &beta, &gamma, CV_VALUE, win, term, scheme );
		img->ReplaceContour(i, ps, np);
		free(ps); ps=NULL;
	}
}
