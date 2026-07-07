#include <iostream>
using namespace std;

int max_subarray_sum_raw(int arr[], int lenn){
	int max_summ=arr[0], summ=arr[0];
	for(int i=0; i<lenn; i++){
		summ = arr[i];
		for (int j=i; j<lenn; j++)
		{
			summ += arr[j];
			if (summ > max_summ) max_summ = summ;
		}
	}
	return max_summ;
}

int main(void){

	int n;
	cin >> n;

	int arr[n];
	for(int i=0; i<n; i++)
		cin >> arr[i];

	cout << max_subarray_sum_raw(arr, n);

	return 0;
}
