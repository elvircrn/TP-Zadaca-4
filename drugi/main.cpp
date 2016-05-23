#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <stdexcept>
#include <memory>

#include "NepreklapajuciPravougaonik.h"
int main()
{
    int n;
    std::cout << "Unesite n: ";
    std::cin >> n;
    std::vector <std::shared_ptr<NepreklapajuciPravougaonik> > rekt(n);
    for (int i = 0; i < n; i++)
    {
        Tacka A, B;
        std::cout << "Unesite 1. tjeme pravougaonika " << i+1 << ": ";
        std::cin >> A.x >> A.y;
        std::cout << "Unesite 2. tjeme pravougaonika " << i+1 << ": ";
        std::cin >> B.x >> B.y;
        try
        {
            rekt[i] = std::make_shared <NepreklapajuciPravougaonik>(A, B);
        }
        catch(std::logic_error e)
        {
            std::cout << "GRESKA: ";
            std::cout << e.what()<<"! ";
            std::cout << "Ponovite unos: "<<std::endl;
            i--;
            continue;
        }
    }

    std::sort(rekt.begin(), rekt.end(),[](std::shared_ptr<NepreklapajuciPravougaonik> p1, std::shared_ptr<NepreklapajuciPravougaonik> p2)
    {
        return p1->DajPovrsinu() < p2->DajPovrsinu();
    });

    std::cout<<"Ispis pravougaonika nakon sortiranja: "<<std::endl;

    for (int i = 0; i < n; i++)
    {
        rekt[i]->Ispisi();
        std::cout << std::endl;
    }

    std::cout <<" Podudarni pravougaonici: "<<std::endl;

    bool Ima = false;

    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (DaLiSuPodudarni(*rekt[i], *rekt[j]))
            {
                rekt[i]->Ispisi();
                std::cout << " i ";
                rekt[j]->Ispisi();
                std::cout << std::endl;
                Ima=true;
            }
        }
    }

    if (!Ima)
        std::cout << "Nema podudarnih pravougaonika." << std::endl;

    for (int i = 0; i < n; i++)
        rekt[i] = nullptr;

    return 0;
}
/*
2
0 0
1 1
51 23
31 17



4
0 0
5 10
1 3
5 1
1 1
3 5
5 5
7 7
1 -2
*/



















