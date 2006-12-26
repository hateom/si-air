#define MOD_CPP
#include "mod_light.h"
#include "../../module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

#define MIN( A, B ) (A)<(B)?(A):(B)

//////////////////////////////////////////////////////////////////////////

modLight::modLight() : alloc_mem(0L)
{
	REG_PARAM( PT_FLOAT_RANGE, factor, "Lighting factor (1.0f = neutral)", float_range( 1.0f, 0.1f, 10.0f ) );
}

//////////////////////////////////////////////////////////////////////////

modLight::~modLight()
{
}

//////////////////////////////////////////////////////////////////////////

const char * modLight::get_module_description()
{
	static char descritpion[] = "Lighting module";
	return( descritpion );
}	
	

//////////////////////////////////////////////////////////////////////////

int modLight::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void modLight::free()
{
}

//////////////////////////////////////////////////////////////////////////

int modLight::input_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

int modLight::output_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

proc_data * modLight::process_frame( proc_data * prev_frame, int * result )
{
	static proc_data p_data = { 0, 0, 0, 0 };
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

	for( int i=0; i<(int)(frame.width*frame.height*frame.depth); ++i )
	{
		frame.bits[i] = (unsigned char)(MIN( ((float)prev_frame->frame->bits[i]*factor), 255.0f ));
	}

	*result = ST_OK;

	p_data.input_frame = prev_frame->input_frame;
	p_data.frame = &frame;

	return( &p_data );
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

extern "C" {

__declspec(dllexport) moduleBase * export_module()
{
	return( new modLight );
}

};

//////////////////////////////////////////////////////////////////////////