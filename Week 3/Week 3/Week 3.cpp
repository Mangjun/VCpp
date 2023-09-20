#include <stdio.h>
#include <conio.h>
#include <Windows.h>

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

int main()
{
	char ch = ' '; // 사용자에게 입력 받음
	int result[100] = {}; // 입력받은 문자를 저장할 배열
	int index = 0; // 배열의 입력된 문자 수

	while (ch != 27) {
		// 문자 배열이 꽉 찬 경우 프로그램 종료
		if (index > 92) {
			break;
		} else if (index >= 5) {
				for(int i=0; i < index; i++) {

					// 좌 상 우 하
					if ((result[i] == -32 && result[i + 1] == 996) && (result[i+2] == -32 && result[i + 3] == 998) && (result[i+4] == -32 && result[i + 5] == 997) && (result[i+6] == -32 && result[i + 7] == 999)) {
						printf("\n(* v *)\n");
						clear(result, index);
						index = 0;
					}

					// 하 우 a
					if ((result[i] == -32 && result[i+1] == 999) && (result[i+2] == -32 && result[i + 3] == 997) && (char)result[i + 4] == 'a') {
						printf("\n아도겐! =o\n");
						clear(result, index);
						index = 0;
					}

					// 우 하 우 f
					if ((result[i] == -32 && result[i+1] == 997) && (result[i+2] == -32 && result[i + 3] == 999) && (result[i+4] == -32 && result[i + 5] == 997) && (char)result[i + 6] == 'f') {
						printf("\n뻐큐! ( -_-)-ㅗ\n");
						clear(result, index);
						index = 0; 
					}

				}
		}

		ch = _getch();
		
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

		Sleep(300);
	}

}