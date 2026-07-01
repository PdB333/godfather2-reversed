// FUNC_NAME: SimObject::update

void __thiscall SimObject::update(void)
{
    uint flags;
    int* childArray;
    int childCount;
    int childIndex;
    int* childPtr;
    int tempData[8]; // used as temporary buffer for child updates
    
    flags = *(uint*)(this + 0x4C);
    
    // Check bit 1 (0x2) – might be a "suspend" or "paused" flag
    if ((flags >> 1 & 1) != 0) {
        FUN_009978b0(); // likely a resume or start function
    }
    
    // Check bit 4 (0x10) – might be "needs initialization" flag
    if ((flags & 0x10) != 0) {
        tempData[0] = (int)this; // pass 'this' as argument
        FUN_00997800(tempData); // init function
    }
    
    // Clear the init flag
    *(uint*)(this + 0x4C) = flags & 0xFFFFFFEF;
    
    // Clear the temporary buffer
    tempData[4] = 0;
    tempData[3] = 0;
    tempData[2] = 0;
    tempData[1] = 0;
    tempData[0] = 0;
    
    // Access the child list: +0x20 points to a container
    childArray = *(int**)(this + 0x20);
    childCount = *(int*)(childArray + 0x0C); // +0x0C = count of children
    
    if (0 < childCount) {
        for (childIndex = 0; childIndex < childCount; childIndex++) {
            // +0x08 is pointer to array of child object pointers
            childPtr = *(int**)(childArray + 0x08);
            childPtr = (int*)childPtr[childIndex];
            
            // Stack frame save/restore? Possibly per-update context
            FUN_009f2000(); // begin
            // Call virtual function at offset 0x40 from a vtable at child+0xD0
            (**(code**)(*(int*)(childPtr + 0xD0) + 0x40))(tempData + 1);
            FUN_009f2000(); // end
            // Call virtual function at offset 0x44 from same vtable
            (**(code**)(*(int*)(childPtr + 0xD0) + 0x44))(tempData);
        }
    }
    
    // Another system call – possibly related to frame timing
    FUN_00996320(1);
    
    // Check sign bit (0x80) – might be "remove pending" flag
    if ((*(int*)(this + 0x4C) & 0x80) != 0) {
        *(uint*)(this + 0x4C) = *(uint*)(this + 0x4C) & 0xFFFFFF7F; // clear it
        FUN_00460880(); // actual removal or cleanup
    }
    
    // Access another component via +0x5C (pointer) and clear a bit at +0x184
    *(uint*)(*(int*)(this + 0x5C) + 0x184) &= 0xFFFFFFEF;
    
    // Set three fields at +0xA8, +0xAC, +0xB0 from globals (likely position/rotation)
    *(undefined4*)(this + 0xA8) = DAT_00d9228c;
    *(undefined4*)(this + 0xAC) = DAT_00d92290;
    *(undefined4*)(this + 0xB0) = DAT_00d92290;
    
    return;
}