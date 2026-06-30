// FUNC_NAME: CommandManager::addOrRemoveCommand

// Function address: 0x004a1c50
// Role: Adds or removes a command/event from the manager based on a flag.
// Structures:
//   this+0x1c0: bool m_isRecording (flag to decide add vs remove)
//   this+0x1bc: int m_commandListCount
//   this+0x14c: CommandEntry m_commandList[] (each 0x1C bytes)
//   this+0x84: int m_activeCount
//   this+0x44: ActiveEntry m_activeList[] (each 8 bytes: pointer + backlink)
// CommandEntry layout:
//   +0x00: int type (set to 2 here)
//   +0x04: int* pObjectPlus0x48 (pointer to object+0x48)
//   +0x08: int* pBacklink (from object+0x4c)
//   +0x0C: argA
//   +0x10: argB
//   +0x14: argC
//   +0x18: argD (byte)
// Parameter order matches Ghidra: param2=eventObj, param3=argB, param4=argA, param5=argC, param6=argD

void __thiscall CommandManager::addOrRemoveCommand(uint32_t eventObj, uint32_t argA, uint32_t argB, uint32_t argC, uint8_t argD)
{
    // +0x1c0
    if (eventObj != 0) {
        if (*(char*)(this + 0x1c0) != 0) {
            // Recording mode: add to command list
            int commandIdx = *(int*)(this + 0x1bc) + 1;
            *(int*)(this + 0x1bc) = commandIdx;
            int entryOffset = this + 0x14c + commandIdx * 0x1c;
            int* pType = (int*)(entryOffset);
            *pType = 2;
            int* pPtr = (int*)(entryOffset + 4); // +0x04
            int newPtr = eventObj + 0x48;
            if (*pPtr != newPtr) {
                if (*pPtr != 0) {
                    FUN_004daf90(pPtr); // free old pointer
                }
                *pPtr = newPtr;
                if (newPtr != 0) {
                    *(int*)(entryOffset + 8) = *(int*)(eventObj + 0x4c); // +0x08
                    *(int**)(eventObj + 0x4c) = (int*)(entryOffset + 4); // backlink
                }
            }
            *(int*)(entryOffset + 0x0c) = argA;
            *(int*)(entryOffset + 0x10) = argB;
            *(int*)(entryOffset + 0x14) = argC;
            *(char*)(entryOffset + 0x18) = argD;
            return;
        }
        // Non-recording mode: remove from active list
        int activeIdx = *(int*)(this + 0x84);
        if (activeIdx >= 0) {
            int* pEntry = (int*)(this + 0x44 + activeIdx * 8);
            while (true) {
                int ptrVal;
                if (*pEntry == 0) {
                    ptrVal = 0;
                } else {
                    ptrVal = *pEntry - 0x48;
                }
                if (eventObj == ptrVal) break;
                activeIdx--;
                pEntry -= 2;
                if (activeIdx < 0) return;
            }
            int objPtr = *(int*)(this + 0x44 + activeIdx * 8);
            int* pActive = (int*)(this + 0x44 + activeIdx * 8);
            if (objPtr == 0) {
                ptrVal = 0;
            } else {
                ptrVal = objPtr - 0x48;
            }
            if (*(char*)(ptrVal + 0x54) != 0 && *pActive != 0) {
                (**(code**)(*pActive - 0x48))(1); // call virtual function with 1
            }
            if (activeIdx < *(int*)(this + 0x84)) {
                do {
                    if (pActive != pActive + 2) {
                        int nextVal = *(pActive + 2);
                        if (*pActive != nextVal) {
                            if (*pActive != 0) {
                                FUN_004daf90(pActive);
                            }
                            *pActive = nextVal;
                            if (nextVal != 0) {
                                *(pActive + 1) = *(int*)(nextVal + 4);
                                *(int**)(nextVal + 4) = pActive;
                            }
                        }
                    }
                    activeIdx++;
                    pActive += 2;
                } while (activeIdx < *(int*)(this + 0x84));
            }
            int lastVal = *(int*)(this + 0x44 + *(int*)(this + 0x84) * 8);
            int* pLast = (int*)(this + 0x44 + *(int*)(this + 0x84) * 8);
            if (lastVal != 0) {
                int* pPrev = *(int**)(lastVal + 4);
                if (pPrev == pLast) {
                    *(int*)(lastVal + 4) = *(pLast + 1);
                } else {
                    int* pCur = (int*)*pPrev + 4;
                    while (pCur != pLast) {
                        pPrev = (int*)*pPrev + 4;
                        pCur = (int*)*pPrev + 4;
                    }
                    *pPrev = *(pLast + 1);
                }
                *pLast = 0;
            }
            int newCount = *(int*)(this + 0x84) - 1;
            *(int*)(this + 0x84) = newCount;
            if (newCount >= 0) {
                int idx = newCount;
                while (idx >= 0) {
                    int val = *(int*)(this + 0x44 + idx * 8);
                    if (val != 0 && val != 0x48) {
                        break;
                    }
                    idx--;
                    *(int*)(this + 0x84) = idx;
                    if (idx < 0) return;
                }
                FUN_004a20a0(argA, argB, argC, argD);
            }
        }
    }
}