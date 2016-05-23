#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stdexcept>
#include <cstring>

#ifndef NEPREKLAPAJUCIPRAVOUGAONIK_H
#define NEPREKLAPAJUCIPRAVOUGAONIK_H

struct Tacka
{
	double x, y;
};

enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer { Nalijevo, Nadesno };

class NepreklapajuciPravougaonik
{
private:


    std::vector<Tacka> points;

    bool contains(const Tacka &t) const;

    static Tacka rotate(const Tacka &t1, const Smjer &smjer);
    static Tacka diff(const Tacka &t1, const Tacka &t2);
    static Tacka add(const Tacka &t1, const Tacka &t2);
    static int posToInt(Pozicija s);
    static Pozicija intToPos(int index);
    static bool cmp(double a, double b);
    static bool cmp(const Tacka &t1, const Tacka &t2);

    bool contains(const NepreklapajuciPravougaonik &p2) const;
    bool overlaps(const NepreklapajuciPravougaonik &p2) const;


    bool contains(const NepreklapajuciPravougaonik *p2) const;
    bool overlaps(const NepreklapajuciPravougaonik *p2) const;

    NepreklapajuciPravougaonik();
    NepreklapajuciPravougaonik *prev;
    static NepreklapajuciPravougaonik *last;
    NepreklapajuciPravougaonik& operator= (const NepreklapajuciPravougaonik &a);


public:
// []
    NepreklapajuciPravougaonik(const NepreklapajuciPravougaonik &np);
// []
	NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2);
// []
	void Postavi(const Tacka &t1, const Tacka &t2);
// []
	void Postavi(Pozicija p, const Tacka &t);
// []
	void Centriraj(const Tacka &t);
// []
	void Transliraj(double delta_x, double delta_y);
// []
	void Rotiraj(const Tacka &t, Smjer s);
// []
	friend bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
// []
	friend bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
// []
	friend bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);



	Tacka DajTjeme(Pozicija p) const;
	Tacka DajCentar() const;
	double DajHorizontalnu() const;
	double DajVertikalnu() const;
	double DajObim() const;
	double DajPovrsinu() const;
	void Ispisi() const;

//  []
    ~NepreklapajuciPravougaonik();
};

#endif




































