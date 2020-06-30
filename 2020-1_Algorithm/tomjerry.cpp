#include<iostream>
#include<fstream>
using namespace std;
int rc[3];
bool check[12][12] = { false, };
int dx[] = { 1, 0 };
int dy[] = {0, 1};
int cnt = 0;

void go(int x, int y) {
	if (x == rc[0] - 1 && y == rc[1] - 1) {
		cnt++;
		return;
	}
	

	for (int i = 0; i < 2; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!check[nx][ny] && nx<rc[0] && ny<rc[1]) {
			check[nx][ny] = true;
			go(nx, ny);
			check[nx][ny] = false;
		}

	}
	
}
int main(int argc, const char* argv[]) {

	ifstream file;
	ofstream wf;
	file.open("tomjerry.inp");
	wf.open("tomjerry.out");
	int i = 0;
	while (!file.eof()) {
		file >> rc[i];
		i++;
	}
	
	
	check[0][0] = true;
	go(0, 0);

	wf<<cnt;

    file.close();
    wf.close();
	

	return 0;
}