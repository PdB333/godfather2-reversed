// FUNC_NAME: Sentient::isAliveOrConscious
bool __fastcall Sentient::isAliveOrConscious(Sentient* this)
{
    // +0x9c: healthState (0 = alive, 0x48 = dead, other values possible)
    // +0x5c: flags (bitmask)
    // Check if health state is not alive (0) and not dead (0x48)
    // OR if certain flags are set (0x660000 = knocked out / incapacitated flags)
    if ((*(int*)((char*)this + 0x9c) != 0 && *(int*)((char*)this + 0x9c) != 0x48) ||
        (*(unsigned int*)((char*)this + 0x5c) & 0x660000) != 0)
    {
        return false;
    }
    return true;
}