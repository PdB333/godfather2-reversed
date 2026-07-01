// FUNC_NAME: AudioStream::~AudioStream
void __fastcall AudioStream::~AudioStream(AudioStream* this)
{
    int iVar;
    int* pField;

    iVar = this->field_0x5c;                                     // +0x5c: some integer
    this->vtable = (void*)&PTR_LAB_00d67ea8;                     // set destroying vtable
    this->subobjectVtable = (void*)&PTR_LAB_00d67ea0;            // +0x70: subobject vtable

    FUN_005512c0(0);                                             // release? (param=0)
    FUN_007f6420(5);                                             // stop stream? (param=5)

    // Check if flag bit1 (0x02) is set and field_0x5c is non-null
    if ((((uint)this->flags >> 1) & 1) != 0 && iVar != 0)       // +0x84: flags
    {
        iVar = FUN_0043b870(DAT_0112af58);                       // global check
        if (iVar != 0)
        {
            FUN_00782d10(1);                                     // some callback
        }
    }

    pField = &this->field_0x7c;                                  // +0x7c: pointer
    if (this->field_0x7c != 0 && this->field_0x7c != 0x48)
    {
        // Clear byte at offset 0xBC from a buffer calculated from field_0x7c
        if (*pField == 0)
            iVar = 0;
        else
            iVar = *pField - 0x48;
        *(char*)(iVar + 0xbc) = 0;
    }

    // Check flag bit2 (0x04)
    if (((uint)this->flags >> 2) & 1)
    {
        FUN_007ee320(&this->subobjectVtable);                    // +0x70 address
    }

    // Delete three sub-objects at offsets +0x8C, +0x94, +0x9C
    {
        int* pCurrent = &this->field_0x9c;                       // start at +0x9C (index 0x27)
        int count = 3;
        do {
            int* pSub = pCurrent - 2;                            // advance backward: +0x9C, +0x94, +0x8C
            pCurrent = pCurrent - 2;
            if (*pSub != 0)
            {
                FUN_004daf90(pSub);                              // likely delete/release sub-object
            }
            count--;
        } while (count >= 0);
    }

    // Delete field_0x7c if non-null
    if (this->field_0x7c != 0)
    {
        FUN_004daf90(&this->field_0x7c);                         // +0x7C
    }

    // Restore vtable pointers to final state
    this->subobjectVtable = (void*)&PTR_LAB_00d61acc;            // new subobject vtable
    this->vtable = (void*)&PTR_LAB_00d63090;                     // new main vtable

    if (this->field_0x68 != 0)                                   // +0x68: another pointer
    {
        FUN_004daf90(&this->field_0x68);
    }

    FUN_0080ea60();                                              // global cleanup
}