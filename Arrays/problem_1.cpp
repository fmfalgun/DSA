#include <iostream>
using namespace std;

int* two_sum(int* arr, int arr_len, int target){
	int* result = new int[2];
	int temp;
	bool found = false;
	for (int i=0;i<arr_len;i++){
		//cout << "i = " << i << "\n";
		temp = arr[i];
		for (int j=i+1; j<arr_len;j++){
			//cout << "j = " << j << "\n";
			if (temp+arr[j] == target){
				//cout << temp << "," << arr[j] << "\n";
				//cout << i << "," << j << "\n";
				result[0] = i;
				result[1] = j;
				found = true;
			}
			if (found) break;
		}
		if (found) break;
	}

	return result;
}

int main (void){

	int lenn,arr_len, target;
	cin >> arr_len >> target;
	int arr[arr_len];
	lenn = arr_len;

	while(lenn--)
		cin >> arr[arr_len - lenn -1];
	int* result = two_sum(arr,arr_len,target);
	
	cout << "[ ";
	for (int i=0; i<2; i++) cout << result[i] << ", ";
	cout << "]\n";
	delete[] result;

	return 0;
}
