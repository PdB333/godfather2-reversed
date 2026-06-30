// FUNC_NAME: ObjectRefHolder::setReferencedObject
void __thiscall ObjectRefHolder::setReferencedObject(int *referencedObject, int *newObject)
{
    int *oldObject = referencedObject;
    int refCountHandle;

    // Call virtual destructor/release on old referenced object (vtable+8)
    (**(code **)(*oldObject + 8))(oldObject);

    // If newObject is non-null, acquire reference; else clear
    if (newObject == 0) {
        refCountHandle = 0;
    } else {
        refCountHandle = FUN_004265d0(newObject, oldObject); // probably AddRef or copy
    }

    // Store the new referenced object (maybe call assignment operator)
    FUN_005fc4a0(oldObject, refCountHandle);

    // Update this's fields: +0x8 = pointer to referenced object, +0xc = handle
    *(int **)(this + 8) = oldObject;
    (**(code **)(*oldObject + 8))(); // release again? (maybe different vtable)

    if (newObject != 0) {
        refCountHandle = FUN_004265d0(newObject, *(int *)(this + 8));
        *(int *)(this + 0xc) = refCountHandle;

        // Call vtable+4 with (newObject, 0) - maybe SetOwner or AddRef
        (**(code **)(*oldObject + 4))(newObject, 0);

        // Call vtable+0xc - notification or finalize
        (**(code **)(*oldObject + 0xc))();
        return;
    }

    *(int *)(this + 0xc) = 0;
    (**(code **)(*oldObject + 0xc))();
    return;
}