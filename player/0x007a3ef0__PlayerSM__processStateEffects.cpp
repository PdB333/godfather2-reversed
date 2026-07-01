// FUNC_NAME: PlayerSM::processStateEffects
void __thiscall PlayerSM::processStateEffects(uint param_2, uint param_3, uint param_4, uint param_5, uint param_6, uint param_7, uint param_8)
{
    if (!isGameActive()) {
        goto callBaseHandler;
    }

    uint stateFlags = *(uint *)(this + 0x8e4); // +0x8E4: stateFlags (bit field)

    // Check bit 25 (0x2000000) - if set, handle specific states
    if ((stateFlags & (1 << 25)) == 0) {
        // Bit 25 is NOT set
        if ((stateFlags & (1 << 27)) == 0) {
            // Bit 27 is NOT set
            if ((stateFlags & (1 << 26)) == 0) {
                // Bit 26 is NOT set
                if ((stateFlags & (1 << 23)) == 0) {
                    goto callBaseHandler;
                }
                // Bit 23 is set => state corresponding to offset +0x2EEC
                if (isGameActive() &&
                    (g_globalCounter1 > 0 || g_globalCounter2 > 0) &&
                    (this + 0x2EEC != 0)) {
                    FUN_007fff40(this + 0x2EEC); // cleanup effect at offset +0x2EEC
                }
                if (FUN_00690150(0x38) != 0) { // check resource availability
                    if (isGameActive()) {
                        this = this + 0x2EBC; // move this to different offset? likely pointer arithmetic
                    }
                }
                goto callBaseHandler;
            }
            // Bit 26 is set => state corresponding to offset +0x2F0C
            if (isGameActive()) {
                this = this + 0x2F0C;
            }
        }
        else {
            // Bit 27 is set => state corresponding to offset +0x2F14
            if (isGameActive()) {
                this = this + 0x2F14;
            }
        }
        // Common cleanup for the chosen offset
        if ((g_globalCounter1 > 0 || g_globalCounter2 > 0) && (this != 0)) {
            FUN_007fff40(this);
        }
    }
    else {
        // Bit 25 is set
        if ((*(uint *)(this + 0x8E0) & (1 << 9)) != 0) { // +0x8E0: another flags field, bit 9
            // Check if there's a state object at +0x1C78
            StateObject* stateObj = *(StateObject**)(this + 0x1C78);
            if (stateObj != nullptr) {
                stateObj = (StateObject*)((uint8*)stateObj - 0x48); // offset to base? possibly vtable hack
            }
            int someFlag = 0;
            // Call virtual function at vtable index 4 (0x10/4) with hash 0x369AC561
            bool result = stateObj->vtable[4](0x369AC561, &someFlag);
            if (result && someFlag != 0) {
                // Another state object at same offset
                StateObject* obj2 = *(StateObject**)(this + 0x1C78);
                if (obj2 != nullptr) {
                    obj2 = (StateObject*)((uint8*)obj2 - 0x48);
                }
                if (isGameActive() &&
                    (g_globalCounter1 > 0 || g_globalCounter2 > 0) &&
                    (this + 0x2EF4 != 0)) {
                    FUN_0045ca00((int)obj2); // push/stack operation
                    StringContainer sc;
                    sc.data = *(uint*)(this + 0x2EF4); // string/array data at +0x2EF4
                    sc.type = 0;
                    FUN_00408a00(&sc, 0); // assign or copy
                    if (sc.somePointer != nullptr) {
                        FUN_004daf90(&sc.somePointer); // free
                    }
                }
                goto callBaseHandler;
            }
        }
        // Default cleanup for bit 25 set
        if (isGameActive() &&
            (g_globalCounter1 > 0 || g_globalCounter2 > 0) &&
            (this + 0x2EF4 != 0)) {
            FUN_0045ca00(0);
            StringContainer sc;
            sc.data = *(uint*)(this + 0x2EF4);
            sc.type = 0;
            FUN_00408a00(&sc, 0);
            if (sc.somePointer != nullptr) {
                FUN_004daf90(&sc.somePointer);
            }
        }
    }

callBaseHandler:
    // Call base class handler with original parameters
    FUN_00803b90(param_2, param_3, param_4, param_5, param_6, param_7, param_8);
}
```