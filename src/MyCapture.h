#pragma once

#ifndef _EiC
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#endif

#include "Util.h"
#include <wx/arrstr.h>

using namespace std;

class MyCapture
{
protected:
	MyCapture(): size(cvSize(0,0)), step(0), frame(NULL), frame_flip(NULL), frameCount(0), pos(-1), fps(5) { }
	virtual void setPos(int pos_);
public:
	CvSize size;
	int width;
	int height;
	int step;
	int frameCount;
	int pos;
	int fps;
	IplImage* frame;
	IplImage* frame_flip;

	virtual ~MyCapture();
	virtual IplImage* queryFrame(int pos_=-1) = 0;
	virtual bool IsOK() { return frameCount!=0; }
};

class MyCapture_Files : public MyCapture
{
protected:
    wxArrayString files;
 	MyCapture_Files() : MyCapture(){};
public:
	MyCapture_Files(const wxArrayString &files_);
	~MyCapture_Files();
	virtual IplImage* queryFrame(int pos_=-1);
};

class MyCapture_Movie : public MyCapture
{
private:
	CvCapture* capture;
	void setPos(int pos_);
	MyCapture_Movie(){};
public:
	MyCapture_Movie(const char *avi);
	~MyCapture_Movie();
	virtual IplImage* queryFrame(int pos_=-1);
};

class MyCapture_Confocal : public MyCapture_Files
{
private:
	int zSlides;
	bool hasFluorescence;
    MyCapture_Confocal(): MyCapture_Files(){};
public:
	MyCapture_Confocal(const wxArrayString &files_, int slides, bool fluorescence);
	~MyCapture_Confocal();
    virtual IplImage* queryFrame(int pos_=-1);
	int getSlideNumber();
	bool getFluorescence();
	wxString getFilename(int pos_);
};
