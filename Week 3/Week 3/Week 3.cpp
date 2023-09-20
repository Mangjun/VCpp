#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UP 72 // -32 + H 998
#define DOWN 80 // -32 + P 999
#define LEFT 75 // -32 + K 996
#define RIGHT 77 // -32 + M 997

int main()
{
	char ch = ' '; // 사용자에게 입력 받음
	int result[100] = {}; // 입력받은 문자를 저장할 배열
	int index = 0; // 배열의 입력된 문자 수

	while (ch != 27) {
		if (index >= 3) {
			for(int i=0; i < index; i++) {
				
				if (result[i] == 999 && result[i + 1] == 997 && (char)result[i + 2] == 'a') {
					printf("아도겐! =o\n");
					index = 0; // 배열을 비움
				}

				if (result[i] == 997 && result[i + 1] == 999 && result[i + 2] == 997 && (char)result[i + 3] == 'f') {
					printf("뻐큐! ( -_-)-ㅗ\n");
					index = 0; // 배열을 비움
				}

			}

		}

		ch = _getch();
		
		
		
		switch (ch)
		{
		case LEFT:
			printf("<-");
			result[index] = 996;
			index++;
			break;
		case RIGHT:
			printf("->");
			result[index] = 997;
			index++;
			break;
		case UP:
			printf("위");
			result[index] = 998;
			index++;
			break;
		case DOWN:
			printf("아래");
			result[index] = 999;
			index++;
			break;
		default:
			if (ch != -32) {
				printf("%c", ch);
				result[index] = ch;
				index++;
			}
			break;
		}

		Sleep(300);
	}

}