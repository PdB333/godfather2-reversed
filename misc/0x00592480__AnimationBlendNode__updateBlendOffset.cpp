// FUNC_NAME: AnimationBlendNode::updateBlendOffset
// Address: 0x00592480 - Computes and applies a positional offset using a scale factor, a byte input, and ushort array data.

void __thiscall AnimationBlendNode::updateBlendOffset(void* thisPtr, byte* inputByte) {
    // in_EAX is a hidden parameter passed in eax (likely a pointer to ushort array member of the object)
    ushort* ushortData = /* placed in eax by caller */ reinterpret_cast<ushort*>(eax);
    
    // Global scale factor (likely world/scene unit scale)
    extern float g_scaleFactor; // DAT_00e44820
    
    // Global constant offset (likely base position or origin)
    extern float g_baseOffset; // DAT_00e44564

    // Extract ushort values from the data array
    float value0 = static_cast<float>(ushortData[0]); // *in_EAX
    float value2 = static_cast<float>(ushortData[2]); // in_EAX[2]

    // Compute scaled input from the byte (multiply by 16)
    float scaledInput = static_cast<float>(static_cast<uint>(*inputByte) << 4) * g_scaleFactor;

    // Compute the first parameter: negative of scaled difference
    float param1 = -(value2 * g_scaleFactor - scaledInput);
    // Equivalent to: -g_scaleFactor * (value2 - (*inputByte << 4))

    // Compute the second parameter: base offset minus scaled first ushort
    float param2 = g_baseOffset - value0 * g_scaleFactor;

    // Apply the offset to the object passed in param_1 (third parameter to this function)
    applyPositionOffset(param1, param2, thisPtr);
}