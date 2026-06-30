// FUNC_NAME: applyGlobalScaling
// Function address: 0x0052d230
// Role: Adjusts a set of global scaling factors (likely viewport or resolution parameters)
//        by multiplying them with a computed ratio of two other global values.
//        This is often called when screen resolution or aspect ratio changes.

extern float DAT_00e2b1a4;   // Numeric constant or config value (numerator)
extern float DAT_01125280;   // Numeric constant or config value (denominator)
extern float _DAT_01125260;  // Scaling factor 1 (e.g., screen width)
extern float _DAT_01125264;  // Scaling factor 2 (e.g., screen height)
extern float _DAT_01125268;  // Scaling factor 3 (e.g., UI X offset)
extern float _DAT_0112526c;  // Scaling factor 4 (e.g., UI Y offset)

void applyGlobalScaling(void)
{
    float fVar1;
    
    // Compute the scale ratio from two global values
    fVar1 = DAT_00e2b1a4 / DAT_01125280;
    
    // Apply this ratio to all four scaling factors (likely contiguous)
    _DAT_01125260 = fVar1 * _DAT_01125260;
    _DAT_01125264 = fVar1 * _DAT_01125264;
    _DAT_01125268 = fVar1 * _DAT_01125268;
    _DAT_0112526c = fVar1 * _DAT_0112526c;
    
    return;
}