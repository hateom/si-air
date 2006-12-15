#ifndef __OPT_FORM_H__
#define __OPT_FORM_H__

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class QTextEdit;
class QGroupBox;

//////////////////////////////////////////////////////////////////////////

class OptForm : public QDialog
{
	Q_OBJECT

public:
	OptForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0, moduleBase * mod = NULL );
	~OptForm();

	QGroupBox * groupBox;

protected slots:
	virtual void save_conf();
	virtual void languageChange();

private:
	moduleBase * module;
	std::vector<QWidget*> wdg_list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __OPT_FORM_H__