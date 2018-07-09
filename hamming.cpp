
#include	"hamming.h"

		hamming::hamming (int degree, float f) {
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
	               0.54 - 0.46 * cos ((2 * M_PI * i) / (degree - 1));
	   sum += filterKernel [i];
	}

	for (i = 0; i < degree; i ++) {
	   filterKernel [i] /= sum;
	   buffer [i] = std::complex<float> (0, 0);
	}
	ip	= 0;
}

	hamming::~hamming	(void) {
	delete[] filterKernel;
	delete[] buffer;
}

std::complex<float>	hamming::Pass	(std::complex<float> z) {
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

