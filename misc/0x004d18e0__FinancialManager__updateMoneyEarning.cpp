// FUNC_NAME: FinancialManager::updateMoneyEarning
void FinancialManager::updateMoneyEarning(void)
{
    // Check if earnings are not disabled (bit 1 of flag at +0xA8)
    if ((this->flags & 2) == 0) {
        // Check global earning state (DAT_00e2df9c)
        int earningState = globalCheckEarningState(&gEarningGlobal);
        if (earningState == 1) {
            // Get some 64-bit value (e.g., reputation or multiplier)
            long long multiplierOrValue = getPlayerReputationLong(); // returns 0x20000?
            if (multiplierOrValue == 0x20000) {
                // Save pending amount before resetting
                int pendingAmount = this->pendingMoney; // +0xC8 (200 decimal)
                // Add earnings to current money
                this->currentMoney += 0x20000; // +0xC0
                // Reset pending money
                this->pendingMoney = 0; // +0xC8
                // Also add to global total (DAT_012234a8)
                gGlobalSingleton->totalMoneyEarned += 0x20000; // +0x88
                // Process the pending amount (e.g., UI update or effects)
                processMoneyEarned(pendingAmount);
                // Check if we reached the money cap
                if (this->currentMoney < this->moneyCap) { // +0xBC
                    // Continue earning progress
                    continueEarnings();
                    return;
                }
                // Cap reached – handle completion
            }
        }
        else {
            // Disable earnings by setting bit 1 of flag
            this->flags |= 2; // +0xA8
        }
    }
    // Finalize updates (e.g., GUI or sounds)
    finalizeEarningsUpdate();
}