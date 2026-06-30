// FUNC_NAME: CalibrationManager::updateInputRange

void CalibrationManager::updateInputRange(int newValue1, int newValue2)
{
    // Clamp upper bound to at least 0xc3 and lower bound to at most 0xc3
    if (s_upperBound < 0xc3)
        s_upperBound = 0xc3;
    if (s_lowerBound > 0xc3)
        s_lowerBound = 0xc3;

    s_currentValue1 = newValue1;

    // Further clamp upper bound to at least 0xaf and lower bound to at most 0xaf
    if (s_upperBound < 0xaf)
        s_upperBound = 0xaf;
    if (s_lowerBound > 0xaf)
        s_lowerBound = 0xaf;

    s_previousValue1 = newValue1;
    s_currentValue2 = newValue2;
    s_previousValue2 = newValue2;
}