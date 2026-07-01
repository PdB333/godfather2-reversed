// FUNC_NAME: Player::updateAnalogInput
void __fastcall Player::updateAnalogInput(int* this)
{
    float axisX, axisY, axisZ;
    int* pController;
    int* pActiveController;

    // Determine primary controller pointer (either m_pPrimaryController or embedded at offset 0x48)
    if (this[0xb89] == 0 || this[0xb89] == 0x48) {
        pController = (int*)*this;  // Use base object's first field
    } else {
        // Use global fallback (likely a singleton)
        pController = (int*)iRam00000000;
        if (this[0xb89] != 0) {
            // Controller pointer stored at (this[0xb89] - 0x48) ? 
            pController = (int*)*(int*)(this[0xb89] - 0x48);
        }
    }

    // Fetch two float values from virtual functions at vtable offsets 0xC4 and 0xC0
    axisX = (float)(**(code**)(pController + 0xC4))();   // e.g., getLeftStickX
    axisY = (float)(**(code**)(pController + 0xC0))();   // e.g., getLeftStickY

    // Clamp to zero (deadzone handling)
    if (axisY < 0.0f) axisY = 0.0f;
    if (axisX < 0.0f) axisX = 0.0f;

    // Apply deadzone/input profile
    FUN_00939410(axisY, (float)axisZ, axisX);   // axisZ from earlier virtual call? Actually fVar3 is separate, likely from combined call

    // Determine secondary controller pointer (for additional input)
    if (this[0x92f] == 0 || this[0x92f] == 0x48) {
        pActiveController = (int*)this[0x1d3];
    } else {
        pActiveController = (int*)(this[0x92f] - 0x48);
    }

    // Update active controller state
    FUN_0093a7e0(pActiveController);

    // Finalize input update
    FUN_0093c530(this);
}