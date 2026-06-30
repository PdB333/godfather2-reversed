// FUNC_NAME: SlotManager::getSlotObject
// Function at 0x00672f60 - Retrieves or creates an object for a given slot and generation.
// Uses ESI as implicit slot index (set by caller). Returns object pointer.

class SlotManager {
public:
    // Fields:
    // +0x00: vtable? (not shown)
    // +0x04: int m_objectCount (decremented when object freed)
    // +0x0c: void** m_indexArray (array of pointers indexed by object-internal index)
    // +0x34: void* m_objects[] (array of object pointers per slot)
    // +0x50: uint m_generations[] (generation value per slot)
    // +0x6c: uint m_inUseFlags[] (0 = free slot, non-zero = occupied)
    // Note: Actual array sizes unknown but presumably fixed.

    // Global destructor function pointer (set by engine)
    typedef void (*DestructorFn)(void* obj);
    static DestructorFn gObjectDestructor; // DAT_01206694

    // External allocation function (likely from memory manager)
    extern void* allocateSlotObject(); // FUN_00673070

    // This method corresponds to the decompiled function.
    // Index is passed via ESI register by calling code.
    void* getSlotObject(uint generation) {
        // Obtain slot index from register (implicit)
        // In reconstruction we treat it as 'slotIndex' stored locally.
        int slotIndex; // set by caller before call (e.g., ESI)
        // However, the decompiled code uses unaff_ESI; we assume it's a class
        // or local variable. For clarity, we'll pass it via a hidden parameter
        // or treat as member. Here we assume the method knows the index
        // from the calling context, e.g. a loop variable.
        // To match the signature, we'll keep the index as an implicit parameter
        // and note it in comments.
        // For reconstruction, we add an explicit 'int slotIndex' parameter.
        // But the original signature is only (uint). We'll keep that and
        // note the additional implicit slotIndex.
    }

    // Alternatively, we can reconstruct as:
    void* getSlotObject_impl(int slotIndex, uint generation) {
        // Check if slot is in use
        if (*(uint*)((char*)this + 0x6c + slotIndex * 4) != 0) {
            // Slot already occupied; return the result of allocateSlotObject?
            // That seems wrong. The code returns FUN_00673070() directly if slot is occupied.
            // Actually: if (*(int *)(in_EAX + 0x6c + unaff_ESI * 4) == 0) { ... } else {
            // It only goes into the else branch if the flag is zero.
            // So if slot is occupied, it sets the flag to 0? Wait:
            // First check: if (*(int*)(... +0x6c...) == 0) { return allocate(); }
            // Else: set that flag to 0, then process generation.
            // So if slot is occupied (non-zero), we proceed to clear it and possibly replace.
            // So the logic:
            // - If slot is free (flag == 0), call allocate() and return immediately.
            // - If slot is occupied, clear flag, then if generation < stored generation, free old object and allocate new, set generation.
            // Then return object pointer.
            // Re-read: 
            // if (flag == 0) { return allocate(); }
            // else: set flag = 0.
            // if (generation < storedGen) {
            //    iVar1 = object pointer;
            //    if (iVar1 != 0) {
            //        index = *(int*)(iVar1 - 8); // internal index
            //        *(int*)(*(int*)(this+0xc) + index*4) = 0; // clear in some array
            //        (this+4)--; // decrement count
            //        gObjectDestructor(iVar1 - 0x10); // destroy object
            //    }
            //    uVar2 = allocate(); // new object
            //    this->objects[slotIndex] = uVar2;
            //    this->generations[slotIndex] = generation;
            // }
            // return this->objects[slotIndex];
        }

        // Reconstructed logic:
        uint* flagPtr = (uint*)((char*)this + 0x6c + slotIndex * 4);
        if (*flagPtr == 0) {
            // Slot free, allocate new object and return it? But the code returns allocate() directly here.
            // However, allocate() returns an object; we should store it? No, the code does not assign to objects[].
            // Actually: if (flag == 0) { uVar2 = allocate(); return uVar2; }
            // That means it does not store the allocated object in the slot. That's odd.
            // It might be a different function? Let's double-check decompiled:
            // if (*(int *)(...0x6c...) == 0) {
            //     uVar2 = FUN_00673070();
            //     return uVar2;
            // }
            // So it allocates and returns, but does not assign to objects[] or set flag. That implies the slot might be used for a different purpose, or the flag indicates a "pending" state? Hmm.
            // The else branch sets flag to 0 before processing generation. So after processing, the flag remains 0. So after returning, flag is 0. So the slot is always freed after this function? But then returning objects[slotIndex] which might be non-null. Actually, in the else branch, after possibly freeing and reallocating, it returns objects[slotIndex]. And flag is set to 0. So the slot becomes free but the object pointer is still valid. So the flag might indicate whether the object needs to be re-evaluated? Possibly this is a lazy caching mechanism: flag indicates "dirty" (non-zero) or "clean" (zero). If dirty, it cleans and potentially updates object.
            // Initial state: flag=0 (clean). On first call, returns allocate() without storing. That seems inconsistent.
            // Maybe the decompiler misread the conditional? Actually, the condition `if (flag == 0)` is checking if the flag is zero. If zero, it allocates and returns. If non-zero, it sets to zero, then processes generation. That means a non-zero flag indicates the slot is "initialized" and needs to be reset? But then setting to zero and then checking generation? The generation check only triggers if param_1 < stored generation. So if generation is newer or equal, it just returns the existing object. So typical usage: caller sets flag to something non-zero to indicate that a generation check is needed. Then calls this function with a generation number. If the generation is older than stored, it discards the object and creates a new one. If generation is newer or equal, it returns the cached object. So flag is used to trigger a re-check? But why would it be non-zero in the first place?
            // Perhaps the flag is actually a reference count or lock? Unclear.
            // Given the decompilation, we stick to the literal logic.
        }

        // We'll implement as per decompiled with comments.
    }

