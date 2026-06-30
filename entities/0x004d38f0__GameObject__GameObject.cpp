// FUNC_NAME: GameObject::GameObject
// Address: 0x004d38f0
// Role: Constructor - initializes member at offset 0xC to 0 and calls sub-initializer

int __thiscall GameObject::GameObject(int thisPtr, int param2, int param3)
{
    *(int*)(thisPtr + 0xC) = 0; // +0xC: likely an identifier or state flag
    FUN_004d3c40(param2, param3); // secondary initialization (unknown)
    return thisPtr; // return this pointer (custom constructor convention)
}