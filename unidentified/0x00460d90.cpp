// FUN_00460d90: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(void)
{
    // Call base class constructor
    this->baseConstructor();  // FUN_0045df20
    
    // Initialize member variable at offset 0x20c (possibly a flag or counter)
    *(int *)((unsigned char *)this + 0x20c) = 0;
}