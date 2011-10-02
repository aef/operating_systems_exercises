#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>

void* transfer_thread(void* parameters);
int process_transfer(int from_acct, int to_acct, float amount);

float* account_balances;

struct transfer_thread_parameter_t {
    int from_account;
    int to_account;
    float amount;
};

void print_account_balances() {
    int i;

    for (i = 0; i < 3; i++) {
        printf("#%d: %f EUR\n", i + 1, account_balances[i]);
    }
}

/*
 * Insertion point
 */
int main(int argc, char** argv) {
    int i;
    pthread_t first_thread;
    pthread_t second_thread;
    struct transfer_thread_parameter_t first_params;
    struct transfer_thread_parameter_t second_params;
    
    account_balances = malloc(sizeof(float) * 3);
    
    for (i = 0; i < 10; i++) {
        account_balances[i] = 100.0f;
    }

    puts("Before:");
    print_account_balances();

    first_params.from_account = 0;
    first_params.to_account = 1;
    first_params.amount = 200.0f;

    second_params.from_account = 1;
    second_params.to_account = 2;
    second_params.amount = 100.0f;
    
    pthread_create(&first_thread, NULL, transfer_thread, (void*)&first_params);
    pthread_create(&second_thread, NULL, transfer_thread, (void*)&second_params);

    pthread_join(first_thread, NULL);
    pthread_join(second_thread, NULL);

    puts("\nAfter:");
    print_account_balances();

    free(account_balances);

    return EXIT_SUCCESS;
}

void* transfer_thread(void* parameters) {
    struct transfer_thread_parameter_t* real_parameters = (struct transfer_thread_parameter_t*)parameters;
    process_transfer(real_parameters->from_account, real_parameters->to_account, real_parameters->amount);

    return NULL;
}

int process_transfer(int from_acct, int to_acct, float amount) {
    int old_cancel_state;

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

    account_balances[from_acct] -= amount;
    account_balances[to_acct]   += amount;

    pthread_setcancelstate(old_cancel_state, NULL);

    return EXIT_SUCCESS;
}