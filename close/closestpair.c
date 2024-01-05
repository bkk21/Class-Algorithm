// 주어진 점 집합에서 가장 작은 거리를 찾기 위한 C/C++의 분할 정복 프로그램
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>

// 2D 평면에서 Point를 나타내는 구조체
typedef struct Point
{
	int x, y;
	
} Point;

// 라이브러리 함수 qsort()에는 다음 두 함수가 필요

// X 좌표에 따라 점 배열을 정렬하는 데 필요
int compareX(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x - p2->x);
}
// Y 좌표에 따라 포인트 배열을 정렬하는 데 필요
int compareY(const void* a, const void* b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y - p2->y);
}

// 두 점 사이의 거리를 찾는 유틸리티 함수
float dist(Point p1, Point p2)
{
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
				(p1.y - p2.y)*(p1.y - p2.y)
			);
}

// n 크기의 P[]에서 두 점 사이의 최소 거리를 반환하는 
// Brute Force 방법

float bruteForce(Point P[], int n)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
}

// 최소 두 개의 float 값을 찾는 유틸리티 함수
float min(float x, float y)
{
	return (x < y)? x : y;
}


// 주어진 크기의 스트립의 가장 가까운 점 사이의 거리를 찾는 유틸리티 함수.
// strip[]의 모든 점은 y 좌표에 따라 정렬됩니다.
// 그들은 모두 최소 거리의 상한을 d로 갖습니다.
// 이 방법은  O(n^2) 메서드처럼 보이지만 내부 루프가 
// 최대 6번 실행되므로 O(n) 메서드입니다.

float stripClosest(Point strip[], int size, float d)
{
	float min = d; // Initialize the minimum distance as d

	qsort(strip, size, sizeof(Point), compareY);

     // 모든 점을 하나씩 선택하고 y 좌표의 차이가 d보다 작아질 때까지 
	 // 다음 점을 시도합니다.
     // 이것은 이 루프가 최대 6번 실행된다는 것이 입증된 사실입니다.
	for (int i = 0; i < size; ++i)
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
			if (dist(strip[i],strip[j]) < min)
				min = dist(strip[i], strip[j]);

	return min;
}

// 최소 거리를 찾는 재귀 함수. 
// 배열 P는 x 좌표에 따라 정렬된 모든 점을 포함합니다.
float closestpair(Point P[], int n)
{
     // 점이 2개 또는 3개이면 Brute Force를 사용합니다.
	if (n <= 3)
		return bruteForce(P, n);

    // 중간점 찾기
	int mid = n/2;
	Point midPoint = P[mid];

    // 중간점을 지나는 수직선을 고려하여 중간점 왼쪽에서 
	// 가장 작은 거리 dl과 오른쪽에서 dr을 계산
	float dl = closestpair(P, mid);
	float dr = closestpair(P + mid, n-mid);

    // 두 거리 중 더 작은 거리 찾기
	float d = min(dl, dr);

    // 가운데 점을 통과하는 선에 가까운(d보다 가까운) 점을 
	// 포함하는 strip[] 배열을 만듭니다.

	Point strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(P[i].x - midPoint.x) < d)
			strip[j] = P[i], j++;

    // 스트립에서 가장 가까운 점을 찾습니다. d의 최소값을 반환하고 가장 가까운 거리는 strip[]입니다.
	return min(d, stripClosest(strip, j, d) );
}

// Driver program to test above functions
int main()
{
	Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
	int n = sizeof(P) / sizeof(P[0]);


	qsort(P, n, sizeof(Point), compareX);
	for(int i = 0; i < n ; i++)
			printf("%d:(%d,%d)\n", i,P[i].x,P[i].y);

	printf("The smallest distance is %f ", closestpair(P, n));
	return 0;
}

