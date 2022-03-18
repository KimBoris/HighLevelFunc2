#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>









/*
<함수 포인터의 역호출 구조 (call back)>

- Pointer > 주소 저장을 위한 '''형식''' = 중요한 것은 포인터 변수가 중요한것이 아니라 가리키는 대상이 중요
- '''형식''' = 자료형에는 '함수형'이라는 것도 있다.
- 함수 이름 = '메모리의 주소' > 당연히 포인터에 담을 수 있다.


< 함수 포인터 해석 >

(ex)
int main(void)
{
	void *pData = main;
	printf("%p\n", pData);
	printf("%p\n", main);
	 =  둘다 같은 말이며 같은 주소값이 나옴

	 return 0;
}

	- 변수도 함수도 사실 다 주소로 식별됨.
	- 다만, 그 주소의 메모리를 어떻게 활용할 것인지가 다르다.
		1. 저장 공간으로 활용
		2. CPU가 인식하는 명령코드
		이 두가지가 다를 뿐이다.








	<함수 포인터>

	- 반환 자료형 ( 호출 규칙 * 변수이름)(매개 변수)

	형태 = int (*이름)(char*)

int TestFunc (char *pszParam)
  {
	return 0;
  }

int main(void)
{
	TestFunc("");
	int nData = (int)TestFunc; (형변환만 해주면)

	= ((int(*)(char*))nData)("");    > (int(*)(*char)  > 형태가 같다. 
	return 0;

}


	(ex)
	- int 매개변수 3개를 받아 int자료형을 반환하는 함수포인터의 선언 및 정의
	int(__cdecl *pfGetMax)(int,int,int) = GetMax;

	printf("Max : %d\n " , pfGetMax(1,3,2)); = Max : 3출력
	return 0; 
	//함수 포인터를 이용해 함수를 호출

	> 다차원 배열에 대한 포인터 처럼 (호출 규칙 *이름)이 괄호로 묶여 복잡해 보이는 것일 뿐
	 나머지는 함수 본래의 반환 자료형과 매개변수 자료형을 그대로 기술하면 된다.



	 * 함수 호출 연산자 ->  (), 형식 = 주소 (매개변수), 주소 = 함수이름
	 ex) 'printf(상수)'와 함수 포인터 변수인 pfGetMax 는 함수호출 연산자의 피 호출연산자 이다.

	 ex)예제

	 int TestFunc(char *pszParam)
	 {
		return 0;
     }

	 void MyTest(int (*pfTest)(char*), int nParam)
	 {
	 }

	 int main(void)
	 {
		MyTest(TestFunc, 10);  > 함수를 매개변수로 
		return;
	 }

	 



	 <역 호출 함수> (중요)

	 형태 - Void qsort(void *base, size_t num, size_t width, int(__cdecl *compare, const void*, const void*)

	 인자 base - 정렬 대상 배열의 기준 주소
		  num  - 배열 요소의 개수
		 width - 배열 요소의 바이트 단위 크기
		compare - 각 요소를 비교하여 같을 경우 0, 그렇지 않을 경우 양수, 음수를 반환하는 함수의 주소

	반환값 - 없음

	설명 - 퀵 정렬 알고리즘을 이요하여 배열에 담긴 요소를 정의하는 함수
		 - 사용자 정의 콜백 함수를 만들어 인수를 전달하는 방식으로 각 항을 비교하는 방법을 구체화 한다.

		 *네번째 매개변수 = Const void* 둘을 매개변수로 받고 int형 자료를 반환하는 함수에 대한 포인터
		 
		 -이에 상응하는 '사용자 정의함수'를 만들고 '이름(주소)'를 전달해야 한다. 
		 ( why? - 연산 방식이 각자 다르기때문에 '정수' '문자열' '그림' 등등)
		 



		 <Call Back>

		 다른 해석 >  함수 주소를 '등록한다' 는 개념을 가지면 쉽다.

		 1. 등록을 받는 쪽에서 주소를 아니까 call해준다.

		 2. 그래서 등록을 하면 '함수'자체는 내가 능동적으로 call하는 것이였는데
		 
		 3. 이 등록을 해놓은 대상으로부터 'called'가 된다.

		 4. 등록하는 대상이 FrameWork이면 'Called by framework'가 된다.
			그런데, 함수를 내가 만들긴 했지만 'called by framework'이면 내가 호출을 하지 않고
			framework가 때되면 알아서 부른다.





	<qsort함수>
	
	(ex)예시

	int MyCmp(Const void * left, const void * right) 좌우 비교해서 정렬하는것
	{
		- 반환 형식 = int
		- 컴퓨터는 수를 비교할때 두수를 빼기하여 비교
		- 0이라면 수가 같다 는 뜻이겠지?

		그러므로 연산할때에
		//1. *left - *right를 빼준다
		//2. 근데 *left - *right 이식을 사용하고 싶으나
		void형이기 때문에 간접지정이 되지 않는다. 따라서, 형변환을 해준다음 연산한다.
		* 배열요소가 int형이므로 '지정'을 해줘야 한다.
		
		return *(int*)left - *(int*)right;

	}

	int main(void)
	{
		int aList[5] = { 20, 50, 10, 30, 40 };

		qsort(aList, 5, sizeof(int), MyCmp);
		[ aList란 배열에 요소가 5개 있고 각 요소의 크기는 int 각 항을 비교할때 MyCmp형식으로 한다 ]

		for(int i = 0; i< 5; i++)
		{
			printf("%d\n", aList[i]);  > 정렬된 상태로 10, 20, 30, 40, 50이 나온다.
		}
		return 0;

	}



		[위 코드에서 중요한 부분]

		영희와 철수가 코드를 만들었다.

		       영 희			|        철 수
							|
		MyCmp()				|	qsort() - qsort제작
		{}					|
							|	MyCmp형식으로 비교한다면 주소를 알기에 Call Back 을 할 수 있다.
		main()				|
		{                   |
		 여기서 qsort()호출  |
		}					|
							|
						
		[순서도]			
		1. '철수' = qsort제작
		2. '영희' = main 제작
		3. 영희가 만든 MyCmp함수를 철수가 만든 qsort함수의 매개변수로 활용
		4. 영희가 main()함수에서 qsort를 Call
		5. Call함수를 호출하면서 매개변수 MyCmp의 주소를 넘김
		6. 주소를 qsort()함수가 넘겨받아 어디인지 알기 때문에 CallBack할 수 있다.
		7. 철수가 만든 함수에서 부른다.
		8. 영희가 MyCmp를 만들었지만 영희가 호출하지는 안흔ㄴ다.
		* 함수주소를 등록한다고 생각하면 쉽다는것이 이런것이다.
		 
		* MyCmp함수를 언제 몇회나 호출할 것이냐?
		> 철수가 코드를 짜놓은 방식에 따라 달라진다.

		즉, 내가만든 함수를 내가 안부른다.
		( 콜백함수가 어려운 이유. > 흐름이 끊기기 때문)



		<콜백함수 정리>
		1. 함수 주소 > 등록한다.
		2. 주소를 받은쪽에서 주소를 아니까 Call 해준다.
		- 등록을 하면 '함수'자체가 내가 능동적으로 Call하는 것이였는데
		이 등록을 해놓은 대상으로 부터 Called가 도니다.
		> 만약 등록하는 대상이 framework라면 'called by framework'가 된다. 

		> 함수를 내가 만들긴 했지만, 내가 호출은 따로 하지 않고 
		프레임 워크가 필요하면, 때되면 부른다.
		(이 함수가 언제 물리는지 나도 모른다.) 

		- 함수의 주소를 등록한다는 이 개념을 들고가자
		- 자동으로 호출 된다.


							
		


		<Why? 콜백을 알아야 하나>

		[User]  1. 프로그램을 켠다.
				2. 이 내부에 있는 함수의 주소를 운영체제에게 넘겨준다 (등록시킨다)
				3. 함수를 제외한 코드는 User모드에서 작동시킨다.
				4. But, 등록한 저 함수는 Os가 주기적으로 Call한다. ( 이런것이 콜백 구조임 )
		----------------------------
		[Kernel]
		5. 그럼
		 (1) - 언제 부르니?
		 (2) - 몇 번이나 부르니?
		 (3) - 왜 불렀니?

		 6. 결정적으로 함수는 내가 작성하였지만 Kernel의 소유에서 호출된다.
		 7. 그러니까 프로그램을 개발하는데 그 흐름이라는 것은 kernel수준에서 결정나 있는것이고
		 8. 함수를 만들어서 얘가 정한 규칙대로 등록을 해놓으면 때 되면 호출된다.

		 -Framework를 이해하는데 있어 가장 중요한 것.
		 * Callback 같은 호출 행위는 '비 동기적인'특징을 가진다.
		 * 함수의 주소를 '등록'한다 = 내가 call 하는것이 아닌 called가 된다.
		 * 고성능 코드를 이야기하면 -> call back구조로 짠다. > '비동기 처리'를 해야하므로
		 



		 ***중요***
		 <그렇다면 qsort함수를 왜 callback함수로 만들까?>

		 (ex)
		 char* aList[5] = {"김", "박", "이", "최", "정"};

		 qsort(aList, 5, sizeof(int), MyCmp);
		  - 이것은 MyCmp를 가지고 정렬을 시키면 정렬이 안됨.
		  - why? > '문자열'이므로 return *(int*)left - *(int*)right 이렇게 연산하면 안된다.

		  -> left를 이루고 있는것 자체가 '배열을 이루고 있는 char 포인터' 형태이다
		     left자체가 'char포인터'라는 뜻
			 *이것을 *(char**)left 형태로 바꾼다.
			 > 문자열 이기에 return strcmp(*(char**)left, *(char**)right); 형식으로 바꿔줘야한다.

			 [만약 '그림'내부의 사람을 수를 구하라면]
			 - 그림을 추출해서 사람을 파악하고 결과값을 낸다. 
			 즉, 여기서 하고싶은 말은 정렬과 자료형은 별도라는 것이다. 
			 정렬을 해줄테니 비교하는 방식을 형식에 맞게 사용자가 만들어서 사용하라는것
			
			'정렬 규칙'을 줄테니 '비교 규칙'은 너가 정해라 (원하는 자료에 따라서 ) - qsort 함수가 callback함수로 구성된 이유

			Callback = 인터페이스이다.
		 


*/



