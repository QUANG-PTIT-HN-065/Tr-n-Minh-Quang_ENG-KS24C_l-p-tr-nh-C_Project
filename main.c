#include <stdio.h>
#include"include/case1.h"
#include <stdbool.h>
int main() {
    Category category[100];
    Product product[100];
    int lengthCategory = 0;
    int lengthStoreManager = 0;
    int choice;
    readFile(category, &lengthCategory, &lengthStoreManager);
    do {
        printf("**** Store Manager ****\n");
        printf("===== MENU Category Management =====\n");
        printf("[1] Add Category\n");
        printf("[2] Show Category\n");
        printf("[3] Edit Category\n");
        printf("[4] Delete Category\n");
        printf("[5] Search Categories\n");
        printf("[6] Sort Categories\n");
        printf("[7] Exit\n");
        do
        {
            printf("Enter Your Selection: ");
            scanf("%d", &choice);
            if (choice == 1 || choice > 0)
            {
                break;
            }else
            {
                printf("Invalid input. Please enter a positive integer\n");
                while (getchar() != '\n'); 
                continue;
            }
            getchar();
        } while (1);
        getchar();
        printf("===================================\n");
        switch (choice) {
            case 1:
                addCategory(category, &lengthCategory, &lengthStoreManager);
                saveFile(category, lengthCategory, lengthStoreManager);
                break;
            case 2:
                printfCategory(category,lengthCategory,lengthStoreManager);
                break;
            case 3:
                //editCategory(category, &lengthCategory);
                break;

            case 4:
               // deleteCategory(category, &lengthCategory);
                break;

            case 5:
                //searchCategory(category, lengthCategory);
                break;

            case 6:
               // sortCategories(category, lengthCategory);
                break;

            case 7:
              //  printf("Exiting program...\n");
                saveFile(category, lengthCategory, lengthStoreManager); 
                break;

            default:
                printf("Error! Please enter a valid option.\n");
                break;
        }
    } while (choice != 7);
    return 0;
}
