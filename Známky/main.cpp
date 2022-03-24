#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Funkce s Tvým kódem, která řeší jeden problém.
 * 	
 * Můžeš využít všechny parametry funkce: cena_nakupu, koruny, dvoukoruny, petikoruny, desetikoruny, dvacetikoruny, padesatikoruny
 */
std::string get_result(vector<int> &tests) {
		int odds = 0;
        int evens = 0;
		std::string result;

        for(int i = 0; i < tests.size(); i++)
        {
            if(tests[i] % 2 == 0)
            {
                evens++;
            }
        }

    

    // Poté to porovnej s cenou nákupu a zjisti výsledek
    if (evens > (tests.size()/2)) {
        result = "ANO";
		} else {
        result = "NE";
		}

    return result;
}

//###########################################################################################
// Všechen kód pod tímto komentářem slouží jen k načítání vstupu a není třeba ho upravovat. #
//###########################################################################################

int main() {
    std::ifstream input("B-tezky.txt");
    std::ofstream output("B-vysledek.txt");

    int T;
    int test;
    int num_days;
    vector<int> tests;
    input >> T;

    for (int t = 0; t < T; t++) {
		input >> num_days;
        tests.clear();

        for(int i = 0; i < num_days; i++)
        {
            input >> test;
            tests.push_back(test);
        }

        std::string result = get_result(tests);

        output << result << std::endl;
    }

    return 0;
}