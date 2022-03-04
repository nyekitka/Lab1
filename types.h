#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h>
#include <stdio.h>
#include "complex.h"
typedef struct TypeInfo {
	size_t size;
	void* (*add) (void*, void*);
	void* (*mult) (void*, void*);
	int (*input) (void*);
	void (*print) (void*);
	void* (*negative) (void*);
	void* zero;
} TypeInfo;
void create_type(TypeInfo* type, size_t size, int (*input) (void*), void* (*add)(void*, void*), void* (*mult)(void*, void*), void (*print) (void*), void* (*negative) (void*), void* zero) {
	type->size = size;
	type->print = print;
	type->add = add;
	type->mult = mult;
	type->negative = negative;
	type->input = input;
	type->zero = zero;
}
//double numbers
void* double_negative(void* a) {
	double* b = (double*)malloc(sizeof(double));
	*b = -(*(double*)a);
	return (void*)b;
}
void* double_add(void* a, void* b) {
	double* c = (double*)malloc(sizeof(double));
	*c = (*(double*)a) + (*(double*)b);
	return (void*)c;
}
void* double_mult(void* a, void* b) {
	double* c = (double*)malloc(sizeof(double));
	*c = (*(double*)a) * (*(double*)b);
	return (void*)c;
}
void print_double(void* a) {
	printf("%g", *(double *)a);
}
int input_double(void* a) {
	return scanf("%lf", (double*)a);
}
//complex numbers
void* complex_negative(void* a) {
	complex* b = (complex*)malloc(sizeof(complex));
	b->re = -((complex*)a)->re;
	b->im = -((complex*)a)->im;
	return (void*)b;
}
void* complex_add(void* a, void* b) {
	complex* c = (complex*)malloc(sizeof(complex));
	c->im = ((complex*)a)->im + ((complex*)b)->im;
	c->re = ((complex*)a)->re + ((complex*)b)->re;
	return (void*)c;
}
void* complex_mult(void* a, void* b) {
	complex* c = (complex*)malloc(sizeof(complex));
	c->im = ((complex*)a)->im * ((complex*)b)->re + ((complex*)b)->im * ((complex*)a)->re;
	c->re = ((complex*)a)->re * ((complex*)b)->re - ((complex*)a)->im*((complex*)b)->im;
	return (void*)c;
}
void print_complex(void* a) {
	complex t = *(complex*)a;
	if (t.re != 0) {
		printf("%g", t.re);
		if (t.im > 0) printf("+ %g*i", t.im);
		else if (t.im < 0) printf("- %g*i", -t.im);
	}
	else {
		if (t.im != 0) printf("%g*i", t.im);
		else printf("0");
	}
}
int input_complex(void* a) {
	char c;
	if (scanf("%lf%lf%c", &(((complex*)a)->re), &(((complex*)a)->im), &c) != 3 || c != 'i') {
		while (getchar() != '\n') {}
		return 0;
	}
	return 1;
}

////////concatenation///////////
void* char_conc(void* a, void* b) {
	char* c = (char*)malloc(sizeof(char) * 2);
	c[0] = *(char*)a;
	c[1] = *(char*)b;
	return (void*)c;
}
////////////////////////////////////
#endif 

