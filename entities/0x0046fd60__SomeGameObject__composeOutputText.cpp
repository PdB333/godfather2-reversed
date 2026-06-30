// FUNC_NAME: SomeGameObject::composeOutputText
void __thiscall SomeGameObject::composeOutputText(int thisPtr, int extraArg)
{
    // +0x0F0: sourceBuffer (e.g., format source string)
    // +0x100: outputBuffer (destination for constructed text)
    // Global constant DAT_00e2e358 is likely a format string or padding constant
    FUN_004a0b00(thisPtr + 0x100, thisPtr + 0xF0, extraArg, &DAT_00e2e358);
    return;
}