/*

	<함수 포인터 + 배열>

	Look up 배열을 기억하니?

	(함수 포인터 + LookUp 배열을 활용하면 (Switch-case = 느림)문을 완벽 대응할 수 있다.
	 -> 완전히 성능이 좋은 코드가 나온다.

	 ex) 
	 void Test1(int nParam)
	 {
		puts("Hello_Test1);
	 }	 
	 void Test2(int nParam)
	 {
		puts("Hell_Test2);
	 }
	 void Test3(int nParam)
	 {
		puts("Helo_Test3);
	 }


	 int main(void)
	 {
		void (*pfList[3])(int) = {Test1, Test2, Test3};

		pfList[1](10); > pf리스트의 1번째를 호출해줘, 매개변수 10

		int nInput;
		scanf_s("%d\n", nInput);
		pfList[nInput](10);   
		//이렇게 코드를 작성하면 Switch-case문을 거치지 않고 할 수 있다. (성능이 올라감)

		return 0;
	}



	<정리>
	void (*pfList[3])(int) = {Test1, Test2, Test3};
	-> Switch-case문 삭제를 위해 사용
	-> 성능이 확 빨라짐
	-> 누군가에게 원하는 기능이 있으면 함수로 만들어서 주소를 나에게 넘겨!
		그리곤 집어넣고 call하는것이 가능함.



		*/
	













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



	for (int i = 0; i < 5; ++i)
	{
		printf("%d\t", aList[i]);
	}
	return 0;
}


