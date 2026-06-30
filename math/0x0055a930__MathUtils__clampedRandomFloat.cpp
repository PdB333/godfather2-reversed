// FUNC_NAME: MathUtils::clampedRandomFloat
// Address: 0x0055a930
// Role: Computes a random value clamped within a threshold. If |x| >= 1, returns 0.0 (or a constant offset if x <= 0).
//       Otherwise returns a random float from a global generator (FUN_00b9a660).
// Constants: DAT_00e2afac (unknown float) is used as a sign-dependent offset.

#include <cmath> // for fabs

// Forward declarations of called functions
extern float DAT_00e2afac; // global constant
double FUN_0040f220(double x); // likely absolute value
double FUN_00b9a660();        // likely random number in [0,1)

double MathUtils::clampedRandomFloat(double param1) {
    double fVar1 = FUN_0040f220(param1); // compute |param1|
    if (fVar1 >= 1.0) {
        double result = 0.0;
        if (param1 <= 0.0) {
            result = DAT_00e2afac; // return constant for non-positive input
        }
        return result;
    }
    // return random value when |param1| < 1
    return FUN_00b9a660();
}