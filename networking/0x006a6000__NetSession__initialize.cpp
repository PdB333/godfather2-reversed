// FUNC_NAME: NetSession::initialize
void __fastcall NetSession::initialize(NetSession* this)
{
    // +0x10: some global constant (likely session ID or connection ID)
    *(int*)((char*)this + 0x10) = DAT_00d5d7b8;

    // +0x678: current send/receive slot index, initialized to -1
    *(int*)((char*)this + 0x678) = -1;

    // +0x69c: max retransmit count? initialized to 6
    *(int*)((char*)this + 0x69c) = 6;

    // +0x6a0: retry/no-ack timer? initialized to 0
    *(int*)((char*)this + 0x6a0) = 0;

    // +0x6b8: timeout? initialized to 0
    *(int*)((char*)this + 0x6b8) = 0;

    // +0x14, 0x18, 0x1c: possibly sequence numbers or flags
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x18) = 0;
    *(int*)((char*)this + 0x1c) = 0;

    // --- Reliable send queue (8 entries, each 40 bytes) at +0x53c ---
    // Each entry starts with a pointer (likely to a packet)
    int* queueEntry = (int*)((char*)this + 0x53c);
    int count = 8;
    do {
        int current = count;                              // temporary, used for loop
        // Clear the first int (maybe flags) at queueEntry[-1]? Actually the decompiler shows piVar5[-1]=0, but that's before the array. It's likely a mistake. We assume it clears the field before the array? Or the loop is misaligned. We'll skip that and just clear the pointer.
        // Since we don't have exact, we'll safely clear the first int of the entry (the pointer)
        queueEntry[-1] = 0;   // This writes to offset 0x538?? Might be part of another member. We'll keep as is but note potential error.
        if (queueEntry[0] != 0) {
            // Free the packet (FUN_004daf90 deletes/releases the packet object)
            FUN_004daf90((int)queueEntry[0]);
            queueEntry[0] = 0;
        }
        // Another write: +0x558 + index*0x28 and +0x55c + index*0x28, but the index is -1 so these write to 0x530 and 0x534 (before array). This may be an artifact. We'll assume the intent was to clear part of the entry or a separate field.
        *(int*)((char*)this + 0x558 + (*(int*)((char*)this + 0x678) << 5) * 8) = 0;
        // Move to next entry (40 bytes = 10 ints)
        queueEntry += 10;
        count = current - 1;
        *(int*)((char*)this + 0x55c + (*(int*)((char*)this + 0x678) << 5) * 8) = 0;
    } while (count != 0);

    // Call another initialization function (likely sets up default handlers)
    FUN_006a5740();

    // --- Packet window (32 entries, each 24 bytes) at +0x6c0 ---
    int* windowEntry = (int*)((char*)this + 0x6c0);
    int remaining = 32;   // from iVar3 initial 1 + 0x1f = 0x20 (32)
    do {
        // Clear fields: the decompiler writes to windowEntry[-1], windowEntry+4, *windowEntry, windowEntry[1], [2], [3].
        // Probably each entry is a struct: first an int (maybe sequence), then a flag byte, then 4 ints for packet data.
        windowEntry[-1] = 0;   // Writes 4 bytes before the array (at +0x6bc) - maybe a separate field
        *(unsigned char*)(windowEntry + 4) = 0;  // set byte at offset 16
        windowEntry[0] = 0;
        windowEntry[1] = 0;
        windowEntry[2] = 0;
        windowEntry[3] = 0;
        windowEntry += 6;     // 6 ints = 24 bytes
        remaining--;
    } while (remaining != 0);

    // +0x6a8, 0x6ac, 0x6b0 - likely timing/counters
    *(int*)((char*)this + 0x6a8) = 0;
    *(int*)((char*)this + 0x6ac) = 0;
    *(int*)((char*)this + 0x6b0) = 0;

    // +0x9bc: active status flag, set to 1 (true)
    *(unsigned char*)((char*)this + 0x9bc) = 1;

    // +0x6a4: some counter? set to 0
    *(int*)((char*)this + 0x6a4) = 0;

    // +0x6b4: set from global (likely time or delta)
    *(int*)((char*)this + 0x6b4) = _DAT_00d5780c;

    // --- Clear the rest of the fields at +0x680-0x694 (part of the send queue area?) ---
    *(int*)((char*)this + 0x688) = 0;
    *(int*)((char*)this + 0x684) = 0;
    *(int*)((char*)this + 0x680) = 0;
    *(int*)((char*)this + 0x67c) = 0;

    int* queueEnd = (int*)((char*)this + 0x68c);
    if (*queueEnd != 0) {
        FUN_004daf90(*queueEnd);
        *queueEnd = 0;
    }
    if (*(int*)((char*)this + 0x694) != 0) {
        FUN_004daf90(*(int*)((char*)this + 0x694));
        *(int*)((char*)this + 0x694) = 0;
    }

    // Event handler registrations (subscribe to global events)
    if (DAT_01206794 != 0) {
        FUN_00408900((int)this, (int)&DAT_01206794, 0x8000);
    }
    if (DAT_0120678c != 0) {
        FUN_00408900((int)this, (int)&DAT_0120678c, 0x8000);
    }
    if (DAT_01206780 != 0) {
        FUN_00408900((int)this, (int)&DAT_01206780, 0x8000);
    }
    if (DAT_012067b4 != 0) {
        FUN_00408900((int)this, (int)&DAT_012067b4, 0x8000);
    }
    if (DAT_012069c4 != 0) {
        FUN_00408900((int)this, (int)&DAT_012069c4, 0x8000);
    }
}