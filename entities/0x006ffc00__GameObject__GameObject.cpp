// FUNC_NAME: GameObject::GameObject
// Address: 0x006ffc00
// This function appears to be a constructor/initializer for a GameObject-derived class.
// It checks if a sub-object pointed at offset +0x1c exists and destroys it first,
// then calls multiple initialization routines including vtable setup.
// Offsets:
//   +0x1c: pointer to a sub-object (e.g., a component or derived instance)

void __fastcall GameObject::GameObject(int thisPtr)
{
    // Destroy any existing sub-object at +0x1c before reinitializing.
    if (*(int *)(thisPtr + 0x1c) != 0) {
        destroySubObject(*(void **)(thisPtr + 0x1c));   // FUN_006ff660 – frees sub-object
    }

    // Initialize base class and/or member data.
    initObjectBase(thisPtr);                             // FUN_006fc560

    // Set up the virtual function table (LAB_006ff930 is the vtable address).
    setupVtable(&vtableTable, thisPtr);                  // FUN_006fc4c0

    // Complete remaining initialization steps.
    initObjectMembers(thisPtr);                          // FUN_006fbca0
}