// FUNC_NAME: GodfatherGameManager::onCheckpointLoadComplete
// Address: 0x0079d4f0
// Increments a loading checkpoint counter and performs state transition when counter reaches 1.

void __fastcall GodfatherGameManager::onCheckpointLoadComplete(GodfatherGameManager* this)
{
    // Increment count of completed checkpoints (offset 0x294c)
    this->m_nCheckpointCount++;

    // When the first checkpoint loads (counter becomes 1),
    // clear bit 1 (0x2) of flags at 0x249c and optionally trigger loading screen.
    if (this->m_nCheckpointCount == 1)
    {
        // Clear bit 1 (loading flag?) – always performed
        this->m_dwFlags &= 0xFFFFFFFD;

        // Check global loading state: if GGameManager->bLoadingScreenShown == 0, show it
        // DAT_01223484 is likely a global pointer to GGameManager or similar.
        // Offset 0xc is assumed to be a bool/int indicating if loading screen is active.
        if (*(int*)((char*)DAT_01223484 + 0xC) == 0)
        {
            showLoadingScreen(1); // FUN_009ae900 – show loading screen
        }
    }
}