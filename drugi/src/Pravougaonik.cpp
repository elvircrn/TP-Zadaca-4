#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "Pravougaonik.h"

Pozicija Pravougaonik::intToPos(int index)
{
    if (index == 0)
        return Pozicija::GoreLijevo;
    else if (index == 1)
        return Pozicija::GoreDesno;
    else if (index == 2)
        return Pozicija::DoljeDesno;
    else
        return Pozicija::DoljeLijevo;
}

Tacka Pravougaonik::rotate(const Tacka &t1, const Smjer &smjer)
{
    float x = t1.x;
    float y = t1.y;

    if (smjer == Smjer::Nalijevo)
        return { y, -x };
    else
        return { -y, x };
}

Tacka Pravougaonik::diff(const Tacka &t1, const Tacka &t2)
{
    return Tacka { t1.x - t2.x, t1.y - t2.y };
}

Tacka Pravougaonik::add(const Tacka &t1, const Tacka &t2)
{
    return Tacka { t1.x + t2.x, t1.y + t2.y };
}

Tacka Pravougaonik::DajCentar() const
{
    return Tacka { (points [0].x + points [2].x) / 2.0, (points [0].y + points [2].y) / 2.0 };
}

Tacka Pravougaonik::DajTjeme(Pozicija p) const
{
    return points [posToInt(p)];
}

Pravougaonik::Pravougaonik(const Tacka &t1, const Tacka &t2)
{
    Postavi(t1, t2);
}

void Pravougaonik::Centriraj(const Tacka &t)
{
    double width  = std::abs(points [0].x - points [2].x);
    double height = std::abs(points [0].y - points [2].y);

    Tacka center = t;

    points = { { center.x - width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y - height / 2.0 },
               { center.x - width / 2.0, center.y - height / 2.0 } };
}


void Pravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    Tacka center = Tacka { (t1.x + t2.x) / 2.0, (t1.y + t2.y) / 2.0 };

    double width  = std::abs(t1.x - t2.x);
    double height = std::abs(t1.y - t2.y);

    points = { { center.x - width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y - height / 2.0 },
               { center.x - width / 2.0, center.y - height / 2.0 } };
}

int Pravougaonik::posToInt(Pozicija s)
{
    if (s == Pozicija::GoreLijevo)
        return 0;
    else if (s == Pozicija::GoreDesno)
        return 1;
    else if (s == Pozicija::DoljeDesno)
        return 2;
    else
        return 3;
}

void Pravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    Tacka offset = diff(t, points [Pravougaonik::posToInt(p)]);
    for (Tacka &p : points)
        p = add(p, offset);
}

double Pravougaonik::DajHorizontalnu() const
{
    return std::abs(points [0].x - points [1].x);
}

double Pravougaonik::DajVertikalnu() const
{
    return std::abs(points [0].y - points [3].y);
}

double Pravougaonik::DajObim() const
{
    return 2 * DajHorizontalnu() + 2 * DajVertikalnu();
}

double Pravougaonik::DajPovrsinu() const
{
    return DajHorizontalnu() * DajVertikalnu();
}

bool Pravougaonik::cmp(double a, double b)
{
    return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

bool Pravougaonik::cmp(const Tacka &a, const Tacka &b)
{
    return cmp (a.x, b.x) && cmp (a.y, b.y);
}

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2)
{
    for (Tacka p : p1.points)
    {
        bool ret = false;
        for (Tacka q : p2.points)
            ret |= Pravougaonik::cmp(p, q);

        if (!ret)
            return false;
    }

    return true;
}

bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    return Pravougaonik::cmp (std::min (p1.DajHorizontalnu(), p1.DajVertikalnu()), std::min (p2.DajHorizontalnu(), p2.DajVertikalnu())) &&
           Pravougaonik::cmp (std::max (p1.DajHorizontalnu(), p1.DajVertikalnu()), std::max (p2.DajHorizontalnu(), p2.DajVertikalnu()));
}

bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2)
{
    return Pravougaonik::cmp(p1.DajHorizontalnu() / p2.DajHorizontalnu(),
                             p1.DajVertikalnu() / p2.DajVertikalnu());
}

bool Pravougaonik::contains(const Tacka &t) const
{
    return (points [3].x < t.x || cmp (points [3].x, t.x)) &&
           (points [3].x + DajHorizontalnu() > t.x || cmp (points [3].x + DajHorizontalnu(), t.x)) &&
           (points [3].y < t.y || (points [3].y, t.y)) &&
           (points [3].y + DajVertikalnu() > t.y || cmp (points [3].y + DajVertikalnu(), t.y));
}

bool Pravougaonik::contains(const Pravougaonik &p2) const
{
    for (int i = 0; i < 4; i++)
        if (!contains (p2.DajTjeme(intToPos(i))))
            return false;
    return true;
}

bool Pravougaonik::overlaps(const Pravougaonik &p2) const
{
    Pravougaonik p1 = (*this);

    if (p1.contains(p2) || p2.contains(p1))
        return false;

    return p1.DajTjeme(Pozicija::DoljeLijevo).x < p2.DajTjeme(Pozicija::DoljeLijevo).x + p2.DajHorizontalnu() &&
           p1.DajTjeme(Pozicija::DoljeLijevo).x + p1.DajHorizontalnu() > p2.DajTjeme(Pozicija::DoljeLijevo).x &&
           p1.DajTjeme(Pozicija::DoljeLijevo).y < p2.DajTjeme(Pozicija::DoljeLijevo).y + p2.DajVertikalnu() &&
           p1.DajTjeme(Pozicija::DoljeLijevo).y + p1.DajVertikalnu() > p2.DajTjeme(Pozicija::DoljeLijevo).y;
}

Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2)
{
    if (DaLiSePoklapaju(p1, p2))
        return p1;


    if (p1.overlaps(p2))
    {
        double ix, iy, iwidth, iheight;
        ix = std::max(p1.points [3].x, p2.points [3].x);
        iy = std::max(p1.points [3].y, p2.points [3].y);

        iwidth = std::min(p1.points [3].x + p1.DajHorizontalnu(), p2.points [3].x + p2.DajHorizontalnu()) - ix;
        iheight = std::min(p1.points [3].y + p1.DajVertikalnu(), p2.points [3].y + p2.DajVertikalnu()) - iy;

        return Pravougaonik({ ix, iy }, { ix + iwidth, iy + iheight });
    }
    else
        throw std::domain_error("Pravougaonici se ne presjecaju");
}

void Pravougaonik::Transliraj(double delta_x, double delta_y)
{
    Centriraj(add (DajCentar(), { delta_x, delta_y }));
}

void Pravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    for (int i = 0; i < 4; i++)
        points [i] = add (t, rotate (diff (points [i], t), s));
}

void Pravougaonik::Ispisi() const
{
    std::cout << "{{" << points [0].x << "," << points [0].y << "},{" << points [2].x << "," << points [2].y << "}}";
}



















