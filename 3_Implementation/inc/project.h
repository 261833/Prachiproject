/**********************************************
* @file project.h
* Standard Resistor Combination for odd values 
  utility
***********************************************/
#ifndef __PROJECT_H__
#define __PROJECT_H__

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

/********************************************
*  reverses the string
* @param[in] str 
* @param[in] len
* @return Result of reversing string
*********************************************/
void reverse(char* str, int len);

/*********************************************
*  Converts a given integer x to string str[]
* @param[in] x
* @param[in] str[]
* @param[in] d
* @return Result of integer to string
**********************************************/
int intToStr(int x, char str[], int d);

/*********************************************
 Converts a floating-point/double number to a 
 string 
 *********************************************/
void dtos(double n, char* res, int afterpoint);

/*********************************************
 Finds Index of value nearest to resistance
 *********************************************/
int FindIndex(double R[1000], double rd);

/*********************************************
 Calculates combination of resistances
 *********************************************/
int CalcRes(double rd);

/*********************************************
 Calculates combination of resistances
 *********************************************/
double select_value(int gv);

#endif
