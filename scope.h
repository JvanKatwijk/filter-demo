
#ifndef	__SCOPE__
#define	__SCOPE__

#include	<stdint.h>
#include        <qwt.h>
#include        <qwt_plot.h>
#include        <qwt_plot_marker.h>
#include        <qwt_plot_grid.h>
#include        <qwt_plot_curve.h>
#include        <qwt_plot_marker.h>

class	scope {
public:
		scope	(QwtPlot *, uint16_t, int16_t);
		~scope	(void);
	void	View	(double *, double *, double, int32_t);
private:
float	get_db	(float);

	QwtPlot	*plotgrid;
	int	DisplaySize;
	int	normalizer;
	QwtPlotGrid	*grid;
	QwtPlotCurve	*SpectrumCurve;
	QBrush		*ourBrush;
	QwtPlotMarker	*Marker;
};

#endif

