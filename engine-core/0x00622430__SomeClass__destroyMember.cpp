// FUNC_NAME: SomeClass::destroyMember
void __thiscall SomeClass::destroyMember(void)
{
    // Local buffer used for temporary construction/destruction
    byte local_10[12]; // +0x0 (size 12 bytes)

    // Call helper function, passing local buffer, this, and the object at offset 0x1c
    // Arguments: (local_10, this, *(*this+0x1c), this, *(this+0x1c))
    FUN_00622b80(local_10, this, **(uint32 **)(*(int *)this->field_0x1c), this, *(uint32 **)(*(int *)this->field_0x1c));

    // Call virtual function at vtable+4 (index 1) on the object pointed to by this->field_0x04
    // The function takes the value at this->field_0x1c and a size (0x28 = 40 bytes)
    (**(code **)(**(int **)(*(int *)this->field_0x04) + 4))(*(undefined4 *)this->field_0x1c, 0x28);

    // Clear pointers to released memory
    *(undefined4 *)this->field_0x1c = 0;
    *(undefined4 *)this->field_0x20 = 0;
    return;
}