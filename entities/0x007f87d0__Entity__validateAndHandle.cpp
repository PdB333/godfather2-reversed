//FUNC_NAME: Entity::validateAndHandle
// Function address: 0x007f87d0
// Role: Checks a condition (likely a buffer comparison) and if false, calls a virtual method (vtable+0x28) with argument 0x80, then a cleanup function.

extern char __thiscall checkCondition(undefined4 param, void* buffer); // FUN_00401e20
extern void __thiscall cleanupFunction(undefined4 param); // FUN_004d3e20

void __thiscall Entity::validateAndHandle(Entity* this, undefined4 someParam)
{
    char result;
    
    // Compare someParam with a buffer at offset +0x844
    result = checkCondition(someParam, (void*)(this + 0x844));
    if (result == '\0') {
        // Call virtual function at vtable offset 0x28 (index 10) with argument 0x80
        // vtable pointer is stored at this+0x58
        (**(code **)(*(int *)(this + 0x58) + 0x28))(0x80);
        cleanupFunction(someParam);
    }
    return;
}