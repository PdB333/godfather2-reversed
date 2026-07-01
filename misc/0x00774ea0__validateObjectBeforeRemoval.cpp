// FUNC_NAME: validateObjectBeforeRemoval
void __fastcall validateObjectBeforeRemoval(int ecx, int objectId)
{
    // ecx is unused (could be 'this' for static call or dummy)
    int* pRoot = *(int**)(*(int*)(DAT_012233a0 + 4)); // dereference global singleton pointer at +0x04
    if (pRoot != nullptr && pRoot != (int*)0x1f30 && (pRoot - 0x1f30) != objectId)
    {
        // objectId does not match the expected root pointer offset; proceed to remove
        removeObject(objectId);
    }
}