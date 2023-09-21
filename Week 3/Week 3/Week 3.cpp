#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <chrono>

#define UP 72 // -32 + H 998
#define DOWN 80 // -32 + P 999
#define LEFT 75 // -32 + K 996
#define RIGHT 77 // -32 + M 997

// 문자 배열을 비움
void clear(int array[], int n)
{
	for (int i = 0; i < n; i++) {
		array[i] = 0;
	}
}

void timer(std::chrono::time_point<std::chrono::system_clock>& time1, std::chrono::time_point<std::chrono::system_clock>& time2, int result[], int& index, char& ch)
{
	time2 = std::chrono::system_clock::now(); // Timer()가 호출된 시간
	std::chrono::duration<double, std::milli> elapsed_time = time2 - time1; // 입력된 시간 구하기

	if (elapsed_time.count() >= 300.0) {
		printf("\nTimeout!\n");
		// 문자 배열 초기화
		if (result[index] == -32) {
			clear(result, index);
			result[0] = -32;
			index = 1;
			ch = ' '; // 문자 초기화
		}
		else {
			clear(result, index);
			index = 0;
			ch = ' '; // 문자 초기화
		}

	}
	time1 = time2; // 시간 재설정
}

int main()
{
	char ch = ' '; // 사용자에게 입력 받음
	int result[100] = { }; // 입력받은 문자를 저장할 배열
	int index = 0; // 배열의 입력된 문자 수
	std::chrono::time_point<std::chrono::system_clock> time1, time2;

	while (ch != 27) {
		// 문자 배열이 꽉 찬 경우 프로그램 종료
		if (index > 92) {
			break;
		} else if (index >= 5) {
				for(int i=0; i < index; i++) {
					timer(time1, time2, result, index, ch);

					// 좌 상 우 하
					if ((result[i] == -32 && result[i + 1] == 996) && (result[i+2] == -32 && result[i + 3] == 998) && (result[i+4] == -32 && result[i + 5] == 997) && (result[i+6] == -32 && result[i + 7] == 999)) {
						printf("\n(* v *)\n");
						clear(result, index);
						index = 0;
						ch = ' ';
					}

					// 하 우 a
					if ((result[i] == -32 && result[i+1] == 999) && (result[i+2] == -32 && result[i + 3] == 997) && (char)result[i + 4] == 'a') {
						printf("\n아도겐! =o\n");
						clear(result, index);
						index = 0;
						ch = ' ';
					}

					// 우 하 우 f
					if ((result[i] == -32 && result[i+1] == 997) && (result[i+2] == -32 && result[i + 3] == 999) && (result[i+4] == -32 && result[i + 5] == 997) && (char)result[i + 6] == 'f') {
						printf("\n뻐큐! ( -_-)-ㅗ\n");
						clear(result, index);
						index = 0;
						ch = ' ';
					}

				}
		}

		ch = _getch();

		if (ch != ' ') {
			auto time1 = std::chrono::system_clock::now();
		}
		
		// 숫자를 준 이유는 알파벳과 구분하기 위함
		switch (ch)
		{
		case LEFT:
			if (result[index - 1] == -32) {
				printf("좌 ");
				result[index] = 996;
			}
			else {
				printf("%c ", ch);
				result[index] = ch;
			}
			index++;
			break;
		case RIGHT:
			if (result[index - 1] == -32) {
				printf("우 ");
				result[index] = 997;
			}
			else {
				printf("%c ", ch);
				result[index] = ch;
			}
			index++;
			break;
		case UP:
			if (result[index - 1] == -32) {
				printf("상 ");
				result[index] = 998;
			}
			else {
				printf("%c ", ch);
				result[index] = ch;
			}
			index++;
			break;
		case DOWN:
			if (result[index - 1] == -32) {
				printf("하 ");
				result[index] = 999;
			}
			else {
				printf("%c ", ch);
				result[index] = ch;
			}
			index++;
			break;
		default:
			if (ch != -32) {
				printf("%c ", ch);
				result[index] = ch;
			}
			else {
				result[index] = ch;
			}
			index++;
			break;
		}

	}

}