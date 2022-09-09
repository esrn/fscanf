/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "0.1.2";

int const DB_SIZE = 20;

struct mensch
{
    struct mensch *elternteil;
    struct mensch *kind;
    char nachname[20];
    char vorname[20];
    int  geburtsjahr;
};

typedef struct mensch mensch_dt;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    mensch_dt database[DB_SIZE];
    while(fscanf(filepointer,
                 "%[^,],%[^,],%[^,],%[^,],%d",
                 database[zaehler].elternteil->vorname,
                 database[zaehler].kind->vorname,
                 database[zaehler].nachname,
                 database[zaehler].vorname,
                 &database[zaehler].geburtsjahr)
            != EOF)
    {
        printf("%s, %s, %s, %s, %d \n",
               database[zaehler].elternteil->vorname,
               database[zaehler].kind->vorname,
               database[zaehler].nachname,
               database[zaehler].vorname,
               database[zaehler].geburtsjahr);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
