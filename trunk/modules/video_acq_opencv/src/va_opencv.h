#ifndef __VA_OPENCV_H__
#define __VA_OPENCV_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy
struct CvCapture;

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) vaOpenCV: public moduleBase
{
public:
	vaOpenCV();
	virtual ~vaOpenCV();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual int init();
	virtual void free();

//	virtual void mouse_select(int sx, int sy, int sw, int sh );

//	virtual frame_data * process_frame( int * result );
	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

protected:
//	int cam_count;
	CvCapture * capture;
	int alloc_mem;

	int		device;		// device num parameter
	char *	filename;	// when capturing from file
};

//////////////////////////////////////////////////////////////////////////

#endif // __VA_OPENCV_H__
