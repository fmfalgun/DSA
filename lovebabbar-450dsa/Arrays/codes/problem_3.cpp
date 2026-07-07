#include<iostream>
using namespace std;

//function which get array of arrays and print the values
void print_arr(int (*a)[2], int rows){
	cout << "\n";
	for(size_t i=0; i<rows; i++){
		for(size_t j=0; j<2; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
}

//function to get values of array of arrays from user and sort them
//using bubble sort algorithm
int (*takeInputAndSort(int &rows))[2]{

	int (*a)[2] = new int[rows][2];
	
	cout << "now provide the details of intervals\n";
	cout << "e.g:\n";
	cout << "2 4\n";
	cout << "6 9,etc\n\n";
	for(int i=0; i<rows; i++)
		cin >> a[i][0] >> a[i][1];

	for(int i=0; i<rows; i++){
		int smallest_val_pos = i;
		for(int j=i+1; j<rows; j++){	
			if (a[smallest_val_pos][0] > a[j][0])
				smallest_val_pos = j;
		}

		//logic to swap the smallest value with the present ith value
		if (smallest_val_pos == i) continue;
		int temp[2] = {a[i][0], a[i][1]};
		a[i][0] = a[smallest_val_pos][0];
		a[i][1] = a[smallest_val_pos][1];	
		a[smallest_val_pos][0] = temp[0];
		a[smallest_val_pos][1] = temp[1];
	}

	return a;
}

int main (void){


	int total_intervals;
	cout << "Give the number of intervals you have.\n";
	cin >> total_intervals;
       	cout << "\n";
	
	int (*list_of_intervals)[2] = takeInputAndSort(total_intervals);

	//logic to remove overlapping intervals
	for(int i=0; i<rows; i++)

	print_arr(list_of_intervals,total_intervals);

	delete[] list_of_intervals;
	return 0;
}
