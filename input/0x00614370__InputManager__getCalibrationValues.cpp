// FUNC_NAME: InputManager::getCalibrationValues
void getCalibrationValues(int slotIndex, float* outMin, float* outMax) {
    // Global arrays for controller calibration data.
    // DAT_011f6bb8 and DAT_011f6bbc point to arrays of 12-byte entries (3 floats each).
    // slotIndex * 3 gives the offset into the flat array for the desired slot.
    *outMin = (&g_controllerCalibData1)[slotIndex * 3];  // First float of the slot's 3-float entry
    *outMax = (&g_controllerCalibData2)[slotIndex * 3];  // Second float of the slot's 3-float entry
    // The third float (at offset +0x8) is unused in this getter.
}