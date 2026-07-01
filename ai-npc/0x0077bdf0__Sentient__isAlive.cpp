// FUNC_NAME: Sentient::isAlive
bool __fastcall Sentient::isAlive(int thisPtr)
{
    byte flags = *(byte *)(thisPtr + 0x2c); // +0x2c: flags byte (bitfield)
    // Check: bit 5 (0x20) is clear (not dead/destroyed),
    //        bit 0 (0x01) is set (active/initialized),
    //        and sign bit is clear (not negative, i.e., not in a special state)
    if ((((flags & 0x20) == 0) && ((flags & 1) != 0)) && (-1 < (char)flags)) {
        return true;
    }
    return false;
}