#include <iostream>
#include <fstream>
#include <string>

/**
 * Funkce s Tvým kódem, která řeší jeden problém.
 * 	
 * Můžeš využít všechny parametry funkce: cena_nakupu, koruny, dvoukoruny, petikoruny, desetikoruny, dvacetikoruny, padesatikoruny
 */
std::string spocitej_vysledek(int cena_nakupu, int koruny, int dvoukoruny, int petikoruny, int desetikoruny, int dvacetikoruny, int padesatikoruny) {
		int celkem_penez;
		std::string vysledek;

    // Zjisti, kolik má Honza vlastně peněz
    celkem_penez = koruny + 2*dvoukoruny + 5*petikoruny + 10*desetikoruny + 20*dvacetikoruny + 50*padesatikoruny;

    // Poté to porovnej s cenou nákupu a zjisti výsledek
    if (celkem_penez < cena_nakupu) {
        vysledek = "NE";
		} else {
        vysledek = "ANO";
		}

    return vysledek;
}

//###########################################################################################
// Všechen kód pod tímto komentářem slouží jen k načítání vstupu a není třeba ho upravovat. #
//###########################################################################################

int main() {
    std::ifstream input("A-tezky.txt");
    std::ofstream output("A-vysledek.txt");

    int T;
    input >> T;

    for (int t = 0; t < T; t++) {
				int cena_nakupu, koruny, dvoukoruny, petikoruny, desetikoruny, dvacetikoruny, padesatikoruny;

				input >> cena_nakupu >> koruny >> dvoukoruny >> petikoruny >> desetikoruny >> dvacetikoruny >> padesatikoruny;

        std::string vysledek = spocitej_vysledek(cena_nakupu, koruny, dvoukoruny, petikoruny, desetikoruny, dvacetikoruny, padesatikoruny);

        output << vysledek << std::endl;
    }

    return 0;
}