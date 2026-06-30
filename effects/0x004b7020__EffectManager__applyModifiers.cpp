// FUNC_NAME: EffectManager::applyModifiers
// Address: 0x004b7020
// Applies a transform (matrix) and two vector modifiers to all active modifiable objects in the managed list.
// Objects with flag at +0xd8 equal to 0x07 or 0x00 are skipped.

void __thiscall EffectManager::applyModifiers(void* thisPtr, void* pTransform, float* pVector1, float* pVector2)
{
    int elementOffset = 0;
    uint i = 0;

    // this->m_objectCount at +0x1c
    if (*(int*)((int)thisPtr + 0x1c) != 0) {
        do {
            // base of object array at this+0x18; each element is 0x70 bytes
            // Inside each element, at offset 0x40 there is a pointer to the actual object
            int objectPtr = *(int*)(elementOffset + 0x40 + *(int*)((int)thisPtr + 0x18));

            // object->m_flag at +0xd8: skip if == 7 (unknown constant) or == 0
            if (*(char*)(objectPtr + 0xd8) != '\a' && *(char*)(objectPtr + 0xd8) != '\0') {
                // Apply transform modifier (pTransform)
                if (pTransform != nullptr) {
                    // Copy 4 floats from pTransform+0x30 (likely the translation/rotation part)
                    float localTransform[4];
                    localTransform[0] = *(float*)((int)pTransform + 0x30);
                    localTransform[1] = *(float*)((int)pTransform + 0x34);
                    localTransform[2] = *(float*)((int)pTransform + 0x38);
                    localTransform[3] = *(float*)0x00e2b1a4; // global constant (likely 1.0f or identity)

                    // Compute some derived data from pTransform into local_50 (48 bytes)
                    char derivedData[48];
                    FUN_004b59d0(pTransform, derivedData);
                    // Apply the derived data to the scene graph (likely set transform)
                    FUN_009f4cd0(derivedData);
                }

                // Apply first vector modifier (pVector1)
                if (pVector1 != nullptr) {
                    float localVec[4];
                    localVec[0] = pVector1[0];
                    localVec[1] = pVector1[1];
                    localVec[2] = pVector1[2];
                    localVec[3] = *(float*)0x00e2b1a4;

                    FUN_009f2000(); // engine internal (maybe update or push matrix)
                    // Call virtual function at vtable+0x40 on the object
                    // vtable pointer is stored at object+0xd0
                    (**(code**)(*(int*)(objectPtr + 0xd0) + 0x40))(&localVec);
                }

                // Apply second vector modifier (pVector2)
                if (pVector2 != nullptr) {
                    float localVec[4];
                    localVec[0] = pVector2[0];
                    localVec[1] = pVector2[1];
                    localVec[2] = pVector2[2];
                    localVec[3] = *(float*)0x00e2b1a4;

                    FUN_009f2000(); // engine internal
                    // Call virtual function at vtable+0x44
                    (**(code**)(*(int*)(objectPtr + 0xd0) + 0x44))(&localVec);
                }

                // If object has an extra pointer at +0x8, call engine function
                if (*(int*)(objectPtr + 8) != 0) {
                    FUN_009f2000();
                }
            }

            i++;
            elementOffset += 0x70; // each element in the array is 0x70 bytes
        } while (i < *(uint*)((int)thisPtr + 0x1c));
    }
    return;
}