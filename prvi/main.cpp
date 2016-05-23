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

#include "Pravougaonik.h"

int main()
{
    /*int n;
    Pravougaonik **rectangles;
    try
    {
        std::cout << "Unesite n: ";
        std::cin >> n;

        Pravougaonik **rectangles = new Pravougaonik* [n];

        for (int i = 0; i < n; i++)
        {
            double x1, y1, x2, y2;
            std::cout << "Unesite 1. tjeme pravougaonika " << i + 1 << ": ";
            std::cin >> x1 >> y1;
            std::cout << "Unesite 2. tjeme pravougaonika " << i + 1 << ": ";
            std::cin >> x2 >> y2;
            rectangles [i] = new Pravougaonik(Tacka { x1, y1 }, Tacka { x2, y2 });
        }

        double delta_x, delta_y;

        std::cout << "Unesite podatke za transliranje (dx dy): ";
        std::cin >> delta_x >> delta_y;

        auto sth = [&] (Pravougaonik* p) -> Pravougaonik*
                    {
                        p->Rotiraj(p->DajCentar(), Smjer::Nadesno);
                        p->Transliraj(delta_x, delta_y);
                        return p;
                    };

        std::transform(rectangles, rectangles + n, rectangles, sth);

        std::cout << "Pravougaonici, nakon transformacija:\n";

        std::for_each(rectangles, rectangles + n, [] (Pravougaonik *p) { p->Ispisi(); std::cout << std::endl; });

        double max_area = -1.0;
        int solution;


        std::cout << "Pravougaonik s najvecom povrsinom: ";


        (*std::max_element(rectangles, rectangles + n, [](const Pravougaonik *r1, const Pravougaonik *r2) -> bool
                                                        {
                                                            return r1->DajPovrsinu() < r2->DajPovrsinu();
                                                        }))->Ispisi();

        for (int i = 0; i < n; i++)
            delete rectangles [i];
        delete[] rectangles;
    }
    catch (std::domain_error e)
    {
        std::cout << e.what() << std::endl;
    }*/

    Pravougaonik p ({0, 0}, {100, 100});
    p.Postavi (GoreDesno, {5, 5}); //sad je (0, 0), (5, 5) [DL, GD]
    p.Ispisi(); std::cout << std::endl;
    p.Postavi (DoljeLijevo, {-5, -5}); //sad je (-5, -5), (5, 5)
    p.Ispisi(); std::cout << std::endl;
    auto c = p.DajCentar(); //sad mu je centar na (0, 0)
    std::cout << "Centar: (" << c.x << ", " << c.y << ")" << std::endl;
    p.Postavi (DoljeDesno, {10, 0}); //sad je (-5, 5), (10, 0); [GL, DD]
    p.Ispisi(); std::cout << std::endl;
    auto r = p; //kopija
    r.Rotiraj ({0, 5}, Nadesno);
    r.Ispisi(); std::cout << std::endl;
    auto P = Pravougaonik::Presjek(p, r); //presjek je kvadrat {(-5, 5), (0, 0)} [GL, DD]
    P.Ispisi(); std::cout << std::endl << std::endl;
    Pravougaonik k ({1, 1}, {7, 5}), q (k);
    k.Rotiraj(k.DajTjeme(DoljeDesno), Nadesno); //rotirajmo jednom (uspravan)
    k.Rotiraj(k.DajTjeme(DoljeLijevo), Nadesno); //rotirajmo jednom (horizontalan)
    k.Transliraj(0, k.DajVertikalnu()); //pomjerimo ga "gore"
    //sada je 'k' u ogledalu u odnosu na 'q' (osa ogledaja im je zajednicna vertikalna stranica
    //lijeva od 'k' odnosno desna od 'q')
    //presjek ova dva pravougaonika je, ocito, ta zajednicka stranica (odnosno degenerirani pravougaonik)
    //sa tjemenima GL: (7, 5), GD: (7, 5), DL: (7, 1), DD: (7, 1), W = 0, H = 4
    k.Ispisi(); std::cout << std::endl;
    q.Ispisi(); std::cout << std::endl;
    P = Pravougaonik::Presjek(k, q);
    P.Ispisi(); std::cout << std::endl << "W: " << P.DajHorizontalnu() << ", H: " << P.DajVertikalnu();

	return 0;
}

/*
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



















