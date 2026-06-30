// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::destructor(GameObject* thisPtr)
{
    // Step 1: Set vtable to first destructor vtable (likely derived class vtable)
    thisPtr->vtablePtr = &PTR_LAB_00d6541c;

    // Step 2: Deallocate or release a 0x34 (52) byte block (maybe an internal buffer)
    FUN_007f6420(0x34);

    // Step 3: Release sub-object at offset +0xB8 (0x2e * 4)
    if (thisPtr->subObjectAt0xB8 != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0xB8));  // likely release/delete
    }

    // Step 4: Set sub-object vtable at +0x8C (0x23 * 4) to another function table
    thisPtr->subVtableAt0x8C = &PTR_FUN_00d64720;

    // Step 5: Release sub-object at offset +0x9C (0x27 * 4)
    if (thisPtr->subObjectAt0x9C != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0x9C));
    }

    // Step 6: Release another sub-object at offset +0x90 (0x24 * 4)
    if (thisPtr->subObjectAt0x90 != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0x90));
    }

    // Step 7: Change the vtable at +0x8C to a different label (possibly base class vtable)
    thisPtr->subVtableAt0x8C = &PTR_LAB_00d64708;

    // Step 8: Release sub-object at offset +0x7C (0x1f * 4)
    if (thisPtr->subObjectAt0x7C != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0x7C));
    }

    // Step 9: Release sub-object at offset +0x70 (0x1c * 4)
    if (thisPtr->subObjectAt0x70 != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0x70));
    }

    // Step 10: Set main vtable to final base class vtable
    thisPtr->vtablePtr = &PTR_LAB_00d63090;

    // Step 11: Release sub-object at offset +0x68 (0x1a * 4)
    if (thisPtr->subObjectAt0x68 != 0) {
        FUN_004daf90(&(thisPtr->subObjectAt0x68));
    }

    // Step 12: Final cleanup (likely deallocate the object itself or global state)
    FUN_0080ea60();
}