// FUNC_NAME: Entity::updateIfActive
void __fastcall Entity::updateIfActive()
{
    // +0x31: byte flags (bit 2 = active flag)
    if ((reinterpret_cast<byte*>(this)[0x31] & 0x2) == 0)
    {
        updateGameState(); // 0x004df650 - global update
    }
}