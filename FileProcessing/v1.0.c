#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ricerca(FILE *f)
{
    char artista[50];
    char canzone[50];
    
    char target[50];
    int num = 0;
    
    printf("Inserisci l'artista da cercare: ");
    scanf("%s", target);
    
    fscanf(f, "%s%s", artista, canzone);
    while(!feof(f))
    {
        if(strcmp(artista, target) == 0)
        {
            printf("%s\n", canzone);
            num++;
        }
        fscanf(f, "%s%s", artista, canzone);
    }
    printf("Canzoni trovate: %d\n", num);
    
    return;
}

void inserisci(FILE *f)
{
    char canzone[50];
    char artista[50];
    char newart[50];
    char newsong[50];
    FILE *temp;
    int insert = 0;
    
    printf("Inserisci il titolo della canzone da inserire: ");
    scanf("%s", newsong);
    printf("Inserisci il nome dell'artista: ");
    scanf("%s", newart);
    
    if((temp=fopen("temp.txt", "w"))==NULL)
    {
        printf("Il file non può essere creato\n");
        fclose(f);
        return;
    }
    
    fscanf(f, "%s%s", artista, canzone);
    while(!feof(f))
    {
        if(strcmp(artista, newart)==0)
        {
            if(strcmp(canzone, newsong)==0)
            {
                printf("Canzone già presente nel database\n");
                fclose(f);
                fclose(temp);
                remove("temp.txt");
                return;
            }
            else if(strcmp(canzone, newsong) > 0)
            {
                fprintf(temp, "%s\t %s\t\n", newart, newsong);
                insert = 1;
            }
        }
        else if((strcmp(artista, newart) > 0) && (insert == 0))
        {
            fprintf(temp,"%s\t %s\t\n", newart, newsong);
            insert = 1;
        }
        fprintf(temp,"%s\t %s\t\n", artista, canzone);
        fscanf(f,"%s%s", artista, canzone);
    }
    if(insert==0)
    {
        fprintf(temp,"%s\t %s\t\n", newart, newsong);
    }
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

void modifica(FILE *f)
{
    char oldart[50];
    char newart[50];
    char artista[50];
    char canzone[50];
    FILE *temp;
    int insert = 0;
    
    if((temp=fopen("temp.txt", "w"))==NULL)
    {
        printf("Il file non può essere creato\n");
        fclose(f);
        return;
    }
    
    printf("Inserisci il nome dell'artista da modificare: ");
    scanf("%s", oldart);
    printf("Inserisci il nuovo nome dell'artista: ");
    scanf("%s", newart);
    
    fscanf(f, "%s%s", artista, canzone);
    while(!feof(f))
    {
        if(strcmp(artista, oldart) == 0)
        {
            if(insert == 0)
            {
                printf("Canzoni a cui è stato modificato l'artista:\n");
            }
            printf("%s\n", canzone);
            fprintf(temp, "%s\t %s\t\n", newart, canzone);
            insert = 1;
        }
        else
        {
            fprintf(temp, "%s\t %s\t\n", artista, canzone);
        }
        fscanf(f, "%s%s", artista, canzone);
    }
    
    if(insert == 0)
    {
        printf("Artista non trovato\n");
    }
    
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

void elimina(FILE *f)
{
    char artista[50];
    char canzone[50];
    char target[50];
    FILE *temp;
    int deleted = 0;
    
    if((temp=fopen("temp.txt", "w"))==NULL)
    {
        printf("Il file non può essere creato\n");
        fclose(f);
        return;
    }
    
    printf("Inserisci il nome dell'artista da cancellare: ");
    scanf("%s", target);
    
    fscanf(f, "%s%s", artista, canzone);
    while(!feof(f))
    {
        if(strcmp(artista, target) == 0)
        {
            if(deleted == 0)
            {
                printf("Artista %s cancellato\n", target);
                printf("Canzoni cancellate:\n");
            }
            printf("%s\n", canzone);
            deleted = 1;
        }
        else
        {
            fprintf(temp, "%s\t %s\t\n", artista, canzone);
        }
        fscanf(f, "%s%s", artista, canzone);
    }
    
    if(deleted == 0)
    {
        printf("Artista non trovato\n");
    }
    
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

int main(void)
{
    FILE *f;
    int scelta = 0;
    
    printf("Inserisci l'azione da compiere: \n");
    printf("1) Ricerca delle canzoni di un artista \n");
    printf("2) Inserimento di una nuova canzone \n");
    printf("3) Modifica del nome di un artista \n");
    printf("4) Rimozione di un artista \n");
    printf("? ");
    scanf("%d", &scelta);
    
    switch(scelta)
    {
        case 1:
            if((f = fopen("playlist.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            ricerca(f);
            fclose(f);
            break;
            
        case 2:
            if((f = fopen("playlist.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            inserisci(f);
            fclose(f);
            break;
            
        case 3:
            if((f = fopen("playlist.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            modifica(f);
            fclose(f);
            break;
            
        case 4:
            if((f = fopen("playlist.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            elimina(f);
            fclose(f);
            break;
            
        default:
            break;
    }
    return 0;
}
