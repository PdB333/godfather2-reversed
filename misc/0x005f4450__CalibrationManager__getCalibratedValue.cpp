// FUNC_NAME: CalibrationManager::getCalibratedValue
int __thiscall CalibrationManager::getCalibratedValue(int this, float inputFloat)
{
    int index;
    int largeStructPtr;
    float* pKeyEntry;
    double readDouble1;
    double readDouble2;

    // Search linear array of 10 key entries at this+0x82b0, stride 0x5c
    index = 0;
    pKeyEntry = (float*)(this + 0x82b0);
    while ((int)*pKeyEntry < 0 || *pKeyEntry != inputFloat) {
        index++;
        pKeyEntry += 0x5c / 4; // step 0x5c bytes (23 floats)
        if (9 < index) {
            return -1;
        }
    }

    // Found matching key entry
    largeStructPtr = this + 0x8210 + index * 0x170; // large structure stride 0x170

    // Enter critical section (mutex at DAT_00e2aea0)
    criticalSectionEnter(&DAT_00e2aea0);

    // Check conditions on the large structure
    if ((((-1 < *(int*)(largeStructPtr + 0xa0)) &&
         (*(int*)(*(int*)(largeStructPtr + 0x9c) * 0x10 + 0x81c4 + this) != 0)) &&
        (someConditionCheck() && 
         DAT_00e2b05c <= *(float*)(largeStructPtr + 0x134))) {
        
        // Read calibration data from a stream
        streamBeginRead();
        streamReadFloat(0, &inputFloat);           // type 0 = float, overwrites input
        streamReadDouble(2, &readDouble1);         // type 2 = double (threshold)
        streamReadDouble(1, &readDouble2);         // type 1 = double (scale)
        streamEndRead();

        // Validate read values and compute final result
        if ((inputFloat == *(float*)(largeStructPtr + 0x134)) && 
            (_DAT_00e44568 < readDouble1)) {
            double resultDouble = readDouble2 * DAT_00e44570;
            criticalSectionLeave(&DAT_00e2aea0);
            return (int)resultDouble;
        }
    }

    criticalSectionLeave(&DAT_00e2aea0);
    return -1;
}