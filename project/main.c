#include <stdio.h>
#include "include/function.c"
#include <stdbool.h>
#include<conio.h>
#include <stdlib.h>
int main() {
    Category category[100];
    Accounts accountAdmin;
    Accounts accountLogIn;
    int lengthCategory = 0, lengthStoreManager = 0, lengthaccount = 0, choice = 0;
    strcpy(accountAdmin.namelogIn, "admin");
    strcpy(accountAdmin.pass, "12345");
    saveFlielogIn(&accountAdmin);
    readFilelogIn(&accountAdmin); 
    do {
        printf("\n=========== ADMIN ===========\n");
        printf("login name: admin\n");
        printf("password: 12345\n");
        printf("1. Log In\n");
        printf("2. End\n");
        printf("============================\n");
        do {
            printf("Enter Your Selection: ");
            scanf("%d",&choice);
            getchar();
        } while (checkNumber(choice)|| choice > 2);  
        if (choice == 1)
        {
            system("cls");
            if (logIn(&accountAdmin) == 1)
            {
                break;
            }
        }else if (choice == 2)
        {
            printf("Exiting program...\n");
            return 0;
        }
    } while (choice != 2); 
    choice = 0;
    readFile(category, &lengthCategory, &lengthStoreManager);
    do {
        choice = 0;
        system("cls"); 
        printf("**** Store Manager ****\n");
        printf("===== MENU Category Management =====\n");
        printf("[1] Add Category\n");
        printf("[2] Show Category\n");
        printf("[3] Edit Category\n");
        printf("[4] Delete Category\n");
        printf("[5] Search Categories\n");
        printf("[6] Sort Categories\n");
        printf("[8] Exit\n");
        do
        {
            printf("Enter Your Selection: ");
            scanf("%d", &choice);
        } while (checkNumber(choice) || choice > 7);
        getchar();
        printf("===================================\n");
        switch (choice) {
            case 1:
                system("cls");
                addCategory(category, &lengthCategory);
                saveFile(category, lengthCategory, lengthStoreManager);
                break;
            case 2:
                if (lengthCategory==0)
                {
                    system("cls");
                    printf("no categories\n");
                    printf("===================================\n");
                }else
                {
                    system("cls");
                    printfCategory(category,lengthCategory);
                }
                break;
            case 3:
                system("cls");
                editCategory(category,lengthCategory);
                saveFile(category,lengthCategory, lengthStoreManager);
                break;
            case 4:
                system("cls");
                deleteCategory(category, &lengthCategory);
                saveFile(category,lengthCategory, lengthStoreManager);
                break;
            case 5:
                system("cls");
                searchCategory(category, lengthCategory);
                break;
            case 6:
                system("cls");
                sortCategories(category, lengthCategory);
                break;
            case 7:
                system("cls");
                itemManagement(category, lengthCategory);
                break;
            case 8:
                system("cls");
			    printf("\n   **** Exit ****");
		     	printf("\n======Thank you ==========");
		    	printf("\n======See you soon =======");
                saveFile(category,lengthCategory, lengthStoreManager); 
                break;
            default:
                printf("Error! Please enter a valid option.\n");
                printf("===================================\n");
                break;
        }
    } while (choice != 7);
    return 0;
}
