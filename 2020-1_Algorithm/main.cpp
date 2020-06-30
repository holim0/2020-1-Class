#include<iostream>
#include<fstream>
#include<string>
using namespace std;

long long arr[60005];
int val;
long long m, n;
int cnt = 0;


int main(int argc, const char* argv[]) {

	ifstream file;
	ofstream wfile;

	file.open("universe.inp");
    wfile.open("universe.out");
	
	int k = 0;
	if (file.is_open()) {
		while (file >> val) {
			arr[k++] = val;
		}
	}
	m = arr[0];
	n = arr[1];
	string first="";
	string second="";
	
	for (int i = 2; i < k; i+=m*n)
	{
		for (int j = i; j <i+n; j++)
		{
			for (int r = j+1; r < i+n; r++)
			{
				if (arr[j] == arr[r]) {
					first += '1';
				}
				else if (arr[j] > arr[r]) {
					first += '2';
				}
				else if (arr[j] < arr[r]) {
					first += '3';
				}
			}
			for (int r = j + 1; r < i + n; r++)
			{
				if (arr[j+n] == arr[r+n]) {
					second += '1';
				}
				else if (arr[j+n] > arr[r+n]) {
					second += '2';
				}
				else if (arr[j+n] < arr[r+n]) {
					second += '3';
				}
			}
			
			if (first.size()==1 &&second.size()==1&&first == second) {
				cnt++;
			}
			if (first == second) {
				first = ""; second = "";
			}
			else {
				first = ""; second = "";
				break;
			}
			
		}
	}

	wfile<<cnt;
	

	file.close();
	wfile.close();

	return 0;
}