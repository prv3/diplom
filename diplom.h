#define DMD "DMD.WDT"
#define BULGLAD "BULGLAD.WDT"

typedef struct{
	int n;
	float step_ord;
	float coeff_ord;
	float coeff_resist;
	int class;
	float step_integ;
	int trend;
} data; 

data d;




/********************************************************************
 * Draw 1 set of points
 * *****************************************************************/

int draw_points(float* a){
    char * commandsForGnuplot[] = {"set title \"Points\"", "plot 'data_points.tmp' with lines"};
    FILE * temp = fopen("data_points.tmp", "w");
    if(temp==NULL){
		fprintf(stderr, "Error in fopen!");
		exit(1);
	}
    FILE * gnuplotPipe = popen ("gnuplot -persist", "w");
    int i;
    for (i=0; i < d.n; i++)
		fprintf(temp, "%lf %lf \n", i*d.step_ord, a[i]);

    for (i=0; i < 2; i++)
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
	fclose(temp);
	fflush(gnuplotPipe);
	return 0;	
}



/********************************************************************
 * Draw 2 sets of points on one plot
 * *****************************************************************/

int draw_right_left(float*r, float *l){
    char * commandsForGnuplot[] = {"set title \"Right and left\"", "plot 'data_r.tmp' with lines, 'data_l.tmp' with lines"};
    FILE * temp_r = fopen("data_r.tmp", "w");
    FILE * temp_l = fopen("data_l.tmp", "w");
    if(temp_r==NULL){
		fprintf(stderr, "Error in fopen!");
		exit(1);
	}
	if(temp_l==NULL){
		fprintf(stderr, "Error in fopen!");
		exit(1);
	}
    FILE * gnuplotPipe = popen ("gnuplot -persist", "w");
    int i;
    for (i=0; i < d.n; i++)
		fprintf(temp_r, "%lf %lf \n", i*d.step_ord, r[i]);

    for (i=0; i < d.n; i++)
		fprintf(temp_l, "%lf %lf \n", i*d.step_ord, l[i]);


    for (i=0; i < 2; i++)
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);

	fclose(temp_r); fclose(temp_l);
	fflush(gnuplotPipe);
	return 0;	
}




/*********************************************************************
 * Draw set of points with it's linear regression line y = kx+b
 * *******************************************************************/

int draw_with_regression(float* a, float k, float b){
    char * commandsForGnuplot[] = {"set title \"With linear regression\"", "plot 'data.tmp' with lines, 'regression.tmp' with lines"};
    FILE * temp = fopen("data.tmp", "w");
    FILE * regression = fopen("regression.tmp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persist", "w");
    int i;
    
    if(temp==NULL){
		fprintf(stderr, "Error in fopen!");
		exit(1);
	}
	if(regression==NULL){
		fprintf(stderr, "Error in fopen!");
		exit(1);
	}

    //fill file with set of points
    for (i=0; i < d.n; i++)
		fprintf(temp, "%lf %lf \n", i*d.step_ord, a[i]);

	//linear regression line x=0 and x=dt*N
	fprintf(regression, "%lf %lf \n", 0.0, b);
	fprintf(regression, "%lf %lf \n", (float)d.n*d.step_ord, k*((float)d.n*d.step_ord)+b);

    for (i=0; i < 2; i++)
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);

	fclose(temp); fclose(regression);
	fflush(gnuplotPipe);
	return 0;	
}
