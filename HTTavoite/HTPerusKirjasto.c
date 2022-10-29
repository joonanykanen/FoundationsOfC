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
/* HTTavoitetaso, HTPerusKirjasto.c */ 

/* Sisällytykset */
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HTPerusKirjasto.h"

char *kysyNimi(char *pNimi, int iValinta) {
    if (iValinta == 1)
        printf("Anna luettavan tiedoston nimi: ");
    else if (iValinta == 3 || iValinta == 4)
        printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return(pNimi);
}

TIEDOT *tiedostoLue(TIEDOT *pAlku, char *pTiedLuku) {
    char aPuskuri[RIVIMERKIT];
    char *pPuskuri = aPuskuri;
    FILE *tiedosto;

    /* Tiedostokahvan avaus*/
    if ((tiedosto = fopen(pTiedLuku, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    /* Listan tyhjennys */
    if (pAlku != NULL)
        pAlku = listaTyhjenna(pAlku);

    /* Puskurista luku ja listan luonti */
    if (fgets(aPuskuri, RIVIMERKIT, tiedosto) == NULL) /* Turhan otsikkorivin luku */
        printf("Analysoitava tiedosto on tyhjä.\n"); 
    while (fgets(aPuskuri, RIVIMERKIT, tiedosto) != NULL) {
        pAlku = listaLisaa(pAlku, pPuskuri);
    }
    fclose(tiedosto);
    printf("Tiedosto '%s' luettu.\n", pTiedLuku);
    return(pAlku);
}

TIEDOT *listaLisaa(TIEDOT *pAlku, char *pRivi) {
    TIEDOT *ptr, *pUusi;
    /* Dynaaminen muistinvaraus linkitetylle listalle */
    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    /* Parsinta */
    pUusi = puskuriParsinta(pUusi, pRivi);
    /* Listaan lisäys */
    if (pAlku == NULL)  /* Ensimmäiselle solmulle */
        pAlku = pUusi;
    else {  /* Lopuille */
        ptr = pAlku;
        while (ptr->pSeuraava != NULL) 
            ptr = ptr->pSeuraava;
        ptr->pSeuraava = pUusi;
    }
    return(pAlku);
}

TIEDOT *puskuriParsinta(TIEDOT *pUusi, char *pRivi) {
    char aPuskuri[RIVIMERKIT];
    char *pPuskuri = aPuskuri;
    if ((pPuskuri = strtok(pRivi, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    memset(&pUusi->tm, 0, sizeof(pUusi->tm));  /* Nollaa tm tietueen käyttämän muistin */
    strptime(pPuskuri, AIKAMUOTO, &pUusi->tm);  /* Aika */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->iViikko = atoi(pPuskuri);  /* Viikot */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lKulutus = atol(pPuskuri);  /* Kulutus */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lAurinkovoima = atol(pPuskuri);  /* Aurinkovoima */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lTuulivoima = atol(pPuskuri);  /* Tuulivoima */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lVesivoima = atol(pPuskuri);  /* Vesivoima */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lYdinvoima = atol(pPuskuri);  /* Ydinvoima */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lYhteistuotanto = atol(pPuskuri);  /* Yhteistuotanto */
    if ((pPuskuri = strtok(NULL, EROTIN)) == NULL) {
        perror("Merkkijonon pilkkominen epäonnistui");
        exit(0);
    }
    pUusi->lLampovoima = atol(pPuskuri);  /* Erillinen lampovoima */
    pUusi->pSeuraava = NULL;
    return(pUusi);
}

TULOS *tulosAnalysoi(TIEDOT *pTiedot, TULOS *pTulos) {
    int iLaskuri = 0;
	TIEDOT *ptr = pTiedot;

    /* Tietueen tyhjennys */
    if (pTulos != NULL) {
        free(pTulos);
        pTulos = NULL;
    }
    /* Muistinvaraus */
    if ((pTulos = (TULOS*)malloc(sizeof(TULOS))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    /* Alustukset laskuja varten */
    pTulos->dYhteisKulutus = 0.0;
    pTulos->lSuurin = ptr->lKulutus;
    pTulos->lPienin = ptr->lKulutus;
    /* Analyysirakenne */
	if (ptr != NULL) {
		while (ptr != NULL) {
            iLaskuri++;
            pTulos->dYhteisKulutus = pTulos->dYhteisKulutus + (double)(ptr->lKulutus);
            pTulos = tulosSuuruus(ptr, pTulos);
			ptr = ptr->pSeuraava;  /* Siirtää liukuria eteenpäin */
		}
		pTulos->iDataAlkiot = iLaskuri;
        pTulos->dKeskiarvo = pTulos->dYhteisKulutus / (double)(pTulos->iDataAlkiot);
	} 
    else 
	    printf("Lista on tyhjä.\n");
    printf("Analysoitu %d mittaustulosta.\n", pTulos->iDataAlkiot);
    printf("Kokonaiskulutus oli yhteensä %.f kWh.\n", pTulos->dYhteisKulutus);
    return(pTulos);
}

TULOS *tulosSuuruus(TIEDOT *ptr, TULOS *pTulos) {
    if (ptr->lKulutus > pTulos->lSuurin) {
        pTulos->lSuurin = ptr->lKulutus;
        strftime(pTulos->aAikaSuurin, AIKAMERKIT, "%d.%m.%Y %H:%M", &ptr->tm);
    }
    if (ptr->lKulutus < pTulos->lPienin) {
        pTulos->lPienin = ptr->lKulutus;
        strftime(pTulos->aAikaPienin, AIKAMERKIT, "%d.%m.%Y %H:%M", &ptr->tm);
    }
    return(pTulos);
}

TULOSKKT *tulosKkAnalysoi(TIEDOT *pTiedot, TULOSKKT *pTulosKk) {
    int iKuukausi;
    int iKuukausiPuskuri;
    double dYhtPuskuri;
	TIEDOT *ptr = pTiedot;

    /* Tietueen tyhjennys */
    if (pTulosKk != NULL) {
        free(pTulosKk);
        pTulosKk = NULL;
    }
    /* Muistinvaraus */
    if ((pTulosKk = (TULOSKKT*)malloc(KUUKAUDET*sizeof(TULOSKKT))) == NULL) {
        perror("Muistinvaraus epäonnistui, lopetetaan");
        exit(0);
    }
    /* Alustukset */
    iKuukausi = ptr->tm.tm_mon + 1;
    dYhtPuskuri = 0.0;
    for (int i = 0; i < KUUKAUDET; i++) {
        pTulosKk[i].iKuukausi = i+1;
        pTulosKk[i].dYhtTuotanto = 0.0;
    }
    /* Analyysirakenne */
	if (ptr != NULL) {
		while (ptr != NULL) {
            iKuukausiPuskuri = ptr->tm.tm_mon + 1;
            if (iKuukausiPuskuri > iKuukausi) {
                pTulosKk[iKuukausi-1].iKuukausi = iKuukausi;
                pTulosKk[iKuukausi-1].dYhtTuotanto = dYhtPuskuri;
                dYhtPuskuri = 0.0;
                iKuukausi = iKuukausiPuskuri;
            }
            dYhtPuskuri =  dYhtPuskuri + (double)ptr->lAurinkovoima +
                    (double)ptr->lTuulivoima + (double)ptr->lVesivoima +
                        (double)ptr->lYdinvoima + (double)ptr->lYhteistuotanto+
                            (double)ptr->lLampovoima;
			ptr = ptr->pSeuraava;  /* Siirtää liukuria eteenpäin */
		}  /* Varmistutaan viimeisen rivin tallennuksesta */
        if (dYhtPuskuri > 0.0) {
            pTulosKk[iKuukausi-1].iKuukausi = iKuukausi;
            pTulosKk[iKuukausi-1].dYhtTuotanto = dYhtPuskuri;
            dYhtPuskuri = 0.0;
            iKuukausi = iKuukausiPuskuri;
        }
	} 
    else 
	    printf("Lista on tyhjä.\n");
    printf("Kuukausittaiset tuotannot analysoitu.\n");
    return(pTulosKk);
}

void tiedostoKirjoita(TULOS *pTulos, TULOSKKT *pTulosKk, char *sKirjoita) {
    FILE *tiedosto;

    /* Standarditulostevirta */
    tiedostoTulosta(pTulos, pTulosKk, stdout);

    if ((tiedosto = fopen(sKirjoita, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    /* Tiedostoon kirjoittaminen */
    tiedostoTulosta(pTulos, pTulosKk, tiedosto);

    fclose(tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", sKirjoita);
    return;
}

void tiedostoTulosta(TULOS *pTulos, TULOSKKT *pTulosKk, FILE *tietovirta) {
    fprintf(tietovirta, "Tilastotiedot %d mittaustuloksesta:\n", pTulos->iDataAlkiot);
    fprintf(tietovirta, "Kulutus oli yhteensä %.lf kWh, ja keskimäärin %.1lf kWh.\n", pTulos->dYhteisKulutus, pTulos->dKeskiarvo);
    fprintf(tietovirta, "Suurin kulutus, %ld kWh, tapahtui %s.\n", pTulos->lSuurin, pTulos->aAikaSuurin);
    fprintf(tietovirta, "Pienin kulutus, %ld kWh, tapahtui %s.\n", pTulos->lPienin, pTulos->aAikaPienin);
    fprintf(tietovirta, "\n");
    fprintf(tietovirta, "Pvm;Tuotanto (GWh)\n");
    for (int i = 0; i < KUUKAUDET; i++)
        fprintf(tietovirta, "Kk %d;%.2lf\n", pTulosKk[i].iKuukausi, pTulosKk[i].dYhtTuotanto/KILOSTAGIGA);
    return;
}

TIEDOT *listaTyhjenna(TIEDOT *pAlku) {
	TIEDOT *ptr = pAlku;
	while (ptr != NULL) {
		pAlku = ptr->pSeuraava;
		free(ptr);
		ptr = pAlku;
	}  /* Viimeinen vaihe jättää palautettavan osoittimen NULLiksi */
	return(pAlku);
}


/* eof */

