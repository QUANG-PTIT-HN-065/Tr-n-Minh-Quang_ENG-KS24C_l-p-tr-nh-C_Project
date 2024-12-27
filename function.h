#include"datatye.h"
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
bool check(Category category[],char str[],int length,int number);
void addCategory(Category Category[],int *legCategory, int *legStoreManager);
void saveFile(Category category[], int legCategory, int legStoreManager);
void readFile(Category Category[],int *legCategory, int *legStoreManager);
void capitalizeFirst(char str[]);
bool isEmpty(char str[]);
void printfCategory(Category category[], int legCategory, int legStoreManager);