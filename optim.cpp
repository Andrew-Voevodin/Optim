
#include <iostream>
#include <random>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <dvec.h>
#include "omp.h"

#define LENGTH 100000000
//#define LENGTH 20

typedef struct {
	long len;
	double *data;
} my_vector;

long my_vector_len(my_vector *v) {
	return v->len;
}

void foo_bar(my_vector *v, double *res)
{
	long i;
	*res = 1;
	for (i = 0; i < my_vector_len(v); i++) {
		*res *= v->data[i];
	}
}

void foo_bar1(my_vector *v, double *res)
{
	long i, len = my_vector_len(v);
	*res = 1;
	for (i = 0; i < len; i++) {
		*res *= v->data[i];
	}
}

void foo_bar2(my_vector *v, double *res)
{
	long i, len = my_vector_len(v);
	double op = 1;
	for (i = 0; i < len; i++) {
		op *= v->data[i];
	}

	*res = op;
}

void foo_bar3_1(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v)-1;
	long len = my_vector_len(v);
	double op = 1;
	for (i = 0; i < lim; i+=2) {
		op = op * v->data[i] * v->data[i+1];
	}

	if (i < len) op *= v->data[i];

	*res = op;
}

void foo_bar3_2(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 1;
	long len = my_vector_len(v);
	double op = 1;
	for (i = 0; i < lim; i += 2) {
		op = op * (v->data[i] * v->data[i + 1]);
	}

	if (i < len) op *= v->data[i];

	*res = op;
}

void foo_bar3_3(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 2;
	long len = my_vector_len(v);
	double op = 1;
	for (i = 0; i < lim; i += 3) {
		op = op * ((v->data[i] * v->data[i + 1])*v->data[i + 2]);
	}

	if (i < len) op *= v->data[i];

	*res = op;
}

void foo_bar4_1(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 1;
	long len = my_vector_len(v);
	
	double op0 = 1;
	double op1 = 1;

	for (i = 0; i < lim; i += 2) {
		op0 *= v->data[i];
		op1 *= v->data[i + 1];
	}

	while (i < len) op0 *= v->data[i++];

	*res = op0*op1;
}

void foo_bar4_2(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 3;
	long len = my_vector_len(v);

	double op0 = 1;
	double op1 = 1;
	double op2 = 1;
	double op3 = 1;

	for (i = 0; i < lim; i += 4) {
		op0 *= v->data[i];
		op1 *= v->data[i + 1];
		op2 *= v->data[i + 2];
		op3 *= v->data[i + 3];
	}

	while (i < len) op0 *= v->data[i++];

	*res = op0*op1*op2*op3;
}

void foo_bar4_3(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 7;
	long len = my_vector_len(v);

	double op0 = 1;
	double op1 = 1;
	double op2 = 1;
	double op3 = 1;
	double op4 = 1;
	double op5 = 1;
	double op6 = 1;
	double op7 = 1;

	for (i = 0; i < lim; i += 8) {
		op0 *= v->data[i];
		op1 *= v->data[i + 1];
		op2 *= v->data[i + 2];
		op3 *= v->data[i + 3];
		op4 *= v->data[i + 4];
		op5 *= v->data[i + 5];
		op6 *= v->data[i + 6];
		op7 *= v->data[i + 7];
	}

	while (i < len) op0 *= v->data[i++];

	*res = op0*op1*op2*op3*op4*op5*op6*op7;
}

void foo_bar4_4(my_vector *v, double *res)
{
	long i, lim = my_vector_len(v) - 10;
	long len = my_vector_len(v);

	double op0 = 1;
	double op1 = 1;
	double op2 = 1;
	double op3 = 1;
	double op4 = 1;
	double op5 = 1;
	double op6 = 1;
	double op7 = 1;
	double op8 = 1;
	double op9 = 1;
	double op10 = 1;

	for (i = 0; i < lim; i +=11) {
		op0 *= v->data[i];
		op1 *= v->data[i + 1];
		op2 *= v->data[i + 2];
		op3 *= v->data[i + 3];
		op4 *= v->data[i + 4];
		op5 *= v->data[i + 5];
		op6 *= v->data[i + 6];
		op7 *= v->data[i + 7];
		op8 *= v->data[i + 8];
		op9 *= v->data[i + 9];
		op10 *= v->data[i + 10];
	}

	while (i < len) op0 *= v->data[i++];

	*res = op0*op1*op2*op3*op4*op5*op6*op7*op8*op9*op10;
}

