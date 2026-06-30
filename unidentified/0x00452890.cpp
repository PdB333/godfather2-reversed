// FUN_NAME: UnknownClass::UnknownClass
// Address: 0x00452890
// Parameter: initFlag - bit0 triggers cleanup function at 0x009c8eb0
undefined4 __thiscall UnknownClass::UnknownClass(UnknownClass *thisPointer, byte initFlag)
{
    FUN_004528e0(); // Base class constructor
    if ((initFlag & 1) != 0) {
        FUN_009c8eb0(thisPointer); // Cleanup / deallocation
    }
    return (undefined4)thisPointer;
}