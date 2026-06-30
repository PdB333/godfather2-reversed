// FUN_0043e900: SomeClass::~SomeClass (destructor frees two member pointers at +0x18 and +0x1c)
void __fastcall SomeClass::~SomeClass(int this)
{
    // Check and free first pointer at +0x18
    if (*(void**)(this + 0x18) != 0) {
        // Calls memory deallocation routine (likely operator delete or custom free)
        // The pointer is assumed passed in a register before call
        FUN_00627360(); // free(*(void**)(this + 0x18))
    }
    // Check and free second pointer at +0x1c
    if (*(void**)(this + 0x1c) != 0) {
        FUN_00627360(); // free(*(void**)(this + 0x1c))
    }
}