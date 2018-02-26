
#ifndef ARRAY_H
#define ARRAY_H

unsigned char *uc1D_Initialize(int nc);
unsigned char **uc2D_Initialize(int nr, int nc);
unsigned char ***uc3D_Initialize(int depth, int nr, int nc);

int *i1D_Initialize(int nc);
int **i2D_Initialize(int nr, int nc);
int ***i3D_Initialize(int depth, int nr, int nc);

float *f1D_Initialize(int nc);
float **f2D_Initialize(int nr, int nc);
float ***f3D_Initialize(int depth, int nr, int nc);

double *d1D_Initialize(int nc);
double **d2D_Initialize(int nr, int nc);
double ***d3D_Initialize(int depth, int nr, int nc);
double ****d4D_Initialize(int block, int depth, int nr, int nc);

void uc1D_Free(unsigned char *src);
void uc2D_Free(unsigned char **src, int nr);
void uc3D_Free(unsigned char ***src, int depth, int nc);

void i1D_Free(int *src);
void i2D_Free(int **src, int nr);
void i3D_Free(int ***src, int depth, int nr);

void f1D_Free(float* src);
void f2D_Free(float** src, int nr);
void f3D_Free(float*** src, int depth, int nr);

void d1D_Free(double* src);
void d2D_Free(double** src, int nr);
void d3D_Free(double*** src, int depth, int nr);
void d4D_Free(double**** src, int block, int depth, int nr);

#endif
