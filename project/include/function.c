#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
#include"function.h"
/*bool check(Category category[],char str[],int length,int number);
void addCategory(Category Category[],int *legCategory, int *legStoreManager);
void saveFile(Category category[], int legCategory, int legStoreManager);
void readFile(Category Category[],int *legCategory, int *legStoreManager);
void capitalizeFirst(char str[]);*/
void addCategory(Category category[], int *legCategory, int *legStoreManager) 
{
    int choice;
    int newLength;
    char Id[10];
    char catId[10];
    char Name[100];
    printf("===== Add Category =====\n");
    printf("[1] Add Category\n");
    printf("[2] Add products to the catalog\n");
    printf("[3] Out\n");
    do 
    {
        printf("Enter Your Selection: ");
        scanf("%d", &choice);
    } while (checkNumber(choice)|| choice > 3);
    if (choice == 1) {
        do {
            printf("Enter the number of categories (number > 0 < 101)\n");
            scanf("%d", &newLength);
            getchar();
        } while (checkNumber(newLength) || newLength > 100);
        for (int i = *legCategory; i < *legCategory + newLength; i++) {
            do {
                printf("Enter ID Category %d: ",i+1);
                fgets(catId, 10, stdin);
                catId[strcspn(catId, "\n")] = '\0';
            } while (check(category, catId, *legCategory, 1) || isValidString(catId,1,10));
            do {
                printf("Enter name category %d: ",i+1);
                fgets(Name, 100, stdin);
                Name[strcspn(Name, "\n")] = '\0';
                capitalizeFirst(Name);
            } while (check(category, Name, *legCategory, 2) || isValidString(Name,1,10));
            strcpy(category[i].categoryId, catId);  
            strcpy(category[i].categoryName, Name);
        }
        *legCategory += newLength;
        printf("added category successfully:\n");
    } else if (choice == 2) {
        getchar();
        do
        {
           printf("Enter Category ID: ");
           fgets(catId, 10, stdin);
           catId[strcspn(catId, "\n")] = '\0';
        } while (isValidString(catId,1,10));
        if (check(category, catId, *legCategory, 1)) 
        {
            do {
                printf("Enter the number of products (number > 0 < 101)\n");
                scanf("%d", &newLength);
                getchar(); 
            } while (checkNumber(newLength) || newLength > 100);
            for (int i = *legStoreManager; i < *legStoreManager + newLength; i++) {
                do {
                    printf("Enter id product %d: ",i+1);
                    fgets(Id, 10, stdin);
                    Id[strcspn(Id, "\n")] = '\0';
                } while (check(category, Id, *legStoreManager, 3)||isValidString(Id,1,10));
                strcpy(category[i].product.productId, Id);
                do {
                    printf("Enter name product %d: ",i+1);
                    fgets(Name, 100, stdin);
                    Name[strcspn(Name, "\n")] = '\0';
                    capitalizeFirst(Name);
                } while (check(category, Name, *legStoreManager, 4) || isValidString(Name,1,10));
                do 
                {
                    printf("Enter quantity: ");
                    scanf("%d", &category[i].product.quantity);
                } while (checkNumber(category[i].product.quantity));
                do 
                {
                    printf("Enter price: ");
                    scanf("%d", &category[i].product.price);
                } while (checkNumber(category[i].product.price));
                getchar();
                strcpy(category[i].product.productName, Name);
                strcpy(category[i].product.categoryId, catId);
            }
            *legStoreManager += newLength;
            printf("Added item successfully:\n");
        } else {
            printf("===================================\n");
            printf("id not found:\n");
            printf("===================================\n");
            return;
        }
    }else if (choice == 3)
    {
        return;
    }
    
}
bool check(Category category[], char str[], int length, int number) {
    for (int i = 0; i < length+1; i++) {
        switch (number) {
            case 1:
                if (strcmp(category[i].categoryId, str) == 0) {
                    printf("Id already exists.\n");
                    return true;
                }
                break;
            case 2:
                if (strcmp(category[i].categoryName, str) == 0) {
                    printf("Category name already exists.\n");
                    return true;
                }
                break;
            case 3:
                if (strcmp(category[i].product.productId, str) == 0) {
                    printf("Product id already exists.\n");
                    return true;
                }
                break;
            case 4:
                if (strcmp(category[i].product.productName, str) == 0) {
                    printf("Product name already exists.\n");
                    return true;
                }
                break;
            default:
                return false;
        }
    }
    return false;
}
void printfCategory(Category category[], int legCategory,int lengthStoreManager){
    printf("+--------------------+--------------------+--------------------+\n");
    printf("| Category ID        | Category Name      | Quantity           |\n");
    printf("+--------------------+--------------------+--------------------+\n");
    for (int i = 0; i < legCategory; i++){ 
    
        printf("| %-18s | %-18s | %-18d |\n",category[i].categoryId,category[i].categoryName,lengthStoreManager);
    }
    printf("+--------------------+--------------------+--------------------+\n");
}
void saveFile(Category category[], int legCategory, int legStoreManager) {
    FILE *ptr = fopen("shop.bin", "wb");
    if (!ptr) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(category, sizeof(Category), legCategory, ptr);
    fclose(ptr);
}
void readFile(Category category[], int *legCategory, int *legStoreManager) {
    FILE *ptr = fopen("shop.bin", "rb");
    if (!ptr) {
        printf("Error reading file.\n");
        return;
    }
    *legCategory = fread(category, sizeof(Category), 100, ptr);
    *legStoreManager = *legCategory;
    fclose(ptr);
}
void capitalizeFirst(char str[]) {
    int n = strlen(str);
    int capitalizeNext = 1; 

    for (int i = 0; i < n; i++) 
    {
        if (capitalizeNext && isalpha(str[i])) 
        { 
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        } else if (!isalpha(str[i]) && !isdigit(str[i])) {
            capitalizeNext = 1; 
        } else {
            str[i] = tolower(str[i]);
        }
    }
}
bool checkNumber(int number){
    if (number > 0)
    {
        return false;
    }else
    {
        printf("===================================\n");
        printf("Invalid input. Please enter a positive integer\n");
        printf("===================================\n");
        while (getchar() != '\n');  
        return true;
    }
}
void editCategory(Category category[],int lengthCategory)
{
    char id[10];
    char name[10];
    printf("Enter ID Category: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < lengthCategory; i++)
    {
        if (strcmp(category[i].categoryId, id) == 0)
        {
            printf("=========================\n");
            printf("Id Category: %s\n");
            printf("Name Category: %s\n ");
            printf("=========================\n");
            printf("Enter Name Category: ");
            fgets(name, 10, stdin);
            name[strcspn(name, "\n")] = '\0';
            strcpy(category[i].categoryName,name);
            printf("Edited successfully\n");
            printf("=========================\n");
            return;
        }
    }
    printf("id does not exist");  
}
void deleteCategory(Category category[], int *lengthCategory) {
    char id[10];
    printf("Enter ID Category: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *lengthCategory; i++) {
        if (strcmp(category[i].categoryId, id) == 0) {
            for (int j = i; j < *lengthCategory - 1; j++) {
                category[j] = category[j + 1];
            }
            (*lengthCategory)--; 
            printf("Delete successfully\n");
            printf("===================================\n");
            return;
        }
    }
    printf("ID does not exist\n");
}
bool isValidString(char *str, int minLen, int maxLen) {
    if (str == NULL) 
    { 
        printf("String is null.\n");
        return true;
    }
    int len = strlen(str);
    if (len < minLen || len > maxLen) 
    {
        printf("Invalid string length. Length must be between %d and %d.\n", minLen, maxLen);
        return true;
    }
    return false; 
}
