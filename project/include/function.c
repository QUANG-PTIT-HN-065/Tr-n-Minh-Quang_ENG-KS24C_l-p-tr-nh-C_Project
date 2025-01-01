#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
#include"function.h"
#include<conio.h>
#include <stdlib.h>
void addCategory(Category category[], int *legCategory) {
    int newLength;
    char catId[10], name[10];
    printf("===== Add Category =====\n");
    do
    {
        printf("Enter The Number Of Categories To Add (1-100): ");
        scanf("%d", &newLength);
        getchar();
    } while (checkNumber(newLength) || newLength > 100);
    for (int i = *legCategory; i < *legCategory + newLength; i++) {
        do {
            printf("Enter ID for Category %d: ", i + 1);
            fgets(catId, sizeof(catId), stdin);
            catId[strcspn(catId, "\n")] = '\0';
        } while (isValidString(catId, 1, 10) || check(category,catId,*legCategory,1));
        do {
            printf("Enter name for Category %d: ", i + 1);
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            capitalizeFirst(name);
        } while (isValidString(name, 1, 100) || check(category,name,*legCategory,2));
        strcpy(category[i].categoryId, catId);
        strcpy(category[i].categoryName, name);
    }
    *legCategory += newLength;
    if (goBack(4)==1)
    {
        return;
    }
}
bool check(Category category[], char str[], int length, int number) {
    for (int i = 0; i < length+1; i++) { 
        switch (number) {
            case 1: 
                if (strcmp(category[i].categoryId, str) == 0) {
                    printf("ID already exists: %s\n", str);
                    return true;
                }
                break;
            case 2:
                if (strcmp(category[i].categoryName, str) == 0) {
                    printf("Category name already exists: %s\n", str);
                    return true;
                }
                break;
            case 3: 
                for (int j = 0; j < category[i].numProducts; j++) {
                    if (strcmp(category[i].product[j].productId, str) == 0) {
                        printf("Product ID already exists: %s\n", str);
                        return true;
                    }
                }
                break;
            case 4: 
                for (int j = 0; j < category[i].numProducts; j++) {
                    if (strcmp(category[i].product[j].productName, str) == 0) {
                        printf("Product name already exists: %s\n", str);
                        return true;
                    }
                }
                break;
            default: 
                printf("Invalid option for checking: %d\n", number);
                return false;
        }
    }
    return false; 
}
void printfCategory(Category category[], int legCategory) {
    char choice;
    printf("+--------------------+--------------------+--------------------+\n");
    printf("| Category ID        | Category Name      | Quantity           |\n");
    printf("+--------------------+--------------------+--------------------+\n");
    for (int i = 0; i < legCategory; i++) {
        int totalQuantity = 0;
        for (int j = 0; j < category[i].numProducts; j++) { 
            totalQuantity += category[i].product[j].quantity; 
        }
        printf("| %-18s | %-18s | %-18d |\n",category[i].categoryId,category[i].categoryName,totalQuantity);
    }
    printf("+--------------------+--------------------+--------------------+\n");
    if (goBackPrintf()==1)
    {
        return;
    }
}
void saveFile(Category category[], int legCategory, int legStoreManager) {
    FILE *ptr = fopen("shop.bin", "wb");
    if (ptr==NULL) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(category, sizeof(Category), legCategory, ptr);
    fclose(ptr);
}
void saveFlielogIn(Accounts *aaccounts){
    FILE *ptr =fopen("accounts.bin","wb"); 
	fwrite(aaccounts,sizeof(Accounts),1,ptr);
    fclose(ptr);
}
void readFile(Category category[],int *legCategory, int *legStoreManager) {
    FILE *ptr = fopen("shop.bin", "rb");
    *legCategory = fread(category, sizeof(Category), 100, ptr);
    fclose(ptr);
}
void readFilelogIn(Accounts *accounts){
    FILE *ptr = fopen("accounts.bin","rb");
    fread(accounts,sizeof(Accounts),100,ptr);
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
            printf("Id Category: %s\n",category[i].categoryId);
            printf("Name Category: %s\n",category[i].categoryName);
            printf("=========================\n");
            do
            {
                printf("Enter Name Category: ");
                fgets(name, 10, stdin);
                name[strcspn(name, "\n")] = '\0';
                capitalizeFirst(name);
            } while (isValidString(name,1,10) || check(category,name,lengthCategory,2) );
            strcpy(category[i].categoryName,name);
            printf("Edited successfully\n");
            printf("=========================\n");
            if (goBack(1)==1)
            {
                return;
            }
        }
    }
    if (goBack(3)==1)
    {
        return;
    }
}
void deleteCategory(Category category[], int *lengthCategory) {
    char id[10];
    char choice;
    printf("Enter ID Category: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *lengthCategory; i++) {
        if (strcmp(category[i].categoryId, id) == 0) {
            do
            {
                printf("Do You Want To Delete It?\n");
                printf("(a) yes   (b) no\n");
                scanf("%c",&choice);
                getchar();
                if (choice == 'b')
                {
                    return;
                }else if (choice == 'a' )
                {
                }else
                {
                    printf("Invalid selection\n");
                }
            } while (choice != 'a');
            for (int j = i; j < *lengthCategory - 1; j++) {
                category[j] = category[j + 1];
            }
            (*lengthCategory)--; 
            printf("Delete successfully\n");
            printf("===================================\n");
            if (goBack(2)==1)
            {
                return;
            }
            return;
        }
    }
    if (goBack(3)==1)
    {
        return;
    }
}
bool isValidString(char *str, int minLeg, int maxLeg) {
    if (str == NULL) 
    { 
        printf("String is null.\n");
        return true;
    }
    int len = strlen(str);
    if (len < minLeg || len > maxLeg) 
    {
        printf("Invalid string length\n");
        return true;
    }
    return false; 
}
int logIn(Accounts *accountAdmin){
    char nameLogIn[10];
    char pass[10];
    char chr;
    int count=0;
    printf("Enter login name: ");
    fgets(nameLogIn, sizeof(nameLogIn), stdin);
    nameLogIn[strcspn(nameLogIn, "\n")] = '\0';
    printf("Enter password: ");
    do
    {
        chr = _getch();
        if (chr == '\r')
        {
            break;
        }else if (chr == 8)
        {
            if (count > 0)
            {
                count--;
                printf("\b \b");
            }
        }else
        {
            pass[count]=chr;
            printf("*");
            count++;
        }
    } while (1);
    pass[count]='\0';
    if (strcmp(nameLogIn,accountAdmin->namelogIn)==0)
    {
        if (strcmp(pass,accountAdmin->pass)==0)
        {
            printf("\nLogin successful!\n");
            return 1;
        }
    }
    printf("\nLogin name or password is incorrect:\n");
    return 0;
}
void searchCategory(Category category[],int lengthCategory){
    char id[10];
    printf("Enter ID Category: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < lengthCategory; i++) 
    {
        if (strcmp(category[i].categoryId, id) == 0) 
        {
           printf("+--------------------+--------------------+--------------------+\n");
           printf("| Category ID        | Category Name      | Quantity           |\n");
           printf("+--------------------+--------------------+--------------------+\n");
           printf("+--------------------+--------------------+--------------------+\n");
           int totalQuantity = 0;
           for (int j = 0; j < category[i].numProducts; j++) 
           { 
                totalQuantity += category[i].product[j].quantity; 
           }
           printf("| %-18s | %-18s | %-18d |\n",category[i].categoryId,category[i].categoryName,totalQuantity);
           if (goBackPrintf()==1)
           {
                return;
           }
        }
    }
    if (goBack(3)==1)
    {
        return;
    }
}
int goBack(int number){
    do
    {
        system("cls");
        char choice;
        if (number == 1)
        {
            printf("Successfully Repaired\n");
        }else if (number == 2)
        {
            printf("Deleted Successfully\n");
        }else if (number == 3)
        {
            printf("ID does not exist\n");
        }else if (number == 4)
        {
            printf("Added Successfully.\n");
        }else if (number == 5)
        {
            printf("Sorted Successfully.\n");
        }else if (number == 6)
        {
            
        }
        printf("(a) go back   (b) exit\n");
        scanf("%c",&choice);
        getchar();
        if (choice == 'a')
        {
            system("cls");
            return 1;
        }else if (choice == 'b')
        {
            system("cls");
			printf("\n    **** Exit ****");
		    printf("\n======Thank you ==========");
		    printf("\n======See you soon =======");
            exit(0);
        }else
        {
            printf("Invalid selection\n");
        }
    } while (1); 
}
int goBackPrintf(){
    do
    {
        char choice;
        printf("(a) go back   (b) exit\n");
        scanf("%c",&choice);
        getchar();
        if (choice == 'a')
        {
            system("cls");
            return 1;
        }else if (choice == 'b')
        {
            system("cls");
			printf("\n\t\t\t     **** Exit ****");
		    printf("\n\t\t\t======Thank you ==========");
		    printf("\n\t\t\t======See you soon =======");
            exit(0);
        }else
        {
            printf("Invalid selection\n");
        }
    } while (1);
}
void sortCategories(Category category[], int lengthCategory){
    char choice;
    do {
        printf("===== Sort Categories =====\n");
        printf("a. Ascending\n");
        printf("d. Descending\n");
        printf("Enter Your Selection: ");
        scanf(" %c", &choice); 
        getchar(); 
        if (choice != 'a' && choice != 'd') {
            printf("Invalid selection.\n");
        }
    } while (choice != 'a' && choice != 'd');
    if (choice == 'a') 
    { 
        for (int i = 0; i < lengthCategory - 1; i++) 
        {
            for (int j = 0; j < lengthCategory - i - 1; j++) {
                if (strcmp(category[j].categoryName, category[j + 1].categoryName) > 0) {
                    Category temp = category[j];
                    category[j] = category[j + 1];
                    category[j + 1] = temp;
                }
            }
        }
    } else if (choice == 'd') 
    {
        for (int i = 0; i < lengthCategory - 1; i++) {
            for (int j = 0; j < lengthCategory - i - 1; j++) 
            {
                if (strcmp(category[j].categoryName, category[j + 1].categoryName) < 0) 
                {
                    Category temp = category[j];
                    category[j] = category[j + 1];
                    category[j + 1] = temp;
                }
            }
        }
    }
    if (goBack(5)==1)
    {
        return;
    }
}
void itemManagement(Category category[],int lengthCategory){
    int choice;
    do {
        choice = 0;
        printf("**** Product Manager ****\n");
        printf("===== MENU Product Management =====\n");
        printf("[1] Add Product\n");
        printf("[2] Show Products\n");
        printf("[3] Edit Product\n");
        printf("[4] Delete Product\n");
        printf("[5] Search Products\n");
        printf("[6] Sort Products\n");
        printf("[7] Exit\n");
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
                addProduct(category,lengthCategory);
                break;
            /*case 2:
                if (lengthCategory==0)
                {
                    system("cls");
                    printf("no categories\n");
                    printf("===================================\n");
                }else
                {
                    system("cls");
                    printfProduct(category,lengthCategory);
                }
                break;
            case 3:
                system("cls");
                editProduct(category,lengthCategory);
                saveFile(category,product, lengthCategory, lengthStoreManager);
                break;
            case 4:
                system("cls");
                deleteProduct(category, &lengthCategory);
                saveFile(category,product, lengthCategory, lengthStoreManager);
                break;
            case 5:
                system("cls");
                searchProduct(category, lengthCategory);
                break;
            case 6:
                system("cls");
                sortProduct(category, lengthCategory);
                break;*/
            case 7:
                return;
                break;
            default:
                printf("Error! Please enter a valid option.\n");
                printf("===================================\n");
                break;
        }
    } while (choice != 7);
}
void addProduct(Category category[],int lengthCategory){
    char id[10], idcategory[10], name[10];
    int newLengthProduct;
    printf("Enter The Category Id: ");
    fgets(idcategory, sizeof(idcategory), stdin);
    idcategory[strcspn(idcategory, "\n")] = '\0';  
    for (int i = 0; i < lengthCategory; i++) {
        if (strcmp(category[i].categoryId, idcategory) == 0) {
            printf("===== Add Product =====\n");
            do {
                printf("Enter The Number Of Products To Add (1-100): ");
                scanf("%d", &newLengthProduct);
                getchar();  
            } while (checkNumber(newLengthProduct) || newLengthProduct > 100);
            for (int j = category[i].numProducts; j < category[i].numProducts + newLengthProduct; j++) {
                do {
                    printf("Enter ID for Product %d: ", j + 1);
                    fgets(id, sizeof(id), stdin);
                    id[strcspn(id, "\n")] = '\0';  
                } while (isValidString(id, 1, 10) || check(category, id, category[i].numProducts, 3));
                do {
                    printf("Enter name for Product %d: ", j + 1);
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                } while (isValidString(name, 1, 10) || check(category, name, category[i].numProducts, 4));
                strcpy(category[i].product[j].productId, id);
                strcpy(category[i].product[j].productName, name);
                do {
                    printf("Enter quantity: ");
                    scanf("%d", &category[i].product[j].quantity);
                    if (category[i].product[j].quantity > 0) {
                        break;
                    } else {
                        printf("Invalid input. Please enter a positive integer.\n");
                    }
                } while (1);
                do {
                    printf("Enter price: ");
                    scanf("%d", &category[i].product[j].price);
                    if (category[i].product[j].price > 0) {
                        break;
                    } else {
                        printf("Invalid input. Please enter a positive integer.\n");
                    }
                } while (1);
                getchar();  
            }
            category[i].numProducts += newLengthProduct;
            printf("Products added successfully to Category:\n");
            if (goBack(4)==1)
            {
                return;
            } 
        }
    }
    if (goBack(3)==1)
    {
        return;
    }
}