// FUNC_NAME: InputManager::dispatchDeviceInput
void __thiscall InputManager::dispatchDeviceInput(int param1, int param2)
{
    // Global pointer to input manager instance (DAT_0121be7c)
    // Offsets: +0x14 = first device, +0x18 = second device
    if (*(int*)(DAT_0121be7c + 0x14) != 0) {
        FUN_0060add0(DAT_0121bc24, *(int*)(DAT_0121be7c + 0x14), param1);
    }
    if (*(int*)(DAT_0121be7c + 0x18) != 0) {
        FUN_0060add0(DAT_0121bc24, *(int*)(DAT_0121be7c + 0x18), param2);
    }
}