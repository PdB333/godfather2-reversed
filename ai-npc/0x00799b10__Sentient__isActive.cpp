// FUNC_NAME: Sentient::isActive
bool __fastcall Sentient::isActive(Sentient* thisPtr)
{
    // Check if the active flag at offset 0x2151 is set to 1
    return *(char*)((uint8_t*)thisPtr + 0x2151) == 1;
}