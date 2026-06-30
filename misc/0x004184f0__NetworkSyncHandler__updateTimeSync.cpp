// FUNC_NAME: NetworkSyncHandler::updateTimeSync

void __fastcall NetworkSyncHandler::updateTimeSync(NetworkSyncHandler* thisPtr)
{
    // Dereference pointer at +0x04 to get the inner network object
    NetworkObject* innerObj = *(NetworkObject**)((char*)thisPtr + 0x4); // +0x04: pointer to inner object

    int globalSequence = DAT_0120543c; // Global sequence/timestamp value
    bool bSequenceChanged = globalSequence != *(int*)((char*)innerObj + 0x10); // +0x10: local sequence

    // Clear flag at +0x1b8 (e.g., pending update flag)
    *(uint8_t*)((char*)innerObj + 0x1b8) = 0;

    if (bSequenceChanged) {
        // Update local sequence with global value
        *(int*)((char*)innerObj + 0x10) = globalSequence;

        // Copy timestamp from +0x1bc to +0x50 (e.g., lastReceivedTime -> lastAppliedTime)
        *(int*)((char*)innerObj + 0x50) = *(int*)((char*)innerObj + 0x1bc); // +0x50: applied time, +0x1bc: received time

        // If this inner object is the local client connection handle, invoke sequence callback
        if (DAT_012058e8 == innerObj) { // Global pointer to local client object
            FUN_0060a460(globalSequence); // Probably sets server time or triggers event
        }
    }

    // Clear flag at +0x0c in the outer handler (e.g., marked as processed)
    *(uint8_t*)((char*)thisPtr + 0xc) = 0;
}