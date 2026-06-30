// FUNC_NAME: JobManager::processActiveJobs

class JobManager {
public:
    // Slot structure (12 bytes each)
    struct JobSlot {
        int flags;   // +0x00 - bit 1 indicates active/pending
        int unknown; // +0x04
        int state;   // +0x08 - 1 means ready to process
    };

    // Array of 20 job slots at offset 0x34
    JobSlot slots[20]; // +0x34

    // Manager state fields
    int someCount;      // +0x3d0 - reset to 20 after processing
    int flagsField;     // +0x3d4 - bit 1 enables processing
    int someCounter1;   // +0x3d8 - reset to 0
    int someCounter2;   // +0x3e0 - reset to 0

    // Process all active jobs when the manager's flag is set
    void processActiveJobs() {
        // Check if bit 1 of the manager's flags is set
        if ((flagsField >> 1) & 1) {
            // Iterate over all 20 job slots
            for (int i = 0; i < 20; i++) {
                JobSlot* slot = &slots[i];
                // Check if the slot's own flags have bit 1 set and state == 1
                if (((slot->flags >> 1) & 1) && slot->state == 1) {
                    // Execute the job-specific action (likely takes slot index or pointer)
                    executeJobSlot(); // FUN_006abee0
                }
            }
            // Reset manager state after processing
            someCount = 20;
            flagsField &= ~2; // clear bit 1
            someCounter1 = 0;
            someCounter2 = 0;
        }
    }

private:
    // External function called for each eligible job slot
    void executeJobSlot(); // defined elsewhere (FUN_006abee0)
};