#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
/*
* Константа для настройки работы приложения
*/
#define LENGTH  9 
/*
* Константы для отображения поля
*/
#define UP_BORDER_FOR5COMPL "%d %d|%d %d|%d"    
#define LOW_BORDER_FOR5COMPL "%d|%d %d|%d %d"
#define UP_BORDER_FOR7COMPL "%d %d|%d %d|%d %d|%d"   
#define LOW_BORDER_FOR7COMPL "%d|%d %d|%d %d|%d %d"
#define UP_BORDER_FOR9COMPL "%d %d|%d %d|%d %d|%d %d|%d"   
#define LOW_BORDER_FOR9COMPL "%d|%d %d|%d %d|%d %d|%d %d"

void menuGame();
int writeResultInFIle(int** arr, int complex, int);
void buildBorder(int** arr, int length);
int changeComplex(int** arr, int oldComplex);
int** changePole(int** arr, int complex);
int isSave(int** arr, int k, int d, int checkNumber, int complex);
int checkResult(int** arr, int complexe);
void playGame(int** arr, int oldComplex);
int** choseArray(int complex);
int printResultInFile();

void main() {
	setlocale(LC_ALL, "RUS");
	menuGame();
}

void menuGame() {
	int** arr = NULL;
	int flag = 1, def, complex = 0;
	while (flag) {
		printf("*********************************\n");
		printf("* Выберите действие:\t\t*\n* 1. Играть\t\t\t*\n* 2. Изменить поле\t\t*\n* 3. Загрузить последние игры\t*\n* 4. Правила игры\t\t*\n* 5. Выйти\t\t\t*\n");
		printf("*********************************\n");
		scanf("%d", &def);
		if (def == 1) {
			playGame(arr, complex);
		}
		else if (def == 2) {
			printf("Выберите какую сложность поля вы хотите изменить: 1, 2 или 3: ");
			scanf("%d", &complex);
			arr = changePole(choseArray(complex), complex);
		}
		else if (def == 3) {
			printResultInFile();
		}
		else if (def == 4) {
			printf("Кирпичи («Bricks») - разновидность логической головоломки.\nНеобходимо заполнить сетку цифрами так, чтобы в каждой строке и в каждом столбце они не повторялись.\nНа каждом кирпиче одна цифра - чётная, другая - нечётная.\n");
		}
		else if (def == 5) {
			flag = 0;
		}
		else printf("Некорректный ввод\n");
	}
}

