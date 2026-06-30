// FUNC_NAME: SceneNode::computeWorldMatrix
void __thiscall SceneNode::computeWorldMatrix(SceneNode* this)
{
    Matrix44* worldMatrix;
    int skeletonData;
    Vector3* localPosition;
    Quaternion* localRotation;

    skeletonData = this->m_pSkeletonData; // +0x2c
    localPosition = &this->m_localPosition; // +0x20
    localRotation = &this->m_localRotation; // +0x30

    if (skeletonData == 0) {
        // No skeleton -> direct transform
        gfxPushMatrix(); // FUN_00491090
        setLocalTransform(*localPosition, 0, *localRotation); // FUN_00418540
    } else {
        // Skeletal animation
        setLocalTransformAnimated(*localPosition, skeletonData, *localRotation); // FUN_0041af10
    }

    // Access the world matrix pointer stored at +0x04
    worldMatrix = this->m_pWorldMatrix; // +0x04

    // If there is a skin/bone node reference, copy its 4x4 matrix into the world matrix
    if (this->m_pSkinData != 0) { // +0x28
        // Access current thread's graphics context and read a matrix from skin data
        int* gfxContext = *(int**)(*(int**)(__readfsdword(0x2C)) + 8); // FS:0x2C -> TLS base
        int skinOffset = *(int*)(this->m_pSkinData + 0x18); // +0x18 offset in skin data
        Matrix44* boneMatrix = (Matrix44*)(gfxContext + 0x40 + skinOffset); // sizeof(Matrix44)=0x10? Actually 4 floats = 16 bytes, but offsets are uint* so 0x40+skinOffset in bytes? To be safe: reinterpret.
        worldMatrix->m[0] = boneMatrix->m[0];
        worldMatrix->m[1] = boneMatrix->m[1];
        worldMatrix->m[2] = boneMatrix->m[2];
        worldMatrix->m[3] = boneMatrix->m[3];

        // If this is the current scene object, upload the matrix to GPU
        if (g_currentSceneObject == worldMatrix) { // DAT_012058e8
            updateGPUMatrix(worldMatrix->m_someId, worldMatrix->m_someOther, worldMatrix); // FUN_0060add0
        }
    }

    // If there is a secondary transform node, combine it
    if (this->m_pSecondaryNode != 0) { // +0x24
        int* gfxContext = *(int**)(*(int**)(__readfsdword(0x2C)) + 8);
        int nodeOffset = *(int*)(this->m_pSecondaryNode + 0x18); // +0x18
        int* nodeData = gfxContext + nodeOffset;
        combineTransforms(nodeData + 0x20, *(Matrix44*)(nodeData + 0x68), *(Matrix44*)(nodeData + 100)); // FUN_004940a0
    }
}