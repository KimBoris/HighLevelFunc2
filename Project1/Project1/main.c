#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>




//각 항을 비교하는 함수
int MyCmp(const void* left, const void* right)
{//반환형식 int  
	// 왼쪽 오른
	//빼서 비교해서 같으면 0 
	//컴퓨터는 두 수를 비교해서 
	//*left - *right 빼준다.
	return *(int*)left - *(int*)right;
	//근데 void포인터라서 간접지정이 되지 않는다. 
	//그러므로 지정해줘야 한다. 
	//배열의 요소가 int이므로 int형으로 지정을 해줘야 한다. 
	 
}

int main(void)
{
	int aList[5] = { 20, 50, 10, 30, 40 };

	qsort(aList, 5, sizeof(int), MyCmp);
	//1. aList란 배열에 
	//2. 요소가 5개있고
	//3. 각 요소의 크기는 int
	//4. 각 항을 비교할 때 MyCmp 이런 형식으로 할 것이다.

	//그럼 정렬을 한다. 

	// ** 여기서 중요한 점 
	//qsort()라는 함수를 만든사람이 철수

	//main()함수를 만든다.
	/*
	1. main함수에서 qsort함수를 call한다.
	*/

		

	for (int i = 0; i< 5; ++i)
	{
		printf("%d\t", aList[i]);
	}
	return 0;
}


