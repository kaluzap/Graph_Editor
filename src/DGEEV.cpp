#include "DGEEV.hxx"
#include "F77_DGEEV.hxx"
#include <iostream>

int DGEEV(double *a, double *Wr, double *Wi, int N)
{
    char jobvl = 'N', jobvr = 'N';
    int n, ldvl, ldvr, lwork, info;
    double *vl=nullptr, *vr=nullptr, *work=nullptr;

    n = N;

    // Setup temporary parameters
    lwork = 4*n;
    ldvl  = 1;
    ldvr  = 1;

    work = new(std::nothrow) double[lwork];

    if(work == nullptr){
        std::cout << "Error in DGEEV. No momory" << std::endl;
        return 0;
    }
    
    /*a can be destroyed!!!!!*/
    dgeev_(jobvl, jobvr, n, a, n, Wr, Wi, vl, ldvl, vr, ldvr, work, lwork, info);
    
    delete[] work;

    return info;
}

int DGEEV1(double **A, double *Wr, double *Wi, double **LE, double **RE, int N)
{
    char jobvl = 'V';	//'V': left eigenvectors of A are computed.
	char jobvr = 'V';	//'V': right eigenvectors of A are computed.
	
    int n, ldvl, ldvr, lwork, info;
    double *a, *work, *le, *re;
    

    n = N;

    // Setup temporary parameters
    lwork = 4*n;
    ldvl  = n;
    ldvr  = n;

    a    = new double[n*n];
	le 	= new double[n*n];
	re 	= new double[n*n];
    work = new double[lwork];
	
    //memcpy( (void*)a, A, n*n*sizeof(double) );

	for( int i = 0; i < N; i++) for( int j = 0; j < N; j++) a[i*N + j] = A[i][j];
    
	dgeev_(jobvl, jobvr, n, a, n, Wr, Wi,
           le, ldvl, re , ldvr, work, lwork, info);
    
	//memcpy( (void*)LE, le, n*n*sizeof(double) );
	//memcpy( (void*)RE, re, n*n*sizeof(double) );
	
	for( int i = 0; i < N; i++) for( int j = 0; j < N; j++)  LE[i][j] = le[i*N + j];
	for( int i = 0; i < N; i++) for( int j = 0; j < N; j++)  RE[i][j] = re[i*N + j];
	
	
    delete[] a;
    delete[] work;
	delete[] re;
	delete[] le;

	return info;
}
