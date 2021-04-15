#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int n_max;
double R[1200];
double out_r1[100];
double out_r2[100];
char out_op[100];
double out_rres[100];
double out_tol[100];
double G[100000];
double Rbase[100];


void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
// Converts a floating-point/double number to a string.
void dtos(double n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    double fpart = n - (double)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

//new function
int FindIndex(double R[1000], double rd)
{
    //  printf("%lf \n",R[5]);
      int index_min = 0;
      int index_max = n_max + 1;
      int index = floor( (index_min + index_max) / 2);
      int i = 0;
    //  printf("%d \n",index);
    //  printf("%lf \n",R[index]);
    while (((index_max - index_min) > 1) && (i < 500))
    {
        if (R[index] == rd)
        {
           // printf("%lf",R[index]);
            break;
        }
        else if (R[index] > rd)
        {
          //  printf("%lf",R[index]);
            index_max = index;
        }
        else if (R[index] < rd)
        {
         //   printf("%lf",R[index]);
            index_min = index;
        }
        index = floor( (index_min + index_max) / 2);
        i++;
    }
  //  printf("%d",index);
    double tol1, tol2;
    if (index < n_max)
    {
      //  printf("%d \n",index);
        tol1 = abs(R[index] / rd - 1.0);
        tol2 = abs(R[index + 1] / rd - 1.0);
        if (tol1 < tol2)
          {
            return index;
          }
        else 
          {
            return (index + 1);
          }
    }
    else
    {
            return index;
    }
}
int CalcRes(double rd)
{
      int r1_idx,r1_idxn, r2_idxn, out_idx,r2_idx,i,j,iter=0;
      double r1, r1a, r2, r1b, rres, rres_tol, best_tol,r2d,r3,r4;
      double out_prres;
      float errp1;
      char out_vrres[20],op;
            /* compute assuming resistors in series */
            /* locate nearest approximation with standard resistor values */
      r1_idx = FindIndex(R, rd);
      r1a= R[r1_idx]; //need this as 1st
      r3= R[r1_idx - 1];
      if(abs(rd-r1a)>abs(rd-r3))
      {
          r1_idxn= r1_idx - 1;
          r1 = R[r1_idxn];
      }
      else
      {
          r1_idxn= r1_idx;
          r1 = R[r1_idxn];
      }
            /* other resistor */
            //r2 = Number.POSITIVE_INFINITY 
            r2 = 0;    
            rres = r1;
            rres_tol = fabs(rres - rd) / rd; /* relative tolerance */
            best_tol = rres_tol;
            
            out_idx = 0;
            out_r1[out_idx] = r1;
            out_r2[out_idx] = r2;
            out_op[out_idx] = '+';
            out_rres[out_idx] = rres;
            out_tol[out_idx++] = rres_tol;

            for (; R[r1_idxn] >= (rd / 2.0); r1_idxn--)
            {
              iter++;
              r1 = R[r1_idxn];
              r2d = rd - r1;
            //  printf("%lf \n",r2d);// this is the value needed
              if (r2d < 0)
              {
                  continue;
              } // might happen...

              r2_idx = FindIndex(R, r2d);
              r1b= R[r2_idx]; //need this as 1st
              r4= R[r2_idx - 1];
              if(fabs(r2d-r1b) > fabs(r2d-r4))
                {
                    r2_idxn= r2_idx - 1;
                    r2 = R[r2_idxn];
                }
              else
                {
                    r2_idxn= r2_idx;
                    r2 = R[r2_idxn];
                }
          //    r2 = R[r2_idx - 1];  // get the nearest standard value
              rres = r1 + r2; // compute the resulting composition
              rres_tol = (rres / rd - 1.0); // and its tolerance
              if (fabs(rres_tol) < fabs(best_tol))      //removed abs
              {
                //best_tol = rres_tol;
                out_r1[out_idx] = r1;
                out_r2[out_idx] = r2;
                out_op[out_idx] = '+';
                out_rres[out_idx] = rres;
                out_tol[out_idx++] = rres_tol;
              }

            }

             rd = 1.0 / rd;
            //compute assuming resistors in parallel 
            r1_idxn = FindIndex(G, rd);
            
            for (; G[r1_idxn] >= rd / 2.1; r1_idxn--)
            {
              iter++;
              r1 = G[r1_idxn];
              r2d = rd - r1; // this is the value needed
              if (r2d < 0)
              {
                  continue;
              } // might happen...

              r2_idx = FindIndex(G, r2d);
              r1b= G[r2_idx]; //need this as 1st
              r4= G[r2_idx - 1];
              if(fabs(r2d-r1b) > fabs(r2d-r4))
                {
                    r2_idxn= r2_idx - 1;
                    r2 = G[r2_idxn];
                }
              else
                {
                    r2_idxn= r2_idx;
                    r2 = G[r2_idxn];
                } 
              // r2 = G[r2_idxn];  // get the nearest standard value
              rres = r1 + r2; // compute the resulting composition
              rres_tol = rd / rres - 1.0; // and its tolerance

              if (fabs(rres_tol) <= fabs(best_tol))
              {
                //best_tol = rres_tol;
                // use values from R array to avoid rounding errors
                //   which will lead to something like 6800.0000001...
                out_r1[out_idx] = R[n_max - r1_idxn]; // 1.0 / r1;
                out_r2[out_idx] = R[n_max - r2_idxn]; // 1.0 / r2;
                out_op[out_idx] = '"';
                out_rres[out_idx] = 1.0 / rres;
                out_tol[out_idx++] = rres_tol;
              }
            }   

            // sort the results
            for (i = 1; i < out_idx; i++) {
              r1 = out_r1[i];
              r2 = out_r2[i];
              op = out_op[i];
              rres = out_rres[i];
              rres_tol = out_tol[i];
              for (j = i - 1; (j >= 0) && fabs(out_tol[j]) > fabs(rres_tol); j--)   //removed abs
              {
                out_r1[j + 1] = out_r1[j];
                out_r2[j + 1] = out_r2[j];
                out_op[j + 1] = out_op[j];
                out_rres[j + 1] = out_rres[j];
                out_tol[j + 1] = out_tol[j];
              }
              out_r1[j + 1] = r1;
              out_r2[j + 1] = r2;
              out_op[j + 1] = op;
              out_rres[j + 1] = rres;
              out_tol[j + 1] = rres_tol;
            }
            printf("Possible outcomes = %d \n",out_idx);
            for (r1_idxn=0; r1_idxn < out_idx; r1_idxn++)
            {
                out_prres = (round(out_rres[r1_idxn] * 1000)) / 1000 ;
                dtos(out_prres, out_vrres, 3);
                errp1 = (round(out_tol[r1_idxn] * 10000)) / 100;
                printf("%.3lf \t ",out_r1[r1_idxn]);
                printf("%c \t",out_op[r1_idxn]);
                printf("%.3lf = \t",out_r2[r1_idxn]);
                printf("%s \t",out_vrres);
                printf(" Error = %.3f %  \n", errp1);
      /*        if(sizeof(out_vrres) < 8)
              {
                
                 leave three decimal digits maximum 
              } */
          // put the focus on the input field
          //document.getElementById('rd').focus();
          }
}


double select_value(int gv)
{
    double Rbase1[12] = {1.0 , 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
    double Rbase2[24] = {1, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1};
    double Rbase3[96] = {1.00, 1.02, 1.05, 1.07, 1.10, 1.13, 1.15, 1.18, 1.21, 1.24, 1.27, 1.30, 1.33, 1.37, 1.40, 1.43, 1.47, 1.50, 1.54, 1.58, 1.62, 1.65, 1.69, 1.74, 1.78, 1.82, 1.87, 1.91, 1.96, 2.00, 2.05, 2.10, 2.15, 2.21, 2.26, 2.32, 2.37, 2.43, 2.49, 2.55, 2.61, 2.67, 2.74, 2.80, 2.87, 2.94, 3.01, 3.09, 3.16, 3.24, 3.32, 3.40, 3.48, 3.57, 3.65, 3.74, 3.83, 3.92, 4.02, 4.12, 4.22, 4.32, 4.42, 4.53, 4.64, 4.75, 4.87, 4.99, 5.11, 5.23, 5.36, 5.49, 5.62, 5.76, 5.90, 6.04, 6.19, 6.34, 6.49, 6.65, 6.81, 6.98, 7.15, 7.32, 7.50, 7.68, 7.87, 8.06, 8.25, 8.45, 8.66, 8.87, 9.09, 9.31, 9.53, 9.76};

    switch (gv)
    {
    case 1 :
        for(int loop = 0; loop < 12; loop++)
        {
        Rbase[loop] = Rbase1[loop];
        }
        //printf("%lf", Rbase[1]);
        
        for (int i = 0; i <= 6; i++)
        {
        for (int j = 0; j < 12; j++)
        {
              double a = round(pow(10,i)*Rbase[j]*100)/100;
              R[j+(i*12)]=a;
         //    printf("%lf",a);
        }
         n_max= 83;
      //  printf("%d \n", n_max);
    }
        break;
    case 2 :
        for(int loop = 0; loop < 24; loop++)
        {
        Rbase[loop] = Rbase2[loop];
        }
     //   printf("%lf", Rbase[23]);
        
        for (int i = 0; i <= 6; i++)
        {
        for (int j = 0; j < 24; j++)
        {
              double a = round(pow(10,i)*Rbase[j]*100)/100;
              R[j+(i*24)]=a;
          //  printf("%lf",a);
        }
         n_max= 167;
     //   printf("%d \n", n_max);
    }
        break;
    case 3 :
        for(int loop = 0; loop < 96; loop++)
        {
        Rbase[loop] = Rbase3[loop];
        }
     //   printf("%lf", Rbase[90]);
        
        for (int i = 0; i <= 6; i++)
        {
        for (int j = 0; j < 96; j++)
        {
              double a = round(pow(10,i)*Rbase[j]*100)/100;
              R[j+(i*96)]=a;
         //  printf("%lf",a);
        }
         n_max= 671;
    //    printf("%d \n", n_max);
    }
        break;
    }

       
   for(int j=0; j <= n_max ;j++)
        {
            G[j]= 1.0 / R[n_max - j];
        }

     double rd;
     printf("Enter the value of resistance required");
     scanf("%lf", &rd);
     CalcRes(rd);
}

int main()
{
  int gv;
  printf("Enter the type of resistors required, enter 1 for E12, 2 for E24 and 3 for E96 \n");
  scanf("%d", &gv);
  select_value(gv);
  return 0;
}
