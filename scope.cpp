#
/*
 *    Copyright (C)  2012, 2013, 2014
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the SDR-J.
 *    Many of the ideas as implemented in SDR-J are derived from
 *    other work, made available through the GNU general Public License. 
 *    All copyrights of the original authors are recognized.
 *
 *    SDR-J is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SDR-J is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SDR-J; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include	"scope.h"

	scope::scope (QwtPlot *plot,
	              uint16_t displaysize, int16_t d) {
	plotgrid		= plot;
	this	-> DisplaySize	= displaysize;
	plotgrid-> setCanvasBackground (Qt::blue);
	grid	= new QwtPlotGrid;
#if defined QWT_VERSION && ((QWT_VERSION >> 8) < 0x0601)
	grid	-> setMajPen (QPen(Qt::white, 0, Qt::DotLine));
#else
	grid	-> setMajorPen (QPen(Qt::white, 0, Qt::DotLine));
#endif
	grid	-> enableXMin (true);
	grid	-> enableYMin (true);
#if defined QWT_VERSION && ((QWT_VERSION >> 8) < 0x0601)
	grid	-> setMinPen (QPen(Qt::white, 0, Qt::DotLine));
#else
	grid	-> setMinorPen (QPen(Qt::white, 0, Qt::DotLine));
#endif
	grid	-> attach (plotgrid);

	SpectrumCurve	= new QwtPlotCurve ("");
   	SpectrumCurve	-> setPen (QPen(Qt::white));
//	SpectrumCurve	-> setStyle	(QwtPlotCurve::Sticks);
	SpectrumCurve	-> setOrientation (Qt::Horizontal);
	SpectrumCurve	-> setBaseline	(get_db (0));
	ourBrush	= new QBrush (Qt::white);
	ourBrush	-> setStyle (Qt::Dense3Pattern);
	SpectrumCurve	-> setBrush (*ourBrush);
	SpectrumCurve	-> attach (plotgrid);
	
	Marker		= new QwtPlotMarker ();
	Marker		-> setLineStyle (QwtPlotMarker::VLine);
	Marker		-> setLinePen (QPen (Qt::red));
	Marker		-> attach (plotgrid);
	plotgrid	-> enableAxis (QwtPlot::yLeft);
	if (d < 0 || d > 32)
	   d = 24;

	normalizer	= 1;
	while (-- d >= 0) 
	   normalizer <<= 1;

}

	scope::~scope (void) {
	plotgrid	-> enableAxis (QwtPlot::yLeft, false);
	Marker		-> detach ();
	SpectrumCurve	-> detach ();
	grid		-> detach ();
	delete		Marker;
	delete		SpectrumCurve;
	delete		grid;
}

float	scope::get_db (float x) {
	return 20 * log10 ((x + 1) / (float)(normalizer));
}

void	scope::View (double *X_axis,
		     double *Y1_value,
	             double amp,
	             int32_t marker) {
uint16_t	i;

	amp		= amp / 100 * (-get_db (0));
	plotgrid	-> setAxisScale (QwtPlot::xBottom,
				         (double)X_axis [0],
				         X_axis [DisplaySize - 1]);
	plotgrid	-> enableAxis (QwtPlot::xBottom);
	plotgrid	-> setAxisScale (QwtPlot::yLeft,
				         get_db (0), get_db (0) + amp);

	for (i = 0; i < DisplaySize; i ++) 
	   Y1_value [i] = get_db (Y1_value [i]); 

	SpectrumCurve	-> setBaseline (get_db (0));
	Y1_value [0]	= get_db (0);
	Y1_value [DisplaySize - 1] = get_db (0);

	SpectrumCurve	-> setSamples (X_axis, Y1_value, DisplaySize);
	Marker		-> setXValue (marker);
	plotgrid	-> replot(); 
}

