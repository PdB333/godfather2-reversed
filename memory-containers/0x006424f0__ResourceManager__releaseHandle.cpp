// FUNC_NAME: ResourceManager::releaseHandle
void __thiscall ResourceManager::releaseHandle(int thisPtr, uint type, uint group, uint index) {
    // Build resource ID from type (in EAX at call), group, index, and type? Actually in_EAX comes from EAX, probably the resource type/class
    uint resourceId = ((type << 9 | group) << 9 | index) << 6 | group; // note: param_2 used as group, param_3 as index? Adjust based on shift pattern
    
    // Release the resource via internal function
    // second arg: (*(int*)(thisPtr+0xc)) is pointer to something, +8 is vtable entry or similar
    FUN_006438e0(resourceId, *(uint*)(*(int*)(thisPtr + 0xc) + 8));
    
    // Set current handle to invalid (-1)
    *(int*)(thisPtr + 0x20) = -1;
    
    // Release default/null resource (constant 0x7fff94)
    uint uVar1 = FUN_006438e0(0x7fff94, *(uint*)(*(int*)(thisPtr + 0xc) + 8));
    
    // Call cleanup or destructor
    FUN_00642880(thisPtr);
}