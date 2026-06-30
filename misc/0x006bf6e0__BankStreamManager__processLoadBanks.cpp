// FUNC_NAME: BankStreamManager::processLoadBanks
void __thiscall BankStreamManager::processLoadBanks(void* this, void* param_2) {
    // Initialize the load state with the given parameter
    someInitFunction(param_2);
    
    // Start loading the bank identified by hash 0x106b846e (likely a "bank" resource hash)
    startBankLoad(param_2, 0x106b846e);  // 0x106b846e = hash for "bank" or similar
    
    // Loop until bank loading is complete
    while (!isLoadComplete()) {
        // Advance the loading state machine
        processNextBank();  // returns pointer to a bank data structure
        
        int bankType = getBankType();  // returns 0 or 1 indicating which slot to fill
        if (bankType == 0) {
            void* bankData = popNextLoadedBank();
            *(void**)((int)this + 0x180) = *(void**)((int)bankData + 8);  // +0x180: m_bank0Handle
        } else if (bankType == 1) {
            void* bankData = popNextLoadedBank();
            *(void**)((int)this + 0x184) = *(void**)((int)bankData + 8);  // +0x184: m_bank1Handle
        }
        
        advanceLoadStep();
    }
}