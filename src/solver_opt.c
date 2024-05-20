/*
 * Tema 3 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	// (A.t * B + B * A) * B.t
	// A.t
	double *At = (double *)calloc(N * N, sizeof(double));
	// B.t
	double *Bt = (double *)calloc(N * N, sizeof(double));
	// A.t *B
	double *AtB = (double *)calloc(N * N, sizeof(double));
	// B * A
	double *BA = (double *)calloc(N * N, sizeof(double));
	// A.t * B + B * A
	double *sum = (double *)calloc(N * N, sizeof(double));
	// (A.t * B + B * A) * B.t
	double *Rez = (double *)calloc(N * N, sizeof(double));

	// int i, j, k;
	
	// Calculez A.t tinand cont ca A e superior triunghilara
	for(register int i = 0; i < N; i++) {
		for(register int j = i; j < N; j++) {
			At[j * N  + i] = A[i * N + j];
		}
	}
	// Calculez B.t
	for(register int i = 0; i < N; i++) {
		for(register int j = 0; j < N; j++) {
			Bt[j * N + i] = B[i * N + j];
		}
	}

	// Calculez A.t * B
	for (register int i = 0; i < N; i++) {
		for (register int j = 0; j < N; j++) {
			register double opt = 0;
			for (register int k = 0; k <= i; k++) {
				opt += At[i * N + k] * B[k * N + j];
			}
			AtB[i * N + j] = opt;
		}
	}

	// Calculez B * A
	for (register int i = 0; i < N; i++) {
		for (register int j = 0; j < N; j++) {
			register double opt = 0;
			for (register int k = 0; k <= j; k++) {
				opt += B[i * N + k] * A[k * N + j];
			}
			BA[i * N + j] = opt;
		}
	}


	// Calculez A.t * B + B * A
	for(register int i = 0; i < N; i++) {
		for(register int j = 0; j < N; j++) {
			sum[i * N + j] = AtB[i * N + j] + BA[i * N + j];
		}
	}

	// Calculez (A.t * B + B * A) * B.t
	for(register int i = 0; i < N; i++) {
		for(register int j = 0; j < N; j++) {
			register double opt = 0;
			for(register int k = 0; k < N; k++) {
				opt += sum[i * N + k] * Bt[k * N + j]; 
			}
			Rez[i * N + j]  = opt;
		}
	}
	free(At);
	free(Bt);
	free(AtB);
	free(BA);
	free(sum);
	return Rez;

}
