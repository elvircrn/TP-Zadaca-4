#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "NepreklapajuciPravougaonik.h"

Pozicija NepreklapajuciPravougaonik::intToPos(int index)
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

Tacka NepreklapajuciPravougaonik::rotate(const Tacka &t1, const Smjer &smjer)
{
    float x = t1.x;
    float y = t1.y;

    if (smjer == Smjer::Nalijevo)
        return { y, -x };
    else
        return { -y, x };
}

Tacka NepreklapajuciPravougaonik::diff(const Tacka &t1, const Tacka &t2)
{
    return Tacka { t1.x - t2.x, t1.y - t2.y };
}

Tacka NepreklapajuciPravougaonik::add(const Tacka &t1, const Tacka &t2)
{
    return Tacka { t1.x + t2.x, t1.y + t2.y };
}

Tacka NepreklapajuciPravougaonik::DajCentar() const
{
    return Tacka { (points [0].x + points [2].x) / 2.0, (points [0].y + points [2].y) / 2.0 };
}

Tacka NepreklapajuciPravougaonik::DajTjeme(Pozicija p) const
{
    return points [posToInt(p)];
}

NepreklapajuciPravougaonik::NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2)
{
    Postavi(t1, t2);
}

NepreklapajuciPravougaonik::NepreklapajuciPravougaonik(const NepreklapajuciPravougaonik &np)
{
    std::cout << "called" << std::endl;
}



void NepreklapajuciPravougaonik::Centriraj(const Tacka &t)
{
    double width  = std::abs(points [0].x - points [2].x);
    double height = std::abs(points [0].y - points [2].y);

    Tacka center = t;

    points = { { center.x - width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y + height / 2.0 },
               { center.x + width / 2.0, center.y - height / 2.0 },
               { center.x - width / 2.0, center.y - height / 2.0 } };
}

NepreklapajuciPravougaonik::NepreklapajuciPravougaonik()
{
    points = std::vector<Tacka>(4);
}

void NepreklapajuciPravougaonik::Postavi(const Tacka &t1, const Tacka &t2)
{
    Tacka center = Tacka { (t1.x + t2.x) / 2.0, (t1.y + t2.y) / 2.0 };

    double width  = std::abs(t1.x - t2.x);
    double height = std::abs(t1.y - t2.y);

    points = { { center.x - width / 2.0, center.y + height / 2.0 },
                   { center.x + width / 2.0, center.y + height / 2.0 },
                   { center.x + width / 2.0, center.y - height / 2.0 },
                   { center.x - width / 2.0, center.y - height / 2.0 } };

    auto current_node = NepreklapajuciPravougaonik::last;

    if (current_node == nullptr)
    {
        NepreklapajuciPravougaonik::last = this;
        prev = nullptr;
    }
    else
    {
        bool found = false;

        while (current_node->prev != nullptr)
        {
            current_node->Ispisi();
            found |= (overlaps(current_node) || contains(current_node) || current_node->contains(this));
            current_node = current_node->prev;
        }

        found |= (overlaps(current_node) || contains(current_node) || current_node->contains(this));

        prev = last;
        last = this;

        if (found)
        {
            throw std::logic_error("Nedozvoljeno preklapanje");
        }
    }
}

int NepreklapajuciPravougaonik::posToInt(Pozicija s)
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

void NepreklapajuciPravougaonik::Postavi(Pozicija p, const Tacka &t)
{
    Tacka offset = diff(t, points [NepreklapajuciPravougaonik::posToInt(p)]);
    for (Tacka &p : points)
        p = add(p, offset);
}

double NepreklapajuciPravougaonik::DajHorizontalnu() const
{
    return std::abs(points [0].x - points [1].x);
}

double NepreklapajuciPravougaonik::DajVertikalnu() const
{
    return std::abs(points [0].y - points [3].y);
}

double NepreklapajuciPravougaonik::DajObim() const
{
    return 2 * DajHorizontalnu() + 2 * DajVertikalnu();
}

double NepreklapajuciPravougaonik::DajPovrsinu() const
{
    return DajHorizontalnu() * DajVertikalnu();
}

bool NepreklapajuciPravougaonik::cmp(double a, double b)
{
    return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

bool NepreklapajuciPravougaonik::cmp(const Tacka &a, const Tacka &b)
{
    return cmp (a.x, b.x) && cmp (a.y, b.y);
}

bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    for (Tacka p : p1.points)
    {
        bool ret = false;
        for (Tacka q : p2.points)
            ret |= NepreklapajuciPravougaonik::cmp(p, q);

        if (!ret)
            return false;
    }

    return true;
}

bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    return NepreklapajuciPravougaonik::cmp (std::min (p1.DajHorizontalnu(), p1.DajVertikalnu()), std::min (p2.DajHorizontalnu(), p2.DajVertikalnu())) &&
           NepreklapajuciPravougaonik::cmp (std::max (p1.DajHorizontalnu(), p1.DajVertikalnu()), std::max (p2.DajHorizontalnu(), p2.DajVertikalnu()));
}

bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2)
{
    return NepreklapajuciPravougaonik::cmp(p1.DajHorizontalnu() / p2.DajHorizontalnu(),
                             p1.DajVertikalnu() / p2.DajVertikalnu());
}

bool NepreklapajuciPravougaonik::contains(const Tacka &t) const
{
    return (points [3].x < t.x /*|| cmp (points [3].x, t.x)*/) &&
           (points [3].x + DajHorizontalnu() > t.x/* || cmp (points [3].x + DajHorizontalnu(), t.x)*/) &&
           (points [3].y < t.y /*|| (points [3].y, t.y)*/) &&
           (points [3].y + DajVertikalnu() > t.y/* || cmp (points [3].y + DajVertikalnu(), t.y)*/);
}

bool NepreklapajuciPravougaonik::contains(const NepreklapajuciPravougaonik &p2) const
{
    for (int i = 0; i < 4; i++)
        if (!contains (p2.DajTjeme(intToPos(i))))
            return false;
    return true;
}

bool NepreklapajuciPravougaonik::contains(const NepreklapajuciPravougaonik *p2) const
{
    for (int i = 0; i < 4; i++)
        if (!contains (p2->DajTjeme(intToPos(i))))
            return false;
    return true;
}

bool NepreklapajuciPravougaonik::overlaps(const NepreklapajuciPravougaonik &p2) const
{
    NepreklapajuciPravougaonik p1 = (*this);

    if (this->contains(p2) || p2.contains(p1))
        return false;

    return this->DajTjeme(Pozicija::DoljeLijevo).x <= p2.DajTjeme(Pozicija::DoljeLijevo).x + p2.DajHorizontalnu() &&
           this->DajTjeme(Pozicija::DoljeLijevo).x + this->DajHorizontalnu() >= p2.DajTjeme(Pozicija::DoljeLijevo).x &&
           this->DajTjeme(Pozicija::DoljeLijevo).y <= p2.DajTjeme(Pozicija::DoljeLijevo).y + p2.DajVertikalnu() &&
           this->DajTjeme(Pozicija::DoljeLijevo).y + this->DajVertikalnu() >= p2.DajTjeme(Pozicija::DoljeLijevo).y;
}

bool NepreklapajuciPravougaonik::overlaps(const NepreklapajuciPravougaonik *p2) const
{
    if (this->contains(p2) || p2->contains(this))
        return false;

    return this->DajTjeme(Pozicija::DoljeLijevo).x <= p2->DajTjeme(Pozicija::DoljeLijevo).x + p2->DajHorizontalnu() &&
           this->DajTjeme(Pozicija::DoljeLijevo).x + this->DajHorizontalnu() >= p2->DajTjeme(Pozicija::DoljeLijevo).x &&
           this->DajTjeme(Pozicija::DoljeLijevo).y <= p2->DajTjeme(Pozicija::DoljeLijevo).y + p2->DajVertikalnu() &&
           this->DajTjeme(Pozicija::DoljeLijevo).y + this->DajVertikalnu() >= p2->DajTjeme(Pozicija::DoljeLijevo).y;
}

void NepreklapajuciPravougaonik::Transliraj(double delta_x, double delta_y)
{
    Centriraj(add (DajCentar(), { delta_x, delta_y }));
}

void NepreklapajuciPravougaonik::Rotiraj(const Tacka &t, Smjer s)
{
    for (int i = 0; i < 4; i++)
        points [i] = add (t, rotate (diff (points [i], t), s));

    if (s == Smjer::Nalijevo)
    {
        auto p = points [0];
        for (int i = 0; i < 3; i++)
            points [i] = points [i + 1];
        points [3] = p;
    }
    else
    {
        auto p = points [3];
        for (int i = 2; i > -1; i--)
            points [i + 1] = points [i];
        points [0] = p;
    }
}

void NepreklapajuciPravougaonik::Ispisi() const
{
    std::cout << "{{" << points [0].x << "," << points [0].y << "},{" << points [2].x << "," << points [2].y << "}}";
}

NepreklapajuciPravougaonik::~NepreklapajuciPravougaonik()
{
    if (this == last)
        last = prev;
    else if (last->prev != nullptr)
    {
        auto current_node = NepreklapajuciPravougaonik::last;
        while (current_node->prev != this)
            current_node = current_node->prev;
        current_node->prev = current_node->prev->prev;
    }
}

NepreklapajuciPravougaonik* NepreklapajuciPravougaonik::last = nullptr;
















