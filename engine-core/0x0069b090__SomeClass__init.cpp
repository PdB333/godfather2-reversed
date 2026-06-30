// FUNC_NAME: SomeClass::init
int SomeClass::init(SomeClass* this, SrcStruct* src1, SrcStruct* src2) // __thiscall
{
    int local_20;
    int local_1c;
    int local_10;
    int local_c;

    // Copy from src1 to global static data (string?)
    FUN_004d3ca0(src1->field0, src1->field4, &DAT_00d5ced8, 3);
    
    // Copy from src2 into local buffer (allocated?)
    FUN_004d3ca0(local_10, local_c, src2->field0, src2->field4);

    // Zero out member at offset 0xc (e.g., a pointer or counter)
    *(undefined4 *)(this + 0xc) = 0;

    // Copy another constant into local variables
    FUN_004d3ca0(local_20, local_1c, &DAT_00e327b8, 1);

    // If the last copy resulted in a non-null pointer, call its destructor (buggy? maybe vtable call)
    if (local_20 != 0) {
        // (*(code *)0x0)(local_20); // Likely meant to call destructor via vtable at offset 0
        // Assume it's operator delete or virtual destructor
        ((void (*)(void*))nullptr)(local_20); // placeholder - actual function missing
    }

    // Similar for the earlier allocation
    if (local_10 != 0) {
        ((void (*)(void*))nullptr)(local_10);
    }

    return (int)this;
}