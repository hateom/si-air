#ifndef __VIDEO_ACQ_BASE_H__
#define __VIDEO_ACQ_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////
/*
struct frame_data
{
	unsigned int  width;
	unsigned int  height;
	unsigned int  depth;
	unsigned char * bits;
};
*/
/// klasa bazowa dla modulow akwizycji wideo
class __declspec(dllexport) vaBase: public moduleBase
{
public:
	vaBase() {}
	virtual ~vaBase() {}

	/// metoda inicjalizujaca
	/// \return kod bledu, lub 0 w przypadku powodzenia
	/// \param device video device number (if filename is null)
	/// \param filename video file 
	virtual int  init( int device, char * filename = 0 ) = 0;

	/// przesyla jedna klatke z pliku video, badz z urzadzenia video
	/// \param result 0 gdy wszystko ok, wartoœæ ujemna w przypadku b³êdu
	/// \return zunifikowana ramka obrazu
	//virtual frame_data * process_frame( int * result ) = 0;

	/// metoda zwalniajaca zasoby
	virtual void free() = 0;
protected:
};

//////////////////////////////////////////////////////////////////////////

#endif // __VIDEO_ACQ_BASE_H__
