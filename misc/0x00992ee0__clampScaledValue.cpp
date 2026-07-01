// FUNC_NAME: clampScaledValue
// Address: 0x00992ee0
// Scales a float by a multiplier, adds an offset, then clamps between lower bound and offset.

extern float DAT_00e576b8;  // multiplier
extern float DAT_00d92140;  // offset and upper clamp bound
extern float DAT_00d9213c;  // lower clamp bound

float clampScaledValue(float input)
{
    float result = DAT_00e576b8 * input + DAT_00d92140;
    if (result < DAT_00d9213c) {
        return DAT_00d9213c;
    }
    if (DAT_00d92140 < result) {
        result = DAT_00d92140;
    }
    return result;
}