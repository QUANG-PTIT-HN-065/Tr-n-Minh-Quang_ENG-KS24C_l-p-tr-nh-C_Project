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
    printf("[1] Add Category\n");
    printf("[2] Add products to the catalog\n");
    do 
    {
        printf("Enter Your Selection: ");
        scanf("%d", &choice);
        if (choice == 1 || choice > 0) {
            printf("Invalid input. Please enter 1 or 2.\n");
            while (getchar() != '\n'); 
            continue;
        }
        getchar();
    } while (choice < 1 || choice > 2);
    if (choice == 1) {
        do {
            printf("Enter the number of categories (number > 0 < 101)\n");
            scanf("%d", &newLength);
            while (getchar() != '\n'); 
            continue;
            getchar(); 
        } while (newLength < 1 || newLength > 100);
        for (int i = *legCategory; i < *legCategory + newLength; i++) {
            do {
                printf("Enter ID Category %d: ",i+1);
                fgets(catId, 10, stdin);
                catId[strcspn(catId, "\n")] = '\0';
            } while (check(category, catId, *legCategory, 1) || isEmpty(catId));
            do {
                printf("Enter name category %d: ",i+1);
                fgets(Name, 100, stdin);
                Name[strcspn(Name, "\n")] = '\0';
                capitalizeFirst(Name);
            } while (check(category, Name, *legCategory, 2) || isEmpty(Name));
            strcpy(category[i].categoryId, catId);  
            strcpy(category[i].categoryName, Name);
        }
        *legCategory += newLength;
    } else if (choice == 2) {
        printf("Enter Category ID: ");
        fgets(catId, 10, stdin);
        catId[strcspn(catId, "\n")] = '\0';
        if (check(category, catId, *legCategory, 1)) 
        {
            do {
                printf("Enter the number of products (number > 0 < 101)\n");
                scanf("%d", &newLength);
                getchar(); 
            } while (newLength < 1 || newLength > 100);
            for (int i = *legStoreManager; i < *legStoreManager + newLength; i++) {
                do {
                    printf("Enter id product %d: ",i+1);
                    fgets(Id, 10, stdin);
                    Id[strcspn(Id, "\n")] = '\0';
                } while (check(category, Id, *legStoreManager, 3));
                strcpy(category[i].product.productId, Id);
                do {
                    printf("Enter name product %d: ",i+1);
                    fgets(Name, 100, stdin);
                    Name[strcspn(Name, "\n")] = '\0';
                    capitalizeFirst(Name);
                } while (check(category, Name, *legStoreManager, 4) || isEmpty(Name));
                do 
                {
                    printf("Enter quantity: ");
                    scanf("%d", &category[i].product.quantity);
                    if (category[i].product.quantity == 1 || category[i].product.quantity > 0) 
                    {
                        break; 
                    }else
                    {
                        printf("Invalid input. Please enter a positive integer\n");
                    }
                } while (1);
                do 
                {
                    printf("Enter price: ");
                    scanf("%d", &category[i].product.price);
                    if (category[i].product.price == 1 || category[i].product.price > 0) 
                    {
                        break; 
                    }else
                    {
                        printf("Invalid input. Please enter a positive integer\n");
                    }
                } while (1);
                getchar();
                strcpy(category[i].product.productName, Name);
                strcpy(category[i].product.categoryId, catId);
            }
            *legStoreManager += newLength;
        } else {
            printf("id not found:\n");
            return;
        }
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
void printfCategory(Category category[], int legCategory, int legStoreManager) {
    printf("+------------------+----------------------------------+--------------------+-------------------+--------------------+--------------------+\n");
    printf("| Category ID      | Category Name                    | Product ID         | Product Name      | Quantity           | Price              |\n");
    printf("+------------------+----------------------------------+--------------------+-------------------+--------------------+--------------------+\n");
    for (int i = 0; i < legCategory; i++) {
        printf("| %-16s | %-32s ", category[i].categoryId, category[i].categoryName);
        int foundProduct = 0; 
        for (int j = 0; j < legStoreManager; j++) {
            if (strcmp(category[i].categoryId, category[j].product.categoryId) == 0) {
                if (foundProduct == 0) {
                    printf("| %-18s | %-18s | %-18d | %-18d |\n",category[j].product.productId,category[j].product.productName, category[j].product.quantity,category[j].product.price);
                    foundProduct = 1;  
                } else 
                {
                    printf("| %-18s | %-18s | %-18d | %-18d |\n",category[j].product.productId,category[j].product.productName,category[j].product.quantity,category[j].product.price);
                }
            }
        }
        if (foundProduct == 0) {
            printf("| %-18s | %-18s | %-18s | %-18s |\n", "N/A", "No products", "", "");
        }
        printf("+------------------+----------------------------------+--------------------+-------------------+--------------------+--------------------+\n");
    }
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
bool isEmpty(char str[]) 
{
    if (str[0] == '\0') {
        return true;
    }
    return false;
}