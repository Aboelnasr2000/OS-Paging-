#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char technique[10];
int frames;
int array[5000];
int count = 0;

//void reads(char *fileName)
//{
//   FILE *fp;
//    fp=fopen(fileName,"r");
//    if (fp!=NULL)
//    {
//        fscanf(fp, "%d\n", &frames);
//        fscanf(fp, "%s[^\n]", &technique);
//        while (!feof(fp))
//        {
//           fscanf(fp, "%d", &array[count]);
//            count++;
//        }
//    }
//    else
//    {
//        printf("File is empty\n");
//    }
//    fclose(fp);
//}


int initialize(int page_frame[])
{
    int i;
    for (i = 0; i < frames ; i++)
        page_frame[i] = -1;
    return 0;
}

int Available(int buffer[], int page)
{
    int i;
    for (i = 0; i < frames ; i++)
    {
        if (buffer[i] == page)
            return 1;
    }
    return 0;
}
int AvailableLocation(int buffer[], int page)
{
    int i;
    for (i = 0; i < frames ; i++)
    {
        if (buffer[i] == page)
            return i;
    }
    return -1;
}

int Empty(int buffer[])
{
    int i = 0;
    for (i = 0; i < frames; i++)
    {
        if (buffer[i] == -1)
            return i;
    }
    return -1;
}
void OPTIMAL()
{
    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int buffer[frames];
    int i  = 0   ;
    int F  ;
    int PF = 0 ;
    int OP[frames];
    initialize(buffer);
    while(array[i] != -1)
    {
        if(Available(buffer,array[i]) == 1)
        {
            printf("%02d     ", array[i] );
            for(int n=0 ;  n < frames ; n++)
            {
                if(buffer[n] != -1)
                    printf("%02d ", buffer[n]);
            }
            printf("\n");
            i++;
        }
        else
        {

            if (Empty(buffer)!= -1)
            {
                int index = Empty(buffer);
                printf("%02d     ", array[i] );
                buffer[index] = array[i];
                for(int n=0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d  ", buffer[n]);
                }
                printf("\n");
                i++;

            }
            else
            {


                for(int j = 0 ; j<frames ; j++ )
                {
                    F = 0  ;
                    for (int k = i + 1  ; k  < count  ; k++ )
                    {
                        if(buffer[j]  ==  array[k])
                        {
                            OP[j] = k;
                            F = 1;
                            break;
                        }
                        else
                        {
                            F  =  0 ;
                        }
                    }
                    if  ( F == 0 )
                    {
                        OP[j] = -1 ;
                    }
                }
                int max = -10000;
                int index ;
                for (int l = 0; l < frames ; l++)
                {
                    if (OP[l] == -1)
                    {
                        max = OP[l];
                        index = l;
                        break;
                    }
                    if (OP[l] > max)
                    {
                        max = OP[l];
                        index = l;
                    }
                }

                printf( "%02d F  ", array[i] );
                PF = PF + 1;
                buffer[index] = array[i];
                for(int n = 0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf(" %02d", buffer[n]);
                }
                printf("\n");
                i++;

            }


        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", PF  );
}

void LRU()
{
    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int buffer[frames];
    int i  = 0   ;
    int F  ;
    int PF = 0 ;
    int LU[frames];
    initialize(buffer);
    while(array[i] != -1)
    {
        if(Available(buffer,array[i]) == 1)
        {
            printf("%02d     ", array[i] );
            for(int n=0 ;  n < frames ; n++)
            {
                if(buffer[n] != -1)
                    printf("%02d ", buffer[n]);
            }
            printf("\n");
            i++;
        }
        else
        {
            if (Empty(buffer)!= -1)
            {
                int index = Empty(buffer);
                printf("%02d    ", array[i] );
                buffer[index] = array[i];
                for(int n=0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf(" %02d", buffer[n]);

                }
                printf("\n");
                i++;

            }
            else
            {

                for(int j = 0 ; j<frames ; j++ )
                {
                    F = 0  ;
                    for (int k = i - 1  ; k   >= 0  ; k-- )
                    {
                        if(buffer[j]  ==  array[k])
                        {
                            LU[j] = k;
                            F = 1;
                            break;
                        }
                        else
                        {
                            F  =  0 ;
                        }
                    }
                    if  ( F == 0 )
                    {
                        LU[j] = -1 ;
                    }
                }
                int min = 10000;
                int index ;
                for (int l = 0; l < frames ; l++)
                {
                    if (LU[l] < min)
                    {
                        min = LU[l];
                        index = l;
                    }
                }

                printf( "%02d F   ", array[i] );
                PF = PF + 1;
                buffer[index] = array[i];
                for(int n = 0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d ", buffer[n]);

                }
                printf("\n");
                i++;

            }

        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d", PF  );
}


void FIFO()
{
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int buffer[frames];
    int i  = 0   ;
    int FI = 1  ;
    int PF = 0  ;
    initialize(buffer);
    while(array[i] != -1)
    {
        if(Available(buffer,array[i]) == 1)
        {
            printf("%02d     ", array[i] );
            for(int n=0 ;  n < frames ; n++)
            {
                if(buffer[n] != -1)
                    printf("%02d ", buffer[n]);

            }
            printf("\n");
            i++;
        }
        else
        {
            if(buffer[FI-1] == -1)
            {
                printf("%02d     ", array[i] );
                buffer[FI-1] = array[i];
                for(int n=0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d ", buffer[n]);

                }
                FI = ( FI % (frames  ) ) +1;
                printf("\n");
                i++;
            }
            else
            {
                printf( "%02d F   ", array[i] );
                PF = PF + 1;
                buffer[FI-1] = array[i];
                for(int n=0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d ", buffer[n]);
                    else
                        printf(" ");
                }
                FI = ( FI % (frames  ) ) +1;
                printf("\n");
                i++;
            }
        }

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d", PF  );
}

void CLOCK()
{
    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int buffer[frames];
    int i  = 0   ;
    int UBI = 0  ;
    int PF = 0 ;
    int UB[frames];
    initialize(buffer);
    while(array[i] != -1)
    {
        if(Available(buffer,array[i]) == 1)
        {
            UB[AvailableLocation(buffer,array[i])]  = 1;
            printf("%02d     ", array[i] );
            for(int n=0 ;  n < frames ; n++)
            {
                if(buffer[n] != -1)
                    printf("%02d ", buffer[n]);
            }
            printf("\n");
            i++;
        }

        else
        {
            if (Empty(buffer)!= -1)
            {
                int index = Empty(buffer);
                printf("%02d     ", array[i] );
                buffer[index] = array[i];
                UB[AvailableLocation(buffer,array[i])]  = 1;
                UBI =  UBI +1 ;
                if (UBI == frames)
                {
                    UBI  = 0  ;
                }
                for(int n=0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d ", buffer[n]);
                }
                printf("\n");

                i++;

            }
            else
            {
                if (UBI == frames)
                {
                    UBI  = 0  ;
                }
                while (UB[UBI]==1)
                {
                    UB[UBI]=0 ;
                    UBI =  UBI +1  ;
                    if (UBI == frames)
                    {
                        UBI  = 0  ;
                    }
                }
                UBI = (UBI) % (frames) ;


                printf( "%02d F   ", array[i] );
                PF = PF + 1;
                buffer[UBI] = array[i];
                UB[UBI]=1;
                UBI = ( UBI % (frames) ) +1;
                for(int n = 0 ;  n <frames ; n++)
                {
                    if(buffer[n] != -1)
                        printf("%02d ", buffer[n]);
                }
                printf("\n");
                i++;

            }

        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d", PF  );
}



int main()
{
    //char fileName[40];
    //printf("Enter file name : " );
    //scanf("%s",fileName);
    //reads(fileName);

    scanf("%d",&frames);
    scanf("%s",technique);
    while(array[count-1] != -1)
    {
       scanf("%d",&array[count]);
        count++;
    }
    array[count]=-1;

    if(strcmp(technique,"FIFO")== 0  )
    {
        FIFO();
    }
    else if (strcmp(technique,"LRU")== 0  )
    {
        LRU();
    }
    else if(strcmp(technique,"CLOCK")== 0  )
    {
        CLOCK();
    }
    else  if(strcmp(technique,"OPTIMAL")== 0  )
    {
        OPTIMAL();
    }
    else
    {
        printf("Error! operator is not correct");
    }




    return 0;
}
