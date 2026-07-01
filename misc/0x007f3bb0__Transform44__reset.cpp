// FUNC_NAME: Transform44::reset
void __fastcall Transform44::reset(Transform44 *thisPtr)
{
    float identityValue = _DAT_00d5780c; // constant (likely 1.0f)

    // Zero first 5 ints (0-4)
    thisPtr->m00 = 0;
    thisPtr->m01 = 0;
    thisPtr->m02 = 0;
    thisPtr->m03 = 0;
    thisPtr->m04 = 0; // actually 4th element?

    // Zero ints at offsets 8-17 (indices 8-0x17)
    thisPtr->m10 = 0;
    thisPtr->m11 = 0;
    thisPtr->m12 = 0;
    thisPtr->m13 = 0;
    thisPtr->m14 = 0;
    thisPtr->m15 = 0;
    thisPtr->m16 = 0;
    thisPtr->m17 = 0;
    thisPtr->m18 = 0;
    thisPtr->m19 = 0;

    // Zero ints at offsets 5-7 (indices 5,6,7)
    thisPtr->m05 = 0;
    thisPtr->m06 = 0;
    thisPtr->m07 = 0;

    // Groups of three zeros followed by identityValue (rows of a matrix?)
    // Group 1: offsets 0x18-0x1b
    thisPtr->m24 = 0; // index 0x18
    thisPtr->m25 = 0;
    thisPtr->m26 = 0;
    thisPtr->m27 = identityValue; // index 0x1b

    // Group 2: offsets 0x1c-0x1f
    thisPtr->m28 = 0;
    thisPtr->m29 = 0;
    thisPtr->m30 = 0;
    thisPtr->m31 = identityValue; // index 0x1f

    // Group 3: offsets 0x20-0x23
    thisPtr->m32 = 0;
    thisPtr->m33 = 0;
    thisPtr->m34 = 0;
    thisPtr->m35 = identityValue; // index 0x23

    // Group 4: offsets 0x24-0x27
    thisPtr->m36 = 0;
    thisPtr->m37 = 0;
    thisPtr->m38 = 0;
    thisPtr->m39 = identityValue; // index 0x27

    // Group 5: offsets 0x28-0x2b
    thisPtr->m40 = 0;
    thisPtr->m41 = 0;
    thisPtr->m42 = 0;
    thisPtr->m43 = identityValue; // index 0x2b

    // Two trailing bytes at offsets 0xB0 and 0xB1
    *(uint8 *)((uint8*)thisPtr + 0xB0) = 0;
    *(uint8 *)((uint8*)thisPtr + 0xB1) = 0;
}