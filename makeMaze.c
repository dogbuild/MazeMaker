/* makeMaze.c */
#include        <stdio.h>
#include        <stdlib.h>
#include        <time.h>

#define Wall 1
#define Path 0

int main(){
        int node = 3;//今回はここに記入してnode*nodeサイズの迷路
        int x,y;
        int n;
        int wallx,wally;
        int **maze;
        int *pmaze;
        int focuse;

        if(node < 3){//異常終了
                printf("ﾑﾘﾀﾞﾅ(・×・)\n");
                return 1;
        }

        node += (node+1);       //迷路作成用セル数

        //--領域確保----------------------------------------
        maze = malloc( sizeof(int *)*node );
        pmaze = malloc( sizeof(int)*(node*node) );

        for( n=0;n<node;n++ ){
                maze[n] = pmaze+(n*node);
        }


        for( y=0;y<node;y++ ){
                for( x=0;x<node;x++ ){
                        if( x==0||y==0||x==(node-1)||y==(node-1) ){
                                maze[y][x] = Wall;
                        }else{
                                maze[y][x] = Path;
                        }
                        printf("%2d",maze[y][x]); 
                }
                printf("\n");
        }

        srand((unsigned)time(NULL));

        //壁の作成------------------------------------------
        for( y=2;y<(node-1);y+=2 ){
                for( x=2;x<(node-1);x+=2 ){
                        
                        printf("x=%2d,y=%2d",x,y);
                        maze[y][x] = Wall;//杭を立てる
                        
                        while(1){
                                wallx = x;
                                wally = y;

                                if(y==2){//最初の行のみ上にも棒倒し可能
                                        focuse = rand()%4;
                                }else{
                                        focuse = rand()%3;
                                }
                                switch(focuse){
                                        case 0://右
                                               wallx++;
                                               printf("右→");
                                               break;
                                        case 1://下
                                               wally++;
                                               printf("下→");
                                               break;
                                        case 2://左
                                               wallx--;
                                               printf("左→");
                                               break;
                                        case 3://上
                                               wally--;
                                               printf("上→");
                                               break;
                                }
                                if( maze[wally][wallx]!=Wall ){
                                        printf(" 壁打x=%2d,y=%2d\n",wallx,wally);
                                        maze[wally][wallx] = Wall;
                                        break;//このブレイクは棒倒し成功のため
                                }

                        }
                }
        }


        for( y=0;y<node;y++ ){ //確認用
                for( x=0;x<node;x++ ){
                        if(maze[y][x]==0)/*printf("0");*/printf("  ");
                        else /*printf("1");*/printf("69");
                }
                printf("\n");
        }
        
        //確保領域の開放------------
        free(pmaze);
        free(maze);
        
        return 0;
}