#include <iostream>

#define MAX_SIZE 200000
int n, k, minHeapSize = 0, MaxHeapSize = 0;

struct omid {
    int amount;
    int position;
    bool inMAx;
} omids[MAX_SIZE];

int minHeap[MAX_SIZE];
int MaxHeap[MAX_SIZE];
long long MaxSum = 0, minSum = 0;

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

void swap(int *heap, int i, int j);

long long int getCost(int median);


void removeFromMax(int i);

void removeFromMin(int i);

int main() {
    //input
    std::cin >> n >> k;
    //omid* omids = (omid*) malloc(n * sizeof(omid));
    for (int i = 0; i < n; ++i) {
        std::cin >> omids[i].amount;
    }
    //build min and max heap and primary fill

    for (int i = 0; i < k; ++i) {
        insert(i);
    }

    //iterate calculate and print
    std::cout << getCost(getMedian()) << " ";

    for (int i = 0; i < (n - k); ++i) {
        insert(k + i);
        remove(i);
        std::cout << getCost(getMedian()) << " ";
    }
    return 0;
}

void minHeapifyUp(int i) {
    if (0 == omids[i].position) return;
    if (omids[i].amount < omids[minHeap[(omids[i].position - 1) / 2]].amount) {
        swap(minHeap, i, minHeap[(omids[i].position - 1) / 2]);
        minHeapifyUp(i);
    }
}

void MaxHeapifyUp(int i) {
    if (0 == omids[i].position) return;
    if (omids[i].amount > omids[MaxHeap[(omids[i].position - 1) / 2]].amount) {
        swap(MaxHeap, i, MaxHeap[(omids[i].position - 1) / 2]);
        MaxHeapifyUp(i);
    }
}

void MaxHeapifyDown(int i) {
    int pos = omids[i].position;
    int j = pos * 2 + 1;
    if (j >= MaxHeapSize) return;
    if (j + 1 == MaxHeapSize);
    else if (omids[MaxHeap[j]].amount < omids[MaxHeap[j + 1]].amount) j += 1;
    if (omids[MaxHeap[j]].amount > omids[i].amount) {
        swap(MaxHeap, i, MaxHeap[j]);
        MaxHeapifyDown(i);
    }
}

void minHeapifyDown(int i) {
    int pos = omids[i].position;
    int j = pos * 2 + 1;
    if (j >= minHeapSize) return;
    if (j + 1 == minHeapSize);
    else if (omids[minHeap[j]].amount > omids[minHeap[j + 1]].amount) j += 1;
    if (omids[minHeap[j]].amount < omids[i].amount) {
        swap(minHeap, i, minHeap[j]);
        minHeapifyDown(i);
    }
}

void remove(int i) {
    if (omids[i].inMAx)
        removeFromMax(i);
    else
        removeFromMin(i);
    balance();
}

void removeFromMin(int i) {
    minSum -= omids[i].amount;
    minHeapSize -= 1;
    int c = minHeap[minHeapSize];
    swap(minHeap, i, minHeap[minHeapSize]);
    if (omids[c].amount < omids[minHeap[(omids[c].position - 1) / 2]].amount)
        minHeapifyUp(c);
    else
        minHeapifyDown(c);
}

void removeFromMax(int i) {
    MaxSum -= omids[i].amount;
    MaxHeapSize -= 1;
    int c = MaxHeap[MaxHeapSize];
    swap(MaxHeap, i, MaxHeap[MaxHeapSize]);
    if (omids[c].amount > omids[MaxHeap[(omids[c].position - 1) / 2]].amount)
        MaxHeapifyUp(c);
    else
        MaxHeapifyDown(c);
}

void swap(int *heap, int i, int j) { // swap place of two omid and update position
    heap[omids[i].position] = j;
    heap[omids[j].position] = i;
    int pos = omids[i].position;
    omids[i].position = omids[j].position;
    omids[j].position = pos;
}

long long int getCost(int median) { // calculate Needed Changes
    return -(MaxSum - ((long long )MaxHeapSize - (long long )minHeapSize) * (long long )median - minSum);
}

void addMaxHeap(int i) {
    MaxSum += omids[i].amount;
    MaxHeap[MaxHeapSize] = i;
    omids[i].inMAx = true;
    omids[i].position = MaxHeapSize++;
    MaxHeapifyUp(i);
}

void addMinHeap(int i) {
    minSum += omids[i].amount;
    minHeap[minHeapSize] = i;
    omids[i].inMAx = false;
    omids[i].position = minHeapSize++;
    minHeapifyUp(i);
}

void balance() {
    if (minHeapSize < MaxHeapSize - 1) {
        removeFromMax(MaxHeap[0]);
        addMinHeap(MaxHeap[MaxHeapSize]);
    } else if (MaxHeapSize < minHeapSize - 1) {
        removeFromMin(minHeap[0]);
        addMaxHeap(minHeap[minHeapSize]);
    }
}

int getMedian() {
    if (k == 1) {
        if (minHeapSize == 0)
            return omids[MaxHeap[0]].amount;
        else return omids[minHeap[0]].amount;
    }
    if (MaxHeapSize <= minHeapSize) return omids[minHeap[0]].amount;
    return omids[MaxHeap[0]].amount;
}

void insert(int i) {//input is omid
    if (minHeapSize == 0) addMinHeap(i);
    else if (omids[i].amount > omids[minHeap[0]].amount)
        addMinHeap(i);
    else addMaxHeap(i);
    balance();
}
