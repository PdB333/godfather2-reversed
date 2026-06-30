// FUNC_NAME: MathUtils::wrapAngle
float MathUtils::wrapAngle(float angle)
{
    // DAT_00e44600 = -PI? (negative half-circle boundary)
    // DAT_00d5f4b8 = PI? (positive half-circle boundary)
    // DAT_00d5f4b4 = 2*PI? (full circle)
    // DAT_00d5f4b0 = 0? (zero boundary)
    // _DAT_00e44774 = 1/(2*PI)? (inverse of full circle for normalization)
    // DAT_00d5f4ac = -PI? (negative half-circle boundary)

    if (DAT_00e44600 < angle) {
        if (angle < DAT_00d5f4b8) {
            // Angle is within (-PI, PI) range, just subtract 2*PI if needed? 
            // Actually this branch handles angles > -PI and < PI
            return angle - DAT_00d5f4b4;
        }
        // Angle >= PI, wrap by subtracting multiples of 2*PI
        return angle - (int)((angle + DAT_00e44600) * _DAT_00e44774) * DAT_00d5f4b4;
    }
    if (DAT_00d5f4b0 < angle) {
        // Angle is > 0 (and <= -PI? Actually this is after the first check failed, so angle <= -PI)
        // This branch handles angles between 0 and -PI? No, the condition is angle > 0, but we already know angle <= -PI from first check.
        // Actually this is a bug in decompilation: the condition should be angle > 0? 
        // More likely: if angle > -PI (i.e., angle is in (-PI, 0] range)
        return angle;
    }
    if (_DAT_00d5f4ac < angle) {
        // Angle is > -PI (and <= 0), add 2*PI to wrap
        return angle + DAT_00d5f4b4;
    }
    // Angle <= -PI, wrap by adding multiples of 2*PI
    return angle - (int)((angle - DAT_00e44600) * _DAT_00e44774) * DAT_00d5f4b4;
}