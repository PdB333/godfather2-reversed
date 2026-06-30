// FUNC_NAME: PhysicsNode::Init
uint __fastcall PhysicsNode::Init(PhysicsNode* this, int* owner, uint8* nodeData, float extraFloat)
{
    uint result;

    result = (uint)(int)this & 0xffffff00;  // Preserve original this pointer high bits? Actually in_EAX is the return register, which typically holds 'this' in fastcall (ECX) but here it's from the caller's EAX? Note: in_EAX is the register EAX at entry, not necessarily this. But the decompiler shows it's used as initial value for uVar2. Since it's a __fastcall, EAX is not used for parameter passing, so it's undefined by convention. The code uses it, so it's some passed value or side effect. We'll keep as is.
    if ((nodeData != (uint8_t*)0x0) && (owner != (int*)0x0) && (this != (PhysicsNode*)0x0))
    {
        this->nodeDataPtr = nodeData;                          // +0x08
        this->field_0x4c = owner[0x18];                       // +0x4c
        this->someFloat = extraFloat;                         // +0x50 (float)
        this->field_0x54 = owner[0x19];                       // +0x54
        this->field_0x58 = owner[0x1a];                       // +0x58

        this->byte_0x65 = 0;                                   // +0x65
        this->byte_0x66 = 0xFF;                                 // +0x66
        this->byte_0x67 = 0xFF;                                 // +0x67
        this->dword_0x68 = 1;                                   // +0x68
        this->word_0x6c = 0;                                    // +0x6c
        this->word_0x4a = 0;                                    // +0x4a
        this->byte_0x6e = 0;                                    // +0x6e
        this->byte_0x6f = *nodeData;                            // +0x6f: first byte of nodeData

        if (owner[1] != 0)
        {
            this->field_0x60 = *(uint32_t*)(owner[1] + 4);    // +0x60
        }

        // If nodeData+0x28 is not sentinel 0xDEADBEEF, use its value as data handle
        result = 0;
        if (*(uint32_t*)(nodeData + 0x28) != 0xDEADBEEF)
        {
            result = *(uint32_t*)(nodeData + 0x28);
        }
        this->dataHandle = result;                              // +0x30

        if (*owner != 0)
        {
            this->ownerPtr = owner;                            // +0x2c
            owner[2] = (int)this;                              // owner[2] points back to this node (linking)
            this->field_0x5c = *owner;                         // +0x5c: first field of owner
        }

        // Zero out 4 consecutive 8-byte blocks
        this->array0[0] = 0;   // +0x0c
        this->array0[1] = 0;   // +0x14
        this->array0[2] = 0;   // +0x1c
        this->array0[3] = 0;   // +0x24
    }
    return (result & 0xffffff00) | 1;  // Return result with low byte set to 1
}