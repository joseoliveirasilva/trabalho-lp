#pragma warning(disable : 4996)
#include<stdio.h>
#include <stdlib.h>
#include <string.h>  /* strcpy */
#include<conio.h>

#include "uthash.h"

struct Date
{
	int Day;
	int Month;
	int Year;
};

struct Product
{
	int id;
	char Name[20];
	int Price;
	int MinimumStockQuantity;
	UT_hash_handle hh;         /* makes this structure hashable */
};
typedef struct Product P;

struct Wharehouse
{
	int id;
	char Name[20];
	UT_hash_handle hh;         /* makes this structure hashable */
};

struct WharehouseProduct
{
	char id[50];
	int WharehouseId;
	int ProductId;
	int Quantity;
	UT_hash_handle hh;         /* makes this structure hashable */
};


struct Product* HashProducts = NULL;    /* important! initialize to NULL */
struct Wharehouse* HashWharehouses = NULL;    /* important! initialize to NULL */
struct WharehouseProduct* HashWharehouseProducts = NULL;    /* important! initialize to NULL */



void add_product(struct Product* product) {

	HASH_ADD_INT(HashProducts, id, product);  /* id: name of key field */
}

struct Product* find_product(int product_id)
{
	struct Product* s;

	HASH_FIND_INT(HashProducts, &product_id, s);
	return s;
}

void add_wharehouse(struct Wharehouse* wharehouse) {

	HASH_ADD_INT(HashWharehouses, id, wharehouse);  /* id: name of key field */
}

struct Wharehouse* find_wharehouse(int wharehouse_id)
{
	struct Wharehouse* s;

	HASH_FIND_INT(HashWharehouses, &wharehouse_id, s);
	return s;
}

void add_wharehouseproduct(struct WharehouseProduct* wharehouseProduct) {

	HASH_ADD_STR(HashWharehouseProducts, id, wharehouseProduct);  /* id: name of key field */
}

struct WharehouseProduct* find_wharehouseproduct(char wharehouseproduct_id[50])
{
	struct WharehouseProduct* s;

	HASH_FIND_STR(HashWharehouseProducts, wharehouseproduct_id, s);
	return s;
}


