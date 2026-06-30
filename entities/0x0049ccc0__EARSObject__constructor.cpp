// FUNC_NAME: EARSObject::constructor
int __fastcall EARSObject::constructor(void *this) {
    // Call base initializer (likely parent class constructor)
    int result = BaseInitialize(this);

    // Initialize fields at offsets 0x90 and 0x94 to 0
    *(int *)((char *)this + 0x90) = 0; // +0x90: unknown handle/pointer
    *(int *)((char *)this + 0x94) = 0; // +0x94: unknown handle/pointer

    return result;
}