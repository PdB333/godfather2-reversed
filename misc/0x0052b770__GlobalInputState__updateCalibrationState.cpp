// FUNC_NAME: GlobalInputState::updateCalibrationState
void __fastcall GlobalInputState::updateCalibrationState(float* inputData)
{
    // inputData points to a structure containing controller or device state.
    // Offsets relative to inputData (float*):
    // +0x00: float axisX (used for max update)
    // +0x04: float axisY (used for max update)
    // +0x10: float someValue1 (copied directly)
    // +0x14: float someValue2
    // +0x18: float someValue3
    // +0x1C: float someValue4
    // +0x20: byte flags (accessed via float pointer bit manipulation)

    uint flagsByte;

    // Track maximum of axisX and axisY (likely analog stick bounds)
    if (g_globalMaxAxisX < inputData[0]) {
        g_globalMaxAxisX = inputData[0];
    }
    if (g_globalMaxAxisY < inputData[1]) {
        g_globalMaxAxisY = inputData[1];
    }

    // Direct copy of four floats starting at offset 0x10
    g_globalCalibrationData[0] = inputData[4];
    g_globalCalibrationData[1] = inputData[5];
    g_globalCalibrationData[2] = inputData[6];
    g_globalCalibrationData[3] = inputData[7];

    // Extract low byte from the float at offset 0x20 to update global flag bits
    flagsByte = (uint)(*(byte*)(inputData + 8));
    // Update bit0: XOR with the existing flag bit0 if the input's bit0 is set
    g_globalCalibrationFlags ^= (flagsByte ^ g_globalCalibrationFlags) & 1;
    // Update bit1: similar, but shift input bit1 to correct position (input bit1 corresponds to byte bit1)
    g_globalCalibrationFlags ^= (((flagsByte >> 1) * 2) ^ g_globalCalibrationFlags) & 2;
}