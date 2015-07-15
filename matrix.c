#include <stdio.h>
#include <stdlib.h> //rand関数用
#include <time.h>//stand関数用

#define MATRIX_SIZE	3

/*
	盤面データの状態
*/
#define NONE		0	// 0:まだ誰もとってない。
#define PLAYER		1	// 1:プレイヤーが取った。
#define COMPUTER	2	// 2:コンピューターが取った。

int matrix[MATRIX_SIZE][MATRIX_SIZE];
int take(int number, int who);
void showMatrix();
int judge();

int main(void) {
	int i,j,n,m,turn;
	int winner;

	printf("三目ならべを始めます\n");

	/*
		盤面を初期化します。
	*/
	// initialize
	for (i =0; i < MATRIX_SIZE; i++) {
		for (j = 0; j<MATRIX_SIZE; j++) {
			matrix[i][j] = NONE;
		}
	}
	
	turn = PLAYER;
	winner = NONE;
	while(winner == NONE) {
		showMatrix();
		switch(turn) {
		case PLAYER:
			printf("あなたの番です、○を置きたい場所の数字を入力してください\n");

			/* 入力待ちループ */
			while(turn == PLAYER) {
				scanf("%d", &n);
				if(take(n, turn) != 0) {
					printf("数値を入れなおしてください\n");
					continue;
				}
				turn = COMPUTER;	// COMPUTERの番にする。
			}
			break;

		case COMPUTER:
			printf("コンピュータの番です\n");

			/* 選択処理ループ */
			while(turn == COMPUTER) {
				srand((unsigned)time(NULL));
				n = rand() % 10;
				if(take(n, turn) != 0) {
					continue;
				}
				turn = PLAYER;	// PLAYERの番にする。
			}
			break;
		}
		// 勝ち負け判定
		winner = judge();
		switch(winner) {
		case PLAYER:
			printf("Player WIN!\n");
			break;
		case COMPUTER:
			printf("Computer WIN!\n");
			break;
		default:
			break;
		}
	}
	exit(0);
}

/*
	勝ち負け判定
*/
int judge(){
	return NONE;
}

/*
	指定した番号の位置を取る。
	 0:指定した場所が取れた。
	-1:指定した場所が取れなかった。
*/
int take(int number, int who) {
	if(matrix[(number - 1) / MATRIX_SIZE][(number - 1) % MATRIX_SIZE] == 0) {
		matrix[(number - 1) / MATRIX_SIZE][(number - 1) % MATRIX_SIZE] = who;
	} else {
		return -1;
	}
	return 0;
}

/*
	盤面を表示します。
*/
void showMatrix(){
	int i,j;

	for (i =0; i < MATRIX_SIZE; i++) {
		for (j = 0; j<MATRIX_SIZE; j++) {
			switch(matrix[i][j])
			{
			case NONE:		// まだ誰も選んでない
				printf("%d",i * MATRIX_SIZE + j + 1);
				break;
			case PLAYER:	// プレイヤーが選んだ
				printf("@");
				break;
			default:
			case COMPUTER:	// コンピュータが選んだ
				printf("o");
				break;
			}
		}
		printf("\n");
	}
}
