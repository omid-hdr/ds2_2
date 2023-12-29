#include <iostream>

#define MAX_SIZE 200000
int n, k;

using namespace std;

struct omid{
    int amount;
    int position;
    bool inMAx;
} omids[MAX_SIZE];

struct Heap {
    int size;
    omid heap[MAX_SIZE];
} minHeap, MaxHeap;

void addMinHeap(int i);

void addMaxHeap(int i);

void balance();

int getMedian();

void insert(int i);

void minHeapifyUp(int i);

void MaxHeapifyUp(int i);

void MaxHeapifyDown(int i);

void minHeapifyDown(int i);

void remove(int i);

void swap(Heap heap, int i, int j);

long long int getNeededChanges(int median, int j);


int main() {
    //input
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> omids[i].amount;

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

void minHeapifyUp(int i) {
    if (minHeap.heap[omids[i].position].amount < minHeap.heap[omids[i].position / 2].amount) {
        swap(minHeap, omids[i].position, omids[i].position / 2);
        minHeapifyUp(i);
    }
}

void MaxHeapifyUp(int i) {
    if (MaxHeap.heap[omids[i].position].amount > MaxHeap.heap[omids[i].position / 2].amount) {
        swap(MaxHeap, omids[i].position, omids[i].position / 2);
        MaxHeapifyUp(i);
    }
}

void MaxHeapifyDown(int i) {
    //TODO
}

void minHeapifyDown(int i) {
    //TODO
}


void remove(int i) {
    //TODO
}

void swap(Heap heap, int i, int j) { // swap place of two omid and update position
    omid heydari = heap.heap[i];
    heap.heap[i] = heap.heap[j];
    heap.heap[j] = heydari;
    int pos = heydari.position;
    heap.heap[i].position = heap.heap[j].position;
    heap.heap[j].position = pos;
}

long long int getNeededChanges(int median, int j) { // calculate Needed Changes
    long long int sum = 0;
    for (int i = j; i < j + k; ++i) sum += abs(omids[i].amount - median);
    return sum;
}

void addMaxHeap(int i) {
    MaxHeap.heap[MaxHeap.size] = omids[i];
    omids[i].inMAx = true;
    omids[i].position = MaxHeap.size;
    MaxHeap.size = MaxHeap.size + 1;
    MaxHeapifyUp(i);
}

void addMinHeap(int i) {
    minHeap.heap[minHeap.size] = omids[i];
    omids[i].inMAx = false;
    omids[i].position = minHeap.size;
    minHeap.size = minHeap.size + 1;
    minHeapifyUp(i);
}

void balance() { //TODO
    if (minHeap.size < MaxHeap.size - 1) {
        remove(MaxHeap.heap[0].amount);

    }
}

int getMedian() {
    if (MaxHeap.size <= minHeap.size) return minHeap.heap[0].amount;
    return MaxHeap.heap[0].amount;
}

void insert(int i) {
    if (omids[i].amount < minHeap.heap[0].amount)
        addMinHeap(i);
    else addMaxHeap(i);
}

