#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "diplom.h"

int draw_right_left(float*r, float *l);
int draw_with_regression(float* a, float k, float b);

int read_data(char* wdt){
	int i;
	FILE* f;
	if((f = fopen(wdt,"r")) == NULL){
		fprintf(stderr, "Error in fopen:\n");
		exit(1);
	}
	
	while(fgetc(f)!='\n');
	fscanf(f, "%d", &d.n);

	while(fgetc(f)!='\n');
	fscanf(f, "%f", &d.step_ord);

	while(fgetc(f)!='\n');
	fscanf(f, "%f", &d.coeff_ord);

	while(fgetc(f)!='\n');
	fscanf(f, "%f", &d.coeff_resist);
	
	while(fgetc(f)!='\n');
	fscanf(f, "%d", &d.class);
	
	while(fgetc(f)!='\n');
	fscanf(f, "%f", &d.step_integ);
	
	while(fgetc(f)!='\n');
	fscanf(f, "%d", &d.trend);
	
	while(fgetc(f)!='\n');

	fclose(f);
	return 1;
}

int read_numbers(float *r, float *l, char *wdt){
	int i;
	FILE* f;
	if((f = fopen(wdt,"r")) == NULL){
		fprintf(stderr, "Error in fopen:\n");
		exit(1);
	}
	for(i=0;i<8;i++)
		while(fgetc(f)!='\n');
	for(i=0;i<d.n;i++)
		fscanf(f,"%f%f",&r[i],&l[i]);
	fclose(f);
	return 1;
}

int remove_linear_trend(float *a, int draw_before_delete){
	double m, nm, k, b;
	int i;
	m, nm = 0.0;
	
	//Substract average value
	for(i=0;i<d.n;i++)
		m+=a[i];
	m/=d.n;
	
	for(i=0; i<d.n ; i++)
		a[i]-=m;
	printf("m=%f\n", m);

	//Compute k, b coeffs
	for(i=0;i<d.n;i++){
		nm+=(a[i]*(i+1));
	}
	nm/=(d.n*(d.n-1));
	
	k = 12.0*nm/(((float)d.n+1.0)*d.step_ord);
	b = -6.0*nm;
	printf("k=%f b=%f\n", k, b);
	if(draw_before_delete)
		draw_with_regression(a, k, b);
	
	//Remove trend
	for(i=0; i<d.n ; i++)
		a[i]-=(k*(d.step_ord*i)+b);
	
	for(i=0;i<d.n;i++){
		m+=a[i];
	}
	m/=d.n;
	printf("m after removal=%f\n", m);
	
	return 1;
}

int main(int argc, char** argv){
	float *r, *l;
	
	read_data(DMD);
	
	if((r=malloc(sizeof(float)*d.n)) == NULL){
		exit(1);
	}

	if((l=malloc(sizeof(float)*d.n)) == NULL){
		exit(1);
	}
	
	read_numbers(r,l, DMD);
	remove_linear_trend(r, 0);
	remove_linear_trend(l, 0);
	draw_right_left(r,l);
	return 0;
}
