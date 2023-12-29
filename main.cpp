#include <iostream>

#define MAX_SIZE 200000
int n, k;

using namespace std;

struct {
    int amount;
    int position;
    bool inMAx;
} omid[MAX_SIZE];

struct Heap {
    int size;
    int heap[MAX_SIZE];
} minHeap, MaxHeap;

void addMinHeap(int i);

void addMaxHeap(int i);

void balance();

int getMedian();

void insert(int i);

void heapifyUp(int i);

void heapifyDown(int i);

void remove(int i);

void swap(int i, int j);

long long int getNeededChanges(int median, int j);


int main() {
    //input
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> omid[i].amount;

    //build min and max heap and primary fill
    for (int i = 0; i < k; ++i) {
        insert(i);
    }

    //iterate calculate and print
    cout << getNeededChanges(getMedian(), 0);

    for (int i = 0; i < (n - k); ++i){
        insert(k + i);
        remove(i);
        balance();
        cout << getNeededChanges(getMedian(), i + 1);
    }
    return 0;
}

void heapifyUp(int i) {
    //TODO
}

void heapifyDown(int i) {
    //TODO
}


void remove(int i) {
    //TODO
}

void swap(int i, int j) {
    //TODO
}

void addMaxHeap(int i) {
    //TODO
}

long long int getNeededChanges(int median, int j) { // calculate Needed Changes
    long long int sum = 0;
    for (int i = j; i < j + k; ++i) sum += abs(omid[i].amount - median);
    return sum;
}

void addMinHeap(int i) {
    //TODO
}

void balance() {
    //TODO
}

int getMedian() {
    if (MaxHeap.size <= minHeap.size) return minHeap.heap[0];
    return MaxHeap.heap[0];
}

void insert(int i) {
    if (omid[i].amount < minHeap.heap[0])
        addMinHeap(i);
    else addMaxHeap(i);
}





