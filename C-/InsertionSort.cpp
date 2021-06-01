//published
//Insertion sort
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//Sorting in non decreasing order
void printArray(int arr[], int len) {
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";

	cout << "\n";
}
void insertionsort(int arr[], int N) {
	for (int i = 1; i < N; i++) {
		int j = i - 1;
		int temp = arr[i];

		while (j >= 0 && temp < arr[j]) {
			arr[j + 1] = arr[j];
			j--;;
		}

		arr[j + 1] = temp;
		cout << "After pass " << i << "  : ";
		//Printing array after pass
		printArray(arr, N);
	}
}
int main() {
	int arr[] = { 10, 7, 3, 1, 9, 7, 4, 3 };
	int len = sizeof(arr) / sizeof(int);
	cout << "Initial Array : ";
	printArray(arr, len);
	insertionsort(arr, len);
	return 0;
}