// FUNC_NAME: Entity::setWorldScaledVector
void __thiscall Entity::setWorldScaledVector(float *inVec) // param_2: pointer to 3-component vector
{
    // +0x54: Pointer to a physics body or child transform component
    void *physicsBody = *(void **)(this + 0x54);
    
    if (physicsBody != 0) {
        // Copy the input vector directly into the physics body's transform at offset 0x424
        // The vector is stored as two floats (x,y) followed by z at +0x42c
        *(float *)(physicsBody + 0x424) = inVec[0];
        *(float *)(physicsBody + 0x428) = inVec[1];
        *(float *)(physicsBody + 0x42c) = inVec[2];
        return;
    }
    
    // Fallback: scale the input vector by the world scale factor
    // DAT_01223480 is a global settings object, +0x60 is the world-to-local scale factor
    float worldScale = *(float *)(DAT_01223480 + 0x60);
    float scaledVec[3];
    scaledVec[0] = inVec[0] * worldScale;
    scaledVec[1] = inVec[1] * worldScale;
    scaledVec[2] = inVec[2] * worldScale;
    
    // +0x48: Pointer to the parent transform or entity with a virtual table
    void *parentTransform = *(void **)(this + 0x48);
    
    if (parentTransform != 0) {
        // Adjust parent pointer to get the base class (offset -0x48) and call virtual function at index 100
        // This virtual function is likely setPosition/scaledVector
        void **vtable = *(void ***)((char *)parentTransform - 0x48);
        typedef void (*SetVectorFunc)(void *, float *);
        SetVectorFunc setVector = (SetVectorFunc)vtable[100]; // index 100 in vtable
        setVector(parentTransform, scaledVec);
        return;
    }
    
    // Default: use a global vtable (iRam00000000) if parent is null (should not happen often)
    void **defaultVtable = *(void ***)(iRam00000000);
    typedef void (*SetVectorFunc)(void *, float *);
    SetVectorFunc setVector = (SetVectorFunc)defaultVtable[100];
    setVector(0, scaledVec); // Note: Passing 0 as this? Might be bug or special case
}