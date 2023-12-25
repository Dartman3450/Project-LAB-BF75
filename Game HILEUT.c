#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct PlayerData {
    char name[50];
    int score;
};

struct PlayerData playerData[5];

char map[10][20];
char player = '^';
char ekor = '*';
char apel = 'O';

int yApel, xApel;

int y = 5, x = 5;

int yEkor[50];
int xEkor[50];
int p = 50, l = 40;
int nEkor = 2;
int maxEkor = 10;
int score;

struct PlayerData playerData[5]; 

void generateMap();
void displayMap();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void showMenu();
void checkCollision();
void sortScores();

int main()
{
    int numPlayers, currentPlayer;
    
    printf("Masukkan jumlah pemain: ");
    scanf("%d", &numPlayers);

    for (currentPlayer = 0; currentPlayer < numPlayers; currentPlayer++)
    {
        score = 0;
        int i, n;
        time_t t;

        char move;
        srand((unsigned)time(&t));
        yApel = rand() % 8 + 1;
        xApel = rand() % 18 + 1;

        system("color 2");

        yEkor[0] = y + 1;
        xEkor[0] = x;
        yEkor[1] = y + 2;
        xEkor[1] = x;

        showMenu();

        printf("Masukkan nama Anda: ");
        scanf("%s", playerData[currentPlayer].name);

        do
        {
            system("cls");

            generateMap();

            displayMap();

            move = getch();

            switch (move)
            {
            case 'w':
                player = '^';
                moveUp();
                break;
            case 's':
                player = 'v';
                moveDown();
                break;
            case 'a':
                player = '<';
                moveLeft();
                break;
            case 'd':
                player = '>';
                moveRight();
                break;
            }
            
            checkCollision();
            if (y == yApel && x == xApel)
            {
                map[y][x] = player;
                score++;

                if (nEkor < 10)
                {
                    nEkor++;
                }

                yApel = (rand() % 8) + 1;

                xApel = (rand() % 18) + 1;
            }

            for (i = 9; i > 0; i--)
            {
                yEkor[i] = yEkor[i - 1];
                xEkor[i] = xEkor[i - 1];
            }

        } while (score <= 10);

        printf("\nCONGRATULATIONS\n");

        playerData[currentPlayer].score = score;
        sortScores(); 
        
        printf("\nTop 5 Scores:\n");
        for (i = 0; i < 5; i++)
        {
            printf("%s: %d\n", playerData[i].name, playerData[i].score);
        }
    }

    return 0;
}

void generateMap()
{
	int i,j;	
	for(i=0; i<10; i++)
	{
		for(j=0; j<20; j++)
		{
			if(i == 0 || i == 9)
			{
				map[i][j] = '-';
			}
			
			else if(j == 0 || j == 19)
			{	
				map[i][j] = '|';
			}
			
			else
			{
				map[i][j] = ' ';
			}	
		}
	}
	
	map[y][x] = player;
	map[yApel][xApel] = apel;
	for(i=0; i<=nEkor; i++) 
	{
		map[yEkor[i]] [xEkor [i]] = ekor;
	}
}


void displayMap()
{

	int i,j;
	
	for(i=0; i<10; i++)
	{	
		for(j=0; j<20; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	printf("Score : %d", score);
}

void moveUp()
{
	int i;
	
	if(y-1 > 0)
	{
		yEkor[0] = y; xEkor[0] = x;
		y--;
	}
}

void moveDown() 
{
	if(y+1 < l-1)
	{
		yEkor[0] = y; xEkor[0] = x;
		y++;
	}
}

void moveLeft()
{

	if(x-1 > 0)
	{
		yEkor[0] = y; xEkor[0] = x;
		x--;
	}
	
}

void moveRight()
{
	if(x+1 < p-1)
	{
		yEkor[0] = y; xEkor[0] = x;
		x++;
	}

}

void showMenu()
{
    printf("=== Game Snake ===\n");
    printf("1. Mulai Game\n");
    printf("2. Keluar\n");

    int choice;
    printf("Pilihan: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        break; 
    case 2:
        exit(0);

    default:
        printf("Pilihan tidak valid. Keluar dari program.\n");
        exit(0);
    }
}

void checkCollision()
{
    int i;
    for ( i = 1; i <= nEkor; i++)
    {
        if (y == yEkor[i] && x == xEkor[i])
        {
            printf("\nGAME OVER\n");
            printf("Total Score: %d\n", score);
            exit(0);
        }
    }
}

void sortScores() {
    int i, j;
    struct PlayerData temp;

    for (i = 0; i < 5 - 1; i++) {
        for (j = 0; j < 5 - i - 1; j++) {
            if (playerData[j].score < playerData[j + 1].score) {
                
                temp = playerData[j];
                playerData[j] = playerData[j + 1];
                playerData[j + 1] = temp;
            }
        }
    }
}

