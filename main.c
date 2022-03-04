#include "matrix.h"
#include "menu.h"
#include <stdio.h>
void enter_int(int* a) {
	while (scanf("%d", a) == 0 || *a <= 0) {
		while (getchar() != '\n') {}
		printf("You've posted the cringe. Enter normally: ");
	}
	while (getchar() != '\n') {}
}

int main() {
	
	TypeInfo double_type, complex_type;
	double dzero = 0;
	complex czero;
	set(&czero, 0, 0);
	create_type(&double_type, sizeof(double), input_double, double_add, double_mult, print_double, double_negative, &dzero);
	create_type(&complex_type, sizeof(complex), input_complex, complex_add, complex_mult, print_complex, complex_negative, &czero);

	Matrix* array = NULL;
	char* ans = NULL;
	size_t status = start_menu(1), size = 0;
	while (status) {
		if (status == 1 || status == 2) { //input
			printf("How many matrices do you wanna enter: ");
			int number_of_matrices = 0;
			enter_int(&number_of_matrices);
			if (status == 1) array = (Matrix*)realloc(array, sizeof(Matrix) * (number_of_matrices + size));
			else {
				for (int i = 0; i < size; i++) del(&array[i]);
				free(array);
				array = (Matrix*)malloc(sizeof(Matrix) * number_of_matrices);
			}
			for (int i = 0; i < number_of_matrices; i++) {
				printf("%d matrix\nEnter the number of rows: ", i + 1);
				int rows, columns;
				enter_int(&rows);
				printf("Enter the number of columns: ");
				enter_int(&columns);
				int type;
				printf("Enter the type of numbers in your matrix:\n1) Real\n2) Complex\nYour choice: ");
				enter_int(&type);
				while (type > 2) {
					printf("You posted the cringe. Enter normally: ");
					enter_int(&type);
				}
				Matrix temp;
				if (type == 1) set_type(&temp, &double_type);
				else set_type(&temp, &complex_type);
				input(&temp, rows, columns);
				if (status == 1) array[i + size] = temp;
				else array[i] = temp;
			}
			if (status == 1) size += number_of_matrices;
			else size = number_of_matrices;
			while (getchar() != '\n') {}
		}
		else if (status == 3) { //output
			for (size_t i = 0; i < size; i++) {
				printf("%d matrix: %d rows, %d columns\n", i + 1, rows(array[i]), columns(array[i]));
				print(array[i]);
				printf("\n");
			}
		}
		else if (status == 4) { //addition
			printf("Matrices under which number should I add up?\nNumber of first matrix: ");
			int first_ind, second_ind;
			enter_int(&first_ind);
			while (first_ind <= 0 || first_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&first_ind);
			}
			printf("Number of second matrix: ");
			enter_int(&second_ind);
			while (second_ind <= 0 || second_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&second_ind);
			}
			Matrix res = add(array + first_ind - 1, array + second_ind - 1);
			if (isempty(res)) {
				printf("The addition of these matrices is impossible\n");
			}
			else {
				printf("Result of the addition is:\n");
				print(res);
				ans = readline("\nShould i save it?\nAnswer: ");
				for (size_t i = 0; i < strlen(ans); i++) {
					ans[i] = ans[i] | 32;
				}
				while (strcmp(ans, "yes") != 0 && strcmp(ans, "yep") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "nope") != 0 && strcmp(ans, "nah") != 0) {
					free(ans);
					ans = readline("I'll assume that I didn't hear it. Enter normally: ");
					for (size_t i = 0; i < strlen(ans); i++) {
						ans[i] = ans[i] | 32;
					}
				}
				if (strcmp(ans, "yes") == 0 || strcmp(ans, "yep") == 0) {
					free(ans);
					size++;
					array = (Matrix*)realloc(array, size * sizeof(Matrix));
					array[size - 1] = res;
					printf("Done! The result is under %d index now\n", size);
				}
				else {
					free(ans);
					printf("As you say.\n");
					del(&res);
				}
			}
		}
		else if (status == 5) {//subtraction
			printf("From which matrix should I subtract which one?\nNumber of first matrix: ");
			int first_ind, second_ind;
			enter_int(&first_ind);
			while (first_ind <= 0 || first_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&first_ind);
			}
			printf("Number of second matrix: ");
			enter_int(&second_ind);
			while (second_ind <= 0 || second_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&second_ind);
			}
			Matrix neg = negative(array + second_ind - 1);
			Matrix res = add(array + first_ind - 1, &neg);
			del(&neg);
			if (isempty(res)) {
				printf("The subtraction of these matrices is impossible\n");
			}
			else {
				printf("Result of the subtraction is:\n");
				print(res);
				ans = readline("\nShould i save it?\nAnswer: ");
				for (size_t i = 0; i < strlen(ans); i++) {
					ans[i] = ans[i] | 32;
				}
				while (strcmp(ans, "yes") != 0 && strcmp(ans, "yep") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "nope") != 0 && strcmp(ans, "nah") != 0) {
					free(ans);
					ans = readline("I'll assume that I didn't hear it. Enter normally: ");
					for (size_t i = 0; i < strlen(ans); i++) {
						ans[i] = ans[i] | 32;
					}
				}
				if (strcmp(ans, "yes") == 0 || strcmp(ans, "yep") == 0) {
					free(ans);
					size++;
					array = (Matrix*)realloc(array, size * sizeof(Matrix));
					array[size - 1] = res;
					printf("Done! The result is under %d index now\n", size);
				}
				else {
					free(ans);
					printf("As you say.\n");
					del(&res);
				}
			}
		}
		else if (status == 6) { //matrix multiplication
			printf("which matrices should I multiply?\nNumber of first matrix: ");
			int first_ind, second_ind;
			enter_int(&first_ind);
			while (first_ind <= 0 || first_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&first_ind);
			}
			printf("Number of second matrix: ");
			enter_int(&second_ind);
			while (second_ind <= 0 || second_ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&second_ind);
			}
			Matrix res = mult(array + first_ind - 1, array + second_ind - 1);
			if (isempty(res)) {
				printf("The multiplication of these matrices is impossible\n");
			}
			else {
				printf("Result of the multiplication is:\n");
				print(res);
				ans = readline("\nShould i save it?\nAnswer: ");
				for (size_t i = 0; i < strlen(ans); i++) {
					ans[i] = ans[i] | 32;
				}
				while (strcmp(ans, "yes") != 0 && strcmp(ans, "yep") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "nope") != 0 && strcmp(ans, "nah") != 0) {
					free(ans);
					ans = readline("I'll assume that I didn't hear it. Enter normally: ");
					for (size_t i = 0; i < strlen(ans); i++) {
						ans[i] = ans[i] | 32;
					}
				}
				if (strcmp(ans, "yes") == 0 || strcmp(ans, "yep") == 0) {
					size++;
					array = (Matrix*)realloc(array, size * sizeof(Matrix));
					array[size - 1] = res;
					printf("Done! The result is under %d index now\n", size);
					free(ans);
				}
				else {
					free(ans);
					printf("As you say.\n");
					del(&res);
				}
			}
		}
		else {
			printf("Which matrix should I transpose?\nNumber of the matrix: ");
			int ind;
			enter_int(&ind);
			while (ind <= 0 || ind > size) {
				printf("There is no matrix under such an index\nEnter again: ");
				enter_int(&ind);
			}
			Matrix res = transpose(array[ind - 1]);
			printf("Result of the transposition is:\n");
			print(res);
			ans = readline("\nShould i save it?\nAnswer: ");
			for (size_t i = 0; i < strlen(ans); i++) {
				ans[i] = ans[i] | 32;
			}
			while (strcmp(ans, "yes") != 0 && strcmp(ans, "yep") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "no") != 0 && strcmp(ans, "nope") != 0 && strcmp(ans, "nah") != 0) {
				free(ans);
				ans = readline("I'll assume that I didn't hear it. Enter normally: ");
				for (size_t i = 0; i < strlen(ans); i++) {
					ans[i] = ans[i] | 32;
				}
			}
			if (strcmp(ans, "yes") == 0 || strcmp(ans, "yep") == 0) {
				free(ans);
				size++;
				array = (Matrix*)realloc(array, size * sizeof(Matrix));
				array[size - 1] = res;
				printf("Done! The result is under %d index now\n", size);
			}
			else {
				free(ans);
				printf("As you say.\n");
				del(&res);
			}
		}
		
		status = start_menu(0);
	}
	for (size_t i = 0; i < size; i++) del(array + i);
	free(array);
	return 0;
}