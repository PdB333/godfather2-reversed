// FUNC_NAME: Player::setAvatarSlotData

void __fastcall Player::setAvatarSlotData(int *this, unsigned int highDword0x26f8, unsigned long long qword0x2700, unsigned int highDword0x2708)
{
    // Stores three fields at offsets 0x26F8, 0x2700, 0x2708.
    // The 32-bit parameters are stored in the high 32 bits of 64-bit fields,
    // low 32 bits are zeroed.
    *(unsigned long long *)((char *)this + 0x26F8) = (unsigned long long)highDword0x26f8 << 32;
    *(unsigned long long *)((char *)this + 0x2700) = qword0x2700;
    *(unsigned long long *)((char *)this + 0x2708) = (unsigned long long)highDword0x2708 << 32;
}