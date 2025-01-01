#include"datatye.h"
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
bool check(Category category[], char str[], int length, int number) ;
bool isValidString(char *str, int minLen, int maxLen);
void addCategory(Category category[], int *legCategory);
void saveFile(Category category[], int legCategory, int legStoreManager);
void saveFlielogIn(Accounts *aaccounts);
void readFile(Category category[],int *legCategory, int *legStoreManager);
void readFilelogIn(Accounts *accounts);
void capitalizeFirst(char str[]);
void editCategory(Category category[],int lengthCategory);
void printfCategory(Category category[], int legCategory);
bool checkNumber(int number);
void deleteCategory(Category category[],int *lengthCategory);
int logIn(Accounts *accountAdmin);
int goBack(int number);
int goBackPrintf();
void sortCategories(Category category[], int lengthCategory);
void searchCategory(Category category[],int lengthCategory);
void itemManagement(Category category[],int lengthCategory);
void addProduct(Category category[],int lengthCategory);
