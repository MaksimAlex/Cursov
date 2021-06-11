#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void changePoints(int, int *, int *, int *);
void handPlay(int *, int, int, int *);
void autoPlay(int *, int, int, int *, int *);
void menu(int *, int *, int *);
void convertation(int *, int *, int);
void notEnoughtPoints(int *, int *, int, char *);

int main()
{
	system("clear");
	srand(time(NULL));
	printf("Игра \"Казино\"\n");
	int sumOfPlayer = 0, sumOfCasino = 100000, points, sumOfPoints, bet, prediction, value = 0, gameMode, maxBet, numberOfCube = 1;
	int pointsToCurrency, currency, currencyValue, firstCurrency;
	char choise = 'y';
	menu(&gameMode, &currency, &pointsToCurrency);
	if (gameMode == 2) 
	{
		sumOfPlayer = 100;
		currency = 0;
	}
	firstCurrency = currency;
	do {
		if (gameMode == 1) system("clear");
		printf("Кол-во ваших очков: %d\nКол-во очков казино: %d\nКоличество имеющейся валюты: %d\n", sumOfPlayer, sumOfCasino, currency);
		
		if (gameMode == 1) convertation(&sumOfPlayer, &currency, pointsToCurrency);
		if (sumOfPlayer > 0)
		{
			(gameMode == 1)? handPlay(&bet, sumOfPlayer, sumOfCasino, &prediction): autoPlay(&bet, sumOfPlayer, sumOfCasino, &prediction, &maxBet);
			
			while (numberOfCube <= 2)
			{
				points = rand() % 6 + 1;
				printf("На %d-м кубике выпало %d\n", numberOfCube, points);
				sumOfPoints += points;
				numberOfCube++;
			}
			numberOfCube = 1;		
			printf("Всего выпало очков: %d\nВаш прогноз: %d\n", sumOfPoints, prediction);
			if (sumOfPoints == prediction)
			{
				bet *= 4;
				printf("Поздравляем, ваш прогноз абсолютно верен!");
				if (bet >= sumOfCasino) printf("Вы выиграли у казино все оставшиеся очки!\nКоличество выигранных очков: %d\n", sumOfCasino);
				else printf("Количество выигранных очков: %d\n\n\n", bet);
			}
			else if (((sumOfPoints < 7) && (prediction < 7)) || ((sumOfPoints >= 7) && (prediction >= 7)))
			{
				printf("Поздравляем, ваш прогноз оправдался!");
				if (bet >= sumOfCasino) printf("Вы выиграли у казино все оставшиеся очки!\nКоличество выигранных очков: %d\n", sumOfCasino);
				else printf("Вы выиграли %d очков\n\n\n", bet);
			}
			else 
			{
				printf("Сожалеем, ваш прогноз не оправдался\nВы потеряли %d очков\n\n\n", bet);
				bet *= -1;
			}
			changePoints(bet, &sumOfPlayer, &sumOfCasino, &value);
			sumOfPoints = 0;
			if ((sumOfPlayer == 0) && (currency <= 0)) printf("К сожалению, у вас больше не осталось ни очков, ни денег\n");
			else if (sumOfCasino == 0) printf("Поздравляем, вы выиграли у казино все очки!\n");
			else if (gameMode == 1)
			{
				getchar();
				printf("Желаете продолжить? (y/n): ");
				choise = getchar();
				if ((choise == 'y') && (sumOfPlayer == 0) && (currency > 0)) notEnoughtPoints(&sumOfPlayer, &currency, pointsToCurrency, &choise);
			}
			else system("sleep 2.5");
		}
		else if ((choise == 'y') && (sumOfPlayer <= 0) && (currency > 0) && (gameMode == 1)) notEnoughtPoints(&sumOfPlayer, &currency, pointsToCurrency, &choise);
	} while (((((sumOfPlayer > 0) || (currency > 0)) && (gameMode == 1)) || ((gameMode == 2) && (sumOfPlayer > 0))) && (sumOfCasino > 0) && (choise == 'y'));
	currency += sumOfPlayer * pointsToCurrency;
	currencyValue = currency - firstCurrency;
	printf("\n\nИтоги игры: Ваш баланс: %d\nВы ", currency);
	(value > 0)? printf("выиграли %d фишек\nВы ", value): printf("проиграли %d фишек\nВы ", abs(value));
	(currency > 0)? printf("заработали %d валюты\n", currencyValue): printf("потратили %d валюты\n", abs(currencyValue));
	return 0;
}	

void changePoints(int bet, int *sumOfPlayer, int *sumOfCasino, int *value)
{
	if ((*sumOfCasino <= bet) && (bet > 0)) bet = *sumOfCasino;
	*sumOfPlayer += bet;
	*sumOfCasino -= bet;
	*value += bet;
}

