/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:54
	plik:    	va_opencv
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __VA_OPENCV_H__
#define __VA_OPENCV_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy
struct CvCapture;

//////////////////////////////////////////////////////////////////////////

/// modul akwizycji wideo oparty o biblioteke OpenCV
class EXPORT_MODULE vaOpenCV: public moduleBase
{
public:
	vaOpenCV();
	virtual ~vaOpenCV();

	virtual const char * get_module_description();

	virtual int input_type();
	virtual int output_type();

	virtual int init( PropertyMgr * pm = NULL );
	virtual void free();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

protected:
	CvCapture * capture;
	int			alloc_mem;
	int			device;		// device num parameter
	char *		filename;	// when capturing from file
	int			invert_x;
};

//////////////////////////////////////////////////////////////////////////

#endif // __VA_OPENCV_H__
