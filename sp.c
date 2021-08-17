/*i
Create a program that accepts user input and store it in a dynamic array of structs.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Size 100
int enterNum();
int printmenu();

typedef struct{
	char name[Size];
	short int Quantity;
	double Price;
}Item;

void printinfo(Item[], int);
Item *getMemory(int);
void ReSizeArray(Item**,int);

int main(){
	char inbuf[Size];
	int o, count = 0;  
	Item *ShoppingCart;	
	printf("*********************** Procedure *************************\nCreates a dynamic array of structures with an initial size\nAllows the user to add items to the shopping cart\nPrints the current list of items when requested\n***********************************************************\n");
	int n = enterNum();
	ShoppingCart = getMemory(n);  
	do{
		o  = printmenu();
		switch(o){
		case 1:	
			// if the items in ShoppingCart is greater than the size do the RESIZE
			if (count >= n){
				ReSizeArray(&ShoppingCart,n);
				n = 2*n;
			}
			printf("Enter Name: ");
			fgets(inbuf, Size, stdin);
			sscanf(inbuf,"%[^\n]", ShoppingCart[count].name);
		
			printf("Enter Quantity: ");
			fgets(inbuf, Size, stdin);
			sscanf(inbuf,"%hi", &ShoppingCart[count].Quantity);
		
			printf("Enter Price: ");
			fgets(inbuf, Size, stdin);
			sscanf(inbuf,"%lf", &ShoppingCart[count].Price);
			count = count+1;
			// count goes up by one each time i add item to ShoppingCart
			break;	
		case 2:
			printinfo(ShoppingCart, count);
			break;
		case 3:
			break;
		default:	
			printf("ERROR! Enter a valid option! \n");
			break;
			}
	}
	while (o != 3);
	return 0;	
}

int enterNum(){
	int i = 0;
	char inbuf[Size];
	do{
		printf("Initial number of items in your shopping cart: ");
		fgets(inbuf,Size,stdin);
		int args = sscanf(inbuf,"%d",&i);		
		if(i < 1 || args < 1){
			printf("ERROR! Initial number of items MUST be an integer > 0\n");
		}
	}
	while(i<1);
	return i;
}
Item *getMemory(int n){
	Item *items = (Item*) malloc(n*sizeof(Item));
	if(items == NULL){
		printf("Error");
		exit(1);
	}
	return items;
}
void ReSizeArray(Item **pShoppingCart,int n){
	Item *dcp = getMemory(2*n);
	memcpy(dcp, *pShoppingCart, 2*n*sizeof(Item));
	free(*pShoppingCart);
	*pShoppingCart = dcp; 
}
void printinfo(Item ShoppingCart[], int n){
	int i;
	printf("\n---------- Shopping Cart ----------\n");
	for (i = 0; i<n; i++){
		printf("%s, Q:%hi each: $%f \n", ShoppingCart[i].name, ShoppingCart[i].Quantity, ShoppingCart[i].Price);	
	}
	printf("-----------------------------------\n");
}
int printmenu(){
	int o = 0;
	char inbuf[Size];
	do{
		printf("\n*************** Menu *****************\n1. Add an item to the shopping cart\n2. Print the current list of items\n3. Quit the program\n***************************************\nSelect your option: ");
		fgets(inbuf,Size,stdin);
		int args = sscanf(inbuf,"%d", &o);
		if (o < 1 || o > 3 || args<1){
			printf("ERROR! Enter a valid option!\n");
		}
	}
	while(o<1 || o>3);
	return o;
}
