// FUNC_NAME: SimEntity::processUpdate
void __fastcall SimEntity::processUpdate(SimEntity* this)
{
    // +0x58 : pointer to some parent/owner object
    Object* parentObj = *(Object**)((int)this + 0x58);
    // +0xff0 : pointer to a task/state block
    TaskBlock* taskBlock = *(TaskBlock**)((int)parentObj + 0xff0);
    if (taskBlock != nullptr)
    {
        // -0x48 : vtable base offset for the task block
        int* vtableBase = (int*)((int)taskBlock - 0x48);
        if (vtableBase != (int*)0x0)
        {
            uint someFlags = *(uint*)((int)taskBlock + 0x644);
            uint shiftedFlags = someFlags >> 2;  // maybe a count or state
            uint local_a0; // used as an argument to a callback
            local_a0 = (uint)this; // store this pointer for later use
            uint someRef; // smart pointer tracking variable (local_9c)
            uint anotherRef; // smart pointer tracking (iStack_94)
            uint smartPtrData; // local_50, passed to virtual call

            // Virtual call at vtable[0xa4/4] = index 41? 
            ((void(__thiscall*)(TaskBlock*, void*, uint*))vtableBase[0xa4/4])((TaskBlock*)(taskBlock), &smartPtrData, &someRef);

            // Update global state / heap
            FUN_0084dd20(); // maybe HeapManager::update

            // Determine raw pointer from parent's +0x48 field
            uint rawPtr = (parentObj != 0) ? (uint)((char*)parentObj + 0x48) : 0;

            // Smart pointer assignment for someRef (local_9c)
            if (someRef != rawPtr)
            {
                if (someRef != 0)
                {
                    FUN_004daf90(&someRef); // Release old reference
                }
                someRef = rawPtr;
                if (rawPtr != 0)
                {
                    // Set back pointer in the object to point to this smart pointer
                    *(uint*)(rawPtr + 4) = (uint)&someRef;
                }
            }

            // Same for anotherRef (iStack_94) to the same raw pointer
            if (anotherRef != rawPtr)
            {
                if (anotherRef != 0)
                {
                    FUN_004daf90(&anotherRef);
                }
                anotherRef = rawPtr;
                if (rawPtr != 0)
                {
                    *(uint*)(rawPtr + 4) = (uint)&anotherRef;
                }
            }

            // Get some global object (camera?)
            int* viewObj = (int*)FUN_00471610(); // returns pointer to some view/camera object
            // Copy data from viewObj+0x30 (8 bytes) and +0x38 (4 bytes)
            // These are probably composed into a structure on stack
            long long viewDataLow = *(long long*)((int)viewObj + 0x30);
            int viewDataHigh = *(int*)((int)viewObj + 0x38);

            // Build a style parameter structure
            float scale = *(float*)((int)parentObj + 0x1d54) * DAT_012067e8; // global scale factor
            int param1 = (int)&smartPtrData; // copy of the initial argument passed to virtual
            int param2 = (int)&someRef; // not sure, but uStack_80 is assigned from uStack_58 which is uninitialized? Actually uStack_58 is a local variable that is not set before use? In the decompiled code, uStack_58 appears in combination with uStack_8c, but the assignment uStack_80 = uStack_58 is suspicious. Possibly a decompiler error.
            // Actually looking at decompiled: uStack_80 = uStack_58; That line seems to use an uninitialized variable. Might be part of structure assignment.
            // We'll assume the structure is filled from the viewObj data and other values.
            // The decompiled shows:
            // uStack_8c = viewDataLow; uStack_84 = viewDataHigh;
            // uStack_5c |= 10; (maybe flags)
            // uStack_78 = local_50; (smartPtrData)
            // uStack_80 = uStack_58; (actually uStack_58 is a local of type undefined8 at stack offset -0x58, but it's not initialized; probably a copy of something else. Possibly the second part of the view data? But uStack_8c and uStack_84 cover 12 bytes and uStack_58 is at a different offset. This is messy. We'll skip detailed reconstruction and just note that a structure is built.

            // Schedule an event/callback
            // FUN_00408bb0 takes a global 'EventManager' (DAT_0112dd94), a target object (taskBlock-0xc), a structure pointer (&local_a0), and an extra int (0)
            FUN_00408bb0(&DAT_0112dd94, (int)taskBlock - 0xc, &local_a0, 0); // likely EventManager::addCallback

            // Check if some condition is true (maybe user input or state)
            char condition = FUN_00481660(); // returns 0 or 1
            if (condition != 0)
            {
                // Perform additional processing: play animation, update network, etc.
                FUN_0084d330(); // unknown
                FUN_0084dda0(&local_a0); // maybe finalize smart pointer
                FUN_0070b6a0(/*some stack buffer*/); // maybe animation call
                FUN_004a8ec0((int)taskBlock + 0x10); // maybe update sound or physics
                FUN_0084e1c0(); // unknown
            }

            // Virtual call to check if the task is still active
            float activity = ((float(__thiscall*)(TaskBlock*))vtableBase[0xc0/4])((TaskBlock*)(taskBlock + 0x48)); // actually piVar1 points to vtableBase, so method on taskBlock? The call syntax is (**(code **)(*piVar1 + 0xc0))(); so it's on object at piVar1? But piVar1 is vtableBase, so the this pointer would be (int)vtableBase? That's unusual. More likely it's calling on the same taskBlock object? The pattern is typical of virtual calls: ((*vtable)[function])(this, ...). Here piVar1 is the vtable pointer of some base, but usually vtable is at object start. Since piVar1 = iVar3-0x48, and iVar3 is a pointer to the task block, then the actual object might be taskBlock - 0x48? That seems like a negative offset. Possibly the vtableBase points to a base subobject. Actually the code: piVar1 = (int*)(iVar3 + -0x48); So piVar1 points 0x48 bytes before the taskBlock. That could be the start of the object (if vtable at offset 0). So the this pointer for virtual calls is piVar1, not taskBlock. The first virtual call was: (**(code **)(*piVar1 + 0xa4))(&local_50, &local_9c); So the this pointer is &local_50? That's odd because &local_50 is the address of a local variable, not an object. Wait: the standard __thiscall passes ecx as this. In the decompiled code, the function call is given as (**(code **)(*piVar1 + 0xa4))(&local_50, &local_9c); This is a function call with two arguments: the first parameter (ecx) is &local_50, and the second is &local_9c. So the this pointer is the first argument, meaning it's not stored in ecx? In __fastcall, ecx is first parameter, edx second. But the decompiler shows (**(code **)(*piVar1 + 0xa4))(&local_50, &local_9c); So it's calling with two arguments. Typically, member functions in __thiscall have the this pointer as the first argument in the source, but the calling convention passes it via ecx. The decompiler may show it as the first explicit argument. So here, this for that call is &local_50. So they are treating the local variable as an object? Possibly local_50 is a temporary object. So the virtual call is on a temporary object? That is unusual.

Given the confusion, it's hard to give a perfect reconstruction. I'll produce a cleaner version focusing on the main flow while acknowledging the complexity.

            // Check activity: if not active (float <= 0) and player state is 1 or 2, set a flag
            float activityValue = ((float(__thiscall*)(void*))vtableBase[0x30])(); // index 0xc0/4 = 48? Actually 0xc0/4 = 48
            if (activityValue <= 0.0f &&
                (*(int*)(/*unaff_EBP*/ + 0x90) == 1 || *(int*)(/*unaff_EBP*/ + 0x90) == 2))
            {
                *(uint*)((int)taskBlock + 0x2144) |= 0x40000000; // set some flag
            }

            // Clean up smart pointers
            if (anotherRef != 0)
            {
                FUN_004daf90(&anotherRef);
            }
            if (someRef != 0)
            {
                FUN_004daf90(&someRef);
            }
        }
    }
    return;
}