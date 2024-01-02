#include <cmath>
#include <iostream>

struct Quarternion
{
    float w;
    float x;
    float y;
    float z;
};
struct RotationVector
{
    float heading; // Yaw
    float attitude; // Pitch
    float bank; // Roll
};
RotationVector toEuler(Quarternion q)
{
    RotationVector vec;
    if((q.y*q.x + q.z*q.w) == 0.5)
    {
        vec.heading = 2*atan2(q.x,q.w);
        vec.attitude = asin(2*q.x*q.y+2*q.z*q.w);
        vec.bank = 0;
        return vec;

    }
    if((q.y*q.x + q.z*q.w) == -0.5)
    {
        vec.heading = -2*atan2(q.x,q.w);
        vec.attitude = asin(2*q.x*q.y+2*q.z*q.w);
        vec.bank = 0;
        return vec;

    }
    vec.heading = atan2(2*q.y*q.w-2*q.x*q.z,1-2*q.y*q.y-2*q.z*q.z);
    vec.attitude = asin(2*q.x*q.y+2*q.z*q.w);
    vec.bank = atan2(2*q.x*q.w-2*q.y*q.z,1-2*q.x*q.x-2*q.z*q.z);
    return vec;
}
