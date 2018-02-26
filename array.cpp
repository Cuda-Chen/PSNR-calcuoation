
#include <stdio.h>
#include "stdlib.h"
#include <string.h>

unsigned char *uc1D_Initialize(int nc){
	if(nc <= 0) return NULL;
	
	unsigned char *src = (unsigned char*)calloc(nc, sizeof(unsigned char));
	
	if(src == NULL){
		printf("i1D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	memset(src, 0, sizeof(unsigned char) * nc);
	
	return src;
}

void uc1D_Free(unsigned char *src){
	free(src);
}

unsigned char **uc2D_Initialize(int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0) return NULL;
	
	unsigned char **src = (unsigned char**)malloc(sizeof(unsigned char*) * nr);
	
	if(src == NULL){
		printf("i2D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < nr;i++){
		src[i] = uc1D_Initialize(nc);
	}
	return src;
}

void uc2D_Free(unsigned char **src, int nr){
	int i;
	for(i = 0;i < nr;i++){
		uc1D_Free(src[i]);
	}
	free(src);
}

unsigned char ***uc3D_Initialize(int depth, int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0 || depth <= 0) return NULL;
	
	unsigned char ***src = (unsigned char***)malloc(sizeof(unsigned char**) * depth);
	
	if(src == NULL){
		printf("i3D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < depth;i++){
		src[i] = uc2D_Initialize(nr, nc);
	}
	return src;
}

void uc3D_Free(unsigned char ***src, int depth, int nr){
	int i;
	for(i = 0;i < depth;i++){
		uc2D_Free(src[i], nr);
	}
	free(src);
}

int *i1D_Initialize(int nc){
	if(nc <= 0) return NULL;
	
	int *src = (int*)calloc(nc, sizeof(int));
	
	if(src == NULL){
		printf("i1D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	memset(src, 0, sizeof(int) * nc);
	
	return src;
}

void i1D_Free(int *src){
	free(src);
}

int **i2D_Initialize(int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0) return NULL;
	
	int **src = (int**)malloc(sizeof(int*) * nr);
	
	if(src == NULL){
		printf("i2D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < nr;i++){
		src[i] = i1D_Initialize(nc);
	}
	return src;
}

void i2D_Free(int **src, int nr){
	int i;
	for(i = 0;i < nr;i++){
		i1D_Free(src[i]);
	}
	free(src);
}

int ***i3D_Initialize(int depth, int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0 || depth <= 0) return NULL;
	
	int ***src = (int***)malloc(sizeof(int**) * depth);
	
	if(src == NULL){
		printf("i3D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < depth;i++){
		src[i] = i2D_Initialize(nr, nc);
	}
	return src;
}

void i3D_Free(int ***src, int depth, int nr){
	int i;
	for(i = 0;i < depth;i++){
		i2D_Free(src[i], nr);
	}
	free(src);
}

float *f1D_Initialize(int nc){
	if(nc <= 0) return NULL;
	
	float *src = (float*)calloc(nc, sizeof(float));
	
	if(src == NULL){
		printf("f1D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	memset(src, 0, sizeof(float) * nc);
	
	return src;
}

void f1D_Free(float* src){
	free(src);
}

float **f2D_Initialize(int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0) return NULL;
	
	float **src = (float**)malloc(sizeof(float*) * nr);
	
	if(src == NULL){
		printf("f2D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < nr;i++){
		src[i] = f1D_Initialize(nc);
	}
	return src;
}

void f2D_Free(float** src, int nr){
	int i;
	
	for(i = 0;i < nr;i++){
		f1D_Free(src[i]);
	}
	
	free(src);
}

float ***f3D_Initialize(int depth, int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0 || depth <= 0) return NULL;
	
	float ***src = (float***)malloc(sizeof(float**) * depth);
	
	if(src == NULL){
		printf("d3D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < depth;i++){
		src[i] = f2D_Initialize(nr, nc);
	}
	return src;
}

void f3D_Free(float*** src, int depth, int nr){
	int i, j;
	
	for(i = 0;i < depth;i++){
		f2D_Free(src[i], nr);
	}
	
	free(src);
}


double *d1D_Initialize(int nc){
	if(nc <= 0) return NULL;
	
	double *src = (double*)malloc(nc * sizeof(double));
	
	if(src == NULL){
		printf("d1D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	memset(src, 0, sizeof(double) * nc);
	
	return src;
}

void d1D_Free(double* src){
	free(src);
}

double **d2D_Initialize(int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0) return NULL;
	
	double **src = (double**)malloc(sizeof(double*) * nr);
	
	if(src == NULL){
		printf("d2D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < nr;i++){
		src[i] = d1D_Initialize(nc);
	}
	return src;
}

void d2D_Free(double** src, int nr){
	int i;
	
	for(i = 0;i < nr;i++){
		d1D_Free(src[i]);
	}
	
	free(src);
}

double ***d3D_Initialize(int depth, int nr, int nc){
	int i;
	
	if(nr <= 0 || nc <= 0 || depth <= 0) return NULL;
	
	double ***src = (double***)malloc(sizeof(double**) * depth);
	
	if(src == NULL){
		printf("d3D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < depth;i++){
		src[i] = d2D_Initialize(nr, nc);
	}
	return src;
}

void d3D_Free(double*** src, int depth, int nr){
	int i, j;
	
	for(i = 0;i < depth;i++){
		d2D_Free(src[i], nr);
	}
	
	free(src);
}

double ****d4D_Initialize(int block, int depth, int nr, int nc){
	int i;
	
	if(block <= 0 || nr <= 0 || nc <= 0 || depth <= 0) return NULL;
	
	double ****src = (double****)malloc(sizeof(double***) * block);
	
	if(src == NULL){
		printf("d4D_Initialize: Fail to allocate memory\n");
		return NULL;
	}
	
	for(i = 0;i < block;i++){
		src[i] = d3D_Initialize(depth, nr, nc);
	}
	return src;
}

void d4D_Free(double**** src, int block, int depth, int nr){
	int i, j;
	
	for(i = 0;i < block;i++){
		d3D_Free(src[i], depth, nr);
	}
	
	free(src);
}



