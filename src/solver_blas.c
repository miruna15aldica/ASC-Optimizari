/*
 * Tema 3 ASC
 * 2024 Spring
 */
#include "utils.h"
#include "cblas.h"
/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	// (A.t * B + B * A) * B.t
	// A.t *B
	double * AtB = (double *)calloc(N * N, sizeof(double));
	// B * A
	double *BA = (double *)calloc(N * N, sizeof(double));
	// A.t * B + B * A
	double *sum = (double *)calloc(N * N, sizeof(double));
	// (A.t * B + B * A) * B.t
	double *Rez = (double *)calloc(N * N, sizeof(double));

	// Copiez B in AtB
	cblas_dcopy(N * N, B, 1, AtB, 1);
	// Copiez B in BA
	cblas_dcopy(N * N, B, 1, BA, 1);
	
	// A.t * B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, AtB, N);
	// B * A
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, BA, N);

	// A.t * B + B * A
	for(int i = 0; i < N * N; i++) {
		sum[i] = AtB[i] + BA[i];
	}

	// (A.t * B + B * A) * B.t
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1.0, sum, N, B, N, 0.0, Rez, N);

	free(AtB);
	free(BA);
	free(sum);
	return Rez;
}
