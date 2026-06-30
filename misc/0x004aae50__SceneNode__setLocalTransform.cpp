// FUNC_NAME: SceneNode::setLocalTransform

void SceneNode::setLocalTransform(const float matrix[4]) { // matrix is 4 floats (16 bytes)
    // Access thread-local game context via FS segment offset 0x2C
    // Get pointer to a global structure then offset to transform buffer
    // this->field_0x18 is an index or offset into the buffer
    int* contextPtr = *(int**)(__readfsdword(0x2C)); // thread local storage
    int* bufferBase = *(int**)(contextPtr + 8); // offset 8 in context
    float* dest = (float*)(bufferBase + 0x40 / sizeof(int)) + *(int*)(this + 0x18); // +0x18 offset from this

    // Copy 4 floats (16 bytes) from input matrix to destination
    dest[0] = matrix[0];
    dest[1] = matrix[1];
    dest[2] = matrix[2];
    dest[3] = matrix[3];

    // Notify system of change (e.g., mark dirty)
    this->onTransformChanged(); // calls FUN_004aab40
}