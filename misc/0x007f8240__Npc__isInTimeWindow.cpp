// FUNC_NAME: Npc::isInTimeWindow
bool Npc::isInTimeWindow(float tolerance)
{
    if (this == nullptr) {
        return false;
    }

    // Retrieve two time values (likely from singleton or global manager)
    // FUN_00471610 appears to return a pointer to a persistent object
    float *timeObj1 = (float *)getGameTimeManager(); // e.g., FUN_00471610
    float *timeObj2 = (float *)getGameTimeManager(); // second call

    // Offsets +0x34 likely represent a float member such as m_time or m_height
    float delta = timeObj1[0x34 / 4] - timeObj2[0x34 / 4]; // difference of float at offset 0x34

    // Global constant DAT_00e44564 defines a baseline deviation
    // Tolerance is compared against delta with an asymmetric range
    // (constant - tolerance) < delta  &&  delta <= tolerance
    if ((kTimeBaselineEpsilon - tolerance < delta) && (delta <= tolerance)) {
        return true;
    }
    return false;
}