#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#define RAND_MAX 0x7fff
#define num 500000

int map[3][3]={{0,0,0},{0,0,0},{0,0,0}};

int vectory_flag(int player_num){
      int flag3=0;
      int flag4=0;
      for(int i=0;i<3;i++){
         int flag1=0;
         int flag2=0;
         for(int h=0;h<3;h++){
               if(map[i][h]==player_num){
                  flag1++;
               }
               if(map[h][i]==player_num){
                  flag2++;
               }
         }
         if(map[i][i]==player_num){
               flag3++;
         }
         if(map[2-i][i]==player_num){
               flag4++;
         }
         if(flag1==3 || flag2==3 || flag3==3 || flag4==3){
               return 1;
         }
      }
      return 0;
}
int win_lost_load(int player_num){
   for(int i=0;i<3;i++){
      for(int h=0;h<3;h++){
         if(map[i][h]==0){
            map[i][h]=player_num;
            if(vectory_flag(player_num)==1){
               map[i][h]=0;
               return i*3+h;
            }
            map[i][h]=0;
         }
      }
   }
   return -1;
}

int main(){
   double QA[10][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
   double QB[10][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
   double PA[9]={0,0,0,0,0,0,0,0,0};
   double PB[9]={0,0,0,0,0,0,0,0,0};
   double maxQA;
   double maxQB;
   int endmap[9];
   int checkmap[10][9];
   int winA=0;
   int winB=0;
   int draw=0;
   double Ta=0.05;
   double aa=0.1;
   double ra=0.7;
   double Tb=0.05;
   double ab=0.1;
   double rb=0.7;
   double allPA;
   double allPB;
   int rA;
   int rB;
   int CA;
   int CB;
   int preA;
   int preB;
   int win_c;
   int flag=0;
   double sikiitiA;
   double sikiitiB;
   int count=0;
   srand((unsigned int)time(NULL));
   while(count < num){
      count++;
      //printf("%d\n",count);
      maxQA=0.0;
      maxQB=0.0;
      preA=0;
      preB=0;
      for(int i=0;i<9;i++){
         endmap[i]=-1;
      }
      for(int i=0;i<10;i++){
         for(int h=0;h<9;h++){
            checkmap[i][h]=-1;
         }
      }
      for(int i=0;i<3;i++){
         for(int h=0;h<3;h++){
            map[i][h]=0;
         }
      }
      while(1){
         //choose
         rA=rand();
         rB=rand();
         allPA=0.0;
         allPB=0.0;
         sikiitiA=0.0;
         sikiitiB=0.0;
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               allPA+=exp(QA[preA][i]/Ta);
            }
         }
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               PA[i]=exp(QA[preA][i]/Ta)/allPA;
            }else{
               PA[i]=0.0;
            }
         }
         for(int i=0;i<9;i++){
            sikiitiA+=PA[i];
            if((double)rA /(double) RAND_MAX <= sikiitiA){
               CA=i;
               break;
            }
         }
         win_c=win_lost_load(1);
         if(win_c!=-1){
            CA=win_c;
         }
         endmap[CA]=1;
         checkmap[preA][CA]=1;
         preA=CA+1;
         map[(int)CA/3][CA%3]=1;
         if(vectory_flag(1)==1){
            winA++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(maxQA<QA[i][h] && checkmap[i][h]==1){
                     maxQA=QA[i][h];
                  }
               }
            }
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(checkmap[i][h]==1){
                     QA[i][h]=(1-aa)*QA[i][h]+aa*(1+ra*maxQA);
                  }else if(checkmap[i][h]==2){
                     QB[i][h]-=0.01;
                  }
               }
            }
            break;
         }
         flag=0;
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(map[i][j]==0 || flag==1){
                  flag=1;
                  break;
               }
            }
         }
         if(flag==0){
            draw++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  QA[i][h]*=0.9;
                  QB[i][h]*=0.9;
               }
            }
            break;
         }
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               allPB+=exp(QB[preB][i]/Tb);
            }
         }
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               PB[i]=exp(QB[preB][i]/Tb)/allPB;
            }else{
               PB[i]=0.0;
            }
         }
         for(int i=0;i<9;i++){
            sikiitiB+=PB[i];
            if((double)rB /(double)RAND_MAX <= sikiitiB){
               CB=i;
               break;
            }
         }
         win_c=win_lost_load(2);
         if(win_c!=-1){
            CB=win_c;
         }
         map[(int)CB/3][CB%3]=2;
         checkmap[preB][CB]=2;
         preB=CB+1;
         endmap[CB]=2;
         if(vectory_flag(2)==1){
            winB++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(maxQB<QB[i][h] && checkmap[i][h]==2){
                     maxQB=QB[i][h];
                  }
               }
            }
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(checkmap[i][h]==2){
                     QB[i][h]=(1-ab)*QB[i][h]+ab*(1+rb*maxQB);
                  }else if(checkmap[i][h]==1){
                     QA[i][h]-=0.01;
                  }
               }
            }
            break;
         }
         flag=0;
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(map[i][j]==0 || flag==1){
                  flag=1;
                  break;
               }
            }
         }
         if(flag==0){
            draw++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  QA[i][h]*=0.9;
                  QB[i][h]*=0.9;
               }
            }
            break;
         }
      }
   }
   printf("--------------------------------\n");
   printf("QA:");
   for(int i=0;i<10;i++){
      for(int h=0;h<9;h++){
         printf("%lf ",QA[i][h]);
      }printf("\n");
   }
   printf("\n");
   printf("QB:");
   for(int i=0;i<10;i++){
      for(int h=0;h<9;h++){
         printf("%lf ",QB[i][h]);
      }printf("\n");
   }
   printf("\n");
   printf("WinA:%d,WinB:%d,Draw:%d\n",winA,winB,draw);
   printf("--------------------------------\n");

   for(int i=0;i<3;i++){
      for(int h=0;h<3;h++){
         map[i][h]=0;
         endmap[i*3+h]=-1;
      }
   }
   for(int i=0;i<10;i++){
      for(int h=0;h<9;h++){
         checkmap[i][h]=-1;
      }
   }
   count=0;
   int num_play=100;
   //test
   while(count < num_play){
      count++;
      //printf("%d\n",count);
      maxQA=0.0;
      maxQB=0.0;
      preA=0;
      preB=0;
      for(int i=0;i<9;i++){
         endmap[i]=-1;
      }
      for(int i=0;i<10;i++){
         for(int h=0;h<9;h++){
            checkmap[i][h]=-1;
         }
      }
      for(int i=0;i<3;i++){
         for(int h=0;h<3;h++){
            map[i][h]=0;
         }
      }
      while(1){
         printf("------------------------\n");
         //choose
         rA=rand();
         allPA=0.0;
         sikiitiA=0.0;
         preA=0;
         preB=0;
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               allPA+=exp(QA[preA][i]/Ta);
            }
         }
         for(int i=0;i<9;i++){
            if(endmap[i]==-1){
               PA[i]=exp(QA[preA][i]/Ta)/allPA;
            }else{
               PA[i]=0.0;
            }
         }
         for(int i=0;i<9;i++){
            sikiitiA+=PA[i];
            //printf("%d %d %f\n",rA,RAND_MAX,(double)rA / (double)RAND_MAX);
            if((double)rA /(double) RAND_MAX <= sikiitiA){
               CA=i;
               break;
            }
         }
         map[(int)CA/3][CA%3]=1;
         checkmap[preA][CA]=1;
         preA=CA+1;
         endmap[CA]=1;
         if(vectory_flag(1)==1){
            printf("lost\n");
            winA++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(maxQA<QA[i][h] && checkmap[i][h]==1){
                     maxQA=QA[i][h];
                  }
               }
            }
            //QA[CA]=(1-aa)*QA[CA]+aa*(1+ra*maxQA);
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(checkmap[i][h]==1){
                     QA[i][h]=(1-aa)*QA[i][h]+aa*(1+ra*maxQA);
                  }
               }
            }
            break;
         }

         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               printf("%2d ",map[i][j]);
            }printf("\n");
         }
         flag=0;
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(map[i][j]==0 || flag==1){
                  flag=1;
                  break;
               }
            }
         }
         printf("flag:%d\n",flag);
         if(flag==0){
            printf("draw\n");
            break;
         }
         int my_choice=0;
         printf("0~8\n");
         while(1){
            scanf("%d",&my_choice);
            CB=my_choice;
            if(endmap[CB]==-1){
               break;
            }
         }
         endmap[CB]=2;
         checkmap[preB][CB]=2;
         preB=CB+1;
         map[(int)CB/3][CB%3]=2;
         if(vectory_flag(2)==1){
            printf("win\n");
            winB++;
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(maxQB<QB[i][h] && checkmap[i][h]==2){
                     maxQB=QB[i][h];
                  }
               }
            }
            for(int i=0;i<10;i++){
               for(int h=0;h<9;h++){
                  if(checkmap[i][h]==2){
                     QB[i][h]=(1-ab)*QB[i][h]+ab*(1+rb*maxQB);
                  }
               }
            }
            break;
         }
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               printf("%2d ",map[i][j]);
            }printf("\n");
         }
               flag=0;
         for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               if(map[i][j]==0 || flag==1){
                  flag=1;
                  break;
               }
            }
         }
         printf("flag:%d\n",flag);
         if(flag==0){
            printf("draw\n");
            break;
         }
      }
   }
   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
         printf("%2d ",map[i][j]);
      }printf("\n");
   }
   return 0;
}