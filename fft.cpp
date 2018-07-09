#
/*
 *    Copyright (C) 2008, 2009, 2010
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair programming
 *
 *    This file is part of the SDR-J (JSDR).
 *    Many of the ideas as implemented in JSDR are derived from
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
 *
 */
#include "fft.h"
/*
 */
	common_fft::common_fft (int32_t fft_size) {
int32_t	i;

	if ((fft_size & (fft_size - 1)) == 0)
	   this	-> fft_size = fft_size;
	else
	   this -> fft_size = 4096;	/* just a default	*/

	fftVector = (std::complex<float> *)
	       FFTW_MALLOC (sizeof (std::complex<float> *) * fft_size);
	plan	= FFTW_PLAN_DFT_1D (fft_size,
	                        reinterpret_cast <fftwf_complex *>(fftVector),
	                        reinterpret_cast <fftwf_complex *>(fftVector),
	                            FFTW_FORWARD, FFTW_ESTIMATE);
}

	common_fft::~common_fft () {
	   FFTW_DESTROY_PLAN (plan);
	   FFTW_FREE (fftVector);
}

void	common_fft::do_FFT () {
	FFTW_EXECUTE (plan);
}
