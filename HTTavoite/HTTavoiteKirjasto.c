/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Joona Nykänen
 * Opiskelijanumero: ******
 * Päivämäärä: 6.3.2022
 * Palauttamalla tämän työn arvioitavaksi vakuutan, että  
 * 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin 
 * 2) En ole antanut tätä koodia kenenkään muun käyttöön 
 *  
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat  
 * lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa: 
 * CodeVault: https://www.youtube.com/watch?v=34DnZ2ewyZo
 */ 
/*************************************************************************/ 
/* HTTavoitetaso, HTTavoiteKirjasto.c */ 

/* Sisällytykset */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"

double *tulosViikkoAnalyysi(TIEDOT *pTiedot, double *pTulosMat) {
    int iViikko = pTiedot->iViikko;
    int iViikkoPuskuri;
    double dYhtAurinko = 0.0;
    double dYhtTuuli = 0.0;
    double dYhtVesi = 0.0;
    double dYhtYdin = 0.0;
    double dYhtYht = 0.0;
    double dYhtLampo = 0.0;
	TIEDOT *ptr = pTiedot;

    /* Tietueen tyhjennys */
    if (pTulosMat != NULL) {
        free(pTulosMat);
        pTulosMat = NULL;
    }

    /* Dynaaminen muistinvaraus matriisille */
    if ((pTulosMat = (double*)malloc(SARAKKEET * sizeof(double))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    /* Analyysirakenne */
	if (ptr != NULL) {
		while (ptr != NULL) {
            iViikkoPuskuri = ptr->iViikko;
            if (iViikkoPuskuri > iViikko) {
                /* Suoritetaan muistin uudelleenvaraus luettujen rivien perusteella */
                if ((pTulosMat = (double*)realloc(pTulosMat, iViikkoPuskuri * SARAKKEET * sizeof(double))) == NULL) {
                    perror("Muistinvaraus epäonnistui, lopetetaan");
                    exit(0);
                }
                if ((iViikkoPuskuri - iViikko) > 1) {
                    /* Tämä olettaa, että ensimmäinen alkava rivi on 1 */
                    pTulosMat = matriisiAlustus(pTulosMat, iViikkoPuskuri, iViikko);
                }
                // Tiedon lisäys  HUOM Muuta iLaskuri osoitteet iViikoksi, myös muistinvaraus
                pTulosMat[((iViikko - 1) * SARAKKEET) + AURINKO] = dYhtAurinko; /* Aurinkovoima */
                pTulosMat[((iViikko - 1) * SARAKKEET) + TUULI] = dYhtTuuli; /* Tuulivoima */
                pTulosMat[((iViikko - 1) * SARAKKEET) + VESI] = dYhtVesi; /* Vesivoima */
                pTulosMat[((iViikko - 1) * SARAKKEET) + YDIN] = dYhtYdin; /* Ydinvoima */
                pTulosMat[((iViikko - 1) * SARAKKEET) + YHTEISTUOT] = dYhtYht; /* Yhteistuotanto */
                pTulosMat[((iViikko - 1) * SARAKKEET) + LAMPO] = dYhtLampo; /* Lämpövoima */
                dYhtAurinko = 0.0;
                dYhtTuuli = 0.0;
                dYhtVesi = 0.0;
                dYhtYdin = 0.0;
                dYhtYht = 0.0;
                dYhtLampo = 0.0;
                iViikko = iViikkoPuskuri;
            }
            /* Analyysiä */
            dYhtAurinko = dYhtAurinko + (double)ptr->lAurinkovoima;
            dYhtTuuli = dYhtTuuli + (double)ptr->lTuulivoima;
            dYhtVesi = dYhtVesi + (double)ptr->lVesivoima;
            dYhtYdin = dYhtYdin + (double)ptr->lYdinvoima;
            dYhtYht = dYhtYht + (double)ptr->lYhteistuotanto;
            dYhtLampo = dYhtLampo + (double)ptr->lLampovoima;
			ptr = ptr->pSeuraava;  /* Siirtää liukuria eteenpäin */
		}
        if (iViikkoPuskuri > 0) {  /* Viimeisen rivin tallennus */
            if ((pTulosMat = (double*)realloc(pTulosMat, iViikkoPuskuri * SARAKKEET * sizeof(double))) == NULL) {
                perror("Muistinvaraus epäonnistui, lopetetaan");
                exit(0);
            }
            pTulosMat[((iViikko - 1) * SARAKKEET) + AURINKO] = dYhtAurinko; /* Aurinkovoima */
            pTulosMat[((iViikko - 1) * SARAKKEET) + TUULI] = dYhtTuuli; /* Tuulivoima */
            pTulosMat[((iViikko - 1) * SARAKKEET) + VESI] = dYhtVesi; /* Vesivoima */
            pTulosMat[((iViikko - 1) * SARAKKEET) + YDIN] = dYhtYdin; /* Ydinvoima */
            pTulosMat[((iViikko - 1) * SARAKKEET) + YHTEISTUOT] = dYhtYht; /* Yhteistuotanto */
            pTulosMat[((iViikko - 1) * SARAKKEET) + LAMPO] = dYhtLampo; /* Lämpövoima */
        }
	}
    else 
	    printf("Lista on tyhjä.\n");
    printf("Viikoittaiset tuotannot analysoitu.\n");
    return(pTulosMat);
}

double *matriisiAlustus(double *pTulosMat, int iViikkoPuskuri, int iViikko) {
    int rivit = iViikkoPuskuri - iViikko;
    for (int startti = iViikko; startti < rivit; startti++) {
        pTulosMat[(startti * SARAKKEET) + AURINKO] = 0.0; /* Aurinkovoima */
        pTulosMat[(startti * SARAKKEET) + TUULI] = 0.0; /* Tuulivoima */
        pTulosMat[(startti * SARAKKEET) + VESI] = 0.0; /* Vesivoima */
        pTulosMat[(startti * SARAKKEET) + YDIN] = 0.0; /* Ydinvoima */
        pTulosMat[(startti * SARAKKEET) + YHTEISTUOT] = 0.0; /* Yhteistuotanto */
        pTulosMat[(startti * SARAKKEET) + LAMPO] = 0.0; /* Lämpövoima */
    }
    return(pTulosMat);
}

void tulosViikkoTulostus(double *pTulosMat, char *sKirjoita, TIEDOT *pTiedot) {
    int i, iViikko;
    FILE *tiedosto;

    iViikko = viikkoSelvitys(pTiedot);

    if ((tiedosto = fopen(sKirjoita, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    /* Tiedostoon kirjoittaminen */
    fprintf(tiedosto, "Viikko;Aurinkovoima;Tuulivoima;Vesivoima;Ydinvoima;Yhteistuotanto;Lämpövoima\n");
    for (i = 0; i < iViikko; i++) {
        fprintf(tiedosto, "Vko %d", (i+1));
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + AURINKO])/KILOSTAGIGA);
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + TUULI])/KILOSTAGIGA);
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + VESI])/KILOSTAGIGA);
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + YDIN])/KILOSTAGIGA);
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + YHTEISTUOT])/KILOSTAGIGA);
        fprintf(tiedosto, ";%.2lf", (pTulosMat[(i * SARAKKEET) + LAMPO])/KILOSTAGIGA);
        fprintf(tiedosto, "\n");
    }

    fclose(tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", sKirjoita);
    return;
}

int viikkoSelvitys(TIEDOT *pTiedot) {
    int iViikko = 0;
    TIEDOT *ptr = pTiedot;

	while (ptr != NULL) {
        iViikko = ptr->iViikko;
        pTiedot = ptr->pSeuraava;
        ptr = pTiedot;
    }
    return(iViikko);
}

/* eof */
