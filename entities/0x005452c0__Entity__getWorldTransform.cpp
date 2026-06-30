// FUNC_NAME: Entity::getWorldTransform
void __thiscall Entity::getWorldTransform(int thisPtr, float* outPos, float* outForward)
{
    int managerPtr = *(int*)(DAT_01223480 + 0x24); // global manager singleton +0x24
    FUN_0045cbe0(); // unknown helper, possibly debug or init

    // Initialize a local transform structure (likely quaternion + position)
    float localTransform[5]; // 20 bytes, maybe quaternion (4) + something
    localTransform[0] = *(float*)&DAT_00e2b1a4; // identity quaternion w?
    float* quatPart = (float*)((int)localTransform + 0x10); // offset 0x10
    *quatPart = *(float*)&DAT_00e2b1a4; // another component
    float* posPart = (float*)((int)localTransform + 0x24); // offset 0x24
    *posPart = *(float*)&DAT_00e2b1a4; // position x?
    // Zero out remaining fields
    float* zeroArea = (float*)((int)localTransform + 0x38); // offset 0x38
    zeroArea[0] = 0.0f;
    zeroArea[1] = 0.0f;
    zeroArea[2] = 0.0f;
    zeroArea[3] = 0.0f;

    // Get component at this+0x2e8 (e.g., TransformComponent)
    int componentPtr = *(int*)(thisPtr + 0x2e8);
    // Get vtable from component
    int vtable = **(int**)componentPtr;
    // Get method at vtable+0x1c (e.g., getWorldTransformInternal)
    void (*getTransformFunc)(float*, float, float*) = (void (*)(float*, float, float*))(*(int*)(vtable + 0x1c));
    // Call with localTransform, a value from manager+0x6c+4, and local_70 (uninitialized output?)
    float unknownValue = *(float*)(*(int*)(managerPtr + 0x6c) + 4);
    float local70[1]; // 4 bytes, possibly output
    getTransformFunc(localTransform, unknownValue, local70);

    // Copy results to output parameters
    outPos[0] = *(float*)&unaff_ESI; // from register/stack
    outPos[1] = *(float*)&uStack_78;
    outPos[2] = *(float*)&uStack_74;
    outForward[0] = *(float*)&uStack_6c;
    outForward[1] = *(float*)&uStack_68;
    outForward[2] = *(float*)&uStack_64;
}