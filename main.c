#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct List{
    int data;
    struct List *next;
};
struct List *head;

struct Node {
    int data;
    struct Node *next;
};
struct Node *bucket[10];

void createRandomArray(int *A, int size);
void printArray(int *A, int size);
int findMax(int *A, int n);
int theNumberOfDigits(int number);
int popList();
void appendList(int data);
int popNode(int index);
void appendNode(int data, int index);
void arrayToList(int *arr, int n);
void readList();
void radixSort(int k);
int findBucketIndex(int number, int desiredDigitIndex);
void concatenateLists();

int main() {
    int n; // Size of the array
    printf("Enter the size of the array:");
    scanf("%d", &n);

    int array[n];
    createRandomArray(array, n);

    printf("Random integer array:\n");
    printArray(array, n);

    arrayToList(array, n);
    readList();

    int maxValue = findMax(array, n);
    int digits = theNumberOfDigits(maxValue);
    radixSort(digits);

    return 0;
}

void createRandomArray(int *A, int size){
    int max_value; // Maximum possible element in the array

    printf("Enter the maximum possible element in the array:");
    scanf("%d", &max_value);

    // Set the seed for the rand() function based on the current time
    srand(time(0));

    // Create and generate random integers for the array
    for (int i = 0; i < size; i++) {
        A[i] = rand() % max_value; // Generate a random number in the range [0, max_value-1]
    }
}

void printArray(int *A, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int findMax(int *A, int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

int theNumberOfDigits(int number){
    int digits = 0;
    if (number == 0){
        return 1;
    }
    while (number != 0){
        number = number / 10;
        digits += 1;
    }
    return digits;
}

void arrayToList(int *arr, int n){
    struct List *pts;
    pts = (struct List*)malloc(n * sizeof(struct List));
    for (int i = 0; i < n; i++){
        (pts + i)->data = arr[i];
        (pts + i)->next = head;
        head = pts + i;
    }
}

void readList(){
    struct List *temp;
    temp=head;
    if(temp==NULL){
        printf("empty");
        return;
    }
    printf("*****************************************************\n");
    while (temp!=NULL){
        printf("%d ", temp->data);
        temp=temp->next;
    }
    printf("\n*****************************************************\n");
}

int popList(){
    int data = head->data;
    //printf("%d ", data);
    //struct List *previous = head;
    head = head->next;
    //free(previous);
    return data;
}

int popNode(int index){
    int data = bucket[index]->data;
    //struct Node *previous = bucket[index];
    bucket[index] = bucket[index]->next;
    //free(previous);
    return data;
}

void appendList(int data){
    struct List *pts;
    pts = (struct List *) malloc(sizeof(struct List));
    pts->data = data;
    pts->next = head;
    head = pts;
}

void appendNode(int data, int index){
    struct Node *pts;
    pts = (struct Node *) malloc(sizeof(struct Node));
    pts->data = data;
    pts->next = bucket[index];
    bucket[index] = pts;
}

int findBucketIndex(int number, int desiredDigitIndex ){
    int divisor = pow(10, desiredDigitIndex);
    int modulo = number % divisor;

    int dividend = modulo;
    divisor = pow(10, desiredDigitIndex - 1);;
    int quotient = dividend / divisor;

    int index = quotient;
    return index;
}

void concatenateLists(){
    for (int i = 9; i >= 0; i--){
        while (bucket[i] != NULL){
            int number = popNode(i);
            appendList(number);
        }
    }
}

void radixSort(int k){
    for (int j = 1; j <= k; j++) {
        while (head != NULL) {
            int number = popList();
            //readList();
            int index = findBucketIndex(number, j);
            appendNode(number, index);
        }
        concatenateLists();
        printf("Pass %d: \n", j);
        readList();
    }
}
