#ifndef COMPLEX_H
#define COMPLEX_H
typedef struct complex {
	double re, im;
} complex;
void set(complex* a, double real, double imaginary) {
	a->re = real;
	a->im = imaginary;
}

#endif
