// FUNC_NAME: NetObject::initEventDelegates
// Function address: 0x004e9a30
// This function initializes event handler function pointers and contexts within a NetObject
// based on the object's version (*this) and a flag (isServerSide).
// Offsets are relative to the object's data (pointed by this[1]).

void __thiscall NetObject::initEventDelegates(uint *this, uint context, char isServerSide)
{
    // this[0] = object version (e.g., network protocol version)
    // this[1] = pointer to the actual object data block (where offsets are applied)
    uint objectData;

    // --- Version >= 8 (7 < v) ---
    if (7 < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x158) = (uint)&FUN_004e9870;  // +0x158: handler1
        *(_DWORD *)(objectData + 0x160) = context;            // +0x160: context1
        if (7 < *this)   // redundant, always true
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x170) = (uint)&FUN_004e9980;  // +0x170: handler2
            *(_DWORD *)(objectData + 0x178) = context;            // +0x178: context2
        }
    }

    // --- Version >= 9 (8 < v) ---
    if (8 < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x188) = (uint)&FUN_004e9870;  // +0x188: handler3
        *(_DWORD *)(objectData + 400) = context;               // +0x190: context3 (decimal)
        if (8 < *this)   // redundant
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x1a4) = (uint)&FUN_004e9960;  // +0x1a4: handler4
            *(_DWORD *)(objectData + 0x1ac) = context;            // +0x1ac: context4
        }
    }

    // --- Version >= 11 (10 < v) ---
    if (10 < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x1e8) = (uint)&FUN_004e9870;  // +0x1e8: handler5
        *(_DWORD *)(objectData + 0x1f0) = context;            // +0x1f0: context5
        if (10 < *this)   // redundant
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x204) = (uint)&FUN_004e9960;  // +0x204: handler6
            *(_DWORD *)(objectData + 0x20c) = context;            // +0x20c: context6
        }
    }

    // --- Version >= 14 (0xd < v) ---
    if (0xd < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x274) = (uint)&FUN_004e9870;  // +0x274: handler7
        *(_DWORD *)(objectData + 0x27c) = context;            // +0x27c: context7
    }

    // --- Version >= 14 again (0xd < v) ---
    if (0xd < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x290) = (uint)&FUN_004e98a0;  // +0x290: handler8
        *(_DWORD *)(objectData + 0x298) = context;            // +0x298: context8
    }

    // --- Server-side only additions (isServerSide != 0) ---
    if (isServerSide != 0)
    {
        // Version >= 3 (2 < v)
        if (2 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x80) = (uint)&FUN_004e99d0;  // +0x80: serverHandler1
            *(_DWORD *)(objectData + 0x88) = context;            // +0x88: serverContext1
        }

        // Version >= 17 (0x10 < v)
        if (0x10 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 800) = (uint)&FUN_004e99c0;   // +0x320: serverHandler2
            *(_DWORD *)(objectData + 0x328) = context;            // +0x328: serverContext2
        }

        // Version >= 19 (0x12 < v)
        if (0x12 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x364) = (uint)&FUN_004e98b0;  // +0x364: serverHandler3
            *(_DWORD *)(objectData + 0x36c) = context;            // +0x36c: serverContext3
        }

        // Version >= 20 (0x13 < v)
        if (0x13 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x394) = (uint)&FUN_004e98c0;  // +0x394: serverHandler4
            *(_DWORD *)(objectData + 0x39c) = context;            // +0x39c: serverContext4
        }

        // Version >= 21 (0x14 < v)
        if (0x14 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x3c4) = (uint)&FUN_004e98e0;  // +0x3c4: serverHandler5
            *(_DWORD *)(objectData + 0x3cc) = context;            // +0x3cc: serverContext5
            if (0x14 < *this)   // redundant
            {
                objectData = this[1];
                *(_DWORD *)(objectData + 0x3e0) = (uint)&FUN_004e9900;  // +0x3e0: serverHandler6
                *(_DWORD *)(objectData + 1000) = context;               // +0x3e8: serverContext6
            }
        }

        // Version >= 22 (0x15 < v)
        if (0x15 < *this)
        {
            objectData = this[1];
            *(_DWORD *)(objectData + 0x3f4) = (uint)&FUN_004e9930;  // +0x3f4: serverHandler7
            *(_DWORD *)(objectData + 0x3fc) = context;            // +0x3fc: serverContext7
            if (0x15 < *this)   // redundant
            {
                objectData = this[1];
                *(_DWORD *)(objectData + 0x410) = (uint)&FUN_004e9940;  // +0x410: serverHandler8
                *(_DWORD *)(objectData + 0x418) = context;            // +0x418: serverContext8
            }
        }
    }

    // --- Version >= 26 (0x19 < v) ---
    if (0x19 < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x4b4) = (uint)&FUN_004e9950;  // +0x4b4: handler9
        *(_DWORD *)(objectData + 0x4bc) = context;            // +0x4bc: context9
    }

    // --- Version >= 24 (0x17 < v) ---
    if (0x17 < *this)
    {
        objectData = this[1];
        *(_DWORD *)(objectData + 0x470) = (uint)&FUN_004e9960;  // +0x470: handler10
        *(_DWORD *)(objectData + 0x478) = context;            // +0x478: context10
    }

    return;
}