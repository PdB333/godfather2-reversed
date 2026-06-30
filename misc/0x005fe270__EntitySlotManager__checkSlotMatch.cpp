// FUNC_NAME: EntitySlotManager::checkSlotMatch
// Address: 0x005fe270
// This function checks if a given entity pair (passed in registers ESI/EDI) matches any of the two stored pairs.
// Returns: -3 if flag 0x4000 is set and param1 is false
//          -2 if matches pair at +0x7c/+0x84
//          -1 if matches pair at +0x70/+0x78
//           0 otherwise

// Note: In original x86 convention, param1 is on stack, while edi and esi are passed in the respective registers.
int __thiscall EntitySlotManager::checkSlotMatch(void* this, void* ediParam, void* esiParam, char param1) {
    // +0x18: flags field (ushort)
    if (((*(unsigned short*)((char*)this + 0x18) & 0x4000) != 0) && (param1 == '\0')) {
        return -3; // RB_FlagSetAndParamFalse
    }

    // +0xb4: another flags field (uint) – check bit 1 (0x2)
    if ((*(unsigned int*)((char*)this + 0xb4) >> 1 & 1) == 0) {
        // Compare with first stored pair at +0x7c and +0x84
        void* firstPtr1 = *(void**)((char*)this + 0x7c);
        void* firstPtr2;
        if (firstPtr1 == 0) {
            firstPtr2 = 0;
        } else {
            firstPtr2 = *(void**)((char*)this + 0x84);
        }
        if (ediParam == firstPtr1 && esiParam == firstPtr2) {
            return -2; // RB_MatchFirstPair
        }

        // Compare with second stored pair at +0x70 and +0x78
        void* secondPtr1 = *(void**)((char*)this + 0x70);
        void* secondPtr2;
        if (secondPtr1 == 0) {
            secondPtr2 = 0;
        } else {
            secondPtr2 = *(void**)((char*)this + 0x78);
        }
        if (ediParam == secondPtr1 && esiParam == secondPtr2) {
            return -1; // RB_MatchSecondPair
        }
    }

    return 0; // RB_NoMatch
}