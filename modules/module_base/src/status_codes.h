/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	status_codes
	autorzy:	Tomasz Huczek, Andrzej Jasi�ski
	
    cel:	    
*********************************************************************/

#ifndef __STATUS_CODES_H__
#define __STATUS_CODES_H__
	
//////////////////////////////////////////////////////////////////////////

#define ST_OK				0x00
#define ST_ALLOC_ERROR		0x01
#define ST_OPEN_ERROR		0x02
#define ST_WRITE_ERROR		0x03

#define ST_DEVICE_NOT_FOUND	0x04
#define ST_FRAME_ERROR		0x05
#define ST_ALREADY_EXISTS	0x06

#define ST_MISSING_DLL		0x07
#define ST_UNKNOWN_MODULE	0x08
#define ST_EXPORT_ERROR		0x09
#define ST_OUT_OF_RANGE		0x0A
#define ST_WINDOW_CLOSED	0x0B

#define ST_UNDEFINED		0xFF

//////////////////////////////////////////////////////////////////////////

#endif //__STATUS_CODES_H__
