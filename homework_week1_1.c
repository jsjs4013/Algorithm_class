#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	float avr[1000]; // 누적평균을 저장하기 위한 변수
	int x[1000]; // 입력받은 수를 int형으로 저장하기 위한 변수
	char input[1000]; // 입력을 받기위한 변수
	char* tmp[1000]; // 입력받은 변수를 잠시 저장하기위한 변수

	int count = 1; // 입력받은 수의 개수를 카운트하기 위한 변수
	int i = 1;
	float temp = 0.0; // 누적합을 저장하기위한 변수


	printf("배열을 입력해주세요 : ");
	gets(input);
	printf("\n");
	// strtok를 사용하여 사용자가 입력한 수가 몇개인지 알아내는 부분
	tmp[0] = strtok(input, " ");
	while (tmp[i] = strtok(NULL, " "))
	{
		// strtok를 사용하여 띄어쓰기 되어진 숫자들의 입력을 받아와
		// 총 몇개의 숫자가 입력되었는지 반복문을 통해 알아내는 부분

		i++;
		count++;
	}
	for (i = 0; i < count; i++)
	{
		// 임시저장된 변수들은 int형이 아니므로 atoi를 사용하여
		// 모든 임시저장된 값들을 int형으로 만들어주어 x[i]변수에 저장하는 부분

		x[i] = atoi(tmp[i]);
	}

	printf("Avr 출력\n");
	for (i = 0; i < count; i++)
	{
		// 누적합과 누적평균을 구하는 부분

		temp += x[i];
		avr[i] = temp / (i + 1);

		printf("Avr[%d]: %f\n", i, avr[i]);
	}


	return 0;
}