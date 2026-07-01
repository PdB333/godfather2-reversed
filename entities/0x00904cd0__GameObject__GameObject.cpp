// FUNC_NAME: GameObject::GameObject
// Address: 0x00904cd0 - Constructor for GameObject, sets up vtable pointers and initializes sub-objects
void __thiscall GameObject::GameObject(GameObject* thisObject)
{
    char initResult;

    // Set primary vtable pointer (offset 0)
    thisObject->vtable = &PTR_FUN_00d82274; // Primary vtable
    // Set secondary vtable at offset 0x3C (15 * 4)
    thisObject->secondaryVtable1 = &PTR_LAB_00d82264;
    // Set additional vtable at offset 0x48 (18 * 4)
    thisObject->secondaryVtable2 = &PTR_LAB_00d82260;

    // Call base class initialization (possibly global object registration)
    baseClassConstructor(&DAT_01218060); // DAT_01218060 is likely a global class registry

    // Initialize sub-object at offset 0x20 (8 * 4)
    initResult = initSubObject(thisObject + 8); // FUN_00904b60
    if (initResult != 0) {
        // If sub-object initialization failed, report error
        reportError(&DAT_0112ff38); // DAT_0112ff38 might be an error string or object
    }

    // Finalize construction (e.g., set up additional state)
    finalizeConstruction(); // FUN_00477eb0
}