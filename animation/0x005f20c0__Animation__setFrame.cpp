// FUNC_NAME: Animation::setFrame
void __fastcall Animation::setFrame(byte frameIndex)
{
    int iVar1;
    int animData;
    int in_EAX;
    
    animData = *(int *)(in_EAX + 8);
    // Clear bit 7 of flags at +0x6c (likely a "loop" or "reverse" flag)
    *(ushort *)(in_EAX + 0x6c) =
         (ushort)(*(byte *)(in_EAX + 0x7b) >> 1 & 1) << 7 | *(ushort *)(in_EAX + 0x6c) & 0xff7f;
    // Check if animation data has no name (string at +1 is empty) and frameIndex is valid
    if ((*(char *)(animData + 1) == '\0') && (frameIndex != 0xff)) {
        // Clamp frameIndex to max frame count - 1
        if (*(byte *)(animData + 2) <= frameIndex) {
            frameIndex = *(byte *)(animData + 2) - 1;
        }
        *(byte *)(in_EAX + 0x66) = frameIndex;
    }
    else {
        // If animation has a name or frameIndex is invalid, call some reset/error handler
        FUN_005f2d10();
    }
    // Call function to update animation state (likely sets up bone transforms)
    FUN_005dbc10(*(undefined1 *)(in_EAX + 100), // +0x64: some byte field
                 *(undefined4 *)(in_EAX + 0x5c), // +0x5c: some int field
                 *(undefined1 *)(in_EAX + 0x65), // +0x65: some byte field
                 *(undefined1 *)(in_EAX + 0x66)); // +0x66: current frame index
    // Calculate keyframe data pointer: base + (frameIndex * numBones * 8)
    iVar1 = *(int *)(animData + 0x2c) + (uint)*(byte *)(animData + 3) * (uint)*(byte *)(in_EAX + 0x66) * 8;
    *(int *)(in_EAX + 0x84) = iVar1; // +0x84: start of keyframe data
    *(int *)(in_EAX + 0x8c) = iVar1; // +0x8c: current keyframe pointer
    *(uint *)(in_EAX + 0x88) = iVar1 + (uint)*(byte *)(animData + 3) * 8; // +0x88: end of keyframe data
    return;
}