//Changes
//Heap Sort
#include <iostream>
#include <string>
#include <vector>
using std::cout;
void printArray(int arr[], int len) {
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";

	cout << "\n";
}
class MaxHeap {

public:
	int len;
	int *arr;
	MaxHeap(int l, int a[]);
};
MaxHeap::MaxHeap(int l, int a[]) {
	len = l;
	arr = a;
}
void swap(int *i, int *j) {
	int temp = *i;
	*i = *j;
	*j = temp;
}
MaxHeap heapify(MaxHeap maxheap, int N) {
	int largest = N;
	int left = 2 * N + 1;
	int right = 2 * N + 2;

	if (left < maxheap.len && maxheap.arr[left] > maxheap.arr[largest]) {
		largest = left;
	}

	if (right < maxheap.len && maxheap.arr[right] > maxheap.arr[largest]) {
		largest = right;
	}

	if (largest != N) {
		swap(&maxheap.arr[largest], &maxheap.arr[N]);
		heapify(maxheap, largest);
	}

	return maxheap;
}
MaxHeap createHeap(int arr[], int N) {
	MaxHeap maxheap(N, arr);
	int i = (maxheap.len - 2) / 2;

	while (i >= 0) {
		maxheap = heapify(maxheap, i);
		i--;
	}

	return maxheap;
}
void heapsort(int arr[], int N) {
	//creating a heap
	MaxHeap heap = createHeap(arr, N);

	//Repeating the below steps till the size of the heap is 1.
	while (heap.len > 1) {
		//Replacing largest element with the last item of the heap
		swap(&heap.arr[0], &heap.arr[heap.len - 1]);
		heap.len--;//Reducing the heap size by 1
		heapify(heap, 0);
	}
}
int main() {
	int arr[] = { 9, 4, 8, 3, 1, 2, 5 };
	int len = sizeof(arr) / sizeof(int);
	cout << "Initial Array  : ";
	printArray(arr, len);
	heapsort(arr, len);
	cout << "After Sorting  : ";
	printArray(arr, len);
	return 0;
}
