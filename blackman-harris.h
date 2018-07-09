
#ifndef	__BLACKMAC_HARRIS__
#define	__BLACKMAN_HARRIS__

#include	"filters.h"

class	blackman_harris : public filters {
public:
		blackman_harris	(int degree, float border);
		~blackman_harris	(void);
std::complex<float>	Pass	(std::complex<float>);
private:
	int	degree;
	float	border;
	std::complex<float>	*buffer;
	int	ip;
};

#endif

