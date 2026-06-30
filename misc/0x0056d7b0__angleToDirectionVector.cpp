// FUNC_NAME: angleToDirectionVector
// Address: 0x0056d7b0
// Converts an angle in game-specific units to a direction vector.
// Output is a 4-float array: out[0]=0, out[1]=0, out[2]=cos(angle_rad), out[3]=sin(angle_rad)
// Uses global conversion factor at 0x00e2cd54 (likely game unit to radians).

extern float kAngleToRadians; // DAT_00e2cd54

void angleToDirectionVector(float angleGameUnits, float* outDirection) {
    outDirection[0] = 0.0f;
    outDirection[1] = 0.0f;

    float angleRadians = angleGameUnits * kAngleToRadians;
    outDirection[2] = cosf(angleRadians);
    outDirection[3] = sinf(angleRadians);
}