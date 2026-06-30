// FUNC_NAME: Entity::initComponentSystem
void __thiscall Entity::initComponentSystem(int this)
{
    int subObject;
    int* vtablePtr;

    // Allocate a sub-object of size 0x348 (likely a component manager)
    subObject = FUN_009c8e50(0x348);
    if (subObject == 0) {
        subObject = 0;
    } else {
        // Call constructor for the sub-object
        subObject = FUN_0056a020();
    }
    // Store sub-object pointer at this+0x20
    *(int*)(this + 0x20) = subObject;

    // If the sub-object's count field (+0x1c) is less than 5,
    // add this+4 (some pointer) to its array at +8
    if (*(unsigned int*)(subObject + 0x1c) < 5) {
        *(int*)(subObject + 8 + *(unsigned int*)(subObject + 0x1c) * 4) = this + 4;
        *(int*)(subObject + 0x1c) = *(int*)(subObject + 0x1c) + 1;
    }

    // Allocate a 4-byte vtable pointer object
    vtablePtr = (int*)FUN_009c8e50(4);
    if (vtablePtr != 0) {
        *vtablePtr = (int)&PTR_LAB_00e44554; // vtable for some interface
        *(int**)(this + 0x128) = vtablePtr;
    } else {
        *(int*)(this + 0x128) = 0;
    }
}