// FUNC_NAME: CommandStream::processSetPropertyFloat
int __thiscall CommandStream::processSetPropertyFloat(int thisPtr) {
    int* pCurrent;    // piVar2
    int* pEnd;        // from +0x8
    int opcode;       // *pCurrent
    int index;        // iVar3
    float value;      // fVar4

    pCurrent = *(int**)(thisPtr + 0xC); // current read pointer in command buffer
    pEnd = *(int**)(thisPtr + 0x8);     // end of command buffer

    // Buffer validation: must have at least one word (opcode)
    if (pEnd <= pCurrent) {
        return 0;
    }
    if (pCurrent == nullptr) {
        return 0;
    }

    // Check opcode: only 7 or 2 are accepted
    if (*pCurrent != 7 && *pCurrent != 2) {
        return 0;
    }

    // Skip opcode and next word (index or offset)
    pCurrent += 2;
    if (pEnd <= pCurrent) {
        return 0;
    }
    if (pCurrent == nullptr) {
        return 0;
    }

    // Second word must be 3 (direct value) or 4 (need validation)
    if (*pCurrent != 3) {
        if (*pCurrent != 4) {
            return 0;
        }
        // Opcode 4: validate via external function
        if (FUN_00636850(&thisPtr) == 0) { // likely validation of the property
            return 0;
        }
    }

    // Re-read original opcode to compute index offset
    pCurrent = *(int**)(thisPtr + 0xC);
    if ((pCurrent < pEnd) && (pCurrent != nullptr)) {
        if (*pCurrent == 2) {
            index = pCurrent[1];            // direct index
            goto LAB_00437115;
        }
        if (*pCurrent == 7) {
            index = pCurrent[1] + 0x10;     // index + 16 for opcode 7
            goto LAB_00437115;
        }
    }
    index = 0;

LAB_00437115:
    // Get the float value (type 2 probably = float property)
    value = (float)FUN_006259b0(thisPtr, 2);
    // Apply the property value at computed index
    FUN_005e6700(index, value);
    return 0;
}