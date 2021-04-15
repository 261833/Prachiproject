#include<project.h>

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