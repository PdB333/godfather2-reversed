// FUNC_NAME: MathUtils::convertTimeToFramesAndFraction
void MathUtils::convertTimeToFramesAndFraction(float timeInSeconds, int* outFramesAndFraction)
{
    // [0] = frame count (integer part)
    // [1] = fractional part as float (0.0 - 1.0)
    // [2] = unknown (set to 0)
    // [3] = another float (seems to be same as [1] but from a different conversion)
    outFramesAndFraction[2] = 0;
    *outFramesAndFraction = 0;
    
    // DAT_00e2cd54 is likely a frame rate conversion factor (e.g., 30.0 for 30fps)
    float scaledTime = timeInSeconds * DAT_00e2cd54;
    
    // Extract integer part (frames)
    double temp = (double)scaledTime;
    FUN_00b99fcb(); // Likely floor() or trunc() to get integer part
    outFramesAndFraction[1] = (float)temp; // Store integer part as float
    
    // Extract fractional part
    temp = (double)scaledTime;
    FUN_00b99e20(); // Likely modf() or frac() to get fractional part
    outFramesAndFraction[3] = (float)temp; // Store fractional part
}