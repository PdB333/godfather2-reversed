// FUNC_NAME: NPC::~NPC (destructor for NPC class) - Address: 0x006a9410

void __fastcall NPC::~NPC(NPC* this)
{
    // Set vtable pointers to base class or virtual base vtables
    this->vtable = &PTR_FUN_00d5d94c;                  // +0x00: main vtable
    this->field_0xF = &PTR_LAB_00d5d93c;              // +0x3C: virtual base vtable
    this->field_0x12 = &PTR_LAB_00d5d938;             // +0x48: virtual base vtable

    // Destroy subobject at +0x50 (offset 0x14 * 4)
    FUN_004086d0(&this->subobject1);                  // Subobject destructor step 1
    FUN_00408310(&this->subobject1);                  // Subobject cleanup step 2

    // Destroy subobject at +0x58 (offset 0x16 * 4)
    FUN_004086d0(&this->subobject2);
    FUN_00408310(&this->subobject2);

    // Destroy two global static subobjects
    FUN_004086d0(&DAT_012069c4);
    FUN_004086d0(&DAT_0120e93c);

    // Destroy subobject at +0x60 (offset 0x18 * 4)
    FUN_004086d0(&this->subobject3);
    FUN_00408310(&this->subobject3);

    // Destroy subobject at +0x68 (offset 0x1A * 4)
    FUN_004086d0(&this->subobject4);
    FUN_00408310(&this->subobject4);

    // Free dynamically allocated pointer if non-null (+0x88)
    if (this->ptrToFree1 != nullptr) {
        FUN_005e6660(this->ptrToFree1);               // operator delete or custom free
        this->ptrToFree1 = nullptr;
    }

    // Free another dynamically allocated pointer (+0xA0)
    if (this->ptrToFree2 != nullptr) {
        FUN_005e6660(this->ptrToFree2);
        this->ptrToFree2 = nullptr;
    }

    // Final global cleanup call
    FUN_0046c640();                                    // Engine-level shutdown/cleanup
}