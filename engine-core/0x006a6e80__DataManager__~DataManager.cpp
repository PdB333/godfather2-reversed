// FUNC_NAME: DataManager::~DataManager
void __fastcall DataManager::~DataManager(DataManager* this)
{
    // Set up vtable pointers (for multiple inheritance or custom destruction)
    this->vtable0 = 0x00d5d7e0;      // +0x00
    this->vtable1 = 0x00d5d7d0;      // +0x3C
    this->vtable2 = 0x00d5d7cc;      // +0x48

    // Decrement reference or unregister from global manager
    FUN_004086d0(&DAT_0120e93c);

    // If a specific flag (byte at +0x1c) is set, perform additional cleanup
    if (*(((char*)this) + 0x1c) != '\0') {
        FUN_004086d0(&DAT_012069c4);
    }

    // Check if any of the four 32-bit resource IDs at +0x60..+0x6C are non-zero
    if (this->resourceIdA != 0 || this->resourceIdB != 0 || this->resourceIdC != 0 || this->resourceIdD != 0) {
        // Convert 4-component identifier (base 33) to combined ID and free resource
        uint combinedId = ((this->fourCCPart0 * 0x21 + this->fourCCPart1) * 0x21 + this->fourCCPart2) * 0x21 + this->fourCCPart3;
        FUN_006a54d0(combinedId);
    }

    // Release two internal structures (pointers at +0x50 and +0x58)
    FUN_00408310(this + 0x14);   // field at offset 0x50
    FUN_00408310(this + 0x16);   // field at offset 0x58

    // Final global cleanup
    FUN_0046c640();
}