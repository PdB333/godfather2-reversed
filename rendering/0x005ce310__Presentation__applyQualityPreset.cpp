// FUNC_NAME: Presentation::applyQualityPreset
void Presentation::applyQualityPreset(void)
{
    // Clear some internal state fields
    this->field_0x00 = 0;
    this->field_0x04 = 0;

    // Initialize default settings (likely resolution, shadow maps, etc.)
    Presentation::initDefaultSettings(); // FUN_005db4c0

    this->field_0x30 = 0; // offset 0x0c * 4

    int qualityLevel = DAT_01205698; // global quality preset index (e.g., 0=Low, 1=Medium, 2=High, 3=Ultra)
    switch (qualityLevel)
    {
    case 0: // Low
        DAT_00f17628 = DAT_00e445a4; // assign low-quality render config
        break;
    case 1: // Medium
    case 2: // High (falls through)
        DAT_00f17628 = DAT_00e445a0; // assign medium-quality render config
        break;
    case 3: // Ultra
        DAT_00f17628 = DAT_00e2b294; // assign high-quality render config
        break;
    }

    // Apply the selected render config to the device
    Presentation::applyRenderConfig(DAT_00f17624); // FUN_005db5c0

    this->field_0x38 = 2; // offset 0x0e * 4 – e.g., current quality tier = 2 (High)
    this->field_0x34 = 0; // offset 0x0d * 4 – possibly custom override flag = false
}