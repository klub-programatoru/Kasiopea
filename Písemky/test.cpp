#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;



int changeDigits(vector<char> A, vector<char> B, vector<char> R, bool carry = false)
{
    int a = 0, b = 0, r = 0, count = 0;

    // extract digits
    a = A[A.size() - 1] - '0';
    b = B[B.size() - 1] - '0';
    r = R[R.size() - 1] - '0';
    // delete the last element
    A.pop_back();
    B.pop_back();
    R.pop_back();

    // if this is the first digit, there cannot be a carry
    //special case
    if((A.empty() || B.empty() || R.empty()) && carry == true)
    {
        if(a + b + 1 == r)
        {
            printf("Error a + b + 1 = 0!");
        }
        else if(a + b + 1 == r + 10)
        {
            // if it is possible to have a sum that is less that r + 10
            if(a <= r && b <= r)
            {
                printf("Error a + b + 1 = 0!");
            }
            // otherwise no change can be made
            else
            {
                return 3;
            }
        }
        else if(a + b != r && a + b != r + 10)
        {
            // if it is possible to have sum that is both r and r + 10
            if(a <= r && b <= r)
            {
                printf("Error a + b + 1 = 0!");
            }
            // otherwise there is an error
            else
            {
                return 3;
            }
        }
        else
        {
            printf("First digit error! \n");
        }
    }
    //normal case
    else if(A.size() == 0 || B.size() == 0 || R.size() == 0)
    {
        if(a + b == r)
        {
            return 0;
        }
        else if(a + b == r + 10)
        {
            // if it is possible to have a sum that is less that r + 10
            if(a <= r || b <= r)
            {
                return 1;
            }
            // otherwise no change can be made
            else
            {
                return 2;
            }
        }
        else if(a + b != r && a + b != r + 10)
        {
            // if it is possible to have sum that is both r and r + 10
            if(a <= r || b <= r)
            {
                return 1;
            }
            // otherwise there is an error
            else
            {
                return 2;
            }
        }
        else
        {
            printf("First digit error! \n");
        }
    }

    // there is a carry digit
    if(carry)
    {
        //LAST DIGITS ARE CORRECT
        if(a + b + 1 == r)
        {
            // it is possible to achieve r + 10
            if (a >= r || b >= r)
            {
                count = std::min(changeDigits(A, B, R, true) + 1, changeDigits(A, B, R));
            }
            // otherwise no change can be made
            else
            {
                count = changeDigits(A, B, R);
            }
            
        }
        // LAST DIGITS ARE CORRECT, BUT 10 LESS
        else if(a + b + 1 == r + 10)
        {
            // if it is possible to have a sum that is less that r + 10
            if(a + 1 <= r || b + 1 <= r)
            {
                count = std::min(changeDigits(A, B, R, true), changeDigits(A, B, R) + 1);
            }
            // otherwise no change can be made
            else
            {
                count = changeDigits(A, B, R, true);
            }
        }
        // LAST DIGITS ARE WRONG
        else if(a + b + 1 != r && a + b + 1 != r + 10)
        {
            // if it is possible to have sum that is both r and r + 10
            if((a >= r || b >= r) && (a + 1 <= r || b + 1 <= r))
            {
                count = std::min(changeDigits(A, B, R, true) + 1, changeDigits(A, B, R) + 1);
            }
            // if it is only possible to have a sum that is r
            else if(a >= r || b >= r)
            {
                count = changeDigits(A, B, R, true) + 1;
            }
            // if it is only possible to have a sum that is r + 10
            else if(a + 1 <= r || b + 1 <= r)
            {
                count = changeDigits(A, B, R) + 1;
            }
            // otherwise there is an error
            else
            {
                printf("Error in sum of digits! \n");
            }

        }
        // ERROR
        else
        {
            printf("Error in last digits! \n");
        }
    }
    //there is not a carry digit
    else
    {
        //LAST DIGITS ARE CORRECT
        if(a + b == r)
        {
            // it is possible to achieve r + 10
            if (a + 9 >= r + 10 || b + 9 >= r +10)
            {
                count = std::min(changeDigits(A, B, R, true) + 1, changeDigits(A, B, R));
            }
            // otherwise no change can be made
            else
            {
                count = changeDigits(A, B, R);
            }
            
        }
        // LAST DIGITS ARE CORRECT, BUT 10 LESS
        else if(a + b == r + 10)
        {
            // if it is possible to have a sum that is less that r + 10
            if(a <= r || b <= r)
            {
                count = std::min(changeDigits(A, B, R, true), changeDigits(A, B, R) + 1);
            }
            // otherwise no change can be made
            else
            {
                count = changeDigits(A, B, R, true);
            }
        }
        // LAST DIGITS ARE WRONG
        else if(a + b != r && a + b != r + 10)
        {
            // if it is possible to have sum that is both r and r + 10
            if((a + 9 >= r + 10 || b + 9 >= r + 10) && (a <= r || b <= r))
            {
                count = std::min(changeDigits(A, B, R, true) + 1, changeDigits(A, B, R) + 1);
            }
            // if it is only possible to have a sum that is r
            else if(a + 9 >= r + 10 || b + 9 >= r + 10)
            {
                count = changeDigits(A, B, R, true) + 1;
            }
            // if it is only possible to have a sum that is r + 10
            else if(a <= r || b <= r)
            {
                count = changeDigits(A, B, R) + 1;
            }
            // otherwise there is an error
            else
            {
                printf("Error in sum of digits! \n");
            }

        }
        // ERROR
        else
        {
            printf("Error in last digits! \n");
        }
    }
    
    return count;
}

int main()
{
    int T = 0, N = 0;
    int digits = 0;

    std::ifstream input("E-lehky.txt");
    std::ofstream output("E-vysledek.txt");

    input >> T;
    for (int i = 0; i < T; i++)
    {
        input >> N;
        vector<char> A(N, '!'), B(N, '!'), R(N, '!');

        for(int j = 0; j < N; j++)
        {
            input >> A[j];
        }
        for(int j = 0; j < N; j++)
        {
            input >> B[j];
        }
        for(int j = 0; j < N; j++)
        {
            input >> R[j];
        }

        digits = changeDigits(A, B, R);
        output << to_string(digits) << endl;
    }
    return 0;
}