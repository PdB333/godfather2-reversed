// FUNC_NAME: debugInputHandler
void debugInputHandler(uint param1, uint param2, uint param3, int param4, uint param5) {
    int frameState;
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        sendDebugCommand(2, param1); // command type 2 with param1
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        gDebugFlag_0120546f = ((param1 >> 8) & 0xFF) == 0;
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        // Build a 3-byte value from: byte1 of param2, byte0 of param2, and byte2 of param1
        uint combined = ((param2 >> 8) & 0xFFFF) | ((param1 >> 16) << 16);
        sendDebugCommand(4, combined);
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        // Build 4-byte from: byte2 of param2, byte1 of param2, byte0 of param2, byte3 of param1
        uint combined = ((param2 >> 16) & 0xFF) | ((param2 >> 8) & 0xFF) << 8 | (param2 & 0xFF) << 16 | ((param1 >> 24) << 24);
        sendDebugCommand(0x10, combined);
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        sendDebugCommand(1, param2);
        sendDebugCommand(0xF, param2);
        sendDebugCommand(0xE, param2);
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        // Build 4-byte from: low byte of param3, and the 3-byte value (param2 >> 8)
        uint combined = (param3 & 0xFF) | ((param2 >> 8) & 0xFFFFFF) << 8;
        sendDebugCommand(0xB, combined);
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        int obj = findDebugObject(0x2e616d62); // ".amb" identifier
        if (obj != 0) {
            // Check byte1 of param2 (index 1)
            if (((param2 >> 8) & 0xFF) == 0) {
                *(uint *)(obj + 0xC) |= 1; // set flag bit 0
            } else {
                *(uint *)(obj + 0xC) &= ~1; // clear flag bit 0
            }
        }
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        obj = findDebugObject(0x2e666c72); // ".flr"
        if (obj != 0) {
            // Check byte2 of param2 (index 2)
            if (((param2 >> 16) & 0xFF) == 0) {
                *(uint *)(obj + 0xC) |= 1;
            } else {
                *(uint *)(obj + 0xC) &= ~1;
            }
        }
        obj = findDebugObject(0x2e666c63); // ".flc"
        if (obj != 0) {
            // Same check based on byte2 of param2
            if (((param2 >> 16) & 0xFF) == 0) {
                *(uint *)(obj + 0xC) |= 1;
            } else {
                *(uint *)(obj + 0xC) &= ~1;
            }
        }
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        byte *globalByte = getDebugGlobalBytePtr();
        *globalByte = (byte)(param3 & 0xFF); // set global byte to low byte of param3
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        gDebugFlag_012054eb = ((param3 >> 8) & 0xFF) == 0;
        gDebugFlag_012054fc = gDebugFlag_012054eb;
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        handleDebugArgument(param4);
        if (param4 == 0) {
            quitGame();
        }
    }
    
    frameState = getDebugInputFrameState();
    if (frameState == 1) {
        processRemainingDebugCommand(param5);
    }
}