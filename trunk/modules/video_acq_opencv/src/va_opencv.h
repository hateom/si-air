#ifndef __VA_OPENCV_H__
#define __VA_OPENCV_H__

//////////////////////////////////////////////////////////////////////////

#include "../../video_acq_base/src/va_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy
struct CvCapture;

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) vaOpenCV: public vaBase
{
public:
	vaOpenCV();
	virtual ~vaOpenCV();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual int init( int device, char * filename = 0 );
	virtual void free();

//	virtual frame_data * process_frame( int * result );
	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

protected:
//	int cam_count;
	CvCapture * capture;
	int alloc_mem;

	int		param1;
	float	param2;
	long	hwnd;
};

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej bez wiklania nazw DLL

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

/// funkcja exportujaca modul z biblioteki	
/// \return wskaznik do obiektu modulu
__declspec(dllexport) vaOpenCV * export_module(); 
												  

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////

#endif // __VA_OPENCV_H__
