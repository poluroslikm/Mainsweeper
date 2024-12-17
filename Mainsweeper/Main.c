#define _CRT_SECURE_NO_WARNINGS
#define D 102
#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>



int cleaning(int saper_array[D][D], int d1, int d2);
int bomb(int saper_array[D][D], int c1, int c2);
int generation(int saper_array[D][D], int d1, int d2);
int fgeneration(FILE* saper_file, int saper_array[D][D], int d1, int d2);
int saper(FILE* saper_file, short int random, short int base);



int main()
{
	FILE* saper_file;
	char sfile[80] = { 's', 'a', 'p', 'e', 'r', '.', 't', 'x', 't' }, txt[5] = { '.', 't', 'x', 't' }, enter[2] = {'\n'};
	char task;
	short int random, base=1;
	saper_file = fopen(sfile, "a");
	setlocale(LC_CTYPE, "RUS");
	//saper(saperFile);
	printf("Данная программа преднозначена для генерации и ручного задавния полей для игры \"Сапер\" (Minesweeper).\n");
	printf("Все созданные поля будут записаны в файл (по умолчанию \"saper.txt\"), для дальнейшего использования полей в игре.\n");
	
	//Повторение программы
	for (short int br=0;br!=1;) 
	{
		printf("Введите \"1\", если хотите сгенерировать одно поле\n");
		printf("Введите \"2\", если хотите сгенерировать несколько полей\n");
		printf("Введите \"3\", если хотите задать поле вручную\n");
		if (base==1) 
			printf("Введите \"4\", если хотите отключить запись в файл\n"); 
		else
			printf("Введите \"4\", если хотите включить запись в файл\n");
		printf("Введите \"5\", если хотите отчистить файл\n");
		printf("Введите \"6\", если хотите ввести название файла\n");
		printf("Введите \"7\", если хотите прекратить программу\n");
		printf("Выполнить                               >>>  ");
		scanf(" %c", &task);
		getchar();
		switch (task)
		{
		case '1': //одно поле
			random = 1;
			saper(saper_file, random, base);
			break;
		case '2': //несколько полей
			random = 2;
			saper(saper_file, random, base);
			break;
		case '3': //вручную
			random = 0;
			saper(saper_file, random, base);
			break;
		case '4': //запись в файл
			base = (base + 1) % 2;
			printf("\n");
			break;
		case '5': //отчистка файла
			saper_file = fopen(sfile, "w");
			printf("\n");
			break;
		case '6': //имя файла
			fclose(saper_file);
			*sfile = '\0';
			printf("Введите название файла                    >  ");
			fgets(sfile, 80, stdin);
			char* find1 = strstr(sfile, enter);
			int position = find1 - sfile;
			sfile[position] = '\0';
			char* find2 = strstr(sfile, txt);
			if (!find2)
			//else
				strcat(sfile, txt);
			saper_file = fopen(sfile, "a");
			break;
		case '7': //завершить программу
			br = 1;
			break;
		default:
			printf("Неизвестная операция\n");
		}
	}
	fclose(saper_file);
}

//отчистка поля
int cleaning(int saper_array[D][D], int d1, int d2)
{
	for (int i1 = 1; i1 <= d1; i1++)
		for (int i2 = 1; i2 <= d2; i2++)
			saper_array[i1][i2] = 0;
}

//генерация бомбы и цифр вокруг нее
int bomb(int saper_array[D][D], int c1, int c2)
{
	saper_array[c1][c2] = 9;
	for (int u1 = c1 - 1; u1 <= c1 + 1; ++u1)
		for (int u2 = c2 - 1; u2 <= c2 + 1; ++u2)
			saper_array[u1][u2] += 1;
}

//вывод на консоль
int generation(int saper_array[D][D], int d1, int d2)
{
	printf(" _");
	for (int i2 = 1; i2 <= d2; i2++) printf("__"); //верхняя граница в консоли
	printf("\n");
	for (int i1 = 1; i1 <= d1; i1++)
	{
		printf("| "); //левая граница в консоли
		for (int i2 = 1; i2 <= d2; ++i2)
		{
			if (saper_array[i1][i2] == 0) printf("  ");
			if ((saper_array[i1][i2] != 0) && (saper_array[i1][i2] < 9)) printf("%d ", saper_array[i1][i2]);
			if (saper_array[i1][i2] > 9) printf("* "); //генерация поля
		}
		printf("|\n"); //правая граница в консоли
	}
}

