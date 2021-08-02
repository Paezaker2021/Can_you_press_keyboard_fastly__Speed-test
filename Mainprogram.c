#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include <locale.h>
#pragma warning(disable :4996)
#define MAX 100
#define _CRT_SECURE_NO_WARNINGS

int time = 0, scan_null, key_speed, end_time, stop;
char example_select[1000], current_path[5000], next_sentence[MAX], current_sentence[MAX], input_sentence[MAX];
char start_alert_message[500] = "타자 연습을 하실 예문의 이름을 입력하시거나, 불러오기를 통해 불러오십시오.\n\n※선택시, 확장자 명(ex > txt, odf)을 같이 입력해주십시오.\n\n※또한, 글자가 100자 이상일 경우에는 인식하지 못합니다.※\n\n※메모장 유니코드가 ANSI이여야 인식합니다.\n\n\n";
char startcaption[50] = "테스트";

unsigned _stdcall Thread_Time(void* arg) { //https://diyver.tistory.com/89
	while (1) {
		TCHAR Title[MAX_PATH], oldTitle[MAX_PATH];

		if (GetConsoleTitle(oldTitle, MAX_PATH)) {
			StringCchPrintf(Title, MAX_PATH, TEXT("[ %hs ] - 경과 시간 : %d || 타자 속도 : %d"), example_select, time, key_speed);

			if (!SetConsoleTitle(Title))
			{
				_tprintf(TEXT("제목 표시줄 변경에 실패 했습니다.\n"), GetLastError());
				return 1;
			}
			else {}
		}

		Sleep(1000);
		time++;
	}
}

void start_option() {

	_wsetlocale(LC_ALL, L"korean"); //제목표시줄 한글 깨짐 방지를 위해 한국어 유니코드로 입출력 관리하는 함수
	system("cls");
	stop = 0;
	//MessageBox(0, (start_alert_message), TEXT(startcaption), MB_OK);
	printf("%s", start_alert_message);
	system("dir /s *.txt");
	printf("\n▶입력 : ");

	fgets(example_select, 101, stdin);

	for (scan_null = 0; scan_null <= 1001; scan_null++) {
		if (example_select[scan_null] == '\n') {
			example_select[scan_null] = 0;
			break;
		}
	}


	if (GetCurrentDirectoryA(5000, current_path) > 0) {
		strcat(current_path, "\\타자연습목록\\");
		strcat(current_path, example_select);

		FILE* fp = fopen(current_path, "r");
		if (fp == NULL) {
			printf("\n파일 읽기에 실패했습니다.\n");
			printf("%s  의 경로에 파일이 존재하지 않습니다.\n\n", current_path);
			system("pause"); 
			return;
		}

		printf("\n\n파일 읽기에 성공했습니다. 아무키나 누르시면 시작합니다.\n");
		system("pause");
		system("cls");
		_beginthreadex(NULL, 0, Thread_Time, 0, 0, NULL);
		//Sleep(3000);

		while (!feof(fp)) {
			fgets(current_sentence, MAX, fp);
			printf("▶ %s\n▶입력 : ", current_sentence);
			fgets(input_sentence, MAX, stdin);
			int identify = strcmp(current_sentence, input_sentence);
			printf("%d\n", identify);
		}
		
		end_time = time;
		printf("종료 시간(초) : %d", time);
		system("pause");
	}
}


int main() {
	while (1) {
		system("cls");
		printf("타자 연습 프로그램 (C언어)\n\n");
		printf("아무키나 누르면 게임시작\n");
		system("pause");
		start_option();
	}
}
