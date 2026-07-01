// FUNC_NAME: triggerAudioEventForState

// Function at 0x0076d880
// Reads a state byte from a sub-object (offset 0x5C -> +0x1E08) and calls a virtual method
// with a corresponding audio event ID and fixed parameters (1,1,0,1.0f,1.0f).

void __fastcall triggerAudioEventForState(int* thisPtr)
{
    // Offset 0x5C: pointer to state data structure
    int* stateDataPtr = (int*)thisPtr[0x17]; // 0x17 * 4 = 0x5C
    unsigned char state = *(unsigned char*)((int)stateDataPtr + 0x1E08);

    unsigned int audioEventId;
    switch (state)
    {
    default:
        audioEventId = 0x4849b656;
        break;
    case 1:
        audioEventId = 0x4849b658;
        break;
    case 2:
        audioEventId = 0xD6BE85F1;
        break;
    case 3:
        audioEventId = 0xD2C80877;
        break;
    case 4:
    case 0x14: // 20
        audioEventId = 0x88154830;
        break;
    case 5:
    case 0x15: // 21
        audioEventId = 0x841ECAB6;
        break;
    case 6:
        audioEventId = 0x355140C5;
        break;
    case 7:
        audioEventId = 0x315AC34B;
        break;
    case 8:
    case 0x1E: // 30
        audioEventId = 0xE442E85A;
        break;
    case 9:
    case 0x1F: // 31
        audioEventId = 0xE04C6AE0;
        break;
    case 10:
        audioEventId = 0xA2075923;
        break;
    case 0xB: // 11
        audioEventId = 0x9E10DBA9;
        break;
    case 0xC: // 12
        audioEventId = 0x9E4D4569;
        break;
    case 0xD: // 13
        audioEventId = 0x9A56C7EF;
        break;
    case 0xE: // 14
        audioEventId = 0x9BDDC5C3;
        break;
    case 0xF: // 15
        audioEventId = 0x97E74849;
        break;
    case 0x10: // 16
    case 0x12: // 18
        audioEventId = 0x5987F526;
        break;
    case 0x11: // 17
    case 0x13: // 19
        audioEventId = 0x559177AC;
        break;
    case 0x16: // 22
        audioEventId = 0x512D8F2C;
        break;
    case 0x17: // 23
        audioEventId = 0x4D3711B2;
        break;
    case 0x18: // 24
    case 0x1A: // 26
        audioEventId = 0x019B482E;
        break;
    case 0x19: // 25
    case 0x1B: // 27
        audioEventId = 0xA654E1A1;
        break;
    case 0x1C: // 28
    case 0x1D: // 29
        audioEventId = 0x9500755B;
        break;
    }

    // Virtual function at vtable offset 0x2C (index 11)
    // Signature: void __thiscall func(void* this, unsigned int id, int a, int b, int c, float d, float e)
    typedef void (__thiscall *VFunc)(void*, unsigned int, int, int, int, float, float);
    VFunc vfunc = (VFunc)(*(int*)(*(int*)thisPtr + 0x2C));
    vfunc(thisPtr, audioEventId, 1, 1, 0, 1.0f, 1.0f);
}