//вывод в файл
int fgeneration(FILE* saper_file, int saper_array[D][D], int d1, int d2)
{
	fprintf(saper_file, " _");
	for (int i2 = 1; i2 <= d2; i2++)
		fprintf(saper_file, "__");
	fprintf(saper_file, "\n");
	for (int i1 = 1; i1 <= d1; i1++)
	{
		fprintf(saper_file, "| ");
		for (int i2 = 1; i2 <= d2; ++i2)
		{
			if (saper_array[i1][i2] == 0) fprintf(saper_file, "  ");
			if ((saper_array[i1][i2] != 0) && (saper_array[i1][i2] < 9)) fprintf(saper_file, "%d ", saper_array[i1][i2]);
			if (saper_array[i1][i2] > 9) fprintf(saper_file, "* ");
		}
		fprintf(saper_file, "|\n");
	}
}

//основная функция
int saper(FILE* saper_file, short int random, short int base)
{
	srand(time(0));
	int d1=INT_MIN, d2= INT_MIN, b= INT_MAX, c1= INT_MIN, c2=INT_MIN, k = 0;
	int saper_array[D][D];

	//ввод данных
	//генерация количества полей при 2 пункте
	if (random == 2)
	{
		while (k <= 0)
		{
			printf("Введите количество полей                  >  ");
			scanf("%d", &k);
			if (k <= 0)
				printf("Количество полей должно быть больше 0 \n");
		}
	}
	else
		++k;

	//генерация длины поля
	while ((d1 > D - 2) || (d1 < 1))
	{
		printf("Введите длину поля       (максимум   100) >  ");
		scanf("%d", &d1);
		if (d1 > D - 2)
			printf("Поле превысило максимальный размер\n");
		else
			if (d1 < 1)
				printf("Размер поля не может быть меньше 1\n");
	}

	//генерация ширины поля
	while ((d2 > D - 2) || (d2 < 1))
	{
		printf("Введите ширину поля      (максимум   100) >  ");
		scanf("%d", &d2);
		if (d2 > D - 2)
			printf("Поле превысило максимальный размер\n");
		else
			if (d2 < 1)
				printf("Размер поля не может быть меньше 1\n");
	}

	//генерация количества бомб
	while ((b > d1 * d2) || (d1 < 1))
	{
		printf("Введите количество бомб  (максимум %5.d) >  ", d1 * d2);
		scanf("%d", &b);
		if (b > d1 * d2)
			printf("Количество бомб больше размера поля\n");
		else
			if (d1 < 1)
				printf("Количество бомб не может быть меньше 1\n");
	}
	cleaning(saper_array, d1, d2); //сбросить поле

	//если 3 пункт
	if (random == 0)
	{
		for (int bm = 0; bm < b;)
		{
			//первая корда при 3 пункте
			while ((c1 > d1) || (c1 <= 0))
			{
				printf("Введите ординату бомбы   (максимум %5.d) >  ", d1);
				scanf("%d", &c1);
				if ((c1 > d1) || (c1 <= 0))
					printf("Координата выходит за рамки поля\n");
			}
			//вторая корда при 3 пункте
			while ((c2 > d2) || (c2 <= 0))
			{
				printf("Введите абсциссу бомбы   (максимум %5.d) >  ", d2);
				scanf("%d", &c2);
				if ((c2 > d2) || (c2 < 0))
					printf("Координата выходит за рамки поля\n");
			}
			//установка бомбы и цифр, потом на функцию заменить
			if (saper_array[c1][c2] < 10)
			{
				bomb(saper_array, c1, c2);
				bm++;
				printf("Бомба установлена\n");
				if (bm < b)
					generation(saper_array, d1, d2);
			}
			else
				printf("По этим координатам уже установлена бомба\n");
			c1 = INT_MIN; 
			c2 = INT_MIN;
		}
	}

	//сама генерация
	for (;k!=0; k--) //количество полей, изначально 1
	{
		//установка бомбы и цифр
		if (random > 0)
		{
			cleaning(saper_array, d1, d2); //сброс поля
			for (int i = 1; i <= b;)
			{
				//рандомизация координат
				c1 = 1 + rand() % (d1);
				c2 = 1 + rand() % (d2);
				if (saper_array[c1][c2] < 10)
				{
					bomb(saper_array, c1, c2);
					i++;
				}
			}
		}
		//вывод поля
		generation(saper_array, d1, d2);
		if (base == 1) 
			fgeneration(saper_file, saper_array, d1, d2);
	}
}