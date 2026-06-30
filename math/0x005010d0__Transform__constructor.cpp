// FUNC_NAME: Transform::constructor
void Transform::constructor(int param_1) {
    // Call base class constructor (vtable setup, etc.)
    baseConstructor();

    // Set vtable pointer for this class
    this->vtable = &VTABLE_Transform;

    // Global constants (likely from data segment)
    const float kEpsilonSq = DAT_00e44848;  // ~1e-10 or similar
    const float kOne = DAT_00e2b1a4;        // 1.0f

    // Check if already initialized (flag at +0xd)
    if (*(char*)(param_1 + 0xd) == '\0') {
        // Store source pointer (from EDI)
        this->mSourcePtr = unaff_EDI;  // unaff_ESI[0x14] = unaff_EDI

        // Compute reciprocal of scale components with zero handling
        float srcX = *(float*)(unaff_EDI + 0x40);
        float srcY = *(float*)(unaff_EDI + 0x44);
        float srcZ = *(float*)(unaff_EDI + 0x48);

        if (srcX * srcX <= kEpsilonSq) {
            this->mInvScaleX = 0.0f;
        } else {
            this->mInvScaleX = kOne / srcX;
        }

        if (srcY * srcY <= kEpsilonSq) {
            this->mInvScaleY = 0.0f;
        } else {
            this->mInvScaleY = kOne / srcY;
        }

        if (srcZ * srcZ <= kEpsilonSq) {
            this->mInvScaleZ = 0.0f;
        } else {
            this->mInvScaleZ = kOne / srcZ;
        }

        // Check source flags at +0x18 for bit 1
        if ((*(byte*)(unaff_EDI + 0x18) & 2) == 0) {
            // Copy a matrix row from another structure (unaff_ESI[1] at +0x4)
            int* otherStruct = this->mOtherStruct;  // unaff_ESI[1]
            this->mMatrixRow0 = *(float*)(otherStruct + 0x60);  // +0x60
            this->mMatrixRow1 = *(float*)(otherStruct + 100);   // +100 (0x64)
            this->mMatrixRow2 = *(float*)(otherStruct + 0x68);
            this->mMatrixRow3 = *(float*)(otherStruct + 0x6c);
        } else {
            // Set to identity-like (last component = kOne, rest zero)
            this->mMatrixRow0 = 0.0f;
            this->mMatrixRow1 = 0.0f;
            this->mMatrixRow2 = 0.0f;
            this->mMatrixRow3 = kOne;
        }

        // Zero out some fields
        this->mField_0x54 = 0;  // unaff_ESI[0x15]
        this->mField_0x48 = 0;  // unaff_ESI[0x12]
        this->mField_0x44 = 0;  // unaff_ESI[0x11]
        this->mField_0x40 = 0;  // unaff_ESI[0x10]
        this->mField_0x4c = kOne; // unaff_ESI[0x13]
        this->mField_0x64 = 0;  // unaff_ESI[0x19]
        this->mField_0x60 = 0;  // unaff_ESI[0x18]
    }
}