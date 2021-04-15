#include<project.h>
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
