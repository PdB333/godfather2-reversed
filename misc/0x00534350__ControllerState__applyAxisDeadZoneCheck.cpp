// FUNC_NAME: ControllerState::applyAxisDeadZoneCheck
// Function address: 0x00534350
// Appears to be a dead zone check for analog input axes.
// It reads offset and scale from a per-axis structure and computes
// scaled = (axisValue - offset) * scale, then returns early if scaled <= 0 or below a global threshold.
// The actual effect is not visible in this function (no return value or side effect); possibly a debug stub or the action was inlined.

void __fastcall ControllerState::applyAxisDeadZoneCheck(int this_, float axisValue)
{
    // this_+4: pointer to ControllerManager
    int managerPtr = *(int *)(this_ + 4);                       // +0x04
    // managerPtr+0x10: pointer to axis data table (each entry 0x24 bytes)
    int axisTable = *(int *)(managerPtr + 0x10);                // +0x10
    // this_+0x0e: short index into axis table
    short axisIndex = *(short *)(this_ + 0xe);                  // +0x0e
    // Base of table +0x30 (header size) + index * 0x24
    int axisData = axisTable + 0x30 + axisIndex * 0x24;        // 0x24 bytes per axis struct
    float offset = *(float *)(axisData + 0x20);                 // +0x20
    float scale  = *(float *)(axisData + 0x1c);                 // +0x1c
    float scaled = (axisValue - offset) * scale;
    if (scaled <= 0.0f)
        return;
    // Global threshold at 0x00e2b1a4
    if (scaled < *(float *)0x00e2b1a4)
        return;
    return;
}