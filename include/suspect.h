#ifndef SUSPECT_H
#define SUSPECT_H

#include <string>
using namespace std;

class Suspect {
protected:
    string name_;
    double lat_, lon_;
    double strength_;
public:
    Suspect(const string& n, double la, double lo, double st)
        : name_(n), lat_(la), lon_(lo), strength_(st) {}
    virtual ~Suspect() {}

    string getName() const { return name_; }
    double getLat()  const { return lat_; }
    double getLon()  const { return lon_; }
    double getStrength() const { return strength_; }

    virtual string type() const = 0;
    virtual double emissionFactor() const = 0;
};

class Landfill : public Suspect {
public:
    Landfill(const string& n, double la, double lo, double st) : Suspect(n, la, lo, st) {}
    string type() const override { return "Landfill"; }
    double emissionFactor() const override { return 0.75; }
};

class Industry : public Suspect {
public:
    Industry(const string& n, double la, double lo, double st) : Suspect(n, la, lo, st) {}
    string type() const override { return "Industry"; }
    double emissionFactor() const override { return 0.85; }
};

class StubbleSmoke : public Suspect {
public:
    StubbleSmoke(const string& n, double la, double lo, double st) : Suspect(n, la, lo, st) {}
    string type() const override { return "StubbleSmoke"; }
    double emissionFactor() const override { return 1.0; }
};

#endif