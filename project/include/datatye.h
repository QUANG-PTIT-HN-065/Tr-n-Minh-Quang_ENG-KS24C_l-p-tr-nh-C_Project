#include<stdbool.h>
typedef struct 
{
    char productId[10];
    char categoryId[10];
    char productName[10];
    int quantity;
    int price;
}Product;
typedef struct 
{
    int day,month,year;
}Date;
typedef struct 
{
    char categoryId[10];
    char categoryName[10];
    Product product[100];
    int numProducts;
}Category;
typedef struct 
{
    char orderId[10];
    char sustomerId[20];
    Date date;
    Product product;
}Order;
typedef struct 
{
    char namelogIn[10];
    char pass[10];
}Accounts;