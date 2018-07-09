
#ifndef	__CONTROLLER__
#define	__CONTROLLER__
#include        <QDialog>
#include        <QStringList>
#include        <QComboBox>
#include        <QLabel>
#include        <QTimer>
#include        <sndfile.h>
#include        "ui_filter-demo.h"
#include	"fft.h"

class	filters;
class	scope;

class	Controller: public QDialog, private Ui_filterdemo {
Q_OBJECT
public:
		Controller	(void);
		~Controller	(void);
private:
	common_fft	*my_fft;
	scope	*scope_1;
	scope	*scope_2;

void	createImage	(void);

public slots:
void	set_filterType		(QString);
void	set_filterDepth		(int);
void	set_freq		(int);
};

#endif




