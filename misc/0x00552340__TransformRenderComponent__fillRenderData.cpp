// FUNC_NAME: TransformRenderComponent::fillRenderData
// Address: 0x00552340
// This function extracts rendering transformation and property data from a render component
// into a flat output buffer (22 floats and a trailing byte).
void __thiscall TransformRenderComponent::fillRenderData(TransformRenderComponent* this, float* outData)
{
    // Dereference: this+0x30 -> internal node pointer, then node+0x18 -> transform pointer
    int transformNode = *(int*)(*(int*)((char*)this + 0x30) + 0x18);
    // Copy first 4 floats from the transform node (likely translation/scale)
    outData[0] = *(float*)(transformNode + 0x30);
    outData[1] = *(float*)(transformNode + 0x34);
    outData[2] = *(float*)(transformNode + 0x38);
    outData[3] = *(float*)(transformNode + 0x3c);
    // Copy next 4 floats from the component's own transform (rotation/quaternion?)
    outData[4] = *(float*)((char*)this + 0x10);
    outData[5] = *(float*)((char*)this + 0x14);
    outData[6] = *(float*)((char*)this + 0x18);
    outData[7] = *(float*)((char*)this + 0x1c);
    // Scattered copy of additional orientation/scale fields from the component
    outData[18] = *(float*)((char*)this + 0x30);
    outData[8] = *(float*)((char*)this + 0x34);
    outData[9] = *(float*)((char*)this + 0x38);
    outData[16] = *(float*)((char*)this + 0x50);
    outData[17] = *(float*)((char*)this + 0x54);
    outData[19] = *(float*)((char*)this + 0x58);
    outData[20] = *(float*)((char*)this + 0x5c);
    outData[21] = *(float*)((char*)this + 0x60);
    // Write a single byte flag (e.g. visibility or enable) at offset 88 (0x58) in the output
    *(char*)(outData + 22) = *(char*)((char*)this + 0x94);
}