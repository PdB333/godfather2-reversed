// FUNC_NAME: StreamManager::constructor
void __fastcall StreamManager::constructor(StreamManager *this)
{
    // Set vtable pointer (global at 0x00d761ec)
    this->vtable = &StreamManager_vtable;

    // Access member at offset +0x50 (this[0x14]) - pointer to a bank manager object
    BankManager *bankMgr = this->bankManager; // +0x50

    // Call virtual function at offset 0x24 on bank manager (likely getBank())
    int bankId = bankMgr->getBank(); // returns 0 if no bank loaded

    if (bankId != 0) {
        // Call same virtual with argument 5 (specific bank index)
        int bank = bankMgr->getBank(5);
        // Register the bank (FUN_0043c5b0) - likely adds to active banks
        registerBank(bank, 5);
    }

    // Check member at offset +0x64 (this[0x19]) - pointer to a resource or stream
    if (this->someResource != 0) { // +0x64
        // Release the resource (FUN_004daf90)
        releaseResource(&this->someResource);
    }

    // Global update call (FUN_0086aff0) - likely processes pending stream operations
    updateStreamManager();
}