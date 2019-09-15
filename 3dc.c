#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coeffs.h"

void lp(char *str, int j, double *P, double *m, int len); // function for saving points on the line in a dat file
void printm(char *str, double **x, int len); // function for saving meshgrid values in a dat file

int  main(void) //main function begins
{
int i,j;
int c = 9; //value of c in the plane equation
int len = 101;
int m1 = 2;
int n1 = 2;
int m2 = 2;
int n2 = 1;

double P[3]; //Point P
P[0]=3;
P[1]=-2;
P[2]=-4;

double m[3]; //Slope of the line
m[0]=2;
m[1]=-1;
m[2]=3;

double n[3]; // Slope of the normal to the plane
n[0]=1;
n[1]=-1;
n[2]=-1;

//Solving the two linear equations to obtain l and m
double **a = createMat(m1,n1);
a[0][0]=3;
a[0][1]=-2;
a[1][0]=2;
a[1][1]=-1;

double **b = createMat(m2,n2);
b[0][0]=5;
b[1][0]=3;

double **a1 = linalg_inv(a,2);

double **x = matmul(a1,b,2,2,1);

printf("l^2+m^2=%lf\n", linalg_norm(x,2)*linalg_norm(x,2));

// Saving the points on the line in a dat file
lp("l_p[0].dat",0,P,m,len);
lp("l_p[1].dat",1,P,m,len);
lp("l_p[2].dat",2,P,m,len);

// Creating points in between -12 and 15
double k[len];

for(i=0;i<len;i++){
    k[i]=-12.0+(i/((double)len-1.0))*27.0;
}

// Generating points on the plane
double **xx = createMat(len,len);

for(j=0;j<len;j++){
    for(i=0;i<len;i++){
        xx[j][i]=k[i];
    }
}

double **yy = createMat(len,len);

for(j=0;j<len;j++){
    for(i=0;i<len;i++){
        yy[i][j]=k[i];
    }
}

double **z = createMat(len,len);

for(j=0;j<len;j++){
    for(i=0;i<len;i++){
        z[j][i]=(c-n[0]*xx[j][i]-n[1]*yy[j][i])/n[2];
    }
}

// Saving the points on the plane in a dat file
printm("xx.dat",xx,len);
printm("yy.dat",yy,len);
printm("z.dat",z,len);

// Saving the coordinates of P in a dat file
FILE *fp;
fp = fopen("P.dat","w");

for(j=0;j<3;j++){
    fprintf(fp,"%lf\n",P[j]);
}
fclose(fp);

// Generating the coordinates for the label of the point P
double textco[3];
textco[0]=P[0]-0.1;
textco[1]=P[1]+0.1;
textco[2]=P[2]+2;

// Saving the coordinates for the label in a dat file
fp = fopen("textco.dat","w");

for(j=0;j<3;j++){
    fprintf(fp,"%lf\n",textco[j]);
}
fclose(fp);

//Saving the value of len in a dat file
fp = fopen("len.dat","w");
fprintf(fp,"%d",len);
fclose(fp);

return 0;
}

void lp(char *str, int j, double *P, double *m, int len)
{
double lam[len]; //lambda
double l_p[3][len];
int i;
//Generating different values of lambda
for(i=0;i<len;i++){
    lam[i]=-5.0+(i/((double)len-1.0))*11.0;
}

//Generating and saving the points on the line in a dat file
FILE *fp;
fp = fopen(str,"w");
for(i=0;i<101;i++){
        l_p[j][i]=P[j]+lam[i]*m[j];
        fprintf(fp,"%lf\n",l_p[j][i]);
}
fclose(fp);
}

void printm(char *str, double **x, int len){
int i,j;

//Saving the coordinates of the points on the plane in a dat file
FILE *fp;
fp = fopen(str,"w");

for(i=0;i<len;i++){
    for(j=0;j<len;j++){
        fprintf(fp,"%lf ",x[i][j]);
    }
    fprintf(fp,"\n");
    }
fclose(fp);
}
