// FUNC_NAME: Sim::Sim
// Constructor for the Sim class (EARS framework base class for game objects).
// Calls base constructor (likely Entity), sets up multiple vtable pointers,
// initializes fields to zero, and fills debug sentinel values for memory tracking.
// Function address: 0x006ab7e0

void __thiscall Sim::Sim(void* this, int baseParam) {
    // Call base class constructor (probably Entity or similar)
    FUN_0046c590(baseParam);

    // Set primary vtable pointer at +0x00
    *(void**)this = (void*)&PTR_FUN_00d5da30;

    // Set secondary interface vtable at +0x3C
    *(void**)((char*)this + 0x3C) = (void*)&PTR_LAB_00d5da20;

    // Set tertiary interface vtable at +0x48
    *(void**)((char*)this + 0x48) = (void*)&PTR_LAB_00d5da1c;

    // Zero out fields from +0x50 to +0x66 (combination of int and short)
    *(int*)((char*)this + 0x50) = 0;
    *(short*)((char*)this + 0x54) = 0;
    *(short*)((char*)this + 0x56) = 0;
    *(int*)((char*)this + 0x58) = 0;
    *(short*)((char*)this + 0x5C) = 0;
    *(short*)((char*)this + 0x5E) = 0;
    *(int*)((char*)this + 0x60) = 0;
    *(short*)((char*)this + 0x64) = 0;
    *(short*)((char*)this + 0x66) = 0;

    // Write debug sentinel values at +0x68 to +0x74
    *(int*)((char*)this + 0x68) = 0xBADBADBA;
    *(int*)((char*)this + 0x6C) = 0xBEEFBEEF;
    *(int*)((char*)this + 0x70) = 0xEAC15A55;
    *(int*)((char*)this + 0x74) = 0x91100911;

    // Zero more shorts at +0x78, +0x7A, +0x7C
    *(short*)((char*)this + 0x78) = 0;
    *(short*)((char*)this + 0x7A) = 0;
    *(short*)((char*)this + 0x7C) = 0;

    // Zero ints at +0x88, +0x8C, +0x90, +0x94
    *(int*)((char*)this + 0x88) = 0;
    *(int*)((char*)this + 0x8C) = 0;
    *(int*)((char*)this + 0x90) = 0;
    *(int*)((char*)this + 0x94) = 0;

    // Zero final bytes at +0x98, +0x99, +0x9A
    *(char*)((char*)this + 0x98) = 0;
    *(char*)((char*)this + 0x99) = 0;
    *(char*)((char*)this + 0x9A) = 0;
}