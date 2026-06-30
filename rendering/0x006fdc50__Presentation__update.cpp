// FUNC_NAME: Presentation::update
void __thiscall Presentation::update() {
    // this pointer: param_1 in decompiled; offsets: +0x00 callback, +0x04 callbackArg, +0x10 someId,
    // +0x18 m_presentation (pointer to another object?), +0x24 m_timer, +0x2C m_flags, +0x35 m_updateFlag
    // DAT_01205210 is a global time or frame counter (g_currentTime)

    if (m_presentation == nullptr) {
        return;
    }

    if ((m_flags & 0x40) != 0) {
        // Bit 6 set: clear animation state to zero
        // FUN_00424fb0 likely memsets a local struct to zero
        struct ZeroData { int data[3]; };
        ZeroData zeroData;
        FUN_00424fb0(&zeroData, 0, sizeof(zeroData));
        // Set presentation to this zero data
        FUN_005e2ce0(m_presentation, &zeroData);
    } else {
        // Bit 6 not set
        if (m_someId != 0 && m_someId != 0x48 && (m_flags & 4) != 0) {
            int idIndex = (m_someId == 0) ? 0 : (m_someId - 0x48);
            int* lookupResult = (int*)FUN_0046a1f0(idIndex, 0x38523fc3); // hash table lookup
            if (lookupResult != nullptr) {
                int currentTime = FUN_00471610(); // get current time/frame
                FUN_005e2ce0(m_presentation, currentTime + 0x30); // set animation time offset
                if ((m_flags & 0x20) == 0) {
                    // Bit 5 not set: call a function from looked-up object
                    int value = (**(int (__thiscall**)(int*))(*lookupResult + 0x58))(lookupResult);
                    FUN_005e2d30(m_presentation, value);
                }
            }
        }
    }

    // Check for timeout: flag at offset 0x35 and elapsed time > 8000
    if (m_updateFlag != 0 && (g_currentTime - m_timer) > 8000) {
        int local_20[3] = {0, 0, 0};
        code* local_14 = nullptr;
        FUN_005e2af0(m_presentation, local_20);
        if (m_callback != nullptr) {
            m_callback(m_presentation, 0, m_callbackArg);
        }
        FUN_006fda60(0);
        // Note: local_14 is not set by FUN_005e2af0; this call may be dead code or decompiler error.
        // In original assembly, local_14 might be the third element of local_20 array.
        if (local_20[0] != 0) {
            (*local_14)(local_20[0]);
        }
    }
}