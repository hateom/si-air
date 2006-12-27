#ifndef __OPTIONS_BOX_H__
#define __OPTIONS_BOX_H__

//////////////////////////////////////////////////////////////////////////

#include <qgroupbox.h>
#include <qscrollview.h>
#include "optform.h"

//////////////////////////////////////////////////////////////////////////

class OptionsBox: public QScrollView
{
public:
	OptionsBox( QWidget* parent=0, const char* name=0 );
	~OptionsBox();

	void remove_last_cfg_form();
	void set_current_cfg_form( OptForm * of );

private:
	OptForm * last;
};

//////////////////////////////////////////////////////////////////////////

#endif // __OPTIONS_BOX_H__
