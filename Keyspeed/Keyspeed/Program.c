#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <process.h>
#include <tchar.h>
#include <conio.h>
#include <strsafe.h>
#include <locale.h>
#include <mmsystem.h>
#pragma warning(disable :4996)
#pragma comment(lib,"winmm.lib")
#define MAX 100
#define _CRT_SECURE_NO_WARNINGS

int time = 0, scan_null, key_speed, end_time, stop = 0, success, fail , score, insert_score;
char example_select[1000], current_path[5000], next_sentence[MAX], current_sentence[MAX], input_sentence[MAX];
char start_alert_message[500] = "타자 연습을 하실 예문의 이름을 입력하시거나, 불러오기를 통해 불러오십시오.\n\n※선택시, 확장자 명(ex > txt, odf)을 같이 입력해주십시오.\n\n※ 글자가 100자 이상일 경우에는 인식하지 못합니다.\n\n※ 텍스트 파일 유니코드가 형식이 UTF-8이 아닌 ANSI이여야 인식합니다.\n\n\n";
char startcaption[50] = "테스트";

unsigned _stdcall Thread_Time(void* arg) { //https://diyver.tistory.com/89
	time = 0;
	while (1) {
		TCHAR Title[MAX_PATH], oldTitle[MAX_PATH];
		score = 1000;
		if(stop == 1)_endthreadex(0);

		score = score + success*100;

		if (GetConsoleTitle(oldTitle, MAX_PATH)) {
			StringCchPrintf(Title, MAX_PATH, TEXT("[ %hs ] - 경과 시간 : %d 초 || 입력된 문장 갯수 : %d 개 (일치 : %d / 불일치 : %d) ||  점수 : %d 점"), example_select, time, success+fail , success, fail, score- time - fail * 30);

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
	success = 0;
	fail = 0;
	MessageBox(0, TEXT("※선택시, 확장자 명(ex > txt, odf)을 같이 입력해주십시오.\n\n※ 글자가 100자 이상일 경우에는 인식하지 못합니다.\n\n※ 텍스트 파일 유니코드가 형식이 UTF-8이 아닌 ANSI이여야 인식합니다."), TEXT("타자 연습 프로그램 - [타자 연습 파일 입력]"), MB_ICONASTERISK);
	printf("%s", start_alert_message);
	system("dir /s *.txt");
	printf("\n ▶입력 : ");

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
			MessageBox(0, TEXT("입력하신 경로에 파일이 존재하지 않습니다."), TEXT("타자 연습 프로그램 - [타자 연습 파일 입력]"), MB_ICONERROR);
			system("pause");
			return;
		}

		printf("\n\n파일 읽기에 성공했습니다. 아무키나 누르시면 시작합니다.\n");
		system("pause");
		system("cls");

		_beginthreadex(NULL, 0, Thread_Time, 0,	 0, NULL);
		
		//Sleep(3000);

		while (!feof(fp)) {
			fgets(current_sentence, MAX, fp);
			printf("\n===================================================\n\n\t▶ %s\n\t▶ ", current_sentence);
			fgets(input_sentence, MAX, stdin);
			int identify = strcmp(current_sentence, input_sentence);
			if (identify == 0) success = success + 1;
			else fail = fail + 1;
		}

		end_time = time;
		stop = 1;
		fclose(fp);
		printf("종료 시간(초) : %d, 최종 점수 : %d\n", time, score-time-fail*30);
		system("pause");
		
	}
}


int main() {
	char list[10000];
	while (1) {
		PlaySound(TEXT("Main.wav"), NULL, SND_ASYNC | SND_LOOP);
		TCHAR Title[MAX_PATH], oldTitle[MAX_PATH];

		if (GetConsoleTitle(oldTitle, MAX_PATH)) {
			StringCchPrintf(Title, MAX_PATH, TEXT("타자 연습 프로그램"));

			if (!SetConsoleTitle(Title))
			{
				_tprintf(TEXT("제목 표시줄 변경에 실패 했습니다.\n"), GetLastError());
				return 1;
			}
			else {}
		}


		system("cls");
		printf("타자 연습 프로그램\n\n");
		printf("아무키나 누르면 게임시작\n\n");

		system("pause");
		start_option();
	}
}