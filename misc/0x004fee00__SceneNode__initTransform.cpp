// FUNC_NAME: SceneNode::initTransform
// Address: 0x004fee00
// This function initializes the transform of a scene node from a TransformData structure.
// Offsets:
//   this+0x00: vtable pointer
//   this+0x0d: flag byte (if non-zero, skip init)
//   this+0x10 (this[4]): pointer to matrix storage block
//   this+0x24 (this[9]): stored TransformData pointer
//   this+0x28 (this[10]): counter/flag (set to 0)
//   this+0x34 (this[0xd]): maybe pointer (set to 0)
//   this+0x3c (this[0xf]): result (2 or 0)
//   this+0x40 (this[0x10]): flag (set to 0)
//   this+0x44: orientation type (0xff, 0, 1)
// TransformData offsets:
//   +0x10: flags
//   +0x1c,0x20,0x24: translation (float x,y,z)
//   +0x6c: some byte flag
//   +0x70,0x74: rotation/quaternion part for FUN_0056b8a0

void* __thiscall SceneNode::initTransform(SceneNode* this, int transformData)
{
    // Base class initialization
    FUN_00533cc0();

    // Set vtable
    *((uint32_t**)this) = (uint32_t*)&PTR_FUN_00e37b70;  // vtable for SceneNode

    // Check if already initialized (byte at +0x0d is non-zero)
    if ( *(int8_t*)((uint8_t*)this + 0x0d) == 0 )
    {
        // Store transform data pointer
        *(int32_t*)((uint8_t*)this + 0x24) = transformData;   // this[9]

        // Clear flag at +0x40
        *(int32_t*)((uint8_t*)this + 0x40) = 0;               // this[0x10]

        // Access per‑thread context via FS segment (TLS)
        // FS:[0x2c] → pointer to per‑thread structure → pointer to context → matrix index at offset 8
        int32_t* tlsPointer = *(int32_t**)__readfsdword(0x2c);
        int32_t* threadContext = (int32_t*)*tlsPointer;
        int32_t matrixIndex = *(int32_t*)((uint8_t*)threadContext + 8);

        // Get pointer to matrix storage from this[4]
        uint8_t* matrixStorage = *(uint8_t**)((uint8_t*)this + 0x10); // this[4]

        // Destination for rotation part: storage + 0x10 + matrixIndex
        float* rotationDest = (float*)(matrixStorage + 0x10 + matrixIndex);
        // Destination for translation part: storage + 0x40 + matrixIndex
        float* translationDest = (float*)(matrixStorage + 0x40 + matrixIndex);

        // Initialize rotation matrix from transformData (quaternion/rotation data)
        // Parameters: (something from +0x70, something from +0x74, 0, dest)
        FUN_0056b8a0(*(int32_t*)(transformData + 0x70),
                     *(int32_t*)(transformData + 0x74),
                     0,
                     rotationDest);

        // Handle translation mode based on flags
        uint32_t flags = *(uint32_t*)(transformData + 0x10);
        if ( (flags & 2) == 0 )
        {
            // Absolute mode (bit 2 clear, bit 4 tested)
            if ( (flags & 4) != 0 )
            {
                // Set translation directly
                *(float*)(translationDest + 0) = *(float*)(transformData + 0x1c);
                *(float*)(translationDest + 1) = *(float*)(transformData + 0x20);
                *(float*)(translationDest + 2) = *(float*)(transformData + 0x24);
            }
        }
        else
        {
            // Additive mode (bit 2 set)
            translationDest[0] = *(float*)(transformData + 0x1c) + translationDest[0];
            translationDest[1] = *(float*)(transformData + 0x20) + translationDest[1];
            translationDest[2] = *(float*)(transformData + 0x24) + translationDest[2];
        }

        // If flag bit 0x1000 is set, set bit 0x100 in the slot header (storage + matrixIndex)
        if ( (flags & 0x1000) != 0 )
        {
            uint32_t* slotHeader = (uint32_t*)(matrixStorage + matrixIndex);
            *slotHeader |= 0x100;
        }

        // Post‑initialization steps
        FUN_00533fb0();
        FUN_004ebb40();

        // Clear additional fields
        *(int32_t*)((uint8_t*)this + 0x28) = 0;     // this[10]
        *(int32_t*)((uint8_t*)this + 0x34) = 0;     // this[0xd]
        *(int8_t*)((uint8_t*)this + 0x44) = 0xff;   // orientation default

        // Determine orientation type from flags
        if ( (flags & 0x40) == 0 )
        {
            // Bit 6 clear: check high bit of low byte (i.e. char(flags) < 0)
            if ( ((int8_t)(flags & 0xFF)) < 0 )
            {
                *(int8_t*)((uint8_t*)this + 0x44) = 1;
            }
        }
        else
        {
            // Bit 6 set: force orientation to 0
            *(int8_t*)((uint8_t*)this + 0x44) = 0;
        }

        // Check flag 0x8 and byte at +0x6c in TransformData
        if ( ((flags & 8) != 0) && (*(int8_t*)(transformData + 0x6c) != 0) )
        {
            *(int32_t*)((uint8_t*)this + 0x3c) = 2;   // this[0xf] = 2
        }
        else
        {
            *(int32_t*)((uint8_t*)this + 0x3c) = 0;   // this[0xf] = 0
        }
    }

    // Return the 'this' pointer (decompiled shows return)
    return this;
}