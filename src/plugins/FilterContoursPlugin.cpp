#include "FilterContoursPlugin.h"
#include "Util.h"

FilterContoursPlugin::FilterContoursPlugin( wxWindow* parent_, MyFrame *win_ ): PluginBase(GetStaticName(), parent_, win_, true, true) {
	sidebar =  new FilterContoursSidebar(parent_, this);
	sidebarw = sidebar;
	double maxArea = cm->size.width*cm->size.height;
	std::cout << "Area: " << maxArea << std::endl;
	sidebar->minArea->SetRange(0, maxArea);
	sidebar->maxArea->SetRange(0, maxArea);
	sidebar->minArea->SetValue(pow(10, ceil(log10(maxArea/100.0))));
	sidebar->maxArea->SetValue(pow(10, ceil(log10(maxArea/10.0))));
	if (cm->viewFluorescence)
        sidebar->scope2->SetSelection(1);
	DoPreview();
}
int FilterContoursPlugin::GetScope() {	return sidebar->scope->GetSelection(); }
int FilterContoursPlugin::GetScope2() {	return sidebar->scope2->GetSelection(); }
bool FilterContoursPlugin::IsPreviewOn(){ return sidebar->preview->GetValue(); }
void FilterContoursPlugin::DoPreview()
{
	cm->ReloadCurrentFrameContours(false);
	ProcessImage(&cm->img);
	cm->Redraw(false);
}

void FilterContoursPlugin::ProcessImage( ImagePlus *img )
{
    ProcessImage_static( img, sidebar->isMinArea->GetValue(), sidebar->isMaxArea->GetValue(), sidebar->minArea->GetValue(), sidebar->maxArea->GetValue(), sidebar->isMinDist->GetValue(), sidebar->minDist->GetValue(), cm->GetSize() );
}

void FilterContoursPlugin::ProcessImage_static( ImagePlus *img, int isMinArea, int isMaxArea, int minArea, int maxArea, int isMinDist, int minDist, CvSize size )
{
	CvSeq *seq;
	for (int i=(int)img->contourArray.size()-1; i>=0; i--)
	{
		seq = img->contourArray[i];
		if (isMinArea || isMaxArea)
		{
			double area = fabs(cvContourArea(seq));
			if ( (isMinArea && area < minArea)
				||(isMaxArea && area > maxArea) )
            {
				img->RemoveContour(i);
				continue;
			}
		}
		if (isMinDist)
		{
			bool removed = false;
			for (int j=0; j<seq->total; j++)
			{
				MyPoint p( (CvPoint*) cvGetSeqElem(seq, j) );
				if ( !(p >= minDist) || !(MyPoint(MyPoint(size) -p) >= minDist) )
				{
					img->RemoveContour(i);
					removed = true;
					break;
				}
			}
			if (removed)
				continue;
		}
	}
}

void FilterContoursPlugin::OnFluorescence()
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
