// FUNC_NAME: Entity::updateAnimationFrame
void __fastcall Entity::updateAnimationFrame(int *this)
{
    undefined1 *animationData;
    int frameCount;
    
    // Get animation data pointer from offset +0x24C (0x93 * 4)
    // If null, use default animation data
    animationData = (undefined1 *)this[0x93];
    if (animationData == (undefined1 *)0x0) {
        animationData = &DAT_0120546e; // Default animation data
    }
    
    // Call virtual function at vtable+0xAC to get frame count
    // This is likely Animation::getFrameCount or similar
    frameCount = (**(code **)(*this + 0xac))(animationData, 0);
    
    // Store frame count at offset +0x19C (0x67 * 4)
    this[0x67] = frameCount;
    return;
}