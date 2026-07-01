// FUNC_NAME: Entity::setWorldTransform
void __thiscall Entity::setWorldTransform(int *thisPtr, int transformSourceId, int transformIndex, long long *transformHandle, int optionalParam) {
    int *positionVectorPtr; // Pointer to a 4D vector (x,y,z,w) in int representation
    int posX, posY, posZ, posW; 
    int vtable; 
    int result; 
    int matrixBuffer[16]; // Temporary 4x4 matrix (16 floats)
    char transformedData[76]; // Output transformation data (likely Havok hkTransform or similar)
    int *bodyPointer; // Pointer to physics body

    // Retrieve position from some lookup system
    positionVectorPtr = (int *)SomeLookupFunction(transformSourceId, transformIndex, 0);
    posX = *positionVectorPtr;
    posY = positionVectorPtr[1];
    posZ = positionVectorPtr[2];
    posW = positionVectorPtr[3];

    // Only process if the position is non-zero (any component non-zero)
    if ((posX != 0) || (posY != 0) || (posZ != 0) || (posW != 0)) {
        // Get the world matrix from some global context (camera? parent transform?)
        int *worldMatrixPtr = (int *)GetWorldMatrix();
        // Copy the 16 floats of the 4x4 matrix into local buffer
        int *src = worldMatrixPtr;
        for (int i = 0; i < 16; i++) {
            matrixBuffer[i] = *src;
            src++;
        }
        // Transform the matrix into a different representation (e.g., quaternion+translation)
        TransformMatrixToHavok(transformedData, matrixBuffer);

        // Call a virtual method on this object (e.g., getRigidBody)
        vtable = *thisPtr;
        if (optionalParam == -1) {
            thisPtr = 0; // Nullify this pointer if special flag
        }
        result = (*(code **)(vtable + 0x58))(0, thisPtr, optionalParam, 0); // vtable[0x58] method

        // Set the physics body's position and rotation from the transformed data
        int *body = &result; // Actually result is a pointer? But we need address for output
        // note: The decompiler shows iStack_a4 is a local variable, so we use a separate variable.
        int bodyRet = 0; // placeholder for iStack_a4
        SetBodyTransform(&bodyRet, &posX, transformedData, result);
        if (bodyRet != 0) {
            *(int *)(bodyRet + 8) = 0; // Clear some flag on the body
        }
    }
}