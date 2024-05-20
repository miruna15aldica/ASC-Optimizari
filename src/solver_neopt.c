/*
 * Tema 3 ASC
 * 2024 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
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

	int i, j, k;
	
	// Calculez A.t tinand cont ca A e superior triunghilara
	for(i = 0; i < N; i++) {
		for(j = i; j < N; j++) {
			At[j * N  + i] = A[i * N + j];
		}
	}
	// Calculez B.t
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			Bt[j * N + i] = B[i * N + j];
		}
	}

	// Calculez A.t * B
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= i; k++) {
				AtB[i * N + j] += At[i * N + k] * B[k * N + j];
			}
		}
	}

	// Calculez B * A
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				BA[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}

	// Calculez A.t * B + B * A
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			sum[i * N + j] = AtB[i * N + j] + BA[i * N + j];
		}
	}

	// Calculez (A.t * B + B * A) * B.t
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				Rez[i * N + j] += sum[i * N + k] * Bt[k * N + j]; 
			}
		}
	}
	free(At);
	free(Bt);
	free(AtB);
	free(BA);
	free(sum);
	return Rez;
}
