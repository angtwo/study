
#include <iostream>
#include <time.h>

void GameManual(); // 게임 설명
void init(int bingo[][5]); // 초기 빙고판 (맨 처음 빙고판에 랜덤 2자리 'x' 표식 설정
void PrintBoard(int bingo[][5]); // 빙고판 출력
void BombSet(int bingo[][5],int k); // 폭탄 좌표 설정 
void CheckBingo(int bingo[][5],int BingoCheck[]); // 빙고 라인 체크
void ChangeBingoLine(int bingo[][5], int BingoCheck[]); // 빙고된 라인의 표식 'x' 를 표식 '@'로 바꾸기(여기까지 이상 무)
void CountBingo(int BingoCheck[12],int count[18],int k); // 빙고된 라인 개수 카운트
int GameResult(int bingo[][5],int count[18], int k); // 게임 결과
int main()
{
	int res = -1;
	int k = 1; // 몇번째 폭탄인지 체크하는 변수
	int count[18] = { 0 }; // 빙고가 된 라인 수
	int bingo[5][5] =
	{
		{'o','o', 'o', 'o', 'o'} ,
		{'o','o', 'o', 'o', 'o'},
		{'o','o', 'o', 'o', 'o'},
		{'o','o', 'o', 'o', 'o'},
		{'o','o', 'o', 'o', 'o'}
	};
	GameManual(); // 게임 설명
	init(bingo); // 초기 빙고판 설정
	PrintBoard(bingo); // 빙고판 출력
	
	while (k<10)
	{
		int BingoCheck[12] = { 0 }; // 빙고 경우의 수 체크 BingoCheck[0~4] : 가로줄, [5~9] : 세로줄 ,[10,11] : 대각선
		BombSet(bingo, k); // 폭탄 설정(좌표, 폭탄으로 인한 빙고판 바꾸기)
		CheckBingo(bingo,BingoCheck); // 빙고라인 체크 
		ChangeBingoLine(bingo,BingoCheck); // 빙고된 라인의 표식 'x' 를 표식 '@'로 바꾸기
		CountBingo(BingoCheck,count, k); // 빙고된 라인 개수 카운트
		GameManual(); // 게임 설명
		PrintBoard(bingo); // 빙고판 출력
		res = GameResult(bingo, count, k); // 리턴값으로 게임 종료 여부 확인
		if (res == 0)
			break;
			

	k++; // 차례 ++
	}
	
}

void GameManual() // 게임 설명
{
	printf("!BOMB BINGO GAME!\n\n");
	printf("좌표를 지정하면 그 지정된 좌표에 폭탄이 떨어집니다. ex) (0,0) ~ (4,4)\n\n");
	printf("폭탄이 떨어진 좌표로부터 인접한 좌표(대각선을 제외한 십자 + 모양으로)에는 'x'표식이 생깁니다.\n\n");
	printf("폭탄으로 인해 'x'표식이 중복 좌표가 생길 경우 'x'표식은 사라집니다.\n\n");
	printf("빙고가 완성된 줄은 'x'표식이 '@'표식으로 바뀌고 '@'표식은 폭탄에 영향을 받지 않습니다.\n\n");
	printf("3의 배수 차례일때 빙고를 만들지 못하면 실패입니다.\n\n");
	printf("9번째 폭탄까지 버티면 승리!\n\n");
}

void init(int bingo[][5])
{
	int r1 = 0, r2 = 0;
	srand((unsigned int)time(NULL)); 
	while (r1 == r2) // 서로 다른 랜덤 숫자를 생성할때까지 반복
	{
		r1 = rand() % 25;	
		r2 = rand() % 25;	
	}
	bingo[r1 / 5][r1 % 5] = 'x'; // 25를 몫과 나머지를 계산하여 bingo 배열에 넣기
	bingo[r2 / 5][r2 % 5] = 'x';
}

void PrintBoard(int bingo[][5]) // 빙고판 출력
{
	int i = 0, j = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
			printf("%c ", bingo[i][j]);
		printf("\n");
	}
	printf("\n");
}