int main()
{
	int selection = 0;

	printf("\nWharehouse Management Menu:\n");
	printf("  1. Create Product\n");
	printf("  2. Create Wharehouse\n");

	printf("  3. Receive Order (entrada de produto)\n");
	printf("  4. Create Shipping Note (saída de produto)\n");

	printf("  5. View Product Details\n");
	printf("  6. Edit Product Details\n");


	printf("  7. List All Products\n");
	printf("  8. List All Wharehouses\n");

	printf("  9. List All 'produtos que é preciso emitir uma encomenda'\n");

	printf("  10. 'Dar baixa de um produto'\n");

	printf("  0. Exit Program\n");
	printf("Option:");

	scanf_s("%d", &selection, 4);


	int productId;
	int wharehouseId;
	int quantity;

	switch (selection)
	{
	case 1:
		printf("Create Product..\n");

		P* addProduct = malloc(sizeof(P));

		printf("ID: ");
		scanf_s("%d", &addProduct->id);

		fflush(stdin);
		printf("Name: ");
		scanf("%s", addProduct->Name);

		fflush(stdin);
		printf("Price: ");
		scanf("%d", &addProduct->Price);

		fflush(stdin);
		printf("Min Stock Quantity: ");
		scanf("%d", &addProduct->MinimumStockQuantity);

		add_product(addProduct);

		return main();

	case 2:
		printf("Create Wharehouse..\n");

		struct Wharehouse* wharehouse = malloc(sizeof(struct Wharehouse));

		printf("ID: ");
		scanf_s("%d", &wharehouse->id);

		fflush(stdin);
		printf("Name: ");
		scanf("%s", wharehouse->Name);

		add_wharehouse(wharehouse);

		return main();

	case 3:
		printf("Receive Order (entrada de produto)..\n");
		
		fflush(stdin);
		printf("Product ID: ");
		scanf("%d", &productId);

		fflush(stdin);
		printf("Wharehouse Id: ");
		scanf("%d", &wharehouseId);

		fflush(stdin);
		printf("Received Quantity: ");
		scanf("%d", &quantity);


		P* product1 = find_product(productId);
		struct Wharehouse* wharehouse1 = find_wharehouse(wharehouseId);

		if (wharehouse1 != NULL && product1 != NULL)
		{
			char wharehouseproductId[50];

			sprintf(wharehouseproductId, "%d_%d", wharehouseId, productId);


			struct WharehouseProduct* wharehouseproduct = find_wharehouseproduct(wharehouseproductId);
			if (wharehouseproduct != NULL)
			{
				wharehouseproduct->Quantity += quantity;
			}
			else
			{
				wharehouseproduct = malloc(sizeof(struct WharehouseProduct));
				strcpy(wharehouseproduct->id, wharehouseproductId);
				wharehouseproduct->WharehouseId = wharehouseId;
				wharehouseproduct->ProductId = productId;
				wharehouseproduct->Quantity = quantity;

				add_wharehouseproduct(wharehouseproduct);
			}
		}

		return main();

	case 4:
		printf("4. Create Shipping Note (saída de produto)\n");

		fflush(stdin);
		printf("Product ID: ");
		scanf("%d", &productId);

		fflush(stdin);
		printf("Wharehouse Id: ");
		scanf("%d", &wharehouseId);

		fflush(stdin);
		printf("Shipping Quantity: ");
		scanf("%d", &quantity);


		P* product2 = find_product(productId);
		struct Wharehouse* wharehouse2 = find_wharehouse(wharehouseId);

		if (wharehouse2 != NULL && product2 != NULL)
		{
			char wharehouseproductId[50];
			sprintf(wharehouseproductId, "%d_%d", wharehouseId, productId);

			struct WharehouseProduct* wharehouseproduct = find_wharehouseproduct(wharehouseproductId);
			if (wharehouseproduct != NULL)
			{
				if (wharehouseproduct->Quantity >= quantity)
				{
					wharehouseproduct->Quantity -= quantity;
				}
				else
				{
					printf("Not enough quantity in stock to ship! :(");
				}
			}
			else
			{
				printf("There's no stock in that wharehouse! :(");
			}
		}

		return main();

	case 5:
		printf("5. View Product Details\n");

		fflush(stdin);
		printf("Product ID: ");
		scanf("%d", &productId);

		P* productView = find_product(productId);

		if (productView != NULL)
		{
			printf("Product:\n Id: %d\n Name: %s\n Price: %d\n Min Stock: %d\n", productView->id, productView->Name, productView->Price, productView->MinimumStockQuantity);
		}
		else
		{
			printf("The product doesn't exist! :(");
		}

		return main();

	case 6:
		printf("6. Edit Product Details\n");

		fflush(stdin);
		printf("Product ID: ");
		scanf("%d", &productId);

		P* productEdit = find_product(productId);

		if (productEdit != NULL)
		{
			fflush(stdin);
			printf("Name: ");
			scanf("%s", productEdit->Name);

			fflush(stdin);
			printf("Price: ");
			scanf("%d", &productEdit->Price);

			fflush(stdin);
			printf("Min Stock Quantity: ");
			scanf("%d", &productEdit->MinimumStockQuantity);
		}
		else
		{
			printf("The product doesn't exist! :(");
		}

		return main();

	case 7:
		printf("7. List All Products\n");

		struct Product* p;

		for (p = HashProducts; p != NULL; p = (struct Product*)(p->hh.next))
		{
			printf("Product:\n Id: %d\n Name: %s\n Price: %d\n Min Stock: %d\n", p->id, p->Name, p->Price, p->MinimumStockQuantity);
		}

		return main();

	case 8:
		printf("8. List All Wharehouses\n");

		struct Wharehouse* w;

		for (w = HashWharehouses; w != NULL; w = (struct Wharehouse*)(w->hh.next))
		{
			printf("Wharehouse:\n Id: %d\n Name: %s\n", w->id, w->Name);
		}

		return main();

	case 9:
		printf("9. List All 'produtos que é preciso emitir uma encomenda'\n");

		for (w = HashWharehouses; w != NULL; w = (struct Wharehouse*)(w->hh.next))
		{
			printf(" - Wharehouse %s (%d): ", w->Name, w->id);

			int hasProductsToOrder = 0;

			for (p = HashProducts; p != NULL; p = (struct Product*)(p->hh.next))
			{
				char wharehouseproductId[50];
				sprintf(wharehouseproductId, "%d_%d", w->id, p->id);

				struct WharehouseProduct* wharehouseproduct = find_wharehouseproduct(wharehouseproductId);
				if (wharehouseproduct != NULL && wharehouseproduct->Quantity < p->MinimumStockQuantity)
				{
					printf(" - Product: %s (%d) | Current Stock: %d (Min: %d)", p->Name, p->id, wharehouseproduct->Quantity, p->MinimumStockQuantity);
					hasProductsToOrder = 1;
				}
			}

			if (!hasProductsToOrder)
			{
				printf(" * No need to order any product!");
			}
		}

		return main();

	case 10:
		// TODO
		printf("'Dar baixa de um produto'\n");
		printf("TODO....\n");
		return main();

		// EXIT
	case 0:
		printf("Exiting Program\n");
		return 0;

		// ERROR
	default:
		printf("Invalid Choice\n");
		return main();
	}

	return main();
}
