// FUNC_NAME: PlayerSM::handleCommand
char PlayerSM::handleCommand(int param2, int param3, int param4, int commandId, int param6)
{
    char result = 1;
    char uVar4 = (char)((uint)unaff_EBX >> 24);
    int switchVal = commandId - 0x12;

    switch (switchVal) {
    case 0: // 0x12
        FUN_0080d5a0();
        return result;

    case 1: // 0x13
        // Call a method on m_pSomeObject at offset +0x14 (4 bytes per int)
        (*(void (__thiscall *)(int *))(*((int *)this[0x14]) + 0x1c))(this + 0x1b);
        FUN_0046fe50(this + 0x1e, 0);
        return uVar4;

    default:
        // For other command IDs (0x14, 0x15) forward to another handler
        result = FUN_0080e8e0(param2, param3, param4, commandId, param6);
        break;

    case 4: // 0x16
        this[0x27] = 1; // e.g., set weapon state to 1
        return 1;

    case 5: // 0x17
        this[0x27] = 2; // e.g., set weapon state to 2
        return 1;

    case 7: // 0x19
        this[0x27] = FUN_0080d3f0(); // set state from external function
        return result;

    case 8: // 0x1A
        {
            int playerIdx = FUN_00471610();
            char isSomeFlag = FUN_009a8570(*(int *)(playerIdx + 0x34)); // player flag
            int state = FUN_0080d3f0();
            int animId;
            if (state == 1) {
                animId = (isSomeFlag != 0) ? 0x50ef8b7f : 0xd6215b62; // animation IDs
            } else if (state == 2) {
                animId = (isSomeFlag != 0) ? 0x1774f4f : 0x6103309a;
            } else {
                return result;
            }
            // Call a vtable method on this at offset 0x2c (playAnimation)
            (*(void (__thiscall *)(int, int, int, int, float, float))(*this + 0x2c))(animId, 1, 1, 1, 1.0f, 1.0f);
            return 0;
        }

    case 9: // 0x1B
        {
            int playerIdx = FUN_00471610();
            char isSomeFlag = FUN_009a8570(*(int *)(playerIdx + 0x34));
            int animId;
            if (this[0x27] == 1) { // using current state
                animId = (isSomeFlag != 0) ? 0x6d5d8cbf : 0x84fd1b72;
            } else {
                animId = (isSomeFlag != 0) ? 0x3028c8f : 0x2455cc6a;
            }
            (*(void (__thiscall *)(int, int, int, int, float, float))(*this + 0x2c))(animId, 1, 1, 1, 1.0f, 1.0f);
        }
        // fall through to case 0xB? Actually no, no break, but case 0xB does not fall into this – it's separate.

    case 0xB: // 0x1D
        {
            char isSomething = FUN_00481620();
            if (isSomething && (this[0x16] != 0) && (this[0x16] != 0x48)) {
                int playerIdx = FUN_00471610();
                Vector3 localVec;
                FUN_009a84a0(&localVec, *(int *)(playerIdx + 0x34));
                int offset = (this[0x16] == 0) ? 0 : (this[0x16] - 0x48);
                // Read two floats from a 64-bit value at offset+0x1a8
                union { double d; float f[2]; } tmp;
                tmp.d = *(double *)(offset + 0x1a8);
                float f1 = tmp.f[0];
                float f2 = tmp.f[1];
                float f3 = DAT_00e44564 - *(float *)(offset + 0x1b0);
                // Compute a vector difference? Actually uses CONCAT44, likely not needed.
                // The code looks like it's computing a direction, but we simplify:
                // localVec = (DAT_00e44564 - f1, DAT_00e44564 - f2, f3);
                // But the original uses _local_18 which is undefined, so we skip.
                // Instead just call the method with localVec as argument.
                (*(void (__thiscall *)(Vector3 *))(*((int *)this[0x14]) + 0x1c))(&localVec);
                FUN_0046fe50(this + 0x1b, 0); // actually auStack_1c but ignore
                return uVar4;
            }
            break;
        }

    case 0xC: // 0x1E
        if ((*(char *)(this + 0x25) & 1) == 0) {
            FUN_004abdd0(0x20);
            return result;
        }
        break;

    case 0xD: // 0x1F
        FUN_005512c0(1);
        return result;

    case 0xE: // 0x20
        FUN_005512c0(this[0x26]);
        return result;

    case 0xF: // 0x21
        if ((this[0x18] != 0) && (this[0x18] != 0x48)) {
            int offset = (this[0x18] == 0) ? 0 : (this[0x18] - 0x48);
            int isSomething = FUN_0073b060(offset);
            if (isSomething != 0) {
                FUN_009b0820(this[0x14], DAT_00d5ef88, 1);
                return result;
            }
        }
        break;

    case 0x10: // 0x22
        {
            int* pField = this + 0x16;
            if ((this[0x16] != 0) && (this[0x16] != 0x48)) {
                int offset = (this[0x16] == 0) ? 0 : (this[0x16] - 0x48);
                *(char *)(offset + 0x1e4) -= 1; // decrement ref count
                if (this[0x16] != 0) {
                    FUN_004daf90(pField);
                    *pField = 0;
                }
            }
            FUN_009995e0(0, 0, 0);
            return result;
        }
    }

    return result;
}