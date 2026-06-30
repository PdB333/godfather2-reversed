// FUNC_NAME: PhysicsObject::applyForceComponent
void __thiscall PhysicsObject::applyForceComponent(int this, int componentIndex, float deltaTime)
{
    // Access global physics system through thread-local storage (FS:[0x2C])
    // The value at FS:[0x2C] points to a struct containing a pointer to the physics manager,
    // and offset +8 from that manager yields the base address for a per-object state array.
    uint32 tlsBase = __readfsdword(0x2C);
    uint32 managerPtr = *(uint32*)tlsBase;
    uint32 objStateArrayBase = *(uint32*)(managerPtr + 8);
    uint32* pObjState = (uint32*)(objStateArrayBase + *(uint32*)esi);

    // State array: each entry is 0x50 bytes, with a float at offset +0x44 (the component being updated)
    float* pComponent = (float*)((uint32)pObjState + 0x44 + componentIndex * 0x50);

    // Read the force scale factor from the object's physics settings (this+0x28 -> settings at +0x68)
    float* pSettings = *(float**)(this + 0x28);
    float forceScale = pSettings[0x1A]; // offset 0x68 (0x1A*4)

    // Apply: v += forceScale * deltaTime
    *pComponent += forceScale * deltaTime;
}