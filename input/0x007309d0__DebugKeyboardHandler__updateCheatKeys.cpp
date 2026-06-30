// FUNC_NAME: DebugKeyboardHandler::updateCheatKeys

void __fastcall DebugKeyboardHandler::updateCheatKeys(DebugKeyboardHandler* this)
{
    uint flags; // bitmask of triggered cheat flags at +0x2188
    char keyDown; // result of isKeyPressed()
    uint cheatHash; // hash/ID of the cheat to process
    char buffer[20]; // local buffer for hash processing

    // Push current input state and clear buffer
    FUN_00892af0(0); // likely pushInputState(0)
    FUN_00892ce0(this, 0); // likely clearInputBuffer(this, 0)

    flags = *(uint*)((int)this + 0x2188); // +0x2188: cheat/progress flags bitmask

    // If the "cheat already processed" flag (bit 9) is not set, check key combinations
    if ((flags >> 9 & 1) == 0) {
        // Check a series of "cheat" keys – each leads to a different cheat hash
        if ((flags >> 3 & 1) == 0) {
            if ((flags >> 4 & 1) == 0) {
                // ... many nested checks based on game state bits
                // Only check keys if the corresponding progress bit is clear

                // Start key checks (hex values are likely virtual-key codes or custom IDs)
                keyDown = FUN_0072c080(0x3e); // e.g., VK_OEM_? (probably ">" key)
                if (keyDown == '\0') {
                    keyDown = FUN_0072c080(0x38); // VK_LMENU? (left Alt)
                    if (keyDown == '\0') {
                        keyDown = FUN_0072c080(0x10); // VK_SHIFT
                        if (keyDown == '\0') {
                            keyDown = FUN_0072c080(0x11); // VK_CONTROL
                            if (keyDown == '\0') {
                                // ... many more key checks (0x1d to 0x39, etc.)
                                // Each successful key press sets a unique cheatHash
                                // ... (abbreviated for clarity – the full chain is identical in pattern)
                                // The final else branch (all keys unpressed) goes to LAB_00730f72
                                goto LAB_00730f72;
                            } else {
                                // key 0x11 (ctrl) pressed -> set cheatHash to 0x88945e78
                                cheatHash = 0x88945e78;
                            }
                        } else {
                            // key 0x10 (shift) pressed -> set cheatHash to 0xe188c13e
                            FUN_00892b40(this, 1); // set some input flag
                            cheatHash = 0xe188c13e;
                        }
                    } else {
                        // key 0x38 (alt) pressed -> set cheatHash to 0xd09ca9a3
                        FUN_00892b40(this, 1);
                        cheatHash = 0xd09ca9a3;
                    }
                } else {
                    // key 0x3e pressed -> set cheatHash to 0x54a1048b
                    cheatHash = 0x54a1048b;
                }
                // ... many more similar blocks for other keys, each setting a different cheatHash
            } else {
                FUN_00892b40(this, 1);
                cheatHash = 0x8c451a48;
            }
        } else {
            FUN_00892b40(this, 1);
            cheatHash = 0x93842a8d;
        }
    } else {
        cheatHash = 0x54a1048b;
    }

    // Process the cheat if a hash was set (falls through from any key match)
    if (cheatHash != 0) {
        FUN_00894c40(cheatHash, buffer); // likely convert hash to command string
    }

LAB_00730f72:
    // Additionally, check independent cheat flags (bits 18-23) and trigger them
    if ((*(uint*)((int)this + 0x2188) >> 0x12 & 1) != 0) {
        FUN_00894c40(0x523fef8f, buffer); // cheat hash for flag bit 18
    }
    if ((*(uint*)((int)this + 0x2188) >> 0x13 & 1) != 0) {
        FUN_00894c40(0xd4da82ad, buffer); // flag bit 19
    }
    if ((*(uint*)((int)this + 0x2188) >> 0x14 & 1) != 0) {
        FUN_00894c40(0x928b022e, buffer); // flag bit 20
    }
    if ((*(uint*)((int)this + 0x2188) >> 0x15 & 1) != 0) {
        FUN_00894c40(0x37996d72, buffer); // flag bit 21
    }
    if ((*(uint*)((int)this + 0x2188) >> 0x16 & 1) != 0) {
        FUN_00894c40(0x32b08ac3, buffer); // flag bit 22
    }
    if ((*(uint*)((int)this + 0x2188) >> 0x17 & 1) != 0) {
        FUN_00894c40(0xf5cff1af, buffer); // flag bit 23
    }

    // Cleanup – possibly destroy a reference object on the stack
    if (local_8[0] != 0) {
        FUN_004daf90(local_8); // likely destructor
    }
    return;
}