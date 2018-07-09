
#ifndef	__HANN__
#define	__HANN__

#include	"filters.h"

class	hann : public filters {
public:
		hann	(int degree, float border);
		~hann	(void);
std::complex<float>	Pass	(std::complex<float>);
private:
	int	degree;
	float	border;
	std::complex<float>	*buffer;
	int	ip;
};

#endif

