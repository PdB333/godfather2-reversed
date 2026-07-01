// FUNC_NAME: PlayerSM::processStateEvent
char __thiscall PlayerSM::processStateEvent(void* thisPtr, int param_2, int param_3, int command) {
    char result = 0;
    // this->+0x58 is a pointer to some object (likely player data)
    int objectPtr = *(int*)((char*)thisPtr + 0x58);
    
    switch (command - 0x13) {
        case 0: { // command == 0x13
            if (objectPtr != 0) {
                if (isGamePaused() == 0) {
                    // Check flag at object+0x2320
                    if (*(char*)(objectPtr + 0x2320) == 0) {
                        *(char*)(objectPtr + 0x2320) = 1;
                        return 1;
                    }
                } else {
                    // Get vtable from sub-object referenced by this+0x78
                    int subObj = *(int*)((char*)thisPtr + 0x78);
                    if (subObj == 0) {
                        subObj = 0;
                    } else {
                        subObj = *(int*)(subObj - 0x48); // subtract offset to get base
                    }
                    // call virtual function at vtable offset 0x178
                    result = ((char (__thiscall*)(void*))(*((int*)subObj + 0x178 / 4)))(subObj);
                    if (result != 0) {
                        // Inlined fast call to some sound/event
                        FUN_007bfcd0();
                        FUN_0079fb90(0xe, 1, 0, /* stack args ignored */);
                        *(unsigned int*)((char*)thisPtr + 0x74) |= 4; // set flag
                        return result;
                    }
                }
            }
            break;
        }
        case 1: { // command == 0x14
            if (objectPtr != 0) {
                if (*(int*)((char*)thisPtr + 0x78) != 0 && *(int*)((char*)thisPtr + 0x78) != 0x48) {
                    int subObj = *(int*)((char*)thisPtr + 0x78);
                    if (subObj == 0) {
                        subObj = 0;
                    } else {
                        subObj = *(int*)(subObj - 0x48);
                    }
                    // virtual 0x150 (update?)
                    result = ((char (__thiscall*)(void*, int))(*((int*)subObj + 0x150 / 4)))(subObj, objectPtr);
                    if (result != 0) return 1;
                }
                result = someCondition1();
                if (result != 0) return 1;
                result = 0;
                char tmp = someCondition2();
                if (tmp != 0) {
                    FUN_007bfd40(); // state transition
                    return 0;
                }
            }
            break;
        }
        case 2: { // command == 0x15
            if (*(int*)((char*)thisPtr + 0x78) != 0 && *(int*)((char*)thisPtr + 0x78) != 0x48) {
                if (objectPtr == 0) return 0;
                int subObj = *(int*)((char*)thisPtr + 0x78);
                if (subObj == 0) {
                    subObj = 0;
                } else {
                    subObj = *(int*)(subObj - 0x48);
                }
                result = ((char (__thiscall*)(void*, int))(*((int*)subObj + 0x150 / 4)))(subObj, objectPtr);
                if (result != 0) return 0;
            }
            FUN_007bfd40();
            return 1;
        }
        case 3: { // command == 0x16
            if (objectPtr != 0) {
                result = someCondition2();
                if (result == 0) return 0;
                result = someCondition2();
                if (result != 0) return 0;
                return 1;
            }
            break;
        }
        case 4: { // command == 0x17
            if (*(int*)((char*)thisPtr + 0x80) != -1) return 0;
            result = someCondition1();
            if (result == 0) return 0;
            return 1;
        }
        case 5: { // command == 0x18
            result = 0;
            if (*(int*)((char*)thisPtr + 0x78) != 0 && *(int*)((char*)thisPtr + 0x78) != 0x48) {
                char tmp = someCondition2();
                if (tmp != 0) {
                    result = 1;
                    if (*(int*)((char*)thisPtr + 0x80) != -1) {
                        setTimer((int)((char*)thisPtr + 0x80));
                        return 1;
                    }
                }
            }
            break;
        }
        case 6: { // command == 0x19
            result = 0;
            int id = *(int*)((char*)thisPtr + 0x80);
            if (id != -1) {
                int timerState = getTimerState(id);
                result = 0;
                if (timerState == 3) {
                    setTimer((int)((char*)thisPtr + 0x80));
                    FUN_007bfd40();
                    return 1;
                }
            }
            break;
        }
        case 7: { // command == 0x1A
            // Check threshold using global float at 0x00d6e2ac
            if (*(float*)((char*)thisPtr + 0x30) <= *(float*)0x00d6e2ac) {
                return 0;
            }
            FUN_007bfd40();
            return 1;
        }
        case 8: { // command == 0x1B
            if (objectPtr != 0) {
                char tmp = isGamePaused();
                if (tmp != 0) {
                    int subObj = *(int*)((char*)thisPtr + 0x78);
                    if (subObj == 0) {
                        subObj = 0;
                    } else {
                        subObj = *(int*)(subObj - 0x48);
                    }
                    result = ((char (__thiscall*)(void*))(*((int*)subObj + 0x17c / 4)))(subObj);
                    if (result == 0) {
                        int subObj2 = *(int*)((char*)thisPtr + 0x78);
                        if (subObj2 == 0) {
                            subObj2 = 0;
                        } else {
                            subObj2 = *(int*)(subObj2 - 0x48);
                        }
                        int v180 = ((int (__thiscall*)(void*))(*((int*)subObj2 + 0x180 / 4)))(subObj2);
                        if (v180 == objectPtr) {
                            return 0;
                        }
                    }
                    if (*(int*)((char*)thisPtr + 0x78) == 0) {
                        FUN_007bfcf0(); // reset?
                        FUN_007bfd40();
                        return 1;
                    }
                    FUN_007bfcf0();
                    FUN_007bfd40();
                    return 1;
                }
                // if not paused, set flag
                if (*(char*)(objectPtr + 0x233c) == 0) {
                    *(char*)(objectPtr + 0x233c) = 1;
                    return 1;
                }
            }
            break;
        }
        default: {
            result = defaultHandler();
            break;
        }
    }
    return result;
}