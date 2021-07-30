//Counting sort
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using std::cout;
void printArray(int *arr, int n) {
	for (int i = 0; i < n; i++)
		cout << *(arr + i) << " ";

	cout << "\n";
}
int* countingsort(int arr[], int N) {
	int count[11] = { 0 }; //Can store the count of positive numbers <= 10

	for (int i = 0; i < N; i++)
		count[arr[i]]++;

	for (int i = 1; i < 11; i++)
		count[i] += count[i - 1];

	cout << "Counting Array  : ";
	printArray(count, 11);
	int *output = (int*)malloc(N);

	for (int i = 0; i < N; i++) {
		int ind = count[arr[i]] - 1;
		*(output + ind) = arr[i];
		count[arr[i]]--;
	}

	return output;
}
int main() {
	int arr[] = { 10, 7, 3, 1, 9, 7, 4, 3 };
	int N = sizeof(arr) / sizeof(int);
	cout << "Initial Array   : ";
	printArray(arr, N);
	int *res = countingsort(arr, N);
	cout << "After Sorting   : ";
	printArray(res, N);
	return 0;
}