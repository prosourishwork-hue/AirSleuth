#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

const double EARTH_RADIUS_KM = 6371.0;
const double PI = 3.14159265358979;

inline double toRadians(double deg) { return deg * PI / 180.0; }

inline double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = sin(dLat/2)*sin(dLat/2) +
               cos(toRadians(lat1))*cos(toRadians(lat2))*
               sin(dLon/2)*sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return EARTH_RADIUS_KM * c;
}

inline double bearing(double lat1, double lon1, double lat2, double lon2) {
    double y = sin(toRadians(lon2-lon1)) * cos(toRadians(lat2));
    double x = cos(toRadians(lat1))*sin(toRadians(lat2)) -
               sin(toRadians(lat1))*cos(toRadians(lat2))*cos(toRadians(lon2-lon1));
    double brng = atan2(y, x) * 180.0 / PI;
    if (brng < 0) brng += 360.0;
    return brng;
}

inline double angleDiff(double a, double b) {
    double d = fabs(a - b);
    if (d > 180.0) d = 360.0 - d;
    return d;
}

#endif