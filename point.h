#ifndef POINT
#define POINT
#include <stdlib.h>
typedef struct Methods {
	void* (*add)(void*, void*);
	void* zero;
} Methods;
typedef struct Point {
	Methods* methods;
	void* x;
	void* y;
	void* z;
} Point;
void SetType(Point* x, void* (*add)(void*, void*), void* zero) {
	x->methods = (Methods*)malloc(sizeof(Methods));
	x->methods->add = add;
	x->methods->zero = zero;
}
void SetPoint(Point* a, void* x, void* y, void* z) {
	a->x = x;
	a->y = y;
	a->z = z;
}
void* GetX(Point* a) {
	return a->x;
}
void* GetY(Point* a) {
	return a->y;
}
void* GetZ(Point* a) {
	return a->z;
}
Methods* Int;
void* int_add(void* a, void* b) {
	int* c = (int*)malloc(sizeof(int));
	*c = *(int*)a + *(int*)b;
	return c;
}
Point* add(Point* a, Point* b) {
	if (a->methods->add != b->methods->add) return NULL;
	else {
		Point* c = (Point*)malloc(sizeof(Point));
		SetType(c, a->methods->add, a->methods->zero);
		SetPoint(c, c->methods->add(a->x, b->x), c->methods->add(a->y, b->y), c->methods->add(a->z, b->z));
		return c;
	}
}
int* int_zero;
*int_zero = 0;
#endif