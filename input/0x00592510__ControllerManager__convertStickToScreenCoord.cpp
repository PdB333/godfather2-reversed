// FUNC_NAME: ControllerManager::convertStickToScreenCoord

void __fastcall ControllerManager::convertStickToScreenCoord(void *this, void *outVec)
{
    // this points to a controller slot struct (size 0x44), containing two ushorts at +0x00 and +0x04 (axis X, Y)
    ushort *stickData = (ushort *)this;
    // Global constants from .data section
    // DAT_00e44564 likely half-screen width/height (central coordinate)
    // DAT_00e44820 likely normalization factor (e.g., 32768.0f)
    float scaledX = s_screenCenter - (float)stickData[0] * s_stickScaleFactor;
    float scaledY = s_screenCenter - (float)stickData[2] * s_stickScaleFactor;
    // Write the converted floats to the output struct (e.g., a Vector2 or a pointing location)
    FUN_0056d040(scaledX, scaledY, outVec);
}