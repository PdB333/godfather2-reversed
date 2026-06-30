// FUNC_NAME: UnknownClass::processInputOffset
void __thiscall UnknownClass::processInputOffset(byte* inputByte)
{
    // in_EAX is likely a register-provided pointer to a ushort array (e.g., from a member or global)
    ushort* offsetData = reinterpret_cast<ushort*>(this); // placeholder - actual source unknown
    float scale = DAT_00e44820; // global scale constant
    float offsetY = DAT_00e44564; // global Y offset constant

    // Compute X delta: (input nybble * scale) - (offset data[2] * scale)
    float xDelta = scale * ((float)((uint)*inputByte << 4) - (float)offsetData[2]);
    // Compute Y delta: offsetY - (offset data[0] * scale)
    float yDelta = offsetY - scale * (float)offsetData[0];

    // Call helper function with computed deltas and this pointer
    FUN_0056d040(xDelta, yDelta, this);
}