void autoPlay(int *bet, int sumOfPlayer, int sumOfCasino, int *prediction, int *maxBet)
{
	if (sumOfPlayer < sumOfCasino) *maxBet = sumOfPlayer;
	else *maxBet = sumOfCasino;
	*bet = rand() % (*maxBet) + 1;
	*prediction = rand() % 11 + 2;
	printf("Ставка: %d\nПрогноз: %d\n", *bet, *prediction);
}

void handPlay(int *bet, int sumOfPlayer, int sumOfCasino, int *prediction)
{
	do {
		printf("Введите ставку: ");
		scanf("%d", bet);
		if (*bet > sumOfPlayer) printf("У вас нет столько очков!\n");
		if (*bet > sumOfCasino) printf("У казино нет столько очков!\n");
	} while ((*bet > sumOfPlayer) || (*bet > sumOfCasino));
	do {
		printf("Введите число, на которое хотите поставить: ");
		scanf("%d", prediction);
		if ((*prediction < 2) || (*prediction > 12)) printf("Ошибка: будьте реалистом, вам столько не выпадет\n");
	} while ((*prediction < 2) || (*prediction > 12));
}

void menu(int *gameMode, int *currency, int *pointsToCurrency)
{
	do {
		printf("Возможные режимы игры: вручную (1), автоматическая игра (2)\nВыберите режим игры: ");
		scanf("%d", gameMode);
		if ((*gameMode < 1) || (*gameMode > 2)) printf("Некорректный ввод\n");
	} while ((*gameMode < 1) || (*gameMode > 2));
	
	if (*gameMode == 1)
	{
		do {
			printf("Введите количество имеющейся валюты: ");
			scanf("%d", currency);
			if (*currency < 0) printf("Ошибка: некорректный ввод\n");
		} while (*currency < 0);
		
		do {
			printf("Введите курс валюты к очкам: ");
			scanf("%d", pointsToCurrency);
			if (*pointsToCurrency < 1) printf("Ошибка: некорректный ввод\n");
		} while (*pointsToCurrency < 1);
	}
}

void convertation(int *sumOfPlayer, int *currency, int pointsToCurrency)
{
	int choise, count;
	do {
		printf("Желаете ли пополнить/вывести очки? (1 - да, 2 - нет): ");
		scanf("%d", &choise);
		if ((choise < 1) && (choise > 2)) printf("Ошибка: некорректный ввод\n");
	} while ((choise < 1) && (choise > 2));
	if (choise == 1)
	{
		do {
			do {
				printf("Возможные операции: \n1: Вывести очки в деньги\n2: Купить очки\n3: Выйти из меню\n\nКурс валюты к очкам: %d\n\nВведите номер операции: ", pointsToCurrency);
				scanf("%d", &choise);
				if ((choise < 1) || (choise > 3)) printf("Ошибка: некорректный ввод\n");
			} while ((choise < 1) || (choise > 3));
			switch (choise)
			{
				case 1:
					if (*sumOfPlayer > 0)
					{
						do {
							printf("Введите количество очков, конвертируемых в валюту: ");
							scanf("%d", &count);
							if (count < 1) printf("Ошибка: некорректный ввод\n");
							if (count > *sumOfPlayer) printf("Ошибка: У вас нет столько очков\n");
						} while ((count < 1) || (count > *sumOfPlayer));
						*currency += pointsToCurrency * count;
						*sumOfPlayer -= count;
					}
					else printf("У вас нет очков для конвертации\n");
					break;
				case 2:
					if (*currency / pointsToCurrency > 0)
					{
						do {
							printf("Введите количество валюты, конвертируемой в очки: ");
							scanf("%d", &count);
							if (count < 1) printf("Ошибка: некорректный ввод\n");
							if (count > *currency) printf("Ошибка: У вас нет столько денег\n");
						} while ((count < 1) || (count > *currency));
						*sumOfPlayer += count / pointsToCurrency;
						*currency -= count;
					}
					else printf("У вас нет денег для конвертации\n");
					break;
				default:
					break;
			}
			printf("Кол-во ваших очков: %d\nКоличество имеющейся валюты: %d\n", *sumOfPlayer, *currency);
			do {
				printf("Выйти из меню?\n1 - да, 2 - нет: ");
				scanf("%d", &choise);
				if ((choise < 1) || (choise > 2)) printf("Ошибка: некорректный ввод\n");
			} while ((choise < 1) || (choise > 2));
		} while (choise == 2);
	}
}	

void notEnoughtPoints(int *sumOfPlayer, int *currency, int pointsToCurrency, char *choise)
{
	printf("У вас закончились фишки. Для продолжение необходимо пополнить баланс фишек\nЖелаете пополнить баланс? (y/n): ");
	getchar();
	*choise = getchar();
	if (*choise == 'y') convertation(sumOfPlayer, currency, pointsToCurrency);
}
