// FUNC_NAME: InputManager::updateSlots

// 0x00512240: Main update loop for input/controller slots
// Called per frame to process all active controller slots and update global input state.
// thisPtr points to an InputManager object with a dynamic array of slot data.
class InputManager {
public:
    void updateSlots() {
        // +0x30: m_slotCount (ushort), number of active controller slots to process this frame
        uint slotCount = (uint)*(ushort*)((uint)this + 0x30);
        
        // Guard: no slots, or missing pointer, or timing conditions not met
        if (slotCount == 0) return;
        if (*(int*)((uint)this + 0x5c) == 0) return; // +0x5c: pointer to some global state/manager
        
        // DAT_00e2af44: global frame time delta or threshold
        if (DAT_00e2af44 >= *(float*)((uint)this + 0x40)) return; // +0x40: threshold1
        if (DAT_00e2af44 >= *(float*)((uint)this + 0x40) * *(float*)((uint)this + 0x2c)) return; // +0x2c: multiplier
        
        // Get a global pointer from FS segment (TLS or process data)
        int* tlsBase = *(int**)(unaff_FS_OFFSET + 0x2c);
        int* networkPtr = *(int**)((uint)this + 8); // +0x08: pointer to network/connection object
        int networkFlags = *(int*)(*networkPtr + *(int*)(tlsBase[2])); // indirect flags
        
        // Determine a boolean based on flag checks
        int unknownFlag = 0;
        if ((*(uint*)(*networkPtr + *(int*)(tlsBase[2])) & 0x200) != 0) {
            // DAT_012234c4+0x24: pointer to some audio/system state
            if (*(int*)(DAT_012234c4 + 0x24) != 0) {
                unknownFlag = 1;
            }
        }
        
        // Call essential pre-update routines
        updateInputDevices();          // 0x00537670
        processButtonStates();         // 0x00537610
        
        // Check a flag on the player state object
        int* playerState = *(int**)((uint)this + 0x10); // +0x10: pointer to player state struct
        if ((*(byte*)(playerState + 0x104) & 4) != 0) {
            handleSpecialAction1();     // 0x00417560
            handleSpecialAction2(DAT_01163840 != '\0'); // 0x00537b40
            handleSubUpdate1();         // 0x005378e0
            handleSubUpdate2();         // 0x00537880
        }
        
        // Handle active input sequence
        int* state = *(int**)((uint)this + 0x10);
        if (*(char*)(state + 0x60) == '\x01') {
            processSequence(*(undefined4*)((uint)this + 0x60)); // 0x00537790
            state = *(int**)((uint)this + 0x10);
        }
        
        // Check if camera/system flag
        if ((*(uint*)(state + 0x104) & 0x100) != 0) {
            handleCameraUpdate();       // 0x005121b0
        }
        
        // If there's a secondary pointer, update it
        if (*(int*)((uint)this + 0x58) != 0) { // +0x58: pointer to some sub-manager
            updateSecondarySystem();    // 0x005120c0
        }
        
        // Another flag check
        if ((*(byte*)(*(int*)((uint)this + 0x10) + 0x104) & 0x40) != 0) {
            handleSubAnimation();       // 0x00b9c041 Note: unaligned address, likely thunk
        }
        
        // General update sequence
        finalizePreUpdate();            // 0x00537a70
        applyInputState(*(undefined4*)((uint)this + 0x5c)); // 0x00537750
        
        // Set rendering and system flags
        setGraphicFlag(~*(byte*)(*(int*)((uint)this + 0x10) + 0x10c) & 1); // 0x00412f50
        setRenderFlag(*(uint*)(*(int*)((uint)this + 0x10) + 0x108) >> 0x1c & 0xffffff01); // 0x00412f10
        
        // Clamp global frame counters
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1; // global state flag
        
        updateFontSystem(1);            // 0x00417fe0
        updateCursor();                 // 0x004ec7a0
        
        // Determine input mode for display
        char inputMode = *(char*)(*(int*)((uint)this + 0x10) + 0x112);
        uint displayMode = DAT_00e2b1a4; // default
        if (inputMode != '\0' && inputMode != '\x02') {
            displayMode = 0;
        }
        setDisplayMode(unknownFlag, displayMode, 1, *(uint*)(*(int*)((uint)this + 0x10) + 0x10c) >> 0x1b & 0xffffff01); // 0x00537d80
        
        byte* stateFlag = (byte*)(*(int*)((uint)this + 0x10) + 0x171);
        // Set global state fields based on byte at +0x171
        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;
        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = (uint)*stateFlag;
        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = (uint)(*stateFlag != 0);
        
        // Additional flag for network
        if ((*(byte*)(*(int*)((uint)this + 8) + *(int*)(tlsBase[2])) & 4) != 0) {
            handleNetworkAction();      // 0x00417560
        }
        
        // Final processing of input state
        processKeyMappings();           // 0x00537ad0
        applyInputReset();              // 0x00537b20
        updateAxisState();             // 0x00537a90
        finalizeAxis();                // 0x00537ab0
        
        uint flags = *(uint*)(*(int*)((uint)this + 0x10) + 0x104);
        finalizeInput();                // 0x00537640
        
        // Main slot update loop - iterate over each active slot
        int result = allocateSlotBuffer(0xd, (-((flags & 0x1000) != 0) & 4U) + 4, 0x80000000, slotCount, 1); // 0x0060cd00
        if (result != 0) {
            uint extraCount = (uint)*(ushort*)((uint)this + 0x32); // +0x32: additional slot counter
            do {
                slotCount = slotCount - 1;
                processSingleSlot();     // 0x00512010
                extraCount = extraCount + 1;
                short limit = *(short*)((uint)this + 0x6e); // +0x6e: wraparound limit
                if ((int)extraCount > (int)limit) {
                    extraCount = extraCount - (uint)limit;
                }
            } while (slotCount != 0);
            releaseSlotBuffer();         // 0x0060cde0
            finalizeSlotProcessing();    // 0x00537230
        }
        
        // Reset input state
        applyInputState(0);             // 0x00537750
        
        // Handle global notification / audio
        if (*(uint*)(DAT_0121b0ac + 4) != 0) {
            uint notifFlags = *(uint*)(DAT_0121b0ac + 4) & 0xff;
            if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0') {
                notifFlags = notifFlags + 0x10;
            }
            updateNotificationAudio();   // 0x00618d40
            (&DAT_011d912c)[notifFlags] = 0;
        }
        
