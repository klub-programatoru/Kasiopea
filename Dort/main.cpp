#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> get_row(vector<vector<int>> tab, int size, int K, int R, int S) {
    int color = 0;
    int count_y = 0;
    int count_x = 0;
    int last_y = -1;
    int last_x = -1;
    bool used = false;

    if(size == K || K < R || K < S)
    {
        return tab;
    }

    for(int j = 0; j < S; j++)
    {
        last_y = 0;
        for(int i = 0; i < R; i++)
        {
            last_x = 0;
            //Free cell
            if(tab[i][j] == -1)
            {
                count_y = 0;
                count_x = 0;
                //Find first filled cell in a column
                for(int k = i; k < R; k++)
                {
                    if(tab[k][j] == -1)
                    {
                        count_y++;
                    }
                    else
                    {
                        color = tab[k][j];
                        break;
                    }
                }
                
                //nothing in column found
                if(count_y == R)
                {
                    printf("Not possible!");
                    return {};
                    
                }
                //Reached end of column
                else if(count_y == R - i && last_y != 0)
                {
                    for(int y = last_y + 1; y < R; y++)
                    {
                        tab[y][j] = color;
                    }
                    i = R - 1;
                }
                //sothething in column found
                else
                {
                    for(int y = i; y < i + count_y; y++)
                    {
                        tab[y][j] = color;
                    }
                    i += count_y;
                    last_y = i;

                }
                
            }
            //Colored cell
            else
            {
                last_y = i;
            }
        }
    }

    return tab;
}
/**
 * Funkce s Tvým kódem, která řeší jeden problém.
 * 	
 * Můžeš využít všechny parametry funkce: cena_nakupu, koruny, dvoukoruny, petikoruny, desetikoruny, dvacetikoruny, padesatikoruny
 */
vector<vector<int>> spocitej_vysledek(vector<vector<int>> tab, int size, int K, int R, int S) {
    int color = 0;
    int count_y = 0;
    int count_x = 0;
    int last_y = -1;
    int last_x = -1;
    vector<int> values;
    int last = 0;
    bool used = false;

    if(size == K || K < R || K < S)
    {
        return tab;
    }

    for(int i = 0; i < R; i++)
    {
        last_y = 0;
        for(int j = 0; j < S; j++)
        {
            last_x = 0;
            //Free cell
            if(tab[i][j] == -1)
            {
                count_y = 0;
                count_x = 0;
                //Find first filled cell in a column
                for(int k = j; k < S; k++)
                {
                    if(tab[i][k] == -1)
                    {
                        count_y++;
                    }
                    else
                    {
                        color = tab[i][k];
                        break;
                    }
                }
                
                //nothing in column found
                if(count_y == S)
                {
                    values.clear();
                    if(i != 0)
                    {
                        for(int a = 0; a < S; a++)
                        {
                            if (tab[i-1][a] != last)
                            {
                                values.push_back(tab[i-1][a]);
                                last = tab[i-1][a];
                            }
                            
                        }
                    }
                    if(i != R)
                    {
                        for(int a = 0; a < S; a++)
                        {
                            if (tab[i+1][a] != last && tab[i+1][a] != -1)
                            {
                                values.push_back(tab[i+1][a]);
                                last = tab[i+1][a];
                            }
                        }
                    }
                    

                    for(int c = 1; c < K; c++)
                    {
                        used = false;
                        for(int d = 0; d < values.size(); d++)
                        {
                            if(c == d)
                            {
                                used = true;
                            }
                        }
                        if(!used)
                        {
                            for(int a = 0; a < S; a++)
                            {
                                tab[i][a] = c;
                            }
                            break;
                        }
                    }
                }
                //Reached end of column
                else if(count_y == S - j && last_y != 0)
                {
                    for(int y = last_y + 1; y < S; y++)
                    {
                        tab[i][y] = color;
                    }
                    j = S - 1;
                }
                //sothething in column found
                else
                {
                    for(int y = j; y < j + count_y; y++)
                    {
                        tab[i][y] = color;
                    }
                    j += count_y;
                    last_y = j;

                }
                
            }
            //Colored cell
            else
            {
                last_y = j;
            }
        }
    }

    return tab;
}

//###########################################################################################
// Všechen kód pod tímto komentářem slouží jen k načítání vstupu a není třeba ho upravovat. #
//###########################################################################################

int main() {
    std::ifstream input("C-tezky.txt");
    std::ofstream output("C-vysledek.txt");

    

    int T, R, S, K;
    input >> T;

    for (int t = 0; t < T; t++) {
		input >> R >> S >> K;
        vector<vector<int>> tab(R, vector<int>(S, 0));
        vector<vector<int>> test(R, vector<int>(S, 0));

        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < S; j++)
            {
                input >> tab[i][j];
            }
        }

        test = spocitej_vysledek(tab, R*S, K, R, S);

        if(test.empty())
        {
            test = get_row(tab, R*S, K, R, S);
            if (!test.empty())
            {
                tab = test;
            }
        }
        else
        {
            tab = test;
        }
        
        for (int i = 0; i < R; i++)
        {
            for(int j = 0; j < S; j++)
            {
                if(j != S - 1)
                {
                    output << to_string(tab[i][j]) + ' ';
                }
                else
                {
                    output << to_string(tab[i][j]) << std::endl;
                }
                 
            }
        }
    }

    return 0;
}