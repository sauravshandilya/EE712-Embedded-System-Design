/*
 * coeff.h
 *
 *  Created on: 01-May-2016
 *      Author: saurav
 */

#ifndef COEFF_H_
#define COEFF_H_

//low pass for 30
///*
#define lp30_R0 8600
#define lp30_R1 8000
#define lp30_R2 7780
#define lp30_R3 7640
#define lp30_R4 7640
#define lp30_R5 7780
#define lp30_R6 8000
#define lp30_R7 8600
//*/



//65:
#define lp65_R0 11673
#define lp65_R1 8511
#define lp65_R2 7051
#define lp65_R3 6451
#define lp65_R4 6451
#define lp65_R5 7051
#define lp65_R6 8511
#define lp65_R7 11673

//100:
#define lp100_R0 34026
#define lp100_R1 10067
#define lp100_R2 6040
#define lp100_R3 4861
#define lp100_R4 4861
#define lp100_R5 6040
#define lp100_R6 10067
#define lp100_R7 34026


// low pass filter coeffs.
/*#define R0 34026
#define R1 10067
#define R2 6040
#define R3 4861
#define R4 4861
#define R5 6040
#define R6 10067
#define R7 34026

*/



/* band pass filter coeffs. fc: 40-120khz
#define R0 27424
#define R1 5620
#define R2 5112
#define R3 3443
#define R4 3443
#define R5 5112
#define R6 5620
#define R7 27424
*/

//band pass filter coeffs. fc: 20-60khz
/*#define R0 56387
#define R1 4858
#define R2 6229
#define R3 3431
#define R4 3431
#define R5 6229
#define R6 4858
#define R7 56387
*/

/*
//high pass filter coeffs. fc: 40khz
#define R0 12169
#define R1 17005
#define R2 16509
#define R3 1861
#define R4 1861
#define R5 16509
#define R6 17005
#define R7 12169
*/




/*
#define R0 4836
#define R1 25254
#define R2 37939
#define R3 45983
#define R4 48755
#define R5 45983
#define R6 37939
#define R7 25254
*/

/*
#define R0 10743
#define R1 1434
#define R2 850
#define R3 750
#define R4 974
#define R5 2651
#define R6 7861
#define R7 65443
*/

/*
#define R0 1282
#define R1 1894
#define R2 2163
#define R3 1433
#define R4 5420
#define R5 1355
#define R6 5165
#define R7 7811
*/

#define amp 5000

uint32_t filter_coeff [8][8] = {
		{4836,25254,37939,45983,48755,45983,37939,25254},			//low pass
		{10743,1434,850,750,974,2651,7861,65443},					// BP 101-201
		{1282, 1894, 2163, 1433, 5420, 1355, 5165, 7811}			//BP 301-401

};

#endif /* COEFF_H_ */
