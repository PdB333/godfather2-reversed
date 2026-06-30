// FUNC_NAME: Player::Player
undefined4 __thiscall Player::Player(byte allocFlag)
{
    // Call base class initialization (likely Sentient or Entity constructor)
    // Previously FUN_00708830
    BaseClassInitializer();

    // If the lowest bit of allocFlag is set, allocate internal player data of size 0x2d0 (720 bytes)
    // Previously FUN_0043b960
    if (allocFlag & 1) {
        AllocateInternalMemory(this, 0x2d0);
    }

    return this;
}