void foo_bar5_1(my_vector *v, double *res)
{
	int num = 4;
	omp_set_num_threads(num);
	long i;
	long len = my_vector_len(v);
	long lim = (len / num)*num;
	int r = len%num;

	double op0 = 1;
	double op1 = 1;
	double op2 = 1;
	double op3 = 1;

	#pragma omp parallel sections shared(op1,op2,op3,op0,lim,v) private(i)
	{
		#pragma omp section
		for (i = 0; i < lim; i += 4)
		{
			op0 *= v->data[i];
		}

		#pragma omp section
		for (i = 0; i < lim; i += 4)
		{
			op1 *= v->data[i + 1];
		}

		#pragma omp section
		for (i = 0; i < lim; i += 4)
		{
			op2 *= v->data[i + 2];
		}

		#pragma omp section
		for (i = 0; i < lim; i += 4)
		{
			op3 *= v->data[i + 3];
		}
	}

	for (int j = 0; j < r; j++)
	{
		op0 *= v->data[len-1-j];
	}

	*res = op0*op1*op2*op3;
}

void foo_bar5_2(my_vector *v, double *res)
{
	int num = 4;
	omp_set_num_threads(num);
	long i;
	long len = my_vector_len(v);
	long lim = (len / num)*num;
	int r = len%num;

	double op0 = 1;
	double op1 = 1;
	double op2 = 1;
	double op3 = 1;

#pragma omp parallel shared(op1,op2,op3,op0) private(i)
	{
			#pragma omp single nowait
			for (i = 0; i < lim; i += 4) {
				op0 *= v->data[i];
			}

			#pragma omp single nowait
			for (i = 0; i < lim; i += 4) {
				op1 *= v->data[i+1];
			}

			#pragma omp single nowait
			for (i = 0; i < lim; i += 4) {
				op2 *= v->data[i+2];
			}

			#pragma omp single nowait
			for (i = 0; i < lim; i += 4) {
				op3 *= v->data[i+3];
			}

			#pragma omp barrier
	}

	for (int j = 0; j < r; j++)
	{
		op0 *= v->data[len - 1 - j];
	}

	*res = op0*op1*op2*op3;
}

void foo_bar6(my_vector *v, double *res)
{
	long i, len = my_vector_len(v);
	double op = 1;
	#pragma	omp simd reduction(*:op)
	for (i = 0; i < len; i++) {
		op *= v->data[i];
	}

	*res = op;
}

int main()
{
	double *a = reinterpret_cast<double*>(_aligned_malloc(LENGTH * sizeof(double),32));
	my_vector v = { LENGTH, a };
	double res;
	double start, finish;

	for (long i = 0; i < LENGTH; i++)  // инициализация вектора случайными числами
		a[i] = 1.0+rand();
	//a[i] = rand()%2 + 1.0;
	
	start = omp_get_wtime();
	foo_bar(&v, &res);
	finish = omp_get_wtime();
	std::cout << "Time: " << finish - start << std::endl;
	//std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar1(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "1" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar2(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "2" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar3_1(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "3_1" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar3_2(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "3_2" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar3_3(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "3_3" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar4_1(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "4_1" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar4_2(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "4_2" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar4_3(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "4_3" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar4_4(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "4_4" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar5_1(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "5_1" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar5_2(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "5_2" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	//
	//start = omp_get_wtime();
	//foo_bar6(&v, &res);
	//finish = omp_get_wtime();
	//std::cout << std::endl << "6" << std::endl;
	//std::cout << "Time: " << finish - start << std::endl;
	////std::cout << "Result: " << res << std::endl;
	
	system("pause");
}