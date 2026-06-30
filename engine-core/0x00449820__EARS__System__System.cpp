// FUNC_NAME: EARS::System::System
void __fastcall EARS::System::System(EARS::System* this)
{
    // Set initial vtable (base class behavior)
    this->vtable = &PTR_FUN_00e311e0;              // +0x00: vtable pointer
    // Set secondary pointer (likely RTTI or parent class reference)
    this->field_4 = &PTR_LAB_00e311e4;             // +0x04: RTTI / base pointer

    // Initialize two global objects (likely critical sections or memory pools)
    FUN_004086d0(&DAT_012069c4);                   // MemoryRegion::Initialize
    FUN_004086d0(&DAT_012069b4);                   // MemoryRegion::Initialize

    // Perform engine-wide initialization (e.g., threading, logger)
    FUN_004083d0();                                // Engine::Startup

    // Override vtable to final derived class behavior
    this->vtable = &PTR_LAB_00e311f4;              // +0x00: final vtable

    // Reset a global state variable (e.g., frame counter, pending flag)
    DAT_01223438 = 0;
}