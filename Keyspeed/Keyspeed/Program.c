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
char start_alert_message[500] = "Ÿ�� ������ �Ͻ� ������ �̸��� �Է��Ͻðų�, �ҷ����⸦ ���� �ҷ����ʽÿ�.\n\n�ؼ��ý�, Ȯ���� ��(ex > txt, odf)�� ���� �Է����ֽʽÿ�.\n\n�� ���ڰ� 100�� �̻��� ��쿡�� �ν����� ���մϴ�.\n\n�� �ؽ�Ʈ ���� �����ڵ尡 ������ UTF-8�� �ƴ� ANSI�̿��� �ν��մϴ�.\n\n\n";
char startcaption[50] = "�׽�Ʈ";

unsigned _stdcall Thread_Time(void* arg) { //https://diyver.tistory.com/89
	time = 0;
	while (1) {
		TCHAR Title[MAX_PATH], oldTitle[MAX_PATH];
		score = 1000;
		if(stop == 1)_endthreadex(0);

		score = score + success*100;

		if (GetConsoleTitle(oldTitle, MAX_PATH)) {
			StringCchPrintf(Title, MAX_PATH, TEXT("[ %hs ] - ��� �ð� : %d �� || �Էµ� ���� ���� : %d �� (��ġ : %d / ����ġ : %d) ||  ���� : %d ��"), example_select, time, success+fail , success, fail, score- time - fail * 30);

			if (!SetConsoleTitle(Title))
			{
				_tprintf(TEXT("���� ǥ���� ���濡 ���� �߽��ϴ�.\n"), GetLastError());
				return 1;
			}
			else {}
		}

		Sleep(1000);
		time++;


	}
}

void start_option() {

	_wsetlocale(LC_ALL, L"korean"); //����ǥ���� �ѱ� ���� ������ ���� �ѱ��� �����ڵ�� ����� �����ϴ� �Լ�
	system("cls");
	stop = 0;
	success = 0;
	fail = 0;
	MessageBox(0, TEXT("�ؼ��ý�, Ȯ���� ��(ex > txt, odf)�� ���� �Է����ֽʽÿ�.\n\n�� ���ڰ� 100�� �̻��� ��쿡�� �ν����� ���մϴ�.\n\n�� �ؽ�Ʈ ���� �����ڵ尡 ������ UTF-8�� �ƴ� ANSI�̿��� �ν��մϴ�."), TEXT("Ÿ�� ���� ���α׷� - [Ÿ�� ���� ���� �Է�]"), MB_ICONASTERISK);
	printf("%s", start_alert_message);
	system("dir /s *.txt");
	printf("\n ���Է� : ");

	fgets(example_select, 101, stdin);

	for (scan_null = 0; scan_null <= 1001; scan_null++) {
		if (example_select[scan_null] == '\n') {
			example_select[scan_null] = 0;
			break;
		}
	}


	if (GetCurrentDirectoryA(5000, current_path) > 0) {
		strcat(current_path, "\\Ÿ�ڿ������\\");
		strcat(current_path, example_select);

		FILE* fp = fopen(current_path, "r");
		if (fp == NULL) {
			printf("\n���� �б⿡ �����߽��ϴ�.\n");
			printf("%s  �� ��ο� ������ �������� �ʽ��ϴ�.\n\n", current_path);
			MessageBox(0, TEXT("�Է��Ͻ� ��ο� ������ �������� �ʽ��ϴ�."), TEXT("Ÿ�� ���� ���α׷� - [Ÿ�� ���� ���� �Է�]"), MB_ICONERROR);
			system("pause");
			return;
		}

		printf("\n\n���� �б⿡ �����߽��ϴ�. �ƹ�Ű�� �����ø� �����մϴ�.\n");
		system("pause");
		system("cls");

		_beginthreadex(NULL, 0, Thread_Time, 0,	 0, NULL);
		
		//Sleep(3000);

		while (!feof(fp)) {
			fgets(current_sentence, MAX, fp);
			printf("\n===================================================\n\n\t�� %s\n\t�� ", current_sentence);
			fgets(input_sentence, MAX, stdin);
			int identify = strcmp(current_sentence, input_sentence);
			if (identify == 0) success = success + 1;
			else fail = fail + 1;
		}

		end_time = time;
		stop = 1;
		fclose(fp);
		printf("���� �ð�(��) : %d, ���� ���� : %d\n", time, score-time-fail*30);
		system("pause");
		
	}
}


int main() {
	char list[10000];
	while (1) {
		PlaySound(TEXT("Main.wav"), NULL, SND_ASYNC | SND_LOOP);
		TCHAR Title[MAX_PATH], oldTitle[MAX_PATH];

		if (GetConsoleTitle(oldTitle, MAX_PATH)) {
			StringCchPrintf(Title, MAX_PATH, TEXT("Ÿ�� ���� ���α׷�"));

			if (!SetConsoleTitle(Title))
			{
				_tprintf(TEXT("���� ǥ���� ���濡 ���� �߽��ϴ�.\n"), GetLastError());
				return 1;
			}
			else {}
		}


		system("cls");
		printf("Ÿ�� ���� ���α׷�\n\n");
		printf("�ƹ�Ű�� ������ ���ӽ���\n\n");

		system("pause");
		start_option();
	}
}