void buildBorder(int** arr, int length) {
	printf("   ");
	for (int i = 0; i < length; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (int i = 0; i < length * 2 + 2; i++) {
		printf("-");
	}
	printf("\n");
	for (int i = 0; i < length; i++) {
		printf("%d| ", i);
			if (i % 2 == 0) {
				if (length == 5) printf(UP_BORDER_FOR5COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
				else if (length == 7) printf(UP_BORDER_FOR7COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
				else if (length == 9) printf(UP_BORDER_FOR9COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6], arr[i][7], arr[i][8]);
				printf("\n");
			}
			else {
				if (length == 5)printf(LOW_BORDER_FOR5COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
				else if (length == 7)printf(LOW_BORDER_FOR7COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
				else if (length == 9)printf(LOW_BORDER_FOR9COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6], arr[i][7], arr[i][8]);
				printf("\n");
			}
	}
}

int** choseArray(int complex) {
	int** arr = NULL;
	int arr5[5][5] = {
				{ 2, 0, 0, 0, 0},
				{ 0, 1, 0, 3, 0},
				{ 1, 0, 3, 0, 0},
				{ 0, 3, 0, 0, 0},
				{ 0, 0, 4, 0, 1},
	};
	int arr7[7][7] = {
				{ 4, 0, 0, 6, 0, 0, 7},
				{ 0, 4, 0, 3, 0, 5, 0},
				{ 0, 7, 0, 0, 0, 6, 0},
				{ 0, 0, 6, 0, 1, 0, 0},
				{ 0, 3, 0, 0, 0, 4, 0},
				{ 0, 2, 0, 7, 0, 1, 0},
				{ 7, 0, 0, 1, 0, 0, 3},
	};
	int arr9[9][9] = {
				{ 5, 0, 0, 0, 0, 0, 4, 9, 0 },
				{ 0, 0, 7, 0, 0, 0, 8, 0, 0 },
				{ 8, 0, 0, 0, 2, 0, 7, 0, 0 },
				{ 7, 2, 0, 0, 9, 0, 0, 0, 0 },
				{ 0, 3, 2, 0, 0, 0, 5, 8, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 7, 8 },
				{ 0, 0, 8, 0, 4, 0, 0, 0, 5 },
				{ 0, 0, 4, 0, 0, 0, 1, 0, 0 },
				{ 0, 9, 5, 0, 0, 0, 0, 0, 1 },
	};
	if (complex == 1) complex = 5;
	else if (complex == 2) complex = 7;
	else if (complex == 3) complex = 9;
	arr = (int**)malloc(complex * sizeof(int*));
	for (int i = 0; i < complex; i++) {
		arr[i] = (int*)malloc(complex * sizeof(int));
		for (int j = 0; j < complex; j++) {
			if (complex == 5) arr[i][j] = arr5[i][j];
			else if (complex == 7) arr[i][j] = arr7[i][j];
			else if (complex == 9) arr[i][j] = arr9[i][j];
		}
	}
	return arr;
}

int** changePole(int** arr, int complex) {
	int flag = 1;
	if (complex == 1) complex = 5;
	else if (complex == 2) complex = 7;
	else if (complex == 3) complex = 9;
	while (flag) {
		int a, b;
		buildBorder(arr, complex);
		printf("Какой элемент необходимо изменить? Или введите -1, чтобы выйти\n*Пример ввода:01 (число)\nВведите индекс элемета:");
		scanf("%d", &a);
		if (a == -1) {
			flag = 0;
			break;
		}

		printf("Введите новое значение: ");
		scanf("%d", &b);
		if (b > 9) {
			printf("Некорректное число.\n");
		}
		else {
			arr[a / 10][a % 10] = b;
		}
	}
	return arr;
}

int changeComplex(int** arr, int oldComplex) {
	int complex;
	printf("Выберите сложность:\n 1 - поле размером 5 на 5\n 2 - поле размером 7 на 7\n 3 - поле размером 9 на 9\n");
	scanf("%d", &complex);
	if (oldComplex == 1 && complex == 1) {
		buildBorder(arr, 5);
	}
	else if (oldComplex == 2 && complex == 2) {
		buildBorder(arr, 7);
	}
	else if (oldComplex == 3 && complex == 3) {
		buildBorder(arr, 9);
	}
	else if (complex == 1) {
		buildBorder(choseArray(complex), 5);
		return 5;
	}
	else if (complex == 2) {
		buildBorder(choseArray(complex), 7);
		return 7;
	}
	else if (complex == 3) {
		buildBorder(choseArray(complex), 9);
		return 9;
	}
	else printf("Некорректный ввод");
}

void playGame(int** arr, int oldComplex) {
	int complex = changeComplex(arr, oldComplex);
	int** arr1 = arr;
	int action, a, b, flag = 1, result;
	if ((oldComplex == 1 && complex == 5)|| (oldComplex == 2 && complex == 7) || (oldComplex == 3 && complex == 9)) arr = arr;
	else {
		arr = choseArray(complex);
		arr1 = choseArray(complex);
	};
	printf("\n***Вы начали игру***\n\nНеобходимо заполнить ТОЛЬКО ячейки, в которых содержится ""0""\n");
	while (flag) {
		printf("\n");
		buildBorder(arr, complex);
		printf("Какой элемент необходимо изменить? Или введите -1, чтобы закончить игру, или -2 если вы закончили игру и хотите посмотреть результат\n*Пример ввода:01 (число), где 0 - строка, 1 - столбец\nВведите индекс элемета:");
		scanf("%d", &a);
		if (a == -1) {
			flag = 0;
			printf("Вы закончили игру.\n");
			break;
		}
		else if (a == -2) {
			flag = 0;
			break;
		}
		printf("Введите новое значение: ");
		scanf("%d", &b);
		if (b > complex) {
			printf("\n***Некорректное число***\n");
		}
		else {
			if (arr1[a / 10][a % 10] == 0) arr[a / 10][a % 10] = b;  // проверка только по исходному массиву
			else printf("\n***Эту ячейку нельзя изменить***\n");
		}
	}
	if (a == -2) {
		result = checkResult(arr, complex);
		if (result == 1) printf("***Вы проиграли***\n");
		else printf("***Вы выиграли***\n");
		printf("Выберите действие\n1. Сохранить результат\n2. Выйти\n");
		scanf("%d", &action);
		if (action == 1)writeResultInFIle(arr, complex, result);
	}
}

int writeResultInFIle(int** arr, int complex, int result) {
	char fname[20] = "result.txt";
	FILE* out;
	puts("Сохранение результата в файл...");
	if ((out = fopen(fname, "a")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 1;
	}
	fprintf(out, "   ");
	for (int i = 0; i < complex; i++) {
		fprintf(out, "%d ", i);
	}
	fprintf(out, "\n");
	for (int i = 0; i < complex * 2 + 2; i++) {
		fprintf(out, "-");
	}
	fprintf(out, "\n");
	for (int i = 0; i < complex; i++) {
		fprintf(out, "%d| ", i);
			if (i % 2 == 0) {
				if (complex == 5) fprintf(out,UP_BORDER_FOR5COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
				else if (complex == 7) fprintf(out, UP_BORDER_FOR7COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
				else if (complex == 9) fprintf(out, UP_BORDER_FOR9COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6], arr[i][7], arr[i][8]);
				fprintf(out, "\n");
			}
			else {
				if (complex == 5)fprintf(out, LOW_BORDER_FOR5COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
				else if (complex == 7)fprintf(out, LOW_BORDER_FOR7COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
				else if (complex == 9)fprintf(out, LOW_BORDER_FOR9COMPL, arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6], arr[i][7], arr[i][8]);
				fprintf(out, "\n");
			}
	}
	if (result == 1) fprintf(out, "Результат: Поражение\n");
	if (result == 2) fprintf(out, "Результат: Победа\n");
	fclose(out);
	return 0;
}

int printResultInFile() {
	int flag = 0;
	char buffer[256];
	char fname[20] = "result.txt";
	FILE* fp = fopen(fname, "r");
	if (fp)
	{
		while ((fgets(buffer, 256, fp)) != NULL)
		{
			printf("%s", buffer);
			flag = 1;
		}
		fclose(fp);
	}
	if (flag == 0) printf("\n***Вы ещё не играли***\n\n");
	return 0;
}


int isSave(int** arr, int k, int d, int checkNumber, int complex) {
	if (checkNumber == 0) return 1;
	for (int j = 0; j < complex; j++) {
		if (k != j && j != d) {
			if (arr[k][j] == checkNumber || arr[j][d] == checkNumber) {
				return 1;
			}
		}
	}
	return 0;
}

int checkResult(int** arr, int complexe) {
	for (int i = 0; i < complexe; i++) {
		for (int j = 0; j < complexe; j += 2) {
			if (i % 2 == 0) {
				if (j == complexe - 1) {
					if (isSave(arr, i, j, arr[i][j], complexe) == 1) return 1;
				}
				else if (isSave(arr, i, j, arr[i][j], complexe) == 1) return 1;
				else if ((arr[i][j + 1] % 2 == 0 && arr[i][j] % 2 == 0) || (arr[i][j + 1] % 2 != 0 && arr[i][j] % 2 != 0)) {
					return 1;
				}
			}
			else {
				if (j == 0) {
					if (isSave(arr, i, j, arr[i][j], complexe) == 1) {
						return 1;
					}
					else {
						j++;
						if ((arr[i][j + 1] % 2 == 0 && arr[i][j] % 2 == 0) || (arr[i][j + 1] % 2 != 0 && arr[i][j] % 2 != 0))
							return 1;
					}
				}
				else if (isSave(arr, i, j, arr[i][j], complexe) == 1) return 1;
				else if ((arr[i][j + 1] % 2 == 0 && arr[i][j] % 2 == 0) || (arr[i][j + 1] % 2 != 0 && arr[i][j] % 2 != 0)) {
					return 1;
				}
			}
		}
	}
	return 0;
}
