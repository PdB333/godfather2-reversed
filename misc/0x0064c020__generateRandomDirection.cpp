// FUNC_NAME: generateRandomDirection
#include <cmath>
#include <cstdint>

// External math functions (likely sin/cos implementations used by EA EARS engine)
extern float __fastcall easSin(float);  // FUN_00b99e20? (assuming sin)
extern float __fastcall easCos(float);  // FUN_00b99fcb? (assuming cos)

// Random number generator returning a 32-bit integer
extern int __fastcall getRandomInt(void); // FUN_0064be80

// Constants from data section (likely 2*PI and PI)
extern const float kTwoPi;  // DAT_00e2afac
extern const float kPi;     // DAT_00e2a850

// Generate a random direction vector on the unit sphere using two random angles.
// param_1: number of random bits used for each angle (<32)
// Result is stored in outVec[3] (EDI register used as output pointer)
void __fastcall generateRandomDirection(byte randomBits, float* outVec) {
    // First random angle (azimuth): scaled by 2*PI
    int rand1 = getRandomInt();
    int max1 = (1 << (randomBits & 0x1f)) - 1; // maximum value for first random
    float theta = ((float)rand1 / (float)max1) * kTwoPi; // azimuth in [0, 2*PI)

    // Second random angle (polar): scaled by PI
    int rand2 = getRandomInt();
    int max2 = (1 << ((randomBits - 1) & 0x1f)) - 1; // maximum value for second random
    float phi = ((float)rand2 / (float)max2) * kPi; // polar angle in [0, PI)

    // Compute spherical coordinates using sin/cos
    float sinPhi = easSin(phi);
    float cosPhi = easCos(phi);
    float sinTheta = easSin(theta);
    float cosTheta = easCos(theta);

    outVec[0] = sinPhi * cosTheta;
    outVec[1] = sinPhi * sinTheta;
    outVec[2] = cosPhi;
}