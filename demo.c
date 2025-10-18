#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int width,lenght;


void get_values(){  
    printf("Welcome our snake game...\n");
    printf("Enter your width:");
    scanf("%d",&width);
    
    printf("\nEnter your width:");
    scanf("%d",&lenght);

}
char* prep_game(int width,int lenght){
    char* dizi = (char*)malloc(width*lenght * sizeof(char));
    int gameint= width-2*lenght-2;
    int gameouint= (width*lenght) - gameint;
    int* gamein= (int*)malloc(gameint* sizeof(int));
    int* gameout= (int*)malloc(gameouint* sizeof(int));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < lenght; j++)
        {
            if (i==0|| j==0|| j==lenght-1||i==width-1)
            {
                dizi[i*lenght+j]='#';

            }
            else
            {
                dizi[i*lenght+j]='.';
            }
            
            
            
        }
        
    }
    return dizi;
    
}
void launch_game(char* dizi,int width,int lenght,int gameint,int*gamein){
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < lenght; j++)
        {
            printf("%c",dizi[i*lenght+j]);
        }
        printf("\n");
        
    }
    createhead(dizi,width,lenght, gameint,gamein);
    
}
void createhead(char* dizi, int width, int lenght,int gameint,int*gamein){
    srand(time(NULL));
    int randhead= rand()%(gameint);
    dizi[gamein[randhead]]='*';

}

int main(){

    get_values();
    char* dizi = prep_game(width,lenght);
    launch_game(dizi,width,lenght,gameint,gamein);
    



}