
#ifndef	__BLACKMAN__
#define	__BLACKMAN__

#include	"filters.h"

class	blackman : public filters {
public:
		blackman	(int degree, float border);
		~blackman	(void);
std::complex<float>	Pass	(std::complex<float>);
private:
	int	degree;
	float	border;
	std::complex<float>	*buffer;
	int	ip;
};

#endif

