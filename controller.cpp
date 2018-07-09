
#include	"controller.h"
#include	"blackman.h"
#include	"hann.h"
#include	"hamming.h"
#include	"blackman-harris.h"
#include	"scope.h"
#include	<math.h>

	Controller::Controller (void) {
	setupUi (this);
	fprintf (stderr, "phase 1\n");
	scope_1	= new scope (amplitudeScope, 1024, 16);
	fprintf (stderr, "phase 2\n");
	scope_2	= new scope (phaseScope, 1024, 16);
	fprintf (stderr, "phase 3\n");
	connect (filterType, SIGNAL (activated (QString)),
                 this,  SLOT (set_filterType (QString)));
	connect (filterDepth, SIGNAL (valueChanged (int)),
	         this, SLOT (set_filterDepth (int)));
	connect (border, SIGNAL (valueChanged (int)),
	         this, SLOT (set_freq (int)));
	fprintf (stderr, "phase 4\n");
	my_fft	= new common_fft (1024);
}

	Controller::~Controller (void) {
	delete	scope_1;
	delete	scope_2;
}

void	Controller::set_filterType (QString fType) {
	createImage ();
}

void	Controller::set_filterDepth (int d) {
	createImage ();
}

void	Controller::set_freq (int v) {
	createImage ();
}

void	Controller::createImage () {
int	i;
filters	*the_filter;

	if (filterType -> currentText () == "blackman") {
           the_filter = new blackman (filterDepth -> value (),
                                      (float)(border -> value ()) / 200.0);
        }
	else
	if (filterType -> currentText () == "hann") {
	   the_filter = new hann (filterDepth -> value (),
	                          (float)(border -> value ()) / 200.0);
	}
	else
	if (filterType -> currentText () == "hamming") {
	   the_filter = new hamming (filterDepth -> value (),
	                          (float)(border -> value ()) / 200.0);
	}
	else
	if (filterType -> currentText () == "blackman_harris") {
	   the_filter = new blackman_harris (filterDepth -> value (),
	                          (float)(border -> value ()) / 200.0);
	}
	else
	   return;

	for (i = 0; i < 1024; i ++) 
	   my_fft -> fftVector [i] = std::complex<float>
	                           (i < filterDepth -> value () ?
	                            40000 * the_filter -> filterKernel [i]: 0, 0);

	my_fft -> do_FFT ();
	for (i = 0; i < 512; i ++) {
	   std::complex<float> x = my_fft -> fftVector [i];
	   my_fft -> fftVector [i] = my_fft -> fftVector [1024 - 512 + i];
	   my_fft -> fftVector [1024 - 512 + i] = x;
	}

	double amplitudes [1024];
	double phases     [1024];
	double	X_axis	  [1024];
	for (i = 0; i < 1024; i ++) {
	   amplitudes	[i] = abs (my_fft -> fftVector [i]);
	   phases	[i] = std::arg (my_fft -> fftVector [i]) + M_PI;
	   X_axis	[i] = (-512 + i) / 1024.0;
	}
	scope_1	-> View (X_axis, amplitudes, 100, 0);
	scope_2	-> View (X_axis, phases, 30, 0);
	delete the_filter;
}

