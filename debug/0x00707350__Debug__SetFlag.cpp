// FUNC_NAME: Debug::SetFlag
// Address: 0x00707350
// Role: Sets a debug flag at offset 0x210 to 1, after calling a global initialization function.
// Called function (0x00471280) likely initializes debug subsystems or singletons.

void __fastcall Debug::SetFlag(Debug* this)
{
    // Global initialization call (possibly allocates resources or registers component)
    FUN_00471280();

    // Set debug flag to active (offset 0x210 from this pointer)
    this->m_debugFlagActive = 1; // +0x210
}