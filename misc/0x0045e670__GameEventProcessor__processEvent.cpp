// FUNC_NAME: GameEventProcessor::processEvent
void __thiscall GameEventProcessor::processEvent(uintptr_t thisPtr, Event* event)
{
    int eventId;
    int iVar2;
    int basePtr;
    float fVar1;
    float fVar6;
    int local_20;
    char local_14[16];

    eventId = *event;  // event->id
    if (g_EventIdDisplayMessage == eventId) {  // DAT_012069c4
        if ((*(byte*)(thisPtr + 0x148) & 0x10) == 0) {
            // Get base object pointer (this is offset from -0x3c)
            basePtr = *(int*)(thisPtr - 0x3c);
            local_20 = g_SomeGlobal;  // DAT_012067e8
            // Call virtual functions on base object
            (*(void(__thiscall**)(int))(*basePtr + 0x110))(0);  // offset 0x110
            (*(void(__thiscall**)(int))(*basePtr + 0x178))();  // offset 0x178
        }
        FUN_0045e5c0();  // some sub-function
        consumeEvent(event);  // FUN_0046efc0
        return;
    }
    if (g_EventIdSomething == eventId) {  // DAT_01206980
        iVar2 = *(int*)(thisPtr + 0x228);
        if (iVar2 != 0) {
            if (*(int*)(thisPtr + 0x128) != 0) {
                // Determine base pointer for message
                int msgBase;
                if (thisPtr == 0x3c) {
                    msgBase = 0;
                } else {
                    msgBase = thisPtr + 0x18;
                }
                // Build a 32-bit value from iVar2
                unsigned short low = (unsigned short)iVar2;
                unsigned short high = (unsigned short)(iVar2 >> 16);
                uint32 packed = (high << 16) | low;
                UNK_FUN_0045d280(msgBase, packed, 12);  // pass 0x10? Actually third arg is 0x10 per decompile
            }
            UNK_FUN_00460f20();  // some function
            consumeEvent(event);
            return;
        }
    } else {
        if (g_EventIdAnother == eventId) {  // DAT_0120ead4
            UNK_FUN_0045e020();
            consumeEvent(event);
            return;
        }
        if (g_EventIdYetAnother == eventId) {  // DAT_0120eaa0
            UNK_FUN_00460120();
            if ((*(uint*)(thisPtr + 0x148) & 0x100) != 0) {
                UNK_FUN_00461850(&local_20);
            }
            if (local_20 != 0) {
                *(int*)(local_20 + 8) = 0;
                consumeEvent(event);
                return;
            }
        } else {
            if (g_EventIdD == eventId) {  // DAT_0120eac4
                UNK_FUN_00460210(*(int*)(event[1] + 4 + 4));  // complicated data extraction
                consumeEvent(event);
                return;
            }
            if (g_EventIdE == eventId) {  // DAT_0120eab4
                char** strPtr = *(char***)(event[1] + 4 + 4);
                if ((strPtr != nullptr) && (**strPtr != '\0')) {
                    local_20 = 0;
                    // Some buffer setup
                    *((short*)&local_20) = 0;
                    *((short*)&local_20 + 1) = 0;
                    UNK_FUN_00408240();
                    UNK_FUN_0045ca00(thisPtr - 0x3c);
                    UNK_FUN_0045c400(&local_20, (int*)local_14, 0);
                    UNK_FUN_00408310(&local_20);
                    UNK_FUN_0045cac0();
                    consumeEvent(event);
                    return;
                }
            } else {
                if (g_EventIdF == eventId) {  // DAT_0120eacc
                    fVar1 = *(float*)(event[1] + 4 + 4);
                    fVar6 = 0.0;
                    // Clamp value between 0.0 and g_MaxFloat
                    if ((fVar1 <= 0.0) || (fVar6 = DAT_00e2b1a4, DAT_00e2b1a4 <= fVar1)) {
                        fVar1 = fVar6;
                    }
                    *(float*)(thisPtr + 0x234) = fVar1;
                    consumeEvent(event);
                    return;
                }
                if (g_EventIdG == eventId) {  // DAT_0120ea98
                    *(int*)(thisPtr + 0x234) = 0;
                    consumeEvent(event);
                    return;
                }
                if (g_EventIdH == eventId) {  // DAT_0120eaa8
                    UNK_FUN_00461240();
                    consumeEvent(event);
                    return;
                }
                if (eventId == g_EventIdI) {  // DAT_0120eabc
                    (*(void(__thiscall**)(int))(*(int*)(thisPtr - 0x3c) + 0x18c))();
                    consumeEvent(event);
                    return;
                }
                if (g_EventIdJ == eventId) {  // DAT_0120e93c
                    int* ptr = *(int**)(thisPtr + 0xf4);
                    if (ptr != nullptr) {
                        (*(void(__thiscall**)(int*))(*ptr + 0x2c))();
                    }
                    (*(void(__thiscall**)(int))(*(int*)(thisPtr - 0x3c) + 0x14))();
                    UNK_FUN_004086d0(&g_EventIdJ);  // likely unsubscribe
                    consumeEvent(event);
                    return;
                }
                if (g_EventIdK == eventId) {  // DAT_01206778
                    int eventData = event[1];
                    int val = *(int*)(*(int*)(eventData + 0xc) + 0x1c);
                    if (val == *(int*)(thisPtr + 0x254)) {
                        char result = (*(char(__thiscall**)(int, int))(*(int*)(thisPtr - 0x3c) + 400))(val);
                        if ((result != 0) && (*(int*)(eventData + 8) == 0)) {
                            *(int*)(eventData + 8) = 1;
                        }
                    }
                }
            }
        }
    }
    consumeEvent(event);
    return;
}