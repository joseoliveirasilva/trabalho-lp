#pragma warning(disable : 4996)
#include<stdio.h>
#include <stdlib.h>
#include<conio.h>

#define ARRAYELEMENTS(x)  (sizeof(x) / sizeof((x)[0]))

int main()
{
	struct Date
	{
		int Day;
		int Month;
		int Year;
	};

	struct Product
	{
		char Name[20];
		int Price;
		int Code;
		int StockQuantity;
		int MinimumStockQuantity;
		struct Date CreatedOn;
	};

	struct Wharehouse
	{
		char Name[20];		
		struct Product Products[100];
	};

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

	// TODO: WTF IS THIS?!
	printf("  9. List All 'produtos que é preciso emitir uma encomenda'\n");

	printf("  0. Exit Program\n");
	printf("Option:");

	scanf_s("%d", &selection, 4);

	/* 
		TODO : Isto devia estar a ler da "a estrutura de dados onde queres armazenar" 
	*/
	struct Product DbProducts[100];
	int numberOfProducts = 0;
	struct Wharehouse DbWharehouses[100];
	int numberOfWharehouses = 0;
	/*
		--------
	*/

	switch (selection)
	{
		/*case 9:
			size_t size = ARRAYELEMENTS(DbProducts);
			printf("%d", (int)size);
			return main();*/

		case 1:
			printf("Create Product..");

			struct Product product;

			fflush(stdin);
			printf("Name: \n");
			scanf("%s", product.Name);
			
			fflush(stdin);
			printf("Code: \n");
			scanf("%d", product.Code);
			
			fflush(stdin);
			printf("price: \n");
			scanf("%d", &product.Price);
			
			fflush(stdin);
			printf("Stock Quantity: \n");
			scanf("%d", &product.StockQuantity);
			
			fflush(stdin);
			printf("Stock Quantity: \n");
			scanf("%d", &product.MinimumStockQuantity);
			
			fflush(stdin);
			printf("Created On (dd-mm-yyyy): \n");
			scanf("%d-%d-%d", &product.CreatedOn.Day, &product.CreatedOn.Month, &product.CreatedOn.Year);

			// TODO : Isto devia estar a escrever para "a estrutura de dados onde queres armazenar"
			DbProducts[numberOfProducts++] = product;

			return main();

		case 2:
			printf("Create Wharehouse..");

			struct Wharehouse wharehouse;

			fflush(stdin);
			printf("Name: \n");
			scanf("%s", wharehouse.Name);

			// TODO : Isto devia estar a escrever para "a estrutura de dados onde queres armazenar"
			DbWharehouses[numberOfWharehouses++] = wharehouse;

			return main();

		case 2:
			printf("Create Wharehouse..");

			struct Wharehouse wharehouse;

			fflush(stdin);
			printf("Name: \n");
			scanf("%s", wharehouse.Name);

			// TODO : Isto devia estar a escrever para "a estrutura de dados onde queres armazenar"
			DbWharehouses[numberOfWharehouses++] = wharehouse;

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
