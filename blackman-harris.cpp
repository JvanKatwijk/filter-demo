
#include	"blackman-harris.h"

		blackman_harris::blackman_harris (int degree, float f) {
int	i;
float	sum	= 0;

	filterKernel		= new float [degree];
	buffer			= new std::complex<float> [degree];
	this	-> degree	= degree;
	for (i = 0; i < degree; i ++) {
	   if (i == degree / 2)
	      filterKernel [i] = 2 * M_PI * f;
	   else
	      filterKernel [i] = sin (2 * M_PI * f * (i - degree / 2)) / (i - degree / 2);
//
//	windowing
	   filterKernel [i] *= 
	      0.35875  -
	      0.48829 * cos ((2 * M_PI * i) / (degree - 1)) +
	      0.14128 * cos ((4 * M_PI * i) / (degree - 1)) -
	      0.01168 * cos ((6 * M_PI * i) / (degree - 1));
	   sum += filterKernel [i];
	}

	for (i = 0; i < degree; i ++) {
	   filterKernel [i] /= sum;
	   buffer [i] = std::complex<float> (0, 0);
	}
	ip	= 0;
}

	blackman_harris::~blackman_harris (void) {
	delete[] filterKernel;
	delete[] buffer;
}

std::complex<float>	blackman_harris::Pass	(std::complex<float> z) {
int16_t i;
std::complex<float>      tmp     = 0;

        buffer [ip]     = z;
        for (i = 0; i < degree; i ++) {
           int16_t index = ip - i;
           if (index < 0)
              index += degree;
           tmp          +=
	         std::complex<float> (real (buffer [index]) * filterKernel [i],
	                              imag (buffer [index]) * filterKernel [i]);
        }

        ip = (ip + 1) % degree;
        return tmp;
}

