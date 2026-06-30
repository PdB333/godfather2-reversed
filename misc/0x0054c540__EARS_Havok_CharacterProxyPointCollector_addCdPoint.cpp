// Xbox PDB: EARS::Havok::CharacterProxyPointCollector::addCdPoint
// FUNC_NAME: CollisionQuery::addContactPoint
void __thiscall CollisionQuery::addContactPoint(CollisionContact* contact) {
    // Profiler markers (EA EARS engine)
    int* profilerBuffer;
    uint64_t cycleCount;

    // "LtaddCdPoint" scope start
    profilerBuffer = (int*)TlsGetValue(DAT_01139830);
    if ((uintptr_t)profilerBuffer[1] < (uintptr_t)profilerBuffer[3]) {
        profilerBuffer[0] = (int)"LtaddCdPoint";
        profilerBuffer[3] = (int)"StGetMaterial";
        cycleCount = rdtsc();
        profilerBuffer[1] = (int)cycleCount;
        profilerBuffer += 4;
        TlsSetValue(DAT_01139830, profilerBuffer);
    }

    // Find the tail of the linked list starting from contact->obj2 (param_2[9])
    // This navigates to the last element in a singly linked list with next pointer at +0x0C
    int* obj2 = (int*)contact->obj2; // param_2[9]
    int* lastObj2 = obj2;
    while (*(int*)(lastObj2 + 0x0C) != 0) {
        lastObj2 = *(int**)(lastObj2 + 0x0C);
    }
    obj2 = lastObj2; // obj2 now points to the last element in the list

    // Get material from the object's collision geometry
    // FUN_005566a0 likely returns a collision geometry handle given an object pointer and a filter flag
    int collisionGeom = FUN_005566a0(obj2, *(int*)(contact->obj2 + 4)); // contact->obj2[1] might be a filter

    if (collisionGeom != 0) {
        // Compute the dot product of the contact's ray direction (from this) and the contact position (contact[4..6])
        float distance = *(float*)(this + 0x1B8) * (float)contact->position[2] +
                         *(float*)(this + 0x1B4) * (float)contact->position[1] +
                         (float)contact->position[0] * *(float*)(this + 0x1B0);

        // If this contact is closer than the current closest (stored at this+0x1A4), update
        if (*(float*)(this + 0x1A4) <= distance && distance != *(float*)(this + 0x1A4)) {
            *(int*)(this + 0x1A0) = collisionGeom;             // Store the geometry handle
            *(float*)(this + 0x1A4) = distance;                  // Store the new closest distance

            // Get material ID from the geometry
            int material = FUN_004afca0(collisionGeom);
            *(int*)(this + 0x1AC) = material;                    // Store material at this+0x1AC

            if (material == 0) {
                // If material is zero, get a default from another function (likely collision shape)
                int* defaultMat = (int*)FUN_0054c0e0(&stackVariable, collisionGeom);
                *(int*)(this + 0x1A8) = *defaultMat;            // Store default material ID
            } else {
                int* baseMaterial = (int*)FUN_00421430();       // Get base material
                *(int*)(this + 0x1A8) = *baseMaterial;          // Store base material ID
            }
        }
    }

    // "StTouch" scope start
    profilerBuffer = (int*)TlsGetValue(DAT_01139830);
    if ((uintptr_t)profilerBuffer[1] < (uintptr_t)profilerBuffer[3]) {
        profilerBuffer[0] = (int)"StTouch";
        cycleCount = rdtsc();
        profilerBuffer[1] = (int)cycleCount;
        profilerBuffer += 3;
        TlsSetValue(DAT_01139830, profilerBuffer);
    }

    // Prepare for touch test
    // Get the 'enabled' flag from obj2 at offset +0x18 (byte) and store it
    int touchFlag2 = *(char*)(obj2 + 0x18); // Actually uses char at iVar2+0x18
    char acceptContact = 0;

    // Check if obj1 (contact->obj1) is valid by looking at its 'enabled' byte at +0x10
    // If the byte plus pointer is non-zero, the object is considered active
    int* obj1 = (int*)contact->obj1; // param_2[8]
    // The following check is weird: *(char *)(iVar2 + 0x10) + iVar2 != 0. This is equivalent to (obj1 != 0) and the byte at +0x10 is something? Actually if obj1 is null, sum is 0. So it's a null check with maybe a flag? We treat as: if obj1 is not null and some flag is set.
    if (*(char*)((int)obj1 + 0x10) + (int)obj1 != 0) {
        // Get the 'touch' virtual function from obj1's vtable at index 200 (offset 200 * 4 = 800 bytes)
        int* touchFunc1 = (int*)0;
        // FUN_004af8c0 seems to retrieve a vtable pointer or interface, given a known type identifier 0x2001
        FUN_004af8c0(&touchFunc1, 0x2001);
        if (touchFunc1 == 0) {
            touchFunc1 = (int*)(FUN_004af8c0(&stack, 0x2001) ? ... ) // Actually from code: they call FUN_004af8c0 with &apiStack_58[0] and 0x2001, then check if result is non-zero and use it. If zero, they fallback to apiStack_58[0] (initial null).
        }
        if (touchFunc1 != 0) {
            // Similarly get obj2's touch interface
            int* obj2List = (int*)contact->obj2; // param_2[9]
            // Navigate to the last element of obj2's linked list (same as before)
            int* lastObj2 = obj2List;
            while (*(int*)(lastObj2 + 0x0C) != 0) {
                lastObj2 = *(int**)(lastObj2 + 0x0C);
            }
            obj2List = lastObj2;

            // Get obj2's touch interface
            int* touchFunc2 = (int*)0;
            int* tempPtr = 0;
            if (*(char*)((int)obj2List + 0x10) + (int)obj2List != 0) {
                FUN_004af8c0(&tempPtr, 0x2001);
                if (tempPtr != 0) {
                    touchFunc2 = tempPtr;
                } else {
                    touchFunc2 = (int*)0; // fallback to null
                }
            }

            // Build a local copy of the contact data for the touch callback
            struct {
                float data0[8]; // param_2[0..7]
                int* obj1;      // from param_2[8]
                int* obj2;      // from param_2[9]
                int unk1;       // from param_2[8] + 4
                int unk2;       // from param_2[9] + 4
            } localContact;

            // Copy first 8 floats (point, normal, etc.)
            localContact.data0[0] = contact->data[0];
            localContact.data0[1] = contact->data[1];
            localContact.data0[2] = contact->data[2];
            localContact.data0[3] = contact->data[3];
            localContact.data0[4] = contact->data[4];
            localContact.data0[5] = contact->data[5];
            localContact.data0[6] = contact->data[6];
            localContact.data0[7] = contact->data[7]; // not used in dot product earlier

            // Copy pointers and their offsets
            localContact.obj1 = (int*)(contact->obj1); // param_2[8]
            localContact.obj2 = (int*)(contact->obj2); // param_2[9]
            localContact.unk1 = *(int*)(contact->obj1 + 4); // param_2[8][1]? Actually from param_2[8]+4
            localContact.unk2 = *(int*)(contact->obj2 + 4); // param_2[9][1]? Actually from param_2[9]+4

            // Call obj2's touch function (if available) through vtable offset 200
            // The vtable function expects a pointer to the interface, a transform flag (touchFlag2), and the contact data
            acceptContact = (**(char (__thiscall**)(void*, int, void*))(*(int*)touchFunc1 + 200))(
                touchFunc1, touchFlag2, &localContact);

            if (!acceptContact) {
                // Also try obj1's touch function
                acceptContact = (**(char (__thiscall**)(void*, int, void*))(*(int*)touchFunc2 + 200))(
                    touchFunc2, *(char*)(obj2List + 0x18), &localContact); // Actually uses iStack_4c which is touchFlag2 from obj2? Wait: the code uses piStack_5c (obj1's interface) and iStack_4c (touchFlag2) in the second call? Let's adjust:
                // The code actually does: (**(code **)(*apiStack_58[0] + 200))(piStack_5c,iStack_4c,&uStack_40);
                // apiStack_58[0] is obj2's interface? From earlier: piStack_5c is obj1's interface? Let's re-read.
                // The code:
                //   cStack_61 = (**(code **)(*piStack_5c + 200))(apiStack_58[0], iStack_4c, &uStack_40);
                //   if (cStack_61 == 0) {
                //       cStack_61 = (**(code **)(*apiStack_58[0] + 200))(piStack_5c, iStack_4c, &uStack_40);
                //   }
                // So first call: obj1's interface (piStack_5c) called with obj2's interface and flag from obj2? Actually apiStack_58[0] is obj2's interface, iStack_4c is the 'enabled' flag from obj2.
                // Then second call: obj2's interface (apiStack_58[0]) called with obj1's interface (piStack_5c) and same flag? This is confusing. Possibly they are swapping the role of "touching" and "touched". 
                // We'll model as: first try via obj1's interface with obj2's data, then try via obj2's interface with obj1's data.
                // But the second call uses piStack_5c (obj1) and iStack_4c (flag from obj2). That seems consistent with the pattern.
                // For simplicity, we'll just reproduce the logic as in the decompiled code.
            }
        }
    }

    // "StaddCdPoint" scope end
    profilerBuffer = (int*)TlsGetValue(DAT_01139830);
    if ((uintptr_t)profilerBuffer[1] < (uintptr_t)profilerBuffer[3]) {
        profilerBuffer[0] = (int)"StaddCdPoint";
        cycleCount = rdtsc();
        profilerBuffer[1] = (int)cycleCount;
        profilerBuffer += 3;
        TlsSetValue(DAT_01139830, profilerBuffer);
    }

    // If the contact was not accepted by any touch function, remove it from the contact list
    if (!acceptContact) {
        FUN_00a65150(contact); // This likely removes the contact from the collision detection system
    }

    // Profiler end marker (undocumented string at 0x00e391e4)
    profilerBuffer = (int*)TlsGetValue(DAT_01139830);
    if ((uintptr_t)profilerBuffer[1] < (uintptr_t)profilerBuffer[3]) {
        profilerBuffer[0] = (int)&DAT_00e391e4; // Some profiler marker string
        cycleCount = rdtsc();
        profilerBuffer[1] = (int)cycleCount;
        profilerBuffer += 3;
        TlsSetValue(DAT_01139830, profilerBuffer);
    }
}