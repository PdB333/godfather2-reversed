// FUN_0046ffe0: GameObject::getVectorToPoint
void __thiscall GameObject::getVectorToPoint(int thisObj, float *inputPoint, uint someFlag)
{
    float dx;
    float dy;
    float dz;
    
    // Compute relative vector from object position (stored at offsets +0x100, +0x104, +0x108) to input point
    dx = *inputPoint - *(float *)(thisObj + 0x100);          // +0x100: position.x
    dy = inputPoint[1] - *(float *)(thisObj + 0x104);        // +0x104: position.y
    dz = inputPoint[2] - *(float *)(thisObj + 0x108);        // +0x108: position.z
    
    // Process the relative vector (likely normalization or clamping)
    FUN_0046fe50(&dx, someFlag);
    
    return;
}