        // Post-update flags
        if ((*(uint*)(*(int*)((uint)this + 0x10) + 0x104) & 0x100) != 0) {
            resetCameraFlag(0);         // 0x00537990
        }
        if (*(int*)((uint)this + 0x58) != 0) {
            resetSecondarySystem(0, 0); // 0x005379d0
        }
        
        // Clear global state
        DAT_012058e8 = 0;
        DAT_0121a390 = 0;
        DAT_0121a394 = 0;
        updateFontSystem(0);            // 0x00417fe0
        
        // Reset global state fields
        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;
        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;
        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;
        
        setRenderMode(1, 5, 6);         // 0x00417cf0
        setGraphicFlag(1);              // 0x00412f50
        setRenderFlag(1);               // 0x00412f10
        
        // Final clamp
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;
    }

private:
    // Forward declarations for subroutines (addresses in comments)
    void updateInputDevices();          // 0x00537670
    void processButtonStates();         // 0x00537610
    void handleSpecialAction1();        // 0x00417560
    void handleSpecialAction2(bool);    // 0x00537b40
    void handleSubUpdate1();            // 0x005378e0
    void handleSubUpdate2();            // 0x00537880
    void processSequence(int);          // 0x00537790
    void handleCameraUpdate();          // 0x005121b0
    void updateSecondarySystem();       // 0x005120c0
    void handleSubAnimation();          // 0x00b9c041
    void finalizePreUpdate();           // 0x00537a70
    void applyInputState(int);          // 0x00537750
    void setGraphicFlag(int);           // 0x00412f50
    void setRenderFlag(int);            // 0x00412f10
    void updateFontSystem(int);         // 0x00417fe0
    void updateCursor();                // 0x004ec7a0
    void setDisplayMode(int, int, int, int); // 0x00537d80
    void handleNetworkAction();         // 0x00417560 (same as special?)
    void processKeyMappings();          // 0x00537ad0
    void applyInputReset();             // 0x00537b20
    void updateAxisState();             // 0x00537a90
    void finalizeAxis();                // 0x00537ab0
    void finalizeInput();               // 0x00537640
    int allocateSlotBuffer(int, int, int, uint, int); // 0x0060cd00
    void processSingleSlot();           // 0x00512010
    void releaseSlotBuffer();           // 0x0060cde0
    void finalizeSlotProcessing();      // 0x00537230
    void updateNotificationAudio();     // 0x00618d40
    void resetCameraFlag(int);          // 0x00537990
    void resetSecondarySystem(int, int); // 0x005379d0
    void setRenderMode(int, int, int);  // 0x00417cf0
};