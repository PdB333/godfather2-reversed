// FUNC_NAME: EARSGhost::packUpdate
// Function at 0x00471b10: Serializes ghost object fields into a bitstream for network replication.
// Uses global stream pointer at DAT_01206880 + 0x14 (likely a BitStream or WriteStream).
// Writes type tags (PTR_LAB_*) and field data for the object at `this`.

#include <cstring> // for memcpy

// Global stream pointer (assumed defined elsewhere)
extern uint8_t* gStreamPtr; // Actually DAT_01206880 (some struct), offset 0x14 is the stream buffer pointer

// Forward declaration of helper function
bool FUN_004709e0(); // returns something like a characteristic flag

void __fastcall EARSGhost::packUpdate(void* this) // this = param_1
{
    int* pStream;
    int adjustedBase; // derived from this+0x54
    int* pStreamAgain;
    void* alignedDst;
    uint* pStreamUint;
    int parentObj; // from this+0x68
    int extraOut_edx; // unused in final version

    // Compute the base offset 0x54 if object is non-null, else 0.
    // This offset is used repeatedly, likely a base field for some ID or offset.
    if (this == 0) {
        adjustedBase = 0;
    } else {
        adjustedBase = (int)this + 0x54;
    }

    // Write type tag PTR_LAB_0110ba44 followed by the base offset value.
    pStream = (int*)(gStreamPtr + 0x14); // pointer to stream position
    **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110ba44; // tag for "TransformID" or similar
    *pStream = *pStream + 4; // advance stream
    *(int*)*pStream = adjustedBase; // write the value
    *pStream = *pStream + 4;

    // Recompute adjustedBase again (same as above)
    if (this == 0) {
        adjustedBase = 0;
    } else {
        adjustedBase = (int)this + 0x54;
    }

    // Write type tag PTR_LAB_0110ba6c followed by the same base offset value.
    pStream = (int*)(gStreamPtr + 0x14);
    **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110ba6c; // tag for "TransformData" or similar
    *pStream = *pStream + 4;
    *(int*)*pStream = adjustedBase;
    *pStream = *pStream + 4;

    // Align stream to 16 bytes and copy 0x40 bytes from this+0x90 (likely a 4x4 transform matrix)
    alignedDst = (void*)((*pStream + 0x13) & 0xFFFFFFF0); // align to 16
    *pStream = (int)alignedDst;
    memcpy(alignedDst, (void*)((int)this + 0x90), 0x40); // copy transform
    *pStream = *pStream + 0x40;

    // Check bit 11 of flags at this+0x15e (0x15e is ushort, but here used as int? Mask: 0x800)
    if ((*(uint16_t*)((int)this + 0x15e) >> 0xB & 1) != 0) {
        // If flag is set, write another tag with a bool true
        pStreamUint = (uint*)(gStreamPtr + 0x14);
        **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110ba94; // tag for "SomeFlag"
        *pStreamUint = *pStreamUint + 4;
        *(int*)*pStreamUint = (int)this + 0x54; // write same base offset
        *pStreamUint = *pStreamUint + 4;
        *(uint8_t*)*pStreamUint = 1; // write byte 1 (true)
        *pStreamUint = (*pStreamUint + 4) & 0xFFFFFFFC; // align to 4
    }

    // Process parent/child object at this+0x68
    if ((*(int*)((int)this + 0x68) != 0) && (*(int*)((int)this + 0x68) != 0x48)) {
        // If parent pointer is non-null and not a special sentinel 0x48
        int parentRef;
        if (*(int*)((int)this + 0x68) == 0) {
            parentRef = 0;
        } else {
            parentRef = *(int*)((int)this + 0x68) - 0x48;
        }
        // Call a virtual function on the parent object (vtable at +0x54, method +0x50)
        (**(code**)(*(int*)(parentRef + 0x54) + 0x50))();

        int parentID = *(int*)((int)this + 0x68);
        if ((parentID == 0) || (parentID == 0x48)) {
            parentRef = 0;
        } else {
            parentRef = parentID + 0xC;
        }

        // Write tag for parent ID
        pStream = (int*)(gStreamPtr + 0x14);
        **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110baa8; // tag for "ParentID"
        *pStream = *pStream + 4;
        *(int*)*pStream = (int)this + 0x54; // write base offset
        *pStream = *pStream + 4;
        *(int*)*pStream = parentRef; // write parent ID
        *pStream = *pStream + 4;
    }

    // Call helper function and write its result as a boolean
    bool helperResult = FUN_004709e0();
    int streamBase = (int)gStreamPtr;
    **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110bad0; // tag for "HelperBool"
    *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
    **(uint32_t**)(*(int*)(streamBase + 0x14)) = extraOut_edx; // ?? extraout_EDX likely placeholder
    *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
    *(bool*)*(int*)(streamBase + 0x14) = helperResult; // write the bool
    *(uint*)(streamBase + 0x14) = *(uint*)(streamBase + 0x14) + 4 & 0xFFFFFFFC;

    // Write an integer from this+0x150
    int streamBase2 = (int)gStreamPtr;
    uint32_t field150 = *(uint32_t*)((int)this + 0x150);
    **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110babc; // tag for "Field150"
    *(int*)(streamBase2 + 0x14) = *(int*)(streamBase2 + 0x14) + 4;
    **(uint32_t**)(*(int*)(streamBase2 + 0x14)) = extraOut_edx; // placeholder
    int pos = *(int*)(streamBase2 + 0x14);
    *(uint32_t*)(pos + 4) = field150;
    *(int*)(streamBase2 + 0x14) = pos + 8;

    // Write sign of this+0x15e as boolean (bit 7)
    char signByte = *(char*)((int)this + 0x15e);
    uint* pStreamUint2 = (uint*)(gStreamPtr + 0x14);
    **(uint32_t**)(gStreamPtr + 0x14) = &PTR_LAB_0110bae4; // tag for "SignFlag"
    *pStreamUint2 = *pStreamUint2 + 4;
    *(uint32_t*)*pStreamUint2 = extraOut_edx; // placeholder
    *pStreamUint2 = *pStreamUint2 + 4;
    *(bool*)*pStreamUint2 = signByte < 0; // true if negative (bit 7 set)
    *pStreamUint2 = (*pStreamUint2 + 4) & 0xFFFFFFFC;

    return;
}