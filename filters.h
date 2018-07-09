
#ifndef	__FILTERS__
#define	__FILTERS__

#include	<complex>

class	filters {
public:
		filters		(void);
virtual		~filters 	(void);
virtual	std::complex<float>	Pass (std::complex<float>);
	float	*filterKernel;
};

#endif


