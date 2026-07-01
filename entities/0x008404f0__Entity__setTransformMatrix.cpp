// FUNC_NAME: Entity::setTransformMatrix
void __thiscall Entity::setTransformMatrix(Entity *this, float *srcMatrix)
{
    // Build a 4x4 matrix from a 3x4 input (rows with implicit w=0 except last row w from global)
    // Local array of 16 floats (0x50 bytes on stack)
    float matrix[16];
    matrix[0] = srcMatrix[0];
    matrix[1] = srcMatrix[1];
    matrix[2] = srcMatrix[2];
    matrix[3] = 0.0f; // local_44
    matrix[4] = srcMatrix[4];
    matrix[5] = srcMatrix[5];
    matrix[6] = srcMatrix[6];
    matrix[7] = 0.0f; // local_34
    matrix[8] = srcMatrix[8];
    matrix[9] = srcMatrix[9];
    matrix[10] = srcMatrix[10];
    matrix[11] = 0.0f; // local_24
    matrix[12] = srcMatrix[12];
    matrix[13] = srcMatrix[13];
    matrix[14] = srcMatrix[14];
    matrix[15] = *(float*)0x00d5780c; // global constant (likely 1.0f for homogeneous coordinate)

    // Check if we have a render node (+0x170)
    if (this->m_renderNode != NULL) // offset +0x170
    {
        // The decompiler shows: (**(code **)(*(int *)(*(int *)(param_1 + 0x170) + -0x48) + 0x28))(&matrix);
        // This suggests the render node's vtable is at a negative offset (-0x48) from the pointer.
        // Possibly due to multiple inheritance or a base class offset.
        // For simplicity, we treat it as a virtual function call at vtable index 0x28 / 4 = 10.
        // We'll call through a function pointer with the cast
        void **vtable = *(void***)((char*)this->m_renderNode - 0x48);
        typedef void (*SetMatrixFunc)(void*, float*);
        SetMatrixFunc setMatrix = (SetMatrixFunc)vtable[0x28 / 4];
        setMatrix(this->m_renderNode, matrix);
    }
    else
    {
        // Fallback to a default implementation at global base address (iRam00000000 + 0x28)
        // iRam00000000 likely represents address 0, but for safety we call a global function pointer
        typedef void (*GlobalSetMatrixFunc)(float*);
        GlobalSetMatrixFunc globalSetMatrix = (GlobalSetMatrixFunc)(*(int*)0 + 0x28); // iRam00000000 + 0x28
        globalSetMatrix(matrix);
    }
}