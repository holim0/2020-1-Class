#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<algorithm>
#define MAX 1000005
using namespace std;
int arr[60005];
int val;
vector<pair<int, int>> first;
vector<pair<int, int>> second;
vector<int> nfirst(3005);
vector<int> nsecond(3005);
int countfir[MAX] = { 0, };
int countsec[MAX] = { 0, };
int accumfir[MAX];
int accumsec[MAX];
int m, n;
int cnt = 0;
bool checkchange(){
	for (int i = 1; i <=n; i++)
	{
		if(nfirst[i]!=i || nsecond[i]!=i) return true;
	}
	
	return false; 

}
bool cntsort(int i) {

	int idx = 1;
	int fmax = 0; int smax = 0;
	for (int j = i; j < i+n; j++)
	{	
		fmax = max(fmax, arr[j]);
		first.push_back({ arr[j], idx });
		idx++;
	}
	idx = 1;
	for (int j = i+n; j < i+n+n; j++)
	{	
		smax = max(smax, arr[j]);
		second.push_back({ arr[j], idx });
		idx++;
	}

	for (int j = i; j < i + n; j++) {
		countfir[arr[j]]++;
	}

	accumfir[0] = countfir[0];

	for (int j = 1; j <= fmax; j++)
	{
		accumfir[j] = accumfir[j - 1] + countfir[j];
	}

	for (int j = i + n; j < i + n + n; j++) {
		countsec[arr[j]]++;
	}

	accumsec[0] = countsec[0];

	for (int j = 1; j <= smax; j++)
	{
		accumsec[j] = accumsec[j - 1] + countsec[j];
	}
	
	for (int j = first.size() - 1; j >= 0; j--) {
		nfirst[accumfir[first[j].first]] = first[j].second;
		accumfir[first[j].first]--;
	}
	

	for (int j = second.size()-1; j>=0; j--)
	{
		nsecond[accumsec[second[j].first]] = second[j].second;
		accumsec[second[j].first]--;
	}
	
	if(!checkchange()){
		for(int i=0; i<n-1; i++){
			if(((first[i].first==first[i+1].first) && (second[i].first!=second[i+1].first)) || ((first[i].first!=first[i+1].first) && (second[i].first==second[i+1].first))){
				first.clear(); second.clear(); nfirst.clear(); nsecond.clear();
				memset(countfir, 0, sizeof(countfir)); memset(countsec, 0, sizeof(countsec)); memset(accumfir, 0, sizeof(accumfir)); memset(accumsec, 0, sizeof(accumsec));
				return false;
			}
		}	
	}
	
	for (int j = 1; j <=n; j++)
	{
		if (nfirst[j] != nsecond[j]) {
			first.clear(); second.clear(); nfirst.clear(); nsecond.clear();
			memset(countfir, 0, sizeof(countfir)); memset(countsec, 0, sizeof(countsec)); memset(accumfir, 0, sizeof(accumfir)); memset(accumsec, 0, sizeof(accumsec));
			return false;
		}

	}

	first.clear(); second.clear(); nfirst.clear(); nsecond.clear();
	memset(countfir, 0, sizeof(countfir)); memset(countsec, 0, sizeof(countsec)); memset(accumfir, 0, sizeof(accumfir)); memset(accumsec, 0, sizeof(accumsec));
	return true;
}


int main(int argc, const char* argv[]) {

	ifstream f;
	ofstream w;

	f.open("universe.inp");
	w.open("universe.out");

	int k = 0;
	if (f.is_open()) {
		while (f >> val) {
			arr[k++] = val;
		}
	}
	
	m = arr[0]; n = arr[1];

	for (int i = 2; i < k; i+=2*n)
	{	
		if (cntsort(i)) cnt++;
	}

	w<<cnt;

	f.close();
	w.close();
	return 0;
}