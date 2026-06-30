// FUNC_NAME: CameraManager::applyScreenShakeOffset
void __thiscall CameraManager::applyScreenShakeOffset(byte *this, undefined4 param_2)
{
    // this[0] and this[2] are likely screen shake intensity values (byte, shifted by 4 bits)
    // in_EAX points to a ushort array (likely from a shake profile or random offset)
    // DAT_00e44820 is a scaling factor for the shake magnitude
    // FUN_0056d040 is likely a function that applies a 2D offset to the camera (e.g., screen shake)
    FUN_0056d040(
        -((float)in_EAX[2] * DAT_00e44820 - (float)((uint)this[2] << 4) * DAT_00e44820), // Y offset: (random * scale) - (intensity * scale)
        -((float)*in_EAX * DAT_00e44820 - (float)((uint)this[0] << 4) * DAT_00e44820), // X offset: (random * scale) - (intensity * scale)
        param_2 // likely a duration or blend parameter
    );
}