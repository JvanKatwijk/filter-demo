
#ifndef	__HAMMING__
#define	__HAMMING__

#include	"filters.h"

class	hamming : public filters {
public:
		hamming	(int degree, float border);
		~hamming	(void);
std::complex<float>	Pass	(std::complex<float>);
private:
	int	degree;
	float	border;
	std::complex<float>	*buffer;
	int	ip;
};

#endif

