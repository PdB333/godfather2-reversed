// FUNC_NAME: Player::processCommand
void __thiscall Player::processCommand(int thisPtr, int* command) // thisPtr offset 0x0, command has vtable
{
    int* globalSingleton = DAT_01223484; // Global engine singleton (could be GameManager)
    int subType = *(int*)(thisPtr + 0xdc); // +0xdc: command sub-type / state selector
    int commandType;

    // Resolve command type based on sub-type
    if (subType == 0xb) {
        commandType = *(int*)(thisPtr + 0x588); // +0x588: specific data for sub-type 0xb
    } else if (subType == 0xc) {
        commandType = *(int*)(thisPtr + 0x6e8); // +0x6e8: specific data for sub-type 0xc
    } else {
        commandType = subType; // default: use subType directly
    }

    switch (commandType) {
        case 3: { // Remove a pending command from list A (e.g., queued actions)
            uint count = *(int*)(thisPtr + 0x33c); // +0x33c: size of array A
            if (count != 0) {
                int* arrayA = *(int**)(thisPtr + 0x338); // +0x338: pointer to array A (array of command objects)
                int cmdId = (**(int (__thiscall**)(int*))(*command + 0xc))(); // command->getID() or getType()
                for (uint i = 0; i < count; i++) {
                    if (*(int*)(arrayA[i] + 0x5c) == cmdId) { // +0x5c: command object's ID
                        if (i != count - 1) {
                            arrayA[i] = arrayA[count - 1]; // move last element to fill the gap
                        }
                        *(int*)(thisPtr + 0x33c) = count - 1; // decrement count
                        break;
                    }
                }
            }
            break;
        }
        case 4: { // Execute a Lua/script command
            if (globalSingleton != 0) {
                if (*(char*)(thisPtr + 0x220) == '\0') { // +0x220: flag indicating valid state?
                    // If flag not set, call a method on the global singleton
                    void (__thiscall *func)() = *(void (__thiscall**)(int*))(*globalSingleton + 0x98);
                    func((int)globalSingleton); // +0x98: e.g., "executeScript"
                } else {
                    // Prepare and execute a script call with formatting
                    char buffer[4112]; // local stack buffer
                    int tempStringIdx = 0;
                    int tempArg1 = 0;
                    int tempArg2 = 0;
                    int* tempFuncPtr = 0;

                    FUN_00604be0(); // start string format context
                    int returnedId = (**(int (__thiscall**)(int*))(*command + 4))(); // command->getSomeID()
                    FUN_00604c10(0x73, returnedId); // push format argument
                    FUN_006038a0(DAT_012234a4, buffer, &tempStringIdx, "{#%u}", 0x533964aa); // format string with returnedId
                    char* scriptStr = (char*)tempStringIdx;
                    if (scriptStr == 0) {
                        scriptStr = (char*)&DAT_0120546e; // default empty string
                    }
                    FUN_00963050(scriptStr, 0); // execute script (takes string and flag)
                    void (__thiscall *cleanupFunc)() = *(void (__thiscall**)(int*))(*globalSingleton + 0x80);
                    cleanupFunc((int)globalSingleton); // +0x80: e.g., "finishScriptExecution"
                    FUN_00604c00(); // end string format context
                    if (tempStringIdx != 0) {
                        (*tempFuncPtr)(tempStringIdx); // free allocated string
                    }
                }
            }
            break;
        }
        case 5: { // Remove from list A with additional actions
            uint count = *(int*)(thisPtr + 0x33c);
            if (count == 0) {
                void (__thiscall *func)() = *(void (__thiscall**)(int*))(*(int*)(thisPtr + 0x2ec) + 0x94);
                func(thisPtr); // call virtual at +0x94 from object at +0x2ec
            } else {
                int* arrayA = *(int**)(thisPtr + 0x338);
                int cmdId = (**(int (__thiscall**)(int*))(*command + 0xc))();
                for (uint i = 0; i < count; i++) {
                    if (*(int*)(arrayA[i] + 0x5c) == cmdId) {
                        int removedElementState = *(int*)(arrayA[i] + 0x14); // +0x14: state of the removed command
                        if (i != count - 1) {
                            arrayA[i] = arrayA[count - 1];
                        }
                        *(int*)(thisPtr + 0x33c) = count - 1;
                        if (removedElementState == 2 && *(char*)(thisPtr + 0x1f4) != '\0') { // +0x1f4: another flag
                            if (globalSingleton != 0) {
                                *(int*)(thisPtr + 0x1e4) = 1; // +0x1e4: set a flag
                                FUN_008a3be0(thisPtr + 0x1a8); // initiate something (e.g., animation)
                            }
                            if ((*(uint*)(thisPtr + 0x6f4) >> 0x13 & 1) != 0) { // +0x6f4: bitfield, bit 19
                                FUN_00982c90(); // some start effect
                                *(char*)(thisPtr + 0x704) = 0; // +0x704: clear a byte
                                FUN_00967ec0(*(int*)(thisPtr + 0x1e0)); // finish event with ID from +0x1e0
                            }
                        }
                        goto callVirtualAfter;
                    }
                }
                // fallthrough to virtual call
                void (__thiscall *func)() = *(void (__thiscall**)(int*))(*(int*)(thisPtr + 0x2ec) + 0x94);
                func(thisPtr);
            }
            break;
        }
        case 6: // No action
            break;
        case 7: { // Remove from list B (different array)
            uint count = *(int*)(thisPtr + 0x3c8); // +0x3c8: size of array B
            if (count == 0) {
                void (__thiscall *func)() = *(void (__thiscall**)(int*))(*(int*)(thisPtr + 0x378) + 0x94);
                func(thisPtr);
            } else {
                int* arrayB = *(int**)(thisPtr + 0x3c4); // +0x3c4: pointer to array B
                int cmdId = (**(int (__thiscall**)(int*))(*command + 0xc))();
                for (uint i = 0; i < count; i++) {
                    if (*(int*)(arrayB[i] + 0x5c) == cmdId) {
                        if (i != count - 1) {
                            arrayB[i] = arrayB[count - 1];
                        }
                        *(int*)(thisPtr + 0x3c8) = count - 1;
                        goto callVirtualAfter;
                    }
                }
                void (__thiscall *func)() = *(void (__thiscall**)(int*))(*(int*)(thisPtr + 0x378) + 0x94);
                func(thisPtr);
            }
            break;
        }
        default:
            break;
    }
    // After switch, check if sub-type is 0xc and call cleanup
    if (*(int*)(thisPtr + 0xdc) == 0xc) {
        FUN_00967c80(); // final cleanup procedure
    }
}