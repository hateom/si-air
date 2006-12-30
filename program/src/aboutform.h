/****************************************************************************
** Form interface generated from reading ui file 'aboutform.ui'
**
** Created: So 30. gru 21:36:54 2006
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ABOUTFORM_H
#define ABOUTFORM_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;

class AboutForm : public QDialog
{
    Q_OBJECT

public:
    AboutForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AboutForm();

    QLabel* pixmapLabel2;

protected:

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // ABOUTFORM_H
