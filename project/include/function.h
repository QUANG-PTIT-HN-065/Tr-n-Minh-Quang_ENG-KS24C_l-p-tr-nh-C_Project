#include"datatye.h"
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
bool check(Category category[],char str[],int length,int number);
bool isValidString(char *str, int minLen, int maxLen);
void addCategory(Category Category[],int *legCategory, int *legStoreManager);
void saveFile(Category category[], int legCategory, int legStoreManager);
void readFile(Category Category[],int *legCategory, int *legStoreManager);
void capitalizeFirst(char str[]);
void editCategory(Category category[],int lengthCategory);
void printfCategory(Category category[], int legCategory,int lengthStoreManager);
bool checkNumber(int number);
void deleteCategory(Category category[],int *lengthCategory);
//void searchCategory(Category category[],int lengthCategory);
