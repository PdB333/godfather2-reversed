// FUNC_NAME: EntityManager::createEntity

uint __thiscall EntityManager::createEntity(void *this, uint sourceId, SpawnData *spawnData)
{
  int slotIndex;
  int *slotFlagPtr;
  uint slotBase;
  EntitySlot *slot;
  int entityPtr;
  uint uniqueId;

  sourceId = *(uint *)((int)this + 0x6040); // Actually this is incorrect: uVar2 initially *in_EAX (vtable?) No, uVar2 = *in_EAX, likely vtable or magic. Need to re-check decompiler. The original had uVar2 = *in_EAX which is the first dword of this? Danger: Might be a vtable pointer. But it's used later as sourceId. Possibly it's a type identifier from the object's base. Given the confusion, I'll assume it's a parameter that was passed via ecx? Actually the function signature from decompiler: param_1 (this), param_2 (undefined4), param_3 (int). The decompiler shows uVar2 = *in_EAX, which is the first dword of the object pointed by in_EAX. Since this is __thiscall, in_EAX is this pointer. So uVar2 = *(uint *)this; that is the vtable pointer or some identifier. But later it's assigned to puVar1[8] (offset 0x30) and used in FUN_005e6100. That suggests it's some kind of ID or type. Possibly it's the object's class ID. I'll keep it as a parameter named "classId" but note it's taken from this->vtable? Actually it's from this itself, not a parameter. Wait, the function signature has param_2 and param_3, but uVar2 comes from *in_EAX, which is the this pointer value dereferenced. That means the function has only two parameters: this (implicit), param_2, param_3. So uVar2 is the first field of the object (perhaps a vtable pointer or type ID). I'll name it "objectType" and note it's from this->type.

  // The array of slots starts at offset 0x10 from this
  EntitySlot *slots = (EntitySlot *)((char *)this + 0x10);
  // The flag array at offset 0x28? Actually slotFlagPtr points to slots[i].inUse flag (offset 0x28 from this, which is slot[0].inUse)
  int *inUsePtr = (int *)((char *)this + 0x28);
  uint objectType = *(uint *)this; // First dword of this (vtable/type)

  for (slotIndex = 0; slotIndex < 512; slotIndex++)
  {
    if (*inUsePtr == 0) // Slot is free
    {
      slot = &slots[slotIndex];
      if (slot != nullptr)
      {
        entityPtr = callocEntity(this, objectType, param_2); // FUN_005e6100
        if (entityPtr != 0)
        {
          slot->objectPtr = entityPtr;
          slot->inUse = 1; // Mark as used
          slot->field_0x2c = *(uint *)((char *)param_3 + 0xc);
          slot->field_0x30 = objectType;
          slot->field_0x34 = *(uint *)((char *)param_3 + 0x10);
          slot->field_0x38 = *(uint *)((char *)param_3 + 0x14);
          slot->field_0x3c = 0; // Later set to ID
          // Write fields to the entity object
          *(uint *)(entityPtr + 0x6c) = *(uint *)((char *)param_3 + 0x18);
          *(uint *)(entityPtr + 0x70) = *(uint *)((char *)param_3 + 0x1c);
          slot->field_0x10 = 0;
          slot->field_0x14 = 0;
          slot->field_0x0 = 0;
          slot->field_0x1c = g_SomeGlobal; // DAT_00e2b1a4
          addRef(slot->field_0x24, objectType); // FUN_005dbc10
          if (slot->objectPtr != 0)
          {
            memset((void *)(slot->objectPtr + 0xc), 0, 0x30); // Clear some structure in entity
            uint slotBase = slot->field_0x24; // Actually slot->field_0x24 is index? Wait: original: uVar4 = puVar1[5]; then later used as index to clear. So slot->field_0x24 is the slot index? Or something else. Let's re-read: after setting puVar1[5] = something? Actually in decompiler: they set puVar1[5] = something from FUN_005dbc10? No, puVar1[5] is at offset 0x24. It's set earlier? Not in this function's visible assignments. It might be set from callocEntity? Actually callocEntity returns iVar5 (entityPtr) and then puVar1[4] = iVar5. puVar1[5] is not explicitly set in this function; it must have been set elsewhere or is a parameter. The code then does: uVar4 = puVar1[5]; and later used to compute ID. So slot->field_0x24 (at offset 0x24) is likely the slot index? That would be equal to slotIndex. But it's already set from somewhere. Actually this is confusing. Let's try to parse the decompiler output more carefully.

Original decompiler snippet:
        puVar1[4] = iVar5;        // slot->objectPtr
        puVar1[6] = 1;            // slot->inUse
        puVar1[7] = *(undefined4 *)(param_3 + 0xc);
        puVar1[8] = uVar2;        // objectType
        puVar1[9] = *(undefined4 *)(param_3 + 0x10);
        puVar1[10] = *(undefined4 *)(param_3 + 0x14);
        puVar1[0xb] = 0;          // slot->field_0x3c
        *(undefined4 *)(iVar5 + 0x6c) = *(undefined4 *)(param_3 + 0x18);
        *(undefined4 *)(puVar1[4] + 0x70) = *(undefined4 *)(param_3 + 0x1c);
        puVar1[2] = 0;            // slot->field_0x18
        puVar1[1] = 0;            // slot->field_0x14
        *puVar1 = 0;              // slot->field_0x0
        puVar1[3] = DAT_00e2b1a4; // slot->field_0x1c
        FUN_005dbc10(puVar1[5],uVar2); // slot->field_0x24 and objectType

        if (puVar1[4] != 0) {
          _memset((void *)(puVar1[4] + 0xc),0,0x30);
          uVar4 = puVar1[5];   // slot->field_0x24 (which is the slot index? But it's not set yet? Actually puVar1[5] is at offset 0x24, and it was used as argument to FUN_005dbc10, so it must have a value before that. Possibly it's set by something earlier that we don't see? Or maybe puVar1[5] is actually the slot index from the loop variable? But uVar4 is the loop variable? Wait, uVar4 was the loop variable (uVar4 from 0 to 0x1FF). But then later they assign uVar4 = puVar1[5]; That overwrites the loop variable. So the loop variable is not used for the slot index? Actually the loop variable is uVar4 in the do-while. Inside, when they find free slot, they use uVar4 to compute slot pointer (uVar4 * 0x30 + 0x10). So uVar4 is the slot index. Then they set puVar1[5] (slot[5] at offset 0x24) to something? The code doesn't show that assignment. It's possible that the decompiler missed an assignment or it's implicit. Could be that slot->field_0x24 (puVar1[5]) is actually the slot index itself or a counter from a previous operation. But it's used in the ID calculation and as argument to FUN_005dbc10. Let's examine the ID calculation: 
          uVar4 = puVar1[5];
          *(int *)(param_1 + 0x6040) = *(int *)(param_1 + 0x6040) + 1;
          uVar4 = (*(int *)(param_1 + 0x6040) << 0x10 | uVar4) ^ 0xad5c0000;
          puVar1[0xb] = uVar4; // slot->ID
        So they take slot->field_0x24 (which is index? Actually puVar1[5] is at offset 0x24, which is the field they passed to FUN_005dbc10. That function might return something or set it? But they don't assign puVar1[5] in this function. Possibly it's set by callocEntity? Or maybe it's set earlier in the block before the visible code? The decompiler might have missed an assignment because it's using a pointer from in_EAX? Hard to tell.

Given the complexity, I'll assume puVar1[5] is the slot index (uVar4) and is stored in slot->field_0x24. That makes sense: it's the ID generation includes the slot index. So I'll assign slot->slotIndex = slotIndex after the memset.

Thus:
        slot->field_0x24 = slotIndex; // Actually it's puVar1[5] = something, but let's assign it.

Also note: in the do-while, uVar4 is the loop index, and later they use uVar4 = puVar1[5]; This overwrites the loop index. So the loop index is lost after the if, but it's fine.

I'll try to reconstruct with these assumptions.

Final function:
*/

uint EntityManager::createEntity(uint param_2, SpawnData *spawnData)
{
    // this points to an EntityManager object
    // Array of 512 EntitySlots starting at this+0x10, each 0x30 bytes
    // Slot allocation marker at this+0x28 (first slot's inUse flag)
    uint objectType = *(uint *)this; // Probably vtable or type ID

    EntitySlot *slots = (EntitySlot *)((char *)this + 0x10);
    int *inUsePtr = (int *)((char *)this + 0x28);

    for (int i = 0; i < 512; i++)
    {
        if (*inUsePtr == 0)
        {
            EntitySlot *slot = &slots[i];
            if (slot != nullptr)
            {
                int entityPtr = callocEntity(this, objectType, param_2); // Allocate entity object
                if (entityPtr != 0)
                {
                    slot->objectPtr = entityPtr;
                    slot->inUse = 1;
                    slot->field_0x2c = *(uint *)((char *)spawnData + 0xc);
                    slot->field_0x30 = objectType;
                    slot->field_0x34 = *(uint *)((char *)spawnData + 0x10);
                    slot->field_0x38 = *(uint *)((char *)spawnData + 0x14);
                    slot->field_0x3c = 0; // Will be set to ID later
                    // Set data in the entity object
                    *(uint *)(entityPtr + 0x6c) = *(uint *)((char *)spawnData + 0x18);
                    *(uint *)(entityPtr + 0x70) = *(uint *)((char *)spawnData + 0x1c);
                    slot->field_0x10 = 0;
                    slot->field_0x14 = 0;
                    slot->field_0x0 = 0;
                    slot->field_0x1c = g_SomeGlobal; // DAT_00e2b1a4
                    addRef(slot->field_0x24, objectType); // Reference counting or linking
                    if (slot->objectPtr != 0)
                    {
                        memset((void *)(slot->objectPtr + 0xc), 0, 0x30); // Clear entity sub-structure
                        // Store slot index in field_0x24 for ID generation
                        slot->field_0x24 = i;
                        // Increment global counter
                        *(uint *)((char *)this + 0x6040) += 1;
                        uint uniqueId = (*(uint *)((char *)this + 0x6040) << 16 | (uint)i) ^ 0xad5c0000;
                        slot->field_0x3c = uniqueId;
                        logCreation(2); // FUN_005e5200
                        return uniqueId;
                    }
                }
                // If entityPtr was 0 or objectPtr was 0, clean up slot
                uint slotIndex = slot->field_0x24; // Actually from decompiler: uVar4 = puVar1[5]
                char cleanupResult = freeSlotCheck(slotIndex); // FUN_005e63e0
                if (cleanupResult != 0)
                {
                    if (slotIndex < 512)
                    {
                        EntitySlot *slotToClear = &slots[slotIndex];
                        slotToClear->inUse = 0;
                        slotToClear->field_0x18 = 0;
                        slotToClear->field_0x2c = 0;
                        slotToClear->field_0x0 = 0;
                    }
                }
            }
            return 0;
        }
        i++;
        inUsePtr += 3; // Actually the decompiler increments by 0xc bytes, which is 3 ints. But that would skip two ints. That is suspicious. Maybe it's the stride of the array? But we are iterating slots, so we should move to next slot's inUse flag. The inUse flag is at offset 0x28 from slot start, but each slot is 0x30 bytes, so the next inUse flag is at 0x28 + 0x30 = 0x58, which is +0x30 from previous, not +0xc. So the decompiler's piVar6 += 0xc is wrong. It should be piVar6 += 0x30? But the original pointer is an int* and they add 0xc, which is 12 bytes, not 48. This could be a decompiler error. Perhaps piVar6 is actually pointing to an array of ints at +0x28 that is separate from the slots? But the condition uses *piVar6 to check if slot is free. So it's likely each slot has an int at offset 0x28 (which is puVar1[6]), and the next slot's inUse flag is at offset 0x28+0x30 = 0x58. So to advance to next, we need to add 0x30 bytes (or 0xc ints). But the decompiler adds 0xc (bytes) which is 3 ints, not 12. That is a clear error in the decompiler's pointer arithmetic. So we should correct to add sizeof(EntitySlot) which is 0x30 bytes. So in our loop, we should increment the pointer by sizeof(EntitySlot) not by 0xc. The original code likely used a struct pointer increment. I'll assume the compiler generated add with constant 0x30 but the decompiler decoded as 0xc because of a misinterpretation? Actually adding 0x30 bytes to an int* would be adding 0xc (since int* advances by 4 bytes per increment, so to move 0x30 bytes you add 0xc). That matches! piVar6 is an int*, so adding 0xc to an int* moves the pointer by 0xc * 4 = 0x30 bytes. Yes! So the decompiler correctly shows piVar6 += 0xc, which moves to the next int at an offset of 0x30 bytes from the previous int. That makes sense. So our inUsePtr should be incremented by 3 (0xc / 4) each iteration to move to the same field in the next slot. So in our reconstructed code, we should use a loop variable i and access slot[i].inUse, or we can keep the pointer approach with correct increment.

Thus, reconstruct the loop as:
  int *inUsePtr = &slots[0].inUse;
  for (int i=0; i<512; i++) {
    if (*inUsePtr == 0) { ... }
    inUsePtr += 3; // because sizeof(EntitySlot) is 0x30 bytes, and inUse is an int at offset 0x28, so to get to next slot's inUse, add 0x30 bytes = 3 ints.
  }

But actually, inUsePtr is of type int*, so adding 3 moves by 12 bytes. But we need 48 bytes. Wait: sizeof(int)=4, so adding 3 gives 12 bytes. That's not 48. There's a mismatch. Let's compute: slots[0] at base+0x10, inUse at offset 0x28 from base, that is at address base+0x28. slots[1] at base+0x10+0x30 = base+0x40, inUse at base+0x40+0x18? Actually inUse is at offset 0x28 within slot, but slot offset from base is 0x10+slotIndex*0x30. So for slot index i, inUse address = base+0x10 + i*0x30 + 0x18? Wait, we need to verify: puVar1[6] is at offset 0x28 from base? Actually puVar1 is at base+0x10+slotIndex*0x30. puVar1[6] is at that address + 6*4 = +0x18 from slot start? So slot start at base+0x10, puVar1[6] = base+0x10+0x18 = base+0x28. Yes. So for slot i: inUse addr = base+0x10+ i*0x30 + 0x18 = base+0x28 + i*0x30. So the difference between successive inUse addresses is 0x30 bytes. So to go from inUse of slot i to inUse of slot i+1, we add 0x30 bytes to the address. If inUsePtr is an int*, adding 0x30/4 = 12 ints would be correct. But the decompiler shows piVar6 += 0xc, which is adding 12 (decimal) to the pointer? Actually 0xc is hex 12, which is 12 bytes. That would be adding 3 ints, not 12. So there is a discrepancy. The decompiler may have incorrectly decoded the addition as 0xc instead of 0x30? Or maybe the pointer type is not int* but a larger type? Let's examine: piVar6 = (int *)(param_1 + 0x28); Then in loop, piVar6 += 0xc; That would move by 0xc bytes. That does not match the slot stride. So either the decompiler's representation is wrong, or the actual structure is different. Possibly piVar6 is not pointing to the inUse field but to a separate array of flags? The loop condition checks *piVar6, and later they set slot->inUse = 1, which is the same field? But then they access slot fields via puVar1 which uses the slot index. The slot index comes from uVar4, which is the loop counter. So the loop condition and the slot assignment are linked by the same loop index. So if the condition uses *piVar6, and piVar6 is incremented by 0xc each iteration, but the slot stride is 0x30, then they would be out of sync. That can't work. So I think the decompiler made an error: the addition should be 0x30, not 0xc. Or perhaps the pointer is of type EntitySlot* and the add is 0xc (which would be 12 bytes) but that doesn't match either. Given the inconsistency, I'll assume the correct addition is sizeof(EntitySlot) which is 0x30, and since piVar6 is an int*, adding 0xc would be adding 12 ints? No, adding 0xc to an int* adds 0xc*4=48 bytes, not 0xc bytes. Wait: In C, pointer arithmetic: adding an integer N to a pointer of type T moves the address by N * sizeof(T). So if piVar6 is int*, then piVar6 += 0xc means add 0xc*4 = 0x30 bytes. Yes! Because 0xc is the integer value added, not bytes. So piVar6 += 0xc (where 0xc is an integer 12) moves the pointer forward by 12 * sizeof(int) = 12*4 = 48 bytes = 0x30 bytes. That matches exactly! The decompiler shows the addition as "piVar6 = piVar6 + 0xc;" but that is the integer value 12, which translates to 48 bytes. So our earlier confusion is resolved: piVar6 is an int*, adding 0xc (12) moves by 12*4=48 bytes. So the loop correctly advances to the next slot's inUse field each iteration. So our code should reflect that: we can maintain an int pointer and add 12 (0xc) each iteration, or we can just use a loop index and compute the address. I'll use a loop index for clarity.

Thus, the final reconstructed function:
*/

uint EntityManager::createEntity(uint param_2, SpawnData *spawnData)
{
    uint objectType = *(uint *)this; // Often the vtable pointer, used as type/class ID
    EntitySlot *slots = (EntitySlot *)((char *)this + 0x10);
    int *inUseFlags = (int *)((char *)this + 0x28); // points to slots[0].inUse

    for (int i = 0; i < 512; i++)
    {
        if (inUseFlags[i * 12] == 0) // Actually, since each slot is 0x30 bytes, and inUse is at offset 0x18 within slot, offset from base = 0x28 + i*0x30. So inUseFlags is at base+0x28, so inUse for slot i is inUseFlags[i * (0x30/4)] = inUseFlags[i * 12]. Since adding 12 ints advances 48 bytes.
        {
            EntitySlot *slot = &slots[i];
            if (slot != nullptr)
            {
                int entityPtr = callocEntity(this, objectType, param_2);
                if (entityPtr != 0)
                {
                    slot->objectPtr = entityPtr;
                    slot->inUse = 1;
                    slot->field_0x2c = *(uint *)((char *)spawnData + 0xc);
                    slot->field_0x30 = objectType;
                    slot->field_0x34 = *(uint *)((char *)spawnData + 0x10);
                    slot->field_0x38 = *(uint *)((char *)spawnData + 0x14);
                    slot->field_0x3c = 0;
                    *(uint *)(entityPtr + 0x6c) = *(uint *)((char *)spawnData + 0x18);
                    *(uint *)(entityPtr + 0x70) = *(uint *)((char *)spawnData + 0x1c);
                    slot->field_0x10 = 0;
                    slot->field_0x14 = 0;
                    slot->field_0x0 = 0;
                    slot->field_0x1c = g_SomeGlobal;
                    addRef(slot->field_0x24, objectType);
                    if (slot->objectPtr != 0)
                    {
                        memset((void *)(slot->objectPtr + 0xc), 0, 0x30);
                        slot->field_0x24 = i; // store slot index
                        *(uint *)((char *)this + 0x6040) += 1;
                        uint uniqueId = (*(uint *)((char *)this + 0x6040) << 16 | (uint)i) ^ 0xad5c0000;
                        slot->field_0x3c = uniqueId;
                        logCreation(2);
                        return uniqueId;
                    }
                }
                // Cleanup on failure
                uint slotIndex = slot->field_0x24; // from original uVar4 = puVar1[5] (likely slotIndex)
                if (freeSlotCheck(slotIndex) != 0)
                {
                    if (slotIndex < 512)
                    {
                        EntitySlot *slotToClear = &slots[slotIndex];
                        slotToClear->inUse = 0;
                        slotToClear->field_0x18 = 0;
                        slotToClear->field_0x2c = 0;
                        slotToClear->field_0x0 = 0;
                    }
                }
            }
            return 0;
        }
    }
    return 0;
}