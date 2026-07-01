// FUNC_NAME: EARS::Framework::Object::release
void EARS::Framework::Object::release(void) {
    // param_1 is the 'this' pointer (derived from the x86 version, passed in ecx)
    // Global manager structure at DAT_012233a0; +4 holds a pointer to some base object
    int *basePtr = reinterpret_cast<int *>((*(int **)(DAT_012233a0 + 4)));
    
    if (basePtr != nullptr) {
        // Negative offset from basePtr to get the derived object (likely containing class)
        int *derivedObj = reinterpret_cast<int *>(reinterpret_cast<char *>(basePtr) - 0x1f30);
        
        // Check if a global feature/singleton is active (e.g., FX system, audio, etc.)
        int *featurePtr = reinterpret_cast<int *>(FUN_007ff880());
        if (featurePtr != nullptr) {
            // Feature active: call virtual method at vtable+0x1b4 (probably ReleaseShared or similar)
            (*(void (**)(int *))(*(*featurePtr) + 0x1b4))(param_1);
            return;
        }
        // Feature not active: call virtual method at vtable+0x4c (probably ReleaseDirect or Detach)
        (*(void (**)(int *))(*(*derivedObj) + 0x4c))(param_1);
        return;
    }
    
    // No global manager: just zero out the first three words (likely reference count or internal state)
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}