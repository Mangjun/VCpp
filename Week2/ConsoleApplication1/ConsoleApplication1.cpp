#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

int main()
{
    printf("--------------------\n");
    printf("  202207043 김명준\n");
    printf("--------------------\n\n");

    while (1)
    {
        char ch;

        printf("command>");
        
        ch = _getche();

        if (ch == 27) {
            break;
        }

        while (1) {
            char enter = _getch();
            if (enter == '\r') break;
        }

        printf("\n");

        switch (ch)
        {
        case 'q':
            printf("qwer 화이팅\n");
            break;
        case 'w':
            printf("과제 너무 좋다\n");
            break;
        case 'e':
            printf("담주부터 과제량 3배다\n");
            break;
        case 'r':
            printf("행복합니다\n");
            break;
        default:
            printf("잘못 입력하였습니다. 다시 입력하세요.\n");
            break;
        }

    }
    
}
