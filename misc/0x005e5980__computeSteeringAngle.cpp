// FUNC_NAME: computeSteeringAngle
// Function address: 0x005e5980
// Description: Computes the desired steering angle based on target angle and input data.
// Uses global constants: g_threshold (0x00e2cd54), g_upperLimit (0x00e2b1a4), g_lowerLimit (0x00e2eff4),
// g_baseAngle (0x00e2afac), g_circleConstant (0x00e2a848), g_someOther (0x00e44564).
// The inputData pointer (in EAX) points to an array of at least 3 floats: [speed, ?, somethingElse].
// The output is written to the pointer in ESI (outputAngle).

extern float g_threshold;      // DAT_00e2cd54
extern float g_upperLimit;     // DAT_00e2b1a4
extern float g_lowerLimit;     // DAT_00e2eff4
extern float g_baseAngle;      // DAT_00e2afac
extern float g_circleConstant; // DAT_00e2a848 (e.g., 360.0f)
extern float g_someOther;      // DAT_00e44564

// Unknown helper function (maybe float conversion or debug)
void unknownHelper(); // FUN_00b9c766

int __cdecl computeSteeringAngle(int flag, float targetAngle, const float* inputData, float* outputAngle)
{
    float fVar2 = g_threshold;

    if (flag == 1)
    {
        *outputAngle = 0.0f;

        if (fVar2 < targetAngle)
        {
            float fVar1 = g_someOther - inputData[0] * (g_upperLimit / targetAngle);
            float fVar4 = inputData[2] * (g_upperLimit / targetAngle);
            fVar2 = g_lowerLimit;

            // Clamp fVar1 between g_lowerLimit and g_upperLimit
            if ((g_lowerLimit < fVar1) && (fVar2 = fVar1, g_upperLimit <= fVar1))
            {
                fVar2 = g_upperLimit;
            }

            if ((fVar4 <= g_lowerLimit) ||
                ((fVar4 < g_upperLimit && (fVar4 <= 0.0f))))
            {
                double dVar3 = (double)fVar2;
                unknownHelper(); // Possibly conversion
                *outputAngle = g_baseAngle - (float)dVar3;
                return 1;
            }

            double dVar3 = (double)fVar2;
            unknownHelper();
            fVar2 = (float)dVar3;
            *outputAngle = fVar2;

            if (fVar2 < 0.0f)
            {
                *outputAngle = fVar2 + g_circleConstant;
            }

            return 1;
        }
    }
    else
    {
        *outputAngle = 0.0f;
    }

    return 1;
}