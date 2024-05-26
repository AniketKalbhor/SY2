#include <stdio.h>

#define SIZE 10
#define h(x) x % SIZE

void insert(int data[], int flag[], int chain[], int x);
void display(int data[], int flag[], int chain[]);

int main() {
    int data[SIZE], flag[SIZE], chain[SIZE], i, j, x, op, loc;

    for (i = 0; i < SIZE; i++) {
        flag[i] = 0;
        chain[i] = -1;
    }

    printf("Enter number of keys to be inserted\n");
    scanf("%d", &op);

    for (i = 0; i < op; i++) {
        printf("Enter key to be inserted\n");
        scanf("%d", &x);

        insert(data, flag, chain, x);
    }

    printf("\nHash Table:\n");
    display(data, flag, chain);

    return 0;
}

void insert(int data[], int flag[], int chain[], int x) {
    int i = 0, j, start;

    start = h(x);

    while (flag[start] && i < SIZE) {
        if (data[start] % SIZE == x % SIZE) {
            break;
        }

        i++;

        start = (start + 1) % SIZE;
    }

    if (i == SIZE) {
        printf("Hash table is full!\n");
        return;
    }

    while (chain[start] != -1) {
        start = chain[start];
        j = start;
    }

    while (flag[j] && j < SIZE) {
        j = (j + 1) % SIZE;
        i++;
    }

    if (i == SIZE) {
        printf("Hash table is full!\n");
        return;
    }

    data[j] = x;
    flag[j] = 1;

    if (j != start) {
        chain[start] = j;
    }
}

void display(int data[], int flag[], int chain[]) {
    int i;

    for (i = 0; i < SIZE; i++) {
        if (flag[i]) {
            printf("(%d) %d %d\n", i, data[i], chain[i]);
        } else {
            printf("(%d) ------\n", i);
        }
    }
}
