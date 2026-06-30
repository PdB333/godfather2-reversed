// FUNC_NAME: SomeClass::createSomeArray
uint * SomeClass::createSomeArray(void)
{
    undefined4 *in_EAX;  // this pointer
    uint *puVar1;
    uint uVar2;
    uint unaff_EDI;      // number of elements to allocate
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    
    // Calculate total size: numElements * 0x38 (56 bytes per element)
    uVar2 = -(uint)((int)((ulonglong)unaff_EDI * 0x38 >> 0x20) != 0) |
            (uint)((ulonglong)unaff_EDI * 0x38);
    
    // Allocate memory via vtable function (likely operator new or allocator)
    // Size = (overflow check ? 0xFFFFFFFF : totalSize) + 4 (for count field)
    puVar1 = (uint *)(**(code **)*in_EAX)(-(uint)(0xfffffffb < uVar2) | uVar2 + 4, &local_c);
    
    if (puVar1 != (uint *)0x0) {
        *puVar1 = unaff_EDI;  // Store element count at beginning
        // Construct each element (0x38 bytes each) using constructor at LAB_0056e800
        _vector_constructor_iterator_
                  (puVar1 + 1, 0x38, unaff_EDI, (_func_void_ptr_void_ptr *)&LAB_0056e800);
        _DAT_01205558 = 0;  // Clear some global flag
        return puVar1 + 1;  // Return pointer to first element (skip count field)
    }
    
    _DAT_01205558 = 0;  // Clear global flag on failure
    return (uint *)0x0;
}