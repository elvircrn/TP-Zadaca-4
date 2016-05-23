#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stdexcept>
#include <cstring>

#ifndef PRAVOUGAONIK_H
#define PRAVOUGAONIK_H

struct Tacka
{
	double x, y;
};

enum Pozicija { GoreLijevo, GoreDesno, DoljeDesno, DoljeLijevo };
enum Smjer { Nalijevo, Nadesno };

class Pravougaonik
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


    bool contains (const Pravougaonik &p2) const;
    bool overlaps (const Pravougaonik &p2) const;

public:
	Pravougaonik(const Tacka &t1, const Tacka &t2);
	void Postavi(const Tacka &t1, const Tacka &t2);
	void Postavi(Pozicija p, const Tacka &t);
	void Centriraj(const Tacka &t);
	Tacka DajTjeme(Pozicija p) const;
	Tacka DajCentar() const;
	double DajHorizontalnu() const;
	double DajVertikalnu() const;
	double DajObim() const;
	double DajPovrsinu() const;
	static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
	void Transliraj(double delta_x, double delta_y);
	void Rotiraj(const Tacka &t, Smjer s);
	void Ispisi() const;
	friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
	friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
	friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

#endif // PRAVOUGAONIK_H




































