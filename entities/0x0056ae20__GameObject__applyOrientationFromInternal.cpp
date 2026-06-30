// FUNC_NAME: GameObject::applyOrientationFromInternal
void __thiscall GameObject::applyOrientationFromInternal(void)
{
    int iSuccess;
    float fQuatW;
    float fQuatX;
    float fQuatY;
    float fQuatZ;

    // Call internal helper to compute orientation components
    iSuccess = Math::computeOrientationComponents(&fQuatW, &fQuatX, &fQuatY, &fQuatZ);
    if (iSuccess == 0) {
        return;
    }

    // Store quaternion at offsets 0x00, 0x04, 0x08, 0x0C
    this->quat.w = fQuatW;   // +0x00
    this->quat.x = fQuatX;   // +0x04
    this->quat.y = fQuatY;   // +0x08
    this->quat.z = fQuatZ;   // +0x0C

    // Retrieve and store additional scalar at offset 0x10
    this->extraFloat = Math::getExtraScalar(); // +0x10
    return;
}