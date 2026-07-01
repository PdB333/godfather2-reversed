// FUNC_NAME: MathUtils::normalizeAngle
float normalizeAngle(float angle, float minAngle, float maxAngle)
{
    float range;
    float diff;
    double dVar3;
    double dVar4;
    
    range = minAngle;
    diff = maxAngle;
    FUN_00b9a9fa(); // likely fmod or fabs
    dVar4 = (double)(angle - range);
    FUN_00b9a9fa(); // likely fmod or fabs
    angle = (float)(dVar3 - (float)dVar4); // dVar3 is from param_3 (maxAngle) after first call
    if (DAT_00d5eeec < angle) { // DAT_00d5eeec likely PI or some threshold
        return fabs(angle - DAT_00d5d70c); // DAT_00d5d70c likely 2*PI
    }
    if (angle < DAT_00e44588) { // DAT_00e44588 likely -PI or negative threshold
        angle = angle + DAT_00d5d70c; // wrap around by 2*PI
    }
    return fabs(angle);
}