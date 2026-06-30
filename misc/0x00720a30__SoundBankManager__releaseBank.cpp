// FUNC_NAME: SoundBankManager::releaseBank
void __thiscall SoundBankManager::releaseBank() {
    // +0x00: pointer to base object (vtable or base class pointer)
    // +0x08: handle to a sound bank or stream resource
    if (bankHandle_ != 0) {
        FUN_00851230(bankHandle_); // release bank resource
        FUN_009f01a0();           // update stream manager / flush
        bankHandle_ = 0;
    }
    if (basePtr_ != 0) {
        FUN_004daf90(this); // base destructor or cleanup
    }
}