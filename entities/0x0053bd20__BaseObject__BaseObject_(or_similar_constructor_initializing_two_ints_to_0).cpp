// FUNC_NAME: BaseObject::BaseObject (or similar constructor initializing two ints to 0)
void __fastcall BaseObject::BaseObject(int thisPtr)
{
    // Call base class constructor (likely vtable setup or common initialization)
    FUN_00612e00();

    // Initialize two integer member variables to 0
    // Offsets: +0x10, +0x14
    *(int*)(thisPtr + 0x10) = 0;
    *(int*)(thisPtr + 0x14) = 0;
}