void BombSet(int bingo[][5],int k) // 폭탄 설정
{		
	int n1 = 0, n2 = 0;
	if (k % 3 == 0) // 3의 배수 라운드시 경고 표시, 좌표 입력
	{
		printf("WARNING!!\n이번에 빙고를 완성 못하면 게임 실패합니다.\n");
		printf("%d 라운드. 좌표를 입력하세요. ex) (2,4) = 2 4 \n", k);
	}
	else // 나머지 라운드 표시, 좌표 입력
	{
		printf("%d 라운드. 좌표를 입력하세요. ex) (2,4) = 2 4 \n", k);
	}
		scanf_s("%d %d", &n1, &n2);
		system("cls");
		
		// 폭탄으로 인한 표식 'x' 'o' 바꾸기 (@는 영향 없음)
		if (bingo[n1 - 1][n2] == 'o')
			bingo[n1 - 1][n2] = 'x';
		else if (bingo[n1 - 1][n2] == 'x')
			bingo[n1 - 1][n2] = 'o';


		if (bingo[n1][n2] == 'o')
			bingo[n1][n2] = 'x';
		else if (bingo[n1][n2] == 'x')
			bingo[n1][n2] = 'o';


		if (bingo[n1 + 1][n2] == 'o')
			bingo[n1 + 1][n2] = 'x';
		else if (bingo[n1 + 1][n2] == 'x')
			bingo[n1 + 1][n2] = 'o';


		if (n2 != 0) //이전 행에 영향주는 거 없애기
		{
			if (bingo[n1][n2 - 1] == 'o')
				bingo[n1][n2 - 1] = 'x';
			else if (bingo[n1][n2 - 1] == 'x')
				bingo[n1][n2 - 1] = 'o';
		}
		if (n2 != 4) //다음 행에 영향주는 거 없애기
		{
			if (bingo[n1][n2 + 1] == 'o')
				bingo[n1][n2 + 1] = 'x';
			else if (bingo[n1][n2 + 1] == 'x')
				bingo[n1][n2 + 1] = 'o';
		}
}

void CheckBingo(int bingo[][5], int BingoCheck[]) //빙고 체크
{
	int i = 0;
	int j = 0;

	// 가로줄 빙고 확인 'x' '@' 둘다 체크
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			if (bingo[i][j] == 'x' || bingo[i][j] == '@')
				BingoCheck[i]++;

	// 세로줄 빙고 확인
	for (i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (bingo[j][i] == 'x' || bingo[j][i] == '@')
				BingoCheck[5 + i]++;

	// 대각선 확인
	for (j = 0; j < 5; j++) // 왼쪽 위에서 오른쪽 아래
		if (bingo[j][j] == 'x' || bingo[j][j] == '@')
			BingoCheck[10]++;

	for (j = 0; j < 5; j++) // 왼쪽 아래에서 오른쪽 위
		if (bingo[4 - j][j] == 'x' || bingo[4 - j][j] == '@')
			BingoCheck[11]++;

}

void ChangeBingoLine(int bingo[][5], int BingoCheck[]) // 빙고 완성된 줄 'x'를 '@'로 바꾸기
{
	int i = 0, j = 0;
	
	for (i = 0; i < 12; i++)
		if (BingoCheck[i] == 5)
		{
			// 가로줄 빙고 라인 'x' 를 '@'로 바꾸기
			if (i < 5)
			{
				for (j = 0; j < 5; j++)
					bingo[i][j] = '@';
			}
			// 세로줄 빙고 라인 'x' 를 '@'로 바꾸기
			else if ((i >= 5) && (i < 10))
				for (j = 0; j < 5; j++)
					bingo[j][i - 5] = '@';

			// 대각선 빙고 라인 'x' 를 '@'로 바꾸기
			else if (i == 10)
				for (j = 0; j < 5; j++)
					bingo[j][j] = '@';
			else if (i == 11)
				for (j = 0; j < 5; j++)
					bingo[4 - j][j] = '@';
		}
}

void CountBingo(int BingoCheck[12], int count[18],int k) // 빙고 몇줄인지 카운트
{
	
	int i = 0;
	for (i = 0; i < 18; i++)
		if (BingoCheck[i] == 5)
			count[k]++;
		
}

int GameResult(int bingo[][5], int count[18], int k)
{
	// 3의 배수 차례일때 빙고 달성 여부 확인

	if (k % 3 == 0)
		if (count[k] == count[k - 1]) // 이전 라운드에 빙고가 된 라인 개수와 현재 라운드 빙고가 된 라인 개수 비교하여 같으면 게임오버
		{
			system("cls");
			PrintBoard(bingo);
			printf("\nGAME OVER \n");
			return 0;
		}
	if (k < 9) // 9라운드 이전에 올빙고하면 실패
		if (count[k] == 12)
		{
			system("cls");
			PrintBoard(bingo);
			printf("\nGAME OVER \n");
			return 0;
		}
	if (k == 9) // 9라운드까지 버티면 승리
	{
			system("cls");
			PrintBoard(bingo);
			printf("\nVictory!\n");
			return  0;
	}
		else
			return 1;
}
