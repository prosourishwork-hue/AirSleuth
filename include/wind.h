#ifndef WIND_H
#define WIND_H

struct WindReading {
    double directionDeg;   // direction wind is COMING FROM
    double speedKmh;
    WindReading(double d = 0, double s = 0) : directionDeg(d), speedKmh(s) {}
};

#endif