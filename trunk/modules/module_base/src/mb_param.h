#ifndef __MB_PARAM_H__
#define __MB_PARAM_H__

//////////////////////////////////////////////////////////////////////////

/// mb_param::type

#define PT_UNDEFINED 0x00
#define PT_INT		 0x01
#define PT_LONG		 0x02
#define PT_FLOAT	 0x03
#define PT_DOUBLE	 0x04

//////////////////////////////////////////////////////////////////////////

struct mb_param
{
	int		type;
	void *	data;
	char *  name;
	char *  description;
};

//////////////////////////////////////////////////////////////////////////

template<typename T>
class mbParam
{
public:
	void assign( mb_param * prm );
	T & value();

private:
	mb_param * param;
	T val;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MB_PARAM_H__