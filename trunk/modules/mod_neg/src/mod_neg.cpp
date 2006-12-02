#include "mod_neg.h"
#include "../../module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

modNeg::modNeg() : alloc_mem(0)
{
}

//////////////////////////////////////////////////////////////////////////

modNeg::~modNeg()
{

}

//////////////////////////////////////////////////////////////////////////

const char * modNeg::get_module_description()
{
	static char descritpion[] = "Negative module";
	return( descritpion );
}	
	

//////////////////////////////////////////////////////////////////////////

int modNeg::init()
{
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void modNeg::free()
{

}

//////////////////////////////////////////////////////////////////////////

int modNeg::get_module_type()
{
	return( MT_NONE );
}

//////////////////////////////////////////////////////////////////////////

int modNeg::input_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

int modNeg::output_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

proc_data * modNeg::process_frame( proc_data * prev_frame, int * result )
{
	static proc_data p_data = { 0, 0, 0 };
	static frame_data frame;

	frame.depth = 4;
	frame.width = prev_frame->frame->width;
	frame.height = prev_frame->frame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = frame.depth*frame.height*frame.width;
		frame.bits = new unsigned char[alloc_mem];
	}
	else
	{
		if( alloc_mem != frame.depth*frame.height*frame.width )
		{
			delete [] frame.bits;
			alloc_mem = frame.depth*frame.height*frame.width;
			frame.bits = new unsigned char[alloc_mem];
		}
	}

	for( int i=0; i<frame.width*frame.height*frame.depth; ++i )
	{
		frame.bits[i] = 255 - prev_frame->frame->bits[i];
	}

	*result = ST_OK;

	p_data.frame = &frame;

	return( &p_data );
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) moduleBase * export_module()
{
	return( new modNeg );
}

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////