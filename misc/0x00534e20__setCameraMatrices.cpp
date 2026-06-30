// FUNC_NAME: setCameraMatrices
// Address: 0x00534e20
// Role: Copies two 4x4 matrices (first row only) to global storage and applies them to camera nodes if they exist.

void __thiscall setCameraMatrices(float* viewMatrix, float* projMatrix) {
    // Copy first 4 floats of view matrix to global storage at 0x01219c40
    _DAT_01219c40 = viewMatrix[0];
    uRam01219c44 = viewMatrix[1];
    uRam01219c48 = viewMatrix[2];
    uRam01219c4c = viewMatrix[3];

    // Copy first 4 floats of projection matrix to global storage at 0x01219c30
    _DAT_01219c30 = projMatrix[0];
    uRam01219c34 = projMatrix[1];
    uRam01219c38 = projMatrix[2];
    uRam01219c3c = projMatrix[3];

    // Access camera node array (size 0x3c per entry) using current camera index
    int cameraIndex = (uint)DAT_01219b21;
    CameraNode* cameraNode = &cameraNodeArray[cameraIndex]; // base at DAT_01219d68

    // If first node pointer is valid, apply view matrix to it
    if (cameraNode->node1 != 0) {
        applyTransformToNode(DAT_01219a84, cameraNode->node1, &_DAT_01219c30);
    }

    // If second node pointer is valid, apply projection matrix to it
    if (cameraNode->node2 != 0) {
        applyTransformToNode(DAT_01219a84, cameraNode->node2, &_DAT_01219c40);
    }
}