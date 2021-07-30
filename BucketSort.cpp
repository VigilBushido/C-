//Bucket sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using std::cout;

void printArray(double *arr, int n) {
	for (int i = 0; i < n - 1; i++)
		cout << *(arr + i) << ", ";

	cout << *(arr + n - 1) << "]\n";
}

void bucketsort(double arr[], int N) {
	vector<vector<double> > bucket;
	bucket.resize(N);

	for (int i = 0; i < N; i++) {
		int index = (int)(N * arr[i]);
		bucket[index].push_back(arr[i]);
	}

	cout << "After sorting " << N << " buckets" << endl;

	for (int i = 0; i < N; i++) {
		sort(bucket[i].begin(), bucket[i].end());
		cout << "[";
		int size = bucket[i].size();

		for (int j = 0; j < size - 1; j++)
			cout << bucket[i][j] << ", ";

		if (size > 0)
			cout << bucket[i][size - 1];

		cout << "]\n";
	}

	int k = 0;
	//Console.WriteLine(String.Join(" ", arr));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < bucket[i].size(); j++) {
			arr[k++] = bucket[i][j];
		}
	}

	cout << "After concatenating " << N << " buckets\n" << "[";
	printArray(arr, N);
}

int main() {
	double arr[] = { 0.987, 0.678, 0.123, 0.887, 0.665, 0.432, 0.342 };
	int N = sizeof(arr) / sizeof(double);
	cout << "Initial Array  :[";
	printArray(arr, N);
	bucketsort(arr, N);
	return 0;
}