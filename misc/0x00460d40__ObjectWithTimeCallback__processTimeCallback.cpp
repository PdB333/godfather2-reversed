// FUNC_NAME: ObjectWithTimeCallback::processTimeCallback
void ObjectWithTimeCallback::processTimeCallback()
{
    // Check if bit 0x10 at offset +0x61 is not set (maybe paused/disabled flag)
    if ((*(byte*)(thisObj + 0x61) & 0x10) == 0)
    {
        int* vtable = *(int**)thisObj; // vtable pointer at +0x00
        float globalTimeScale = DAT_012067e8; // global time scale multiplier

        // Call vtable function at +0x110, passing 0 (likely returns current time or a base value)
        float timeValue = (*(float (*)(int))(vtable[0x110 / 4]))(0);

        // Call vtable function at +0x178, passing scaled time
        (*(void (*)(float))(vtable[0x178 / 4]))(timeValue * globalTimeScale);
    }
}