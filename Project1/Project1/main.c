#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>




//�� ���� ���ϴ� �Լ�
int MyCmp(const void* left, const void* right)
{//��ȯ���� int  
	// ���� ����
	//���� ���ؼ� ������ 0 
	//��ǻ�ʹ� �� ���� ���ؼ� 
	//*left - *right ���ش�.
	return *(int*)left - *(int*)right;
	//�ٵ� void�����Ͷ� ���������� ���� �ʴ´�. 
	//�׷��Ƿ� ��������� �Ѵ�. 
	//�迭�� ��Ұ� int�̹Ƿ� int������ ������ ����� �Ѵ�. 
	 
}

int main(void)
{
	int aList[5] = { 20, 50, 10, 30, 40 };

	qsort(aList, 5, sizeof(int), MyCmp);
	//1. aList�� �迭�� 
	//2. ��Ұ� 5���ְ�
	//3. �� ����� ũ��� int
	//4. �� ���� ���� �� MyCmp �̷� �������� �� ���̴�.

	//�׷� ������ �Ѵ�. 

	// ** ���⼭ �߿��� �� 
	//qsort()��� �Լ��� �������� ö��

	//main()�Լ��� �����.
	/*
	1. main�Լ����� qsort�Լ��� call�Ѵ�.
	*/

		

	for (int i = 0; i< 5; ++i)
	{
		printf("%d\t", aList[i]);
	}
	return 0;
}


