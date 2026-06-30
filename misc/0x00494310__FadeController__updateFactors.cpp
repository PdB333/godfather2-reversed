// FUNC_NAME: FadeController::updateFactors
void __fastcall FadeController::updateFactors(float* targetValues) {
    const float maxValue = g_maxValue;              // 0x00e2b1a4
    const float minDiff  = g_minDiff;               // 0x00e2e210

    // Component 0 – store ratio and complement
    float diff0 = maxValue - targetValues[0];
    if (diff0 < minDiff) diff0 = minDiff;
    float ratio0 = maxValue / diff0;
    m_field0x60 = static_cast<int>(ratio0);         // +0x60
    m_field0x80 = static_cast<int>(maxValue - ratio0); // +0x80

    // Component 1 – store complement first, then ratio
    float diff1 = maxValue - targetValues[1];
    if (diff1 < minDiff) diff1 = minDiff;
    float invRatio1 = maxValue / diff1;
    m_field0x84 = static_cast<int>(maxValue - invRatio1); // +0x84
    m_field0x64 = static_cast<int>(invRatio1);       // +0x64

    // Component 2 – store ratio and complement again
    float diff2 = maxValue - targetValues[2];
    if (diff2 < minDiff) diff2 = minDiff;
    float ratio2 = maxValue / diff2;
    m_field0x68 = static_cast<int>(ratio2);         // +0x68
    m_field0x88 = static_cast<int>(maxValue - ratio2); // +0x88

    // If the first pointer member matches a global, apply the computed values
    if (m_pBase == g_someGlobal) {                   // *this == 0x012058e8
        FUN_0060ad20(m_pBase->field0x14, m_field0x14, &m_field0x60);
        FUN_0060ad20(m_pBase->field0x14, m_field0x1c, &m_field0x80);
    }
}