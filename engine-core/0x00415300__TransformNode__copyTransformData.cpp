// FUNC_NAME: TransformNode::copyTransformData

// Reconstructed from 0x00415300
// Copies a 4x4 matrix (16 floats) from a source transform provider to a target transform slot.

struct TransformProvider {
    // vtable: +0x0, virtual functions
    // +0x60: virtual float* getMatrixData(); // returns pointer to 16 floats
};

struct TransformNode {
    // +0x0C: TransformProvider* mSourceProvider;
    // +0x20: TransformNode* mTargetNode;     // target that receives the transform data
    // Target's transform data starts at +0x30 (16 floats)
};

void __fastcall TransformNode::copyTransformData(TransformNode* this) {
    TransformNode* targetNode = this->mTargetNode;
    if (targetNode != nullptr) {
        // Get matrix data from the source provider via vtable call at offset 0x60
        float* srcMatrix = this->mSourceProvider->getMatrixData(); // virtual function call
        // Copy 16 floats (4x4 matrix) into target node's transform storage at +0x30
        float* destMatrix = reinterpret_cast<float*>(reinterpret_cast<char*>(targetNode) + 0x30);
        for (int i = 0; i < 16; ++i) {
            destMatrix[i] = srcMatrix[i];
        }
    }
}