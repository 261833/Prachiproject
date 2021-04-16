#include<project.h>

int main()
{
  int gv; //integer to select the type of resistors required
  printf("Enter the type of resistors required \n Enter 1 for E12 (10% tolerance) \n Enter 2 for E24 (5% tolerance) \n Enter 3 for E96 (1% tolerance) \n");
  scanf("%d", &gv); //gets the value of gv
  select_value(gv); //will calculate and display combinations based on the required tolerance value
  return 0;
}
