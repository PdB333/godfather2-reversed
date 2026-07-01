// FUNC_NAME: SomeGameObject::~SomeGameObject()
void __fastcall SomeGameObject::~SomeGameObject(SomeGameObject* this)
{
    int* piVar1;
    int iVar2;
    SomeGameObject* thisPtr;

    // Set vtable pointer and virtual function table pointers
    *(int**)this = &PTR_FUN_00d69b54;          // vtable
    this->field_0x3C = &PTR_LAB_00d69b44;      // offset +0x3C
    this->field_0x48 = &PTR_LAB_00d69b40;      // offset +0x48

    // Destroy optional sub-object if flag is set
    if (this->field_0x184 != 0)                // bool at offset +0x184
    {
        sub_78E350(this);
    }

    // Cleanup at offset +0x174
    sub_408310(&this->field_0x174);            // offset +0x174

    // Destroy static singleton (global)
    sub_4086D0(&DAT_0120e93c);

    // Destroy pointer at offset +0x17C if non-null
    if (this->field_0x17C != 0)                // offset +0x17C
    {
        sub_4DAF90(&this->field_0x17C);
    }

    // Destroy two pointers at offsets +0x148 and +0x110
    thisPtr = this;
    iVar2 = 2;
    do {
        piVar1 = thisPtr->field_0x148;        // offset +0x148, actually piVar1 points to pointer
        thisPtr = (SomeGameObject*)((char*)thisPtr - 0x38); // Move to previous pointer slot
        if (*(int*)piVar1 != 0)
        {
            sub_4DAF90(&thisPtr->field_0x148); // destroy at current offset (lower address)
        }
        iVar2--;
    } while (iVar2 >= 0);

    // Destroy two pointers at offsets +0xB4 and +0x90
    thisPtr = (SomeGameObject*)((char*)this + 0xD8); // base offset +0x36*4 = 0xD8
    iVar2 = 2;
    do {
        piVar1 = thisPtr->field_0xB4;        // offset +0xB4 (calculated)
        thisPtr = (SomeGameObject*)((char*)thisPtr - 0x24); // Move to previous pointer slot
        if (*(int*)piVar1 != 0)
        {
            sub_4DAF90(&thisPtr->field_0xB4);
        }
        iVar2--;
    } while (iVar2 >= 0);

    // Final global cleanup calls
    sub_78DC80();
    sub_46C640();
}