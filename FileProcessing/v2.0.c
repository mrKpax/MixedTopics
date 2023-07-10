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

void insdettagli(char *newart)
{
    char newgruppo[3];
    char newgenere[20];
    int newanni;
    char artista[50];
    char gruppo[3];
    char genere[20];
    int anni;
    FILE *det;
    FILE *temp;
    int insert = 0;
    
    printf("Inserisci i dettagli sul nuovo artista:\n");
    printf("Nome: %s\n", newart);
    printf("Gruppo (si/no): ");
    scanf("%s", newgruppo);
    printf("Età (anagrafica o del gruppo): ");
    scanf("%d", &newanni);
    printf("Genere principale: ");
    scanf("%s", newgenere);
    
    if((det = fopen("details.txt", "r")) == 0)
    {
        printf("Il file non può essere creato\n");
        return;
    }
    
    if((temp = fopen("tempdet.txt", "w")) == 0)
    {
        printf("Il file non può essere creato\n");
        fclose(det);
        return;
    }
    
    fscanf(det, "%s%s%d%s", artista, gruppo, &anni, genere);
    while(!feof(det))
    {
        if(strcmp(artista, newart) == 0)
        {
            printf("Artista già presente\n");
            return;
        }
        else if((strcmp(artista, newart) > 0) && (insert == 0))
        {
            fprintf(temp,"%s\t %s\t %d\t %s\t\n", newart, newgruppo, newanni, newgenere);
            insert = 1;
        }
        fprintf(temp,"%s\t %s\t %d\t %s\t\n", artista, gruppo, anni, genere);
        fscanf(det, "%s%s%d%s", artista, gruppo, &anni, genere);
    }
    if(insert==0)
    {
        fprintf(temp,"%s\t %s\t %d\t %s\t\n", newart, newgruppo, newanni, newgenere);
    }
    fclose(det);
    fclose(temp);
    remove("details.txt");
    rename("tempdet.txt", "details.txt");
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
            insdettagli(newart);
        }
        fprintf(temp,"%s\t %s\t\n", artista, canzone);
        fscanf(f,"%s%s", artista, canzone);
    }
    if(insert==0)
    {
        fprintf(temp,"%s\t %s\t\n", newart, newsong);
        insdettagli(newart);
    }
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

void moddettagli(char *oldart, char *newart)
{
    char artista[50];
    char gruppo[3];
    int anno;
    char genere[20];
    FILE *det;
    FILE *temp;
    
    if((det = fopen("details.txt", "r")) == 0)
    {
        printf("Il file non può essere creato\n");
        return;
    }
    
    if((temp = fopen("tempdet.txt", "w")) == 0)
    {
        printf("Il file non può essere creato\n");
        fclose(det);
        return;
    }
    
    fscanf(det, "%s%s%d%s", artista, gruppo, &anno, genere);
    while(!feof(det))
    {
        if((strcmp(artista, oldart))==0)
        {
            fprintf(temp, "%s\t %s\t %d\t %s\t \n", newart, gruppo, anno, genere);
        }
        else
        {
            fprintf(temp, "%s\t %s\t %d\t %s\t \n", artista, gruppo, anno, genere);
        }
        fscanf(det, "%s%s%d%s", artista, gruppo, &anno, genere);
    }
    fclose(det);
    fclose(temp);
    remove("details.txt");
    rename("tempdet.txt", "details.txt");
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
    
    moddettagli(oldart, newart);
    
    if(insert == 0)
    {
        printf("Artista non trovato\n");
    }
    
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

void eliminadet(char *target)
{
    char artista[50];
    char gruppo[3];
    int anno;
    char genere[20];
    FILE *det;
    FILE *temp;
    
    if((det = fopen("details.txt", "r")) == 0)
    {
        printf("Il file non può essere creato\n");
        return;
    }
    
    if((temp = fopen("tempdet.txt", "w")) == 0)
    {
        printf("Il file non può essere creato\n");
        fclose(det);
        return;
    }
    
    fscanf(det, "%s%s%d%s", artista, gruppo, &anno, genere);
    while(!feof(det))
    {
        if(strcmp(artista, target) == 0)
        {
            printf("Dettagli artista %s rimossi\n", artista);
        }
        else
        {
            fprintf(temp, "%s\t %s\t %d\t %s\n", artista, gruppo, anno, genere);
        }
        fscanf(det, "%s%s%d%s", artista, gruppo, &anno, genere);
    }
    fclose(det);
    fclose(temp);
    remove("details.txt");
    rename("tempdet.txt", "details.txt");
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
    eliminadet(target);
    
    if(deleted == 0)
    {
        printf("Artista non trovato\n");
    }
    
    fclose(temp);
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    return;
}

void ricavanzata(FILE *p, FILE *d)
{
    char artista[50];
    char gruppo[50];
    int anno;
    char genere[20];
    
    char artplay[50];
    char canzone[50];
    
    int n = 0;
    
    fscanf(d, "%s%s%d%s", artista, gruppo, &anno, genere);
    while(!feof(d))
    {
        if( ((strcmp(gruppo, "si")==0) && (anno<5)) || ((strcmp(gruppo, "no")==0) && (anno<30)) )
        {
            fscanf(p, "%s%s", artplay, canzone);
            while(!feof(p))
            {
                if((strcmp(artista, artplay)) == 0)
                {
                    printf("%s\t%s\n", artplay, canzone);
                    n++;
                }
                fscanf(p, "%s%s", artplay, canzone);
            }
            rewind(p);
        }
        fscanf(d, "%s%s%d%s", artista, gruppo, &anno, genere);
    }
    printf("Canzoni trovate: %d\n", n);
    return;
}

int main(void)
{
    FILE *f;
    FILE *d;
    int scelta = 0;
    
    printf("1) Ricerca delle canzoni di un artista \n");
    printf("2) Inserimento di una nuova canzone \n");
    printf("3) Modifica del nome di un artista \n");
    printf("4) Rimozione di un artista \n");
    printf("5) Ricerca delle canzoni di artista under 30 o gruppo under 5 \n");
    printf("Inserisci l'azione da compiere: ");
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
            
        case 5:
            if((f = fopen("playlist.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            if((d = fopen("details.txt", "r")) == NULL)
            {
                fprintf(stderr, "File non aperto\n");
                return -1;
            }
            ricavanzata(f, d);
            fclose(f);
            fclose(d);
            break;
            
        default:
            break;
    }
    return 0;
}
