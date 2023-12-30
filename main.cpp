#include <iostream>

#define MAX_SIZE 200000
int n, k, minHeapSize = 0, MaxHeapSize;
using namespace std;

struct omid {
    int amount;
    int position;
    bool inMAx;
} omids[MAX_SIZE];

omid minHeap[MAX_SIZE];
omid MaxHeap[MAX_SIZE];

void addMinHeap(omid i);

void addMaxHeap(omid i);

void balance();

int getMedian();

void insert(omid i);

void minHeapifyUp(omid i);

void MaxHeapifyUp(omid i);

void MaxHeapifyDown(omid i);

void minHeapifyDown(omid i);

void remove(omid i);

void swap(omid *heap, omid i, omid j);

long long int getNeededChanges(int median, int j, omid* omids);


void removeFromMax(omid i);

void removeFromMin(omid i);

int main() {
    //input
    cin >> n >> k;
    //omid* omids = (omid*) malloc(n * sizeof(omid));
    for (int i = 0; i < n; ++i) cin >> omids[i].amount;
    //build min and max heap and primary fill

    for (int i = 0; i < k; ++i) {
        insert(omids[i]);
    }

    //iterate calculate and print
    cout << getNeededChanges(getMedian(), 0, omids);

    for (int i = 0; i < (n - k); ++i) {
        insert(omids[k + i]);
        remove(omids[i]);
        cout << getNeededChanges(getMedian(), i + 1, omids);
    }
    return 0;
}

void minHeapifyUp(omid i) {
    if (0 == i.position) return;
    if (i.amount < minHeap[(i.position - 1) / 2].amount) {
        swap(minHeap, i, minHeap[(i.position - 1) / 2]);
        minHeapifyUp(i);
    }
}

void MaxHeapifyUp(omid i) {
    if (0 == i.position) return;
    if (i.amount > MaxHeap[(i.position - 1) / 2].amount) {
        swap(MaxHeap, i, MaxHeap[(i.position - 1) / 2]);
        MaxHeapifyUp(i);
    }
}

void MaxHeapifyDown(omid i) {
    int pos = i.position;
    int j = pos * 2 + 1;
    if (j > MaxHeapSize) return;
    if (j + 1 == MaxHeapSize);
    else if (MaxHeap[j].amount < MaxHeap[j + 1].amount) j += 1;
    if (MaxHeap[j].amount > MaxHeap[i.position].amount) {
        swap(MaxHeap, i, MaxHeap[j]);
        MaxHeapifyDown(i);
    }
}

void minHeapifyDown(omid i) {
    int pos = i.position;
    int j = pos * 2 + 1;
    if (j > minHeapSize) return;
    if (j + 1 == minHeapSize);
    else if (minHeap[j].amount > minHeap[j + 1].amount) j += 1;
    if (minHeap[j].amount < minHeap[i.position].amount) {
        swap(minHeap, i, minHeap[j]);
        minHeapifyDown(i);
    }
}

void remove(omid i) {
    if (i.inMAx)
        removeFromMax(i);
    else
        removeFromMin(i);
    balance();
}

void removeFromMin(omid i) {
    minHeapSize -= 1;
    omid heydari = minHeap[minHeapSize];
    swap(minHeap, i, heydari);
    minHeapifyUp(heydari);
    minHeapifyDown(heydari);
}

void removeFromMax(omid i) {
    MaxHeapSize -= 1;
    omid heydari = MaxHeap[MaxHeapSize];
    swap(MaxHeap, i, heydari);
    MaxHeapifyUp(heydari);
    MaxHeapifyDown(heydari);
}

void swap(omid *heap, omid i, omid j) { // swap place of two omid and update position
    heap[i.position] = j;
    heap[j.position] = i;
    int pos = i.position;
    i.position = j.position;
    j.position = pos;
}

long long int getNeededChanges(int median, int j, omid *omids) { // calculate Needed Changes
    long long int sum = 0;
    for (int i = j; i < j + k; ++i) sum += abs(omids[i].amount - median);
    return sum;
}

void addMaxHeap(omid i) {
    MaxHeap[MaxHeapSize] = i;
    i.inMAx = true;
    i.position = MaxHeapSize;
    MaxHeapSize = MaxHeapSize + 1;
    MaxHeapifyUp(i);
}

void addMinHeap(omid i) {
    minHeap[minHeapSize] = i;
    i.inMAx = false;
    i.position = minHeapSize;
    minHeapSize = minHeapSize + 1;
    minHeapifyUp(i);
}

void balance() {
    if (minHeapSize < MaxHeapSize - 1) {
        omid heydari = MaxHeap[0];
        remove(heydari);
        addMinHeap(heydari);
    } else if (MaxHeapSize < minHeapSize - 1) {
        omid heydari = minHeap[0];
        remove(heydari);
        addMaxHeap(heydari);
    }
}

int getMedian() {
    if (k == 1) {
        if (minHeapSize == 0)
            return MaxHeap[0].amount;
        else return minHeap[0].amount;
    }
    if (MaxHeapSize <= minHeapSize) return minHeap[0].amount;
    return MaxHeap[0].amount;
}

void insert(omid i) {//input is omid
    if (minHeapSize == 0) addMinHeap(i);
    else if (i.amount > minHeap[0].amount)
        addMinHeap(i);
    else addMaxHeap(i);
    balance();
}

