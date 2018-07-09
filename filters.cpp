
#include	"filters.h"

	filters::filters	(void) {}
	filters::~filters 	(void) {}
std::complex<float>
	filters::Pass		(std::complex<float> x) {
	return x;
}



