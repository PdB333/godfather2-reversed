// FUNC_NAME: Component::Component
int __thiscall Component::constructor(Component* thisPtr, int arg2)
{
    // Call base class initialization (likely parent constructor)
    baseConstructor(); // FUN_008a30d0

    // Initialize fields at offset 0x70-0x7a (10-byte block)
    thisPtr->field_0x70 = 0;      // +0x70: some integer
    thisPtr->field_0x74 = 0;      // +0x74: some integer
    thisPtr->field_0x78 = 0;      // +0x78: byte
    thisPtr->field_0x79 = 0;      // +0x79: byte
    thisPtr->field_0x7a = 1;      // +0x7a: byte (flag, set to true)

    // Call a setup function with mode/type 0,3 and flags
    setupFunction(0, 3, 0, 0, 0); // FUN_008a2dd0

    // Initialize fields at offset 0xcc-0xd8 (12-byte block)
    thisPtr->field_0xcc = 0;      // +0xcc: some integer
    thisPtr->field_0xd0 = 0;      // +0xd0: some integer
    thisPtr->field_0xd4 = 0;      // +0xd4: byte
    thisPtr->field_0xd5 = 0;      // +0xd5: byte
    thisPtr->field_0xd8 = 0;      // +0xd8: some integer

    // Initialize with the passed argument (maybe a parent pointer or config)
    otherInit(arg2);              // FUN_00960030

    return (int)thisPtr;
}