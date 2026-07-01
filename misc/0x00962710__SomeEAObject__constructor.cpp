// FUNC_NAME: SomeEAObject::constructor
int __fastcall SomeEAObject::constructor(int thisPtr)
{
    FUN_008a30d0(); // Base class constructor
    *(int*)(thisPtr + 0x70) = 0;
    *(int*)(thisPtr + 0x74) = 0;
    *(bool*)(thisPtr + 0x78) = false;
    *(bool*)(thisPtr + 0x79) = false;
    *(bool*)(thisPtr + 0x7a) = true; // Initialize some flag to true
    return thisPtr;
}