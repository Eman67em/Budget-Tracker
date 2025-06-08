#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100

typedef struct {
    char category[30];
    double amount;
    char date[15];
} Expense;

typedef struct {
    double income;
    Expense expenses[MAX_EXPENSES];
    int expense_count;
} Budget;

// Function declarations
void add_income(Budget* budget);
void add_expense(Budget* budget);
void show_summary(Budget* budget);
void load_budget(Budget* budget);
void save_budget(Budget* budget);
void show_menu();

void add_income(Budget* budget) {
    double income;
    printf("Enter your monthly income: ");
    scanf("%lf", &income);
    budget->income = income;
    printf("Income saved successfully.\n");
}

void add_expense(Budget* budget) {
    if (budget->expense_count >= MAX_EXPENSES) {
        printf("Maximum number of expenses reached!\n");
        return;
    }

    Expense e;
    printf("Enter category (e.g., Food): ");
    scanf("%s", e.category);
    printf("Enter amount: ");
    scanf("%lf", &e.amount);
    printf("Enter date (e.g., 2025-06-09): ");
    scanf("%s", e.date);

    budget->expenses[budget->expense_count++] = e;
    printf("Expense added successfully.\n");
}

void show_summary(Budget* budget) {
    double total = 0;
    printf("\n--- Expense Summary ---\n");
    for (int i = 0; i < budget->expense_count; i++) {
        printf("Category: %s | Amount: %.2lf | Date: %s\n",
               budget->expenses[i].category,
               budget->expenses[i].amount,
               budget->expenses[i].date);
        total += budget->expenses[i].amount;
    }
    printf("Total Income: %.2lf\n", budget->income);
    printf("Total Expenses: %.2lf\n", total);
    printf("Remaining Balance: %.2lf\n", budget->income - total);
}

void load_budget(Budget* budget) {
    budget->income = 0;
    budget->expense_count = 0;

    FILE* f = fopen("budget_data.txt", "r");
    if (!f) return;

    fscanf(f, "%lf\n", &budget->income);
    while (fscanf(f, "%s %lf %s\n", budget->expenses[budget->expense_count].category,
           &budget->expenses[budget->expense_count].amount,
           budget->expenses[budget->expense_count].date) == 3) {
        budget->expense_count++;
    }

    fclose(f);
}

void save_budget(Budget* budget) {
    FILE* f = fopen("budget_data.txt", "w");
    if (!f) return;

    fprintf(f, "%.2lf\n", budget->income);
    for (int i = 0; i < budget->expense_count; i++) {
        fprintf(f, "%s %.2lf %s\n", budget->expenses[i].category,
                budget->expenses[i].amount,
                budget->expenses[i].date);
    }

    fclose(f);
}

void show_menu() {
    printf("\n--- Budget Tracker Menu ---\n");
    printf("1. Add Income\n");
    printf("2. Add Expense\n");
    printf("3. Show Summary\n");
    printf("4. Save Data\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main() {
    Budget budget;
    load_budget(&budget);

    int choice;
    do {
        show_menu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                add_income(&budget);
                break;
            case 2:
                add_expense(&budget);
                break;
            case 3:
                show_summary(&budget);
                break;
            case 4:
                save_budget(&budget);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (choice != 0);

    return 0;
}