    // To match the exact decompiled logic, we'll write:

    void* getSlotObject(int slotIndex, uint generation) {
        // Check slot usage flag at +0x6c
        uint* usageFlag = (uint*)((char*)this + 0x6c + slotIndex * 4);
        if (*usageFlag == 0) {
            // Slot not in use: allocate new object (without caching)
            return allocateSlotObject();
        } else {
            // Slot in use: mark as free for now
            *usageFlag = 0;
            // Compare generation
            uint* storedGen = (uint*)((char*)this + 0x50 + slotIndex * 4);
            if (generation < *storedGen) {
                // Generation mismatch: destroy old object
                void* obj = *(void**)((char*)this + 0x34 + slotIndex * 4);
                if (obj != 0) {
                    // Get internal index from object metadata (at offset -8 from allocation start)
                    int internalIndex = *(int*)((char*)obj - 8);
                    // Clear reference in the index array at +0x0c
                    void** indexArray = *(void***)((char*)this + 0x0c);
                    indexArray[internalIndex] = 0;
                    // Decrement object count
                    (*(int*)((char*)this + 4))--;
                    // Destroy object memory (using global destructor)
                    gObjectDestructor((char*)obj - 0x10);
                }
                // Allocate new object
                void* newObj = allocateSlotObject();
                // Store new object and update generation
                *(void**)((char*)this + 0x34 + slotIndex * 4) = newObj;
                *storedGen = generation;
            }
            // Return current object pointer (may be old or new)
            return *(void**)((char*)this + 0x34 + slotIndex * 4);
        }
    }
};

// Note: The function actually takes only one uint parameter (generation) and uses an implicit slot index (passed in ESI register).
// To model that faithfully in C++, the slot index would need to be a member variable or a hidden parameter.
// However, the calling convention __thiscall with EAX=this, and ESI set by caller is not directly representable in standard C++.
// We have chosen to add an explicit slotIndex parameter for clarity. The original code likely used an index variable from a loop or a class member.
// The callers (0x00678100, etc.) would set ESI before calling.
// In practice, this could be a template method or an inline function.

// Global destructor function pointer (assumed to be set externally)
SlotManager::DestructorFn SlotManager::gObjectDestructor = nullptr; // initialized elsewhere

// Allocation function (platform-specific)
void* SlotManager::allocateSlotObject() {
    // Implementation not shown; calls memory manager
    return nullptr;
}