/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Joona Nykänen
 * Opiskelijanumero: ******
 * Päivämäärä: 4.3.2022
 * Palauttamalla tämän työn arvioitavaksi vakuutan, että  
 * 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin 
 * 2) En ole antanut tätä koodia kenenkään muun käyttöön 
 *  
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat  
 * lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa: 
 * CodeVault: https://www.youtube.com/watch?v=34DnZ2ewyZo
 */ 
/*************************************************************************/ 
/* HTTavoitetaso, HTPerusKirjasto.h */ 


#ifndef HTPERUSKIRJASTO_H  /* Ehdollinen sisällytys */
#define HTPERUSKIRJASTO_H

#include <time.h>  /* Jotta tietue tietää tm viemän tilan */

/* Kiintoarvot */
#define AIKAMERKIT 20
#define RIVIMERKIT 150
#define TIEDMERKIT 30
#define KUUKAUDET 12
#define KILOSTAGIGA 1000000
#define EROTIN ";"
#define AIKAMUOTO "%d.%m.%Y %H:%M"
#define _XOPEN_SOURCE
#define SARAKKEET 6
#define AURINKO 0
#define TUULI 1
#define VESI 2
#define YDIN 3
#define YHTEISTUOT 4
#define LAMPO 5

/* Tietueet */
typedef struct tiedot {
    int iViikko;
    long lKulutus;
    long lAurinkovoima;
    long lTuulivoima;
    long lVesivoima;
    long lYdinvoima;
    long lYhteistuotanto;
    long lLampovoima;
    struct tm tm;
    struct tiedot *pSeuraava;
} TIEDOT;

typedef struct tulos {
    int iDataAlkiot;
    double dYhteisKulutus;
    double dKeskiarvo;
    long lSuurin;
    long lPienin;
    char aAikaSuurin[AIKAMERKIT];
    char aAikaPienin[AIKAMERKIT];
} TULOS;

typedef struct tuloskkt {
    int iKuukausi;
    double dYhtTuotanto;
} TULOSKKT;


/* HTPerusKirjasto esittelyt */
char *kysyNimi(char *pNimi, int iValinta);
TIEDOT *tiedostoLue(TIEDOT *pAlku, char *pTiedLuku);
TIEDOT *listaLisaa(TIEDOT *pAlku, char *pRivi);
TIEDOT *puskuriParsinta(TIEDOT *pUusi, char *pRivi);
TULOS *tulosAnalysoi(TIEDOT *pTiedot, TULOS *pTulos);
TULOS *tulosSuuruus(TIEDOT *ptr, TULOS *pTulos);
TULOSKKT *tulosKkAnalysoi(TIEDOT *pTiedot, TULOSKKT *pTulosKk);
void tiedostoKirjoita(TULOS *pTulos, TULOSKKT *pTulosKk, char *sKirjoita);
void tiedostoTulosta(TULOS *pTulos, TULOSKKT *pTulosKk, FILE *tietovirta);
TIEDOT *listaTyhjenna(TIEDOT *pAlku);

/* HTTavoiteKirjasto esittelyt */
double *tulosViikkoAnalyysi(TIEDOT *pTiedot, double *pMat);
double *matriisiAlustus(double *pTulosMat, int iViikkoPuskuri, int iViikko);
void tulosViikkoTulostus(double *pTulosMat, char *sKirjoita, TIEDOT *pTiedot);
int viikkoSelvitys(TIEDOT *pTiedot);

#endif  /* Ehdollinen sisällytys päättyy */

/* eof */
