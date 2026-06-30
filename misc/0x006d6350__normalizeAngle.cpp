// FUNC_NAME: normalizeAngle
// Address: 0x006d6350
// This function normalizes an angle (in radians) to the range [-PI, PI].
// It uses an optimization to avoid a full modulo operation for angles within three revolutions.

// Global constants (set during initialization)
static const double s_pi = 3.14159265358979323846;           // +0x00e44600 (gPI)
static const double s_twoPi = 6.28318530717958647693;        // +0x00d5f4b4 (gTwoPi)
static const double s_threePi = s_pi + s_twoPi;              // +0x00d5f4b8 (gThreePi)
static const double s_negPi = -s_pi;                         // +0x00d5f4b0 (gNegPi)
static const double s_negThreePi = -s_threePi;               // +0x00d5f4ac (gNegThreePi)
static const double s_invTwoPi = 1.0 / s_twoPi;              // +0x00e44774 (gInvTwoPi)

double normalizeAngle(double angle)
{
    if (angle > s_pi)
    {
        if (angle < s_threePi)
        {
            // Angle is between PI and 3*PI: subtract one full rotation.
            return angle - s_twoPi;
        }
        else
        {
            // For larger positive angles, compute the number of full rotations to remove.
            int fullRotations = (int)((angle + s_pi) * s_invTwoPi);
            return angle - (double)fullRotations * s_twoPi;
        }
    }

    if (angle > s_negPi)
    {
        // Angle is already in the range (-PI, PI] (or [-PI, PI])
        return angle;
    }

    if (angle > s_negThreePi)
    {
        // Angle is between -3*PI and -PI: add one full rotation.
        return angle + s_twoPi;
    }
    else
    {
        // For larger negative angles, compute the number of full rotations to remove.
        int fullRotations = (int)((angle - s_pi) * s_invTwoPi);
        return angle - (double)fullRotations * s_twoPi;
    }
}