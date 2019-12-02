/* testMazeMatrix.c */
/*無理やり統合したもの*/
#include        <stdio.h>
#include        <stdlib.h>
#include        <time.h>

#define Wall 1
#define Path 0
#define N 10;

int main(){
        int node = N;//今回はここに記入してnode*nodeサイズの迷路
        int x,y;
        int n;
        int wallx,wally;
        int **maze;
        int *pmaze;
        int focuse;

        int Basenode;
        int Totalnode;
        int Mtr;//隣接行列座標
        int **Matrix; //隣接行列
        int *pMatrix;

        Totalnode = node*node;//ノード数(総数)
        Basenode = node;

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

        //領域の動的確保
        Matrix = malloc( sizeof(int *)*Totalnode );
        pMatrix = malloc( sizeof(int)*(Totalnode*Totalnode) );
        for( n=0;n<Totalnode;n++ ){
                Matrix[n] = pMatrix+(n*Totalnode);
        }

        //隣接行列の全てに 0を代入
        for( y=0;y<Totalnode;y++ ){
                for( x=0;x<Totalnode;x++ ){
                        Matrix[x][y] = 0;
                        //printf("%2d",Matrix[x][y]); 
                }
                //printf("\n");
        }


        for( y=0;y<node;y++ ){
                for( x=0;x<node;x++ ){
                        if( x==0||y==0||x==(node-1)||y==(node-1) ){
                                maze[y][x] = Wall;
                        }else{
                                maze[y][x] = Path;
                        }
                        //printf("%2d",maze[y][x]); 
                }
                //printf("\n");
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

        //ノード識別
        for( x=1;x<node;x+=2 ){
                for( y=(node-2);y>0;y-=2 ){
                        printf("識別内(%d,%d)node:%d\n",x,y,Mtr);
                        if(maze[y][x+1]==0){Matrix[Mtr+Basenode][Mtr]=1; Matrix[Mtr][Mtr+Basenode]=1;printf("maze[%d][%d]=%d 右M(%d,%d)\n",x+1,y,maze[y][x+1],Mtr,Mtr);}//右
                        if(maze[y][x-1]==0){Matrix[Mtr-Basenode][Mtr]=1; Matrix[Mtr][Mtr-Basenode]=1;printf("maze[%d][%d]=%d 左M(%d,%d)\n",x-1,y,maze[y][x-1],Mtr,Mtr);}//左
                        if(maze[y-1][x]==0){Matrix[Mtr+1][Mtr]=1; Matrix[Mtr][Mtr+1]=1;printf("maze[%d][%d]=%d 上M(%d,%d)\n",x,y+1,maze[y-1][x],Mtr,Mtr);}//上
                        if(maze[y+1][x]==0){Matrix[Mtr-1][Mtr]=1; Matrix[Mtr][Mtr-1]=1;printf("maze[%d][%d]=%d 下M(%d,%d)\n",x,y+1,maze[y+1][x],Mtr,Mtr);}//下
                        Mtr += 1;
                }
        }

        printf("\nmaze確認用\n");
        for( y=0;y<node;y++ ){ //確認用
                for( x=0;x<node;x++ ){
                        if(maze[y][x]==0)/*printf("0");*/printf("  ");
                        else /*printf("1");*/printf("69");
                }
                printf("\n");
        }


        printf("\n");
        for( y=0;y<Totalnode;y++ ){
                for( x=0;x<Totalnode;x++ ){
                        printf("%2d",Matrix[x][y]); 
                }
                printf("\n");
        }

        free(pMatrix);
        free(Matrix);


        // for( y=0;y<node;y++ ){ //確認用
        //         for( x=0;x<node;x++ ){
        //                 if(maze[y][x]==0)/*printf("0");*/printf("  ");
        //                 else /*printf("1");*/printf("69");
        //         }
        //         printf("\n");
        // }
        
        //確保領域の開放------------
        free(pmaze);
        free(maze);
        
        return 0;
}