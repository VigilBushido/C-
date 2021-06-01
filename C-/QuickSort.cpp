#include <iostream>
#include <string>
#include <vector>
using std::cout;
int len;
//Sorting in non decreasing order
void printArray(int arr[]) {
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";

	cout << "\n";
}
void swap(int arr[], int k, int small) {
	int temp;
	temp = arr[k];
	arr[k] = arr[small];
	arr[small] = temp;
}
int partition(int arr[], int i, int j) {
	int pivot = arr[j];
	int small = i - 1;

	for (int k = i; k < j; k++) {
		if (arr[k] <= pivot) {
			small++;
			swap(arr, k, small);
		}
	}

	swap(arr, j, small + 1);
	cout << "Pivot = " << arr[small + 1] << "\n";
	printArray(arr);
	return small + 1;
}
void quickSort(int arr[], int i, int j) {
	if (i < j) {
		int pos = partition(arr, i, j);
		quickSort(arr, i, pos - 1);
		quickSort(arr, pos + 1, j);
	}
}
int main() {
	int arr[] = { 6, 9, 2, 1, 10, 7, 12, 8 };
	len = sizeof(arr) / sizeof(int);
	cout << "Initial Array : ";
	printArray(arr);
	quickSort(arr, 0, len - 1);
	return 0;
}
