#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int mine[9][9];
void initMine(){
	int placed = 0;
	while(placed < 10){
		int r = rand() % 9;
		int c = rand() % 9;
		if(mine[r][c] == 0){
			mine[r][c] = 1;
			placed++;
		}
	}
}

void initshow(char show[9][9]){
	int i,j;
	for(i = 0;i < 9;i++){
		for(j = 0;j < 9;j++){
			show[i][j] = '#';
		}
	} 
}

void printBoard(char show[9][9]){
	int i,j;
	for(i = 0;i < 9;i++){
		for(j = 0;j < 9;j++){
			printf("%c ",show[i][j]);
		}
		printf("\n");
	}
}

void openCell(int i,int j,char show[9][9],int cnt[9][9]){
	if(mine[i][j] == 1){
		show[i][j] = 'X';
		return;
	}
	show[i][j] = (cnt[i][j] == 0) ? '.': cnt[i][j] + '0'; 
}

void countMine(int cnt[9][9])
{
    int i, j, dr, dc;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
        {
            int c = 0;                    
            for (dr = -1; dr <= 1; dr++)
                for (dc = -1; dc <= 1; dc++)
                {
                    if (dr == 0 && dc == 0) continue;
                    int nr = i + dr, nc = j + dc;
                    if (nr < 0 || nr >= 9 || nc < 0 || nc >= 9) continue;
                    if (mine[nr][nc] == 1) c++;
                }
            cnt[i][j] = c;
        }
}

int isWin(char show[9][9]){
	int i,j,opened = 0;
	for(i = 0;i < 9; i++){
		for(j = 0;j < 9;j++){
			if(show[i][j] != '#' && show[i][j] !='F'){
				opened++;
			}
		}
	}
	return opened == 81 - 10;
}

int main(){
	int i,j;
	char show[9][9];
	int cnt[9][9];
	
	srand((unsigned)time(NULL));
	initMine();
	countMine(cnt);
	initshow(show);
	
	 while (1){
    printf("输入行列(0-8): ");
    fflush(stdout);
    scanf("%d %d", &i, &j);
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
    {
        printf("超范围，重输\n");
        continue;
    }
    openCell(i, j, show, cnt);
    printBoard(show);              
    if (show[i][j] == 'X') { printf("boom\n"); break; }
    if (isWin(show))       { printf("win\n");  break; }
	}
	return 0;
}
