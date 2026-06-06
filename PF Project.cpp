#include <stdio.h>

// ----------------------------------------------------
// FUNCTION PROTOTYPES
// ----------------------------------------------------
void calculateZakat(float total, float *zakat);
float inputAsset(char *name);
float sumArray(float *arr, int size);
void zakatMenu();

void calculateTax(float income, float *tax);
void taxMenu();


// ----------------------------------------------------
// MAIN FUNCTION
// ----------------------------------------------------
int main() {
    int choice;

    while (1) {
        printf("\n================ MAIN MENU ================\n");
        printf("1. Calculate Zakat\n");
        printf("2. Calculate Tax (Latest 2025-26 Slabs)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                zakatMenu();
                break;

            case 2:
                taxMenu();
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}


// ----------------------------------------------------
// ZAKAT FUNCTIONS — USE POINTERS
// ----------------------------------------------------

// returns zakat through pointer
void calculateZakat(float total, float *zakat) {
    *zakat = total * 0.025;     // 2.5%
}

// taking asset name as char pointer
float inputAsset(char *name) {
    float value;
    printf("Enter total amount for %s: ", name);
    scanf("%f", &value);
    return value;
}

// arr is pointer; uses pointer arithmetic
float sumArray(float *arr, int size) {
    float sum = 0;
    int i;

    for ( i = 0; i < size; i++) {
        sum += *(arr + i);      // pointer arithmetic
    }

    return sum;
}

void zakatMenu() {
    float assets[50];
    float *ptr = assets;    // pointer to array

    int index = 0;

    printf("\n============= ZAKAT CALCULATOR =============\n");

    *(ptr + index++) = inputAsset("Gold");
    *(ptr + index++) = inputAsset("Silver");
    *(ptr + index++) = inputAsset("Cash");
    *(ptr + index++) = inputAsset("Bank Balance");
    *(ptr + index++) = inputAsset("Business Inventory");
    *(ptr + index++) = inputAsset("Investment Property");

    // Additional user-defined assets
    int otherCount;
    printf("\nHow many OTHER assets do you want to add? ");
    scanf("%d", &otherCount);
    int i;

    for ( i = 0; i < otherCount; i++) {
        char name[30];
        printf("Enter asset name %d: ", i + 1);
        scanf("%s", name);

        *(ptr + index++) = inputAsset(name);
    }

    float total = sumArray(ptr, index);

    float zakat;
    calculateZakat(total, &zakat);     // passing pointer

    printf("\n---------------------------------------------\n");
    printf("Total Assets : %.2f PKR\n", total);
    printf("Zakat (2.5%%) : %.2f PKR\n", zakat);
    printf("---------------------------------------------\n\n");
}



// ----------------------------------------------------
// TAX FUNCTIONS — LATEST 2025–26 SLABS (Pointer Used)
// ----------------------------------------------------
void calculateTax(float income, float *tax) {

    if (income <= 600000) {
        *tax = 0;
    }
    else if (income <= 1200000) {
        *tax = (income - 600000) * 0.01;
    }
    else if (income <= 2200000) {
        *tax = 6000 + (income - 1200000) * 0.11;
    }
    else if (income <= 3200000) {
        *tax = 116000 + (income - 2200000) * 0.23;
    }
    else if (income <= 4100000) {
        *tax = 346000 + (income - 3200000) * 0.30;
    }
    else {
        *tax = 616000 + (income - 4100000) * 0.35;
    }

    // 9% surcharge for income > 10M
    if (income > 10000000) {
        float surcharge = *tax * 0.09;
        *tax += surcharge;
    }
}

void taxMenu() {
    float income, tax;

    printf("\n============== TAX CALCULATOR ==============\n");
    printf("Enter your annual TAXABLE salary income (PKR): ");
    scanf("%f", &income);

    calculateTax(income, &tax);    // passing pointer

    printf("---------------------------------------------\n");
    printf("Annual Income : %.2f PKR\n", income);
    printf("Tax Payable   : %.2f PKR\n", tax);
    printf("---------------------------------------------\n\n");
}
