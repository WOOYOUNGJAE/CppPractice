#include <iostream>
#include <vector>
#include <algorithm>

#define COMPARE_YEAR 0
#define COMPARE_MONTH 1
#define COMPARE_DAY 2


using namespace std;

struct tagInfo
{
	char czName[15];
	short sDay;
	short sMonth;
	short sYear;
};

bool SortCompare(tagInfo _tInfo0, tagInfo _tInfo1)
{
	if (_tInfo0.sYear != _tInfo1.sYear)
		return _tInfo0.sYear < _tInfo1.sYear; // 오름차순, 나이 많은 순
	else if (_tInfo0.sMonth != _tInfo1.sMonth)
		return _tInfo0.sMonth < _tInfo1.sMonth; // 나이 많은 순
	else
		return _tInfo0.sDay < _tInfo1.sDay;
}


int main()
{
	int n; // 학생 수
	cin >> n;
	// 이름 생일 월 연도

	vector<tagInfo> vecInfos = {};
	vecInfos.reserve(n); // resize X

	for (int i = 0; i < n; ++i)
	{
		cin >> vecInfos[i].sDay;
		cin >> vecInfos[i].czName;
		cin >> vecInfos[i].sMonth;
		cin >> vecInfos[i].sYear;
	}

	sort(vecInfos.begin(), vecInfos.end() - 1, SortCompare);

	for (register int i = 0; i < n; ++i)
	{
		cout << vecInfos[i].czName << endl;
	}

	return 0;
}