// FUNC_NAME: ConditionSet::findFirstMatch
int ConditionSet::findFirstMatch(int numToProcess, int currentPos) {
    int totalNodes = *(int*)(this + 0x2c);
    int bestMatchIdx = totalNodes - 1;

    // Quick rejection if state is invalid or last node opcode != 0x1b
    if ((*(byte*)(this + 0x47) > 0xfa) ||
        ((*(int*)(this + 0x30) != totalNodes && *(int*)(this + 0x30) != 0) ||
         (*(int*)(this + 0xc) && (*(int*)(this + 0xc) && 
          ((*(int*)(this + 0xc) + (totalNodes - 1) * 4) & 0x3f) != 0x1b))))
    {
        return 0;
    }

    int idx = 0;
    if (numToProcess < 1) {
        goto return_best;
    }

    uint limitByte = (uint)*(byte*)(this + 0x47);
    int* nodeTable = (int*)*(int*)(this + 0xc);

loop:
    uint instr = (uint)nodeTable[idx];
    int highByte = (int)(instr >> 24);
    uint fieldA = 0;
    uint fieldB = 0;

    if ((int)limitByte <= highByte) {
        return 0;
    }

    byte opFlags = opFlagTable[instr & 0x3f]; // static table
    uint shifted6 = instr >> 6;

    if ((opFlags & 3) == 0) {
        fieldA = shifted6 & 0x1ff;
        fieldB = (instr >> 15) & 0x1ff;
        if ((opFlags & 4) == 0) {
            if ((opFlags & 8) != 0 && !someConditionCheck()) {
                return 0;
            }
        } else {
            if (limitByte <= fieldB) return 0;
        }
        if ((opFlags & 0x10) != 0) {
            if (limitByte <= fieldA) {
                if (fieldA < 0xfa) return 0;
                int diff = fieldA - 0xfa;
                if (diff < *(int*)(this + 0x28)) return 0;
            }
        }
    } else if ((opFlags & 3) == 1) {
        fieldB = shifted6 & 0x3ffff;
        if ((opFlags & 0x40) != 0) {
            if ((int)fieldB < *(int*)(this + 0x28)) return 0;
        }
    } else if ((opFlags & 3) == 2) {
        fieldB = (shifted6 & 0x3ffff) - 0x1ffff;
    }

    if ((opFlags & 0x20) != 0 && highByte == currentPos) {
        bestMatchIdx = idx;
    }

    if ((char)opFlags < 0) {
        if (totalNodes <= idx + 2) return 0;
        if ((nodeTable[idx + 1] & 0x3f) != 0x14) return 0;
    }

    switch (instr & 0x3f) {
    case 2:
        if (fieldA != 0 && totalNodes <= idx + 2) return 0;
        break;
    case 3:
        if (highByte <= currentPos && currentPos <= (int)fieldB) {
            bestMatchIdx = idx;
        }
        break;
    case 4:
    case 8:
        fieldA = (uint)*(byte*)(this + 0x44);
        if ((int)fieldA <= (int)fieldB) return 0;
        break;
    case 5:
    case 7:
        if (*(int*)(*(int*)(this + 8) + fieldB * 8) != 4) return 0;
        break;
    case 0xb:
        if ((int)limitByte <= highByte + 1) return 0;
        if (currentPos == highByte + 1) bestMatchIdx = idx;
        break;
    case 0x13:
        if (fieldA > 0xf9) return 0;
        if ((int)fieldA <= (int)fieldB) return 0;
        break;
    case 0x14:
        goto case_0x14;
    case 0x19:
    case 0x1a: {
        if (fieldB != 0 && (int)limitByte <= (int)((fieldB - 1) + highByte)) return 0;
        int skipBase = fieldA - 1;
        int skipIdx;
        if (skipBase == -1) {
            uint64 result = someFunction(); // returns a 64-bit value
            skipIdx = (int)(result >> 32);
            if ((int)result == 0) return 0;
        } else {
            skipIdx = idx;
            if (skipBase != 0 && (int)limitByte <= highByte - 1 + skipBase) return 0;
        }
        if (highByte <= currentPos) bestMatchIdx = skipIdx;
        break;
    }
    case 0x1b:
        if (0 < (int)(fieldB - 1)) {
            int range = fieldB - 2;
            if ((int)limitByte <= range + highByte) return 0;
        }
        break;
    case 0x1c:
        goto case_0x1c;
    case 0x1d:
        if ((int)limitByte <= highByte + 5 + (int)fieldA) return 0;
        if (highByte <= currentPos) bestMatchIdx = idx;
        goto case_0x1c;
    case 0x1f: {
        int range = (fieldB & 0x1f) + 1;
        if ((int)limitByte <= range + highByte) return 0;
        break;
    }
    case 0x22: {
        if (*(int*)(this + 0x34) <= (int)fieldB) return 0;
        uint count = *(byte*)(*(int*)(*(int*)(this + 0x10) + fieldB * 4) + 0x44);
        if (totalNodes <= (int)(count + idx)) return 0;
        if (count != 0) {
            int* ptr = &nodeTable[count + idx];
            do {
                if ((*ptr & 0x3f) != 4 && (*ptr & 0x3f) != 0) return 0;
                count--;
                ptr--;
            } while (0 < (int)count);
        }
        break;
    }
    }

    idx++;
    if (idx < numToProcess) goto loop;

return_best:
    return nodeTable[bestMatchIdx];

case_0x1c:
    if ((int)limitByte <= highByte + 2) return 0;
case_0x14: {
    int newIdx = (int)fieldB + 1 + idx;
    if (newIdx < 0) return 0;
    if (totalNodes <= newIdx) return 0;
    if (currentPos != 0xff && idx < newIdx && newIdx <= numToProcess) {
        idx = (int)fieldB + idx;  // skip forward
    }
    idx++;
    if (idx < numToProcess) goto loop;
    goto return_best;
}
}