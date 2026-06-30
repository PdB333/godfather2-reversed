// FUNC_NAME: ControllerInputHandler::processAnalogUpdate
void ControllerInputHandler::processAnalogUpdate(float* inputAxes, uint32_t inputStateFlags) {
    // Source object (likely raw controller state) from EDI register pass
    // Offsets: +0x0c = previous X axis, +0x10 = previous Y axis (float)
    // Destination object (this) from ESI register
    // Offsets: +0x10 = scaled X value, +0x14 = scaled Y value, +0x0c = inputStateFlags

    float rawX = inputAxes[0] - *(float*)(m_sourceObj + 0x0c);
    float rawY = inputAxes[2] - *(float*)(m_sourceObj + 0x10);

    if (rawX < 0.0f) rawX = 0.0f;
    if (rawY < 0.0f) rawY = 0.0f;

    int scaledX = (int)(s_analogScaleFactor * rawX);
    int scaledY = (int)(s_analogScaleFactor * rawY);

    if (scaledX > 0xfff) scaledX = 0xfff;
    if (scaledY > 0xfff) scaledY = 0xfff;

    if (scaledX != m_storedScaledX || scaledY != m_storedScaledY) {
        // Notify old state and set new state
        FUN_00415f90(*(uint32_t*)(m_sourceObj + 0x08), m_storedScaledX, m_storedScaledY, 2, this);
        FUN_00415ea0(m_sourceObj, *(uint32_t*)(m_sourceObj + 0x08), scaledX, scaledY, 2, this);
    }

    // Internal update callback
    FUN_00414aa0();

    m_storedScaledY = scaledY;
    m_storedScaledX = scaledX;
    m_inputStateFlags = inputStateFlags;
}