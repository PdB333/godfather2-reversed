// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int this)
{
    char cVar1;
    undefined4 unaff_EBP;
    int *piVar2;
    undefined4 unaff_EDI;
    
    // Check if pointer at +0xe8 is null
    if (*(int *)(this + 0xe8) == 0) {
        piVar2 = (int *)0x0;
    }
    else {
        // Calculate pointer by subtracting 0x48 from the value at +0xe8
        piVar2 = (int *)(*(int *)(this + 0xe8) + -0x48);
    }
    
    // Mask flags at +0xf0 with 1 (keep only bit 0)
    *(uint *)(this + 0xf0) = *(uint *)(this + 0xf0) & 1;
    
    if (piVar2 != (int *)0x0) {
        // Call virtual function at vtable offset 0x9c (index 39)
        cVar1 = (**(code **)(*piVar2 + 0x9c))();
        if (cVar1 != '\0') {
            // Call virtual functions at vtable offsets 0x94 (index 37) and 0xa4 (index 41)
            (**(code **)(*piVar2 + 0x94))(this + 0xf0, this + 0x10);
            (**(code **)(*piVar2 + 0xa4))(&stack0xffffffe8, this + 0xf0);
            
            // Set fields at offsets +0x190, +0x194, +0x198, +0x19c
            *(int *)(this + 400) = this + 0x10;  // +0x190
            *(undefined4 *)(this + 0x194) = unaff_EBP;
            *(undefined4 *)(this + 0x198) = unaff_EDI;
            *(undefined4 *)(this + 0x19c) = _DAT_00d5780c;
        }
    }
    return;
}