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
/* HTTavoitetaso, HTTavoitetaso.c */ 

/* Sisällytykset */
#include <stdio.h>
#include <stdlib.h>
#include "HTPerusKirjasto.h"

/* Valikko-ohjelma */
int valikko(void) {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("4) Laske viikoittaiset tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

/* Pääohjelma */
int main(void) {
	/* Muuttujien määrittely */
    TIEDOT *pTiedot = NULL;
    TULOS *pTulos = NULL;
    TULOSKKT *pTulosKk = NULL;
    char aTiedostoLuku[TIEDMERKIT];
    char aTiedostoKirjoitus[TIEDMERKIT];
    char *pTiedLuku = aTiedostoLuku;
    char *pTiedKirjoitus = aTiedostoKirjoitus;
    double *pTulosMat = NULL;

	/* Valikkorakenne */
    int iValinta;
    do {
        iValinta = valikko();
        if (iValinta == 1) {
            pTiedLuku = kysyNimi(pTiedLuku, iValinta);
            pTiedot = tiedostoLue(pTiedot, pTiedLuku);
        }
        else if (iValinta == 2) {
            if (pTiedot == NULL) {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
            else {
                pTulos = tulosAnalysoi(pTiedot, pTulos);
                pTulosKk = tulosKkAnalysoi(pTiedot, pTulosKk);
            }
        }
        else if (iValinta == 3) {
            if (pTulos == NULL || pTulosKk == NULL) {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
            else {
                pTiedKirjoitus = kysyNimi(pTiedKirjoitus, iValinta);
                tiedostoKirjoita(pTulos, pTulosKk, pTiedKirjoitus);
            }
        }
        else if (iValinta == 4) {
            if (pTiedot == NULL) {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
            else {
                pTiedKirjoitus = kysyNimi(pTiedKirjoitus, iValinta);
                pTulosMat = tulosViikkoAnalyysi(pTiedot, pTulosMat);
                tulosViikkoTulostus(pTulosMat, pTiedKirjoitus, pTiedot);
            }
        }
        else if (iValinta == 0) {
            // Ohjelmasta poistuminen
        }
        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);

	/* Lopetusrutiinit */
    pTiedot = listaTyhjenna(pTiedot);
    pTiedot = NULL;
    free(pTulos);
    pTulos = NULL;
    free(pTulosKk);
    pTulosKk = NULL;
    free(pTulosMat);
    pTulosMat = NULL;
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

/* eof */
