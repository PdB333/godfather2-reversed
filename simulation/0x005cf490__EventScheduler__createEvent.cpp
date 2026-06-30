// FUNC_NAME: EventScheduler::createEvent
// Function address: 0x005cf490
// Creates a new scheduled event with given parameters and returns a handle (wrapper).
// The class has a field at +0x04 indicating if initialized.
// The event object has fields at +0x04 (typeFlags), +0x08 (someId), +0x14 (duration),
// +0x18 (param6), +0x1c (param8), +0x24 (param7), +0x2c (subObject).
// Global constants: DAT_00e446e8 (startTime), DAT_00e448c0 (endTime).

int* __thiscall EventScheduler::createEvent(
    int this,                // +0x04 = m_initialized
    bool loop,               // param_3
    bool repeat,             // param_4
    int someId,              // param_5
    int param6,               // param_6
    byte byteParam1,          // param_7
    byte byteParam2)          // param_8
{
    int iVar1;
    uint uVar2;
    int* piVar3;
    int flagLocal;  // local_4

    if (*(int*)(this + 4) == 0) {
        return (int*)0x0;
    }

    flagLocal = 0;
    uVar2 = getEventTypeId(this, &flagLocal);  // FUN_005ce1c0

    piVar3 = (int*)allocateEventObject();       // FUN_005d0df0
    piVar3[1] = 0;   // +0x04 of wrapper
    piVar3[2] = 0;   // +0x08
    piVar3[3] = g_startTime;      // DAT_00e446e8
    piVar3[4] = g_endTime;        // DAT_00e448c0
    piVar3[5] = 0;   // +0x14
    piVar3[6] = 0;   // +0x18: flags

    if (repeat) {
        piVar3[6] |= 1;       // repeat flag (bit 0)
    }
    if (loop) {
        piVar3[6] |= 8;       // loop flag (bit 3)
    }
    piVar3[6] |= 0x40;        // always set bit 6

    iVar1 = piVar3[0];          // dereference to event object
    *(uint*)(iVar1 + 4) = uVar2;      // +0x04 = type ID
    if (flagLocal == 1) {
        *(uint*)(iVar1 + 4) = uVar2 | 0xF000000; // special type flag
    }

    *(int*)(iVar1 + 0x18) = param6;    // +0x18
    *(uint*)(iVar1 + 0x1c) = byteParam2; // +0x1c
    *(uint*)(iVar1 + 0x24) = byteParam1; // +0x24
    *(int*)(iVar1 + 8) = someId;       // +0x08
    *(int*)(iVar1 + 0x14) = (int)((float)g_startTime - (float)g_endTime); // duration = start - end (as int)

    initSubObject(iVar1 + 0x2c);  // FUN_005cd370

    return piVar3;
}