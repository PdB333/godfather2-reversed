// FUNC_NAME: BaseEntity::isDead
bool __fastcall BaseEntity::isDead(int *this)
{
    float health = (**(float (__fastcall **)(int *))(*this + 0x28))(this); // virtual call, returns health (likely)
    // Check: health <= 0 and bit 1 of flags at +0x18 is clear (bit = alive flag? 0 means dead)
    if ((health <= 0.0f) && ((((uint)this[6] >> 1) & 1) == 0))
    {
        return true;
    }
    return false;
}