#ifndef MATRIX_H
#define MATRIX_H
#include "types.h"
#include <string.h>
typedef struct Matrix {
	TypeInfo* type;
	void* matrix;
	size_t columns;
	size_t rows;
} Matrix;
void set_type(Matrix* m, TypeInfo* type) {
	m->type = type;
}
void input(Matrix* m, size_t rows, size_t columns) {
	size_t size_of = m->type->size;
	m->rows = rows;
	m->columns = columns;
	m->matrix = malloc(rows * columns * size_of);
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			while (m->type->input((void*)((size_t)m->matrix + (i * columns + j) * m->type->size)) != 1) {
				printf("Incorrect entry of complex number in %d row %d column.\n Enter all elements starting from this again:\n", i + 1, j + 1);
			}
		}
	}
}
void init(Matrix* m, size_t rows, size_t columns, void* data) {
	size_t size_of = m->type->size;
	m->rows = rows;
	m->columns = columns;
	m->matrix = (void*)malloc(rows*columns*size_of);
	memcpy(m->matrix, data, rows * columns * size_of);
}
size_t rows(Matrix a) {
	return a.rows;
}
size_t columns(Matrix a) {
	return a.columns;
}
int isempty(Matrix a) {
	return a.rows == 0 || a.columns == 0;
}
void del(Matrix* m) {
	free(m->matrix);
	m->rows = 0;
	m->columns = 0;
}
Matrix negative(Matrix* a) {
	Matrix b;
	b.rows = a->rows;
	b.columns = a->columns;
	set_type(&b, a->type);
	b.matrix = malloc(b.type->size * b.rows * b.columns);
	for (size_t i = 0; i < b.rows; i++) {
		for (size_t j = 0; j < b.columns; j++) {
			void* t = a->type->negative((void*)((size_t)a->matrix + a->type->size * (i * a->columns + j)));
			memcpy((void*)((size_t)b.matrix + b.type->size * (i * b.columns + j)), t, b.type->size);
		}
	}
	return b;
}
Matrix add(Matrix* a, Matrix* b) {
	if (a->rows != b->rows || a->columns != b->columns || a->type->add != b->type->add) {
		Matrix empty;
		empty.rows = 0;
		return empty;
	}
	else {
		Matrix c;
		size_t size_of = a->type->size;
		c.columns = a->columns;
		c.rows = a->rows;
		set_type(&c, a->type);
		void* matr = malloc(c.rows * c.columns * size_of);
		for (size_t i = 0; i < c.rows; i++) {
			for (size_t j = 0; j < c.columns; j++) {
				void* t = c.type->add((void*)((size_t)a->matrix + i * size_of * a->columns + j * size_of), (void*)((size_t)b->matrix + i * size_of * b->columns + j * size_of));
				memcpy((void*)((size_t)matr + i * size_of * c.columns + j * size_of), t, size_of);
				free(t);
			}
		}
		c.matrix = matr;
		return c;
	}
}
Matrix mult(Matrix* a, Matrix* b) {
	if (a->columns != b->rows || a->type->add != b->type->add || a->type->mult != b->type->mult) {
		Matrix empty;
		empty.rows = 0;
		return empty;
	}
	else {
		Matrix c;
		c.rows = a->rows;
		c.columns = b->columns;
		set_type(&c, a->type);
		void* matr = malloc(c.rows * c.columns * c.type->size);
		for (size_t i = 0; i < c.rows; i++) {
			for (size_t j = 0; j < c.columns; j++) {
				void* sum = c.type->zero;
				for (size_t k = 0; k < a->columns; k++) {
					void* t = c.type->mult((void*)((size_t)a->matrix + i * a->type->size * a->columns + k * a->type->size), (void*)((size_t)b->matrix + k * b->type->size * b->columns + j * b->type->size));
					void* u = c.type->add(t, sum);
					if (k) free(sum);
					sum = u;
					free(t);
				}
				memcpy((void*)((size_t)matr + i * c.columns * c.type->size + j * c.type->size), sum, c.type->size);
				free(sum);
			}
		}
		c.matrix = matr;
		return c; 
	}
}
Matrix transpose(Matrix a) {
	Matrix b;
	b.matrix = malloc(a.rows * a.columns * a.type->size);
	set_type(&b, a.type);
	b.rows = a.columns;
	b.columns = a.rows;
	for (size_t i = 0; i < a.rows; i++) {
		for (size_t j = 0; j < a.columns; j++) {
			memcpy((void*)((size_t)b.matrix + (j*b.columns + i)*b.type->size), (void*)((size_t)a.matrix + (i * a.columns + j) * a.type->size), a.type->size);
		}
	}
	return b;
}
void print(Matrix a) {
	for (size_t i = 0; i < a.rows; i++) {
		for (size_t j = 0; j < a.columns; j++) {
			a.type->print((void*)((size_t)a.matrix + i * a.columns * a.type->size + j * a.type->size));
			printf("\t");
		}
		printf("\n");
	}
}
#endif
