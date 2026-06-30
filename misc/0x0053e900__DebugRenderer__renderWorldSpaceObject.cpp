// FUNC_NAME: DebugRenderer::renderWorldSpaceObject
void __thiscall DebugRenderer::renderWorldSpaceObject(void *this, void *someParentObj)
{
    int childObj;
    undefined4 matrixData[16]; // 64-byte transformation matrix (float4x4)
    undefined4 outputBuffer[8]; // 32-byte buffer for render output (maybe a transform)
    undefined1 stackBuffer[12]; // unused? passed to subsequent function

    // Check if the parent object is visible (byte at +0x28 == 1)
    if ((*(char *)((int)someParentObj + 0x28) != '\x01') ||
        // Compute child object pointer: base at +0x10 + byte index at +0x20
        (childObj = (int)*(char *)((int)someParentObj + 0x20) + (int)someParentObj + 0x10, childObj == 0) ||
        // Child object type check: byte at +0xd8 != 7 (probably "not a special type")
        (*(char *)(childObj + 0xd8) == '\a'))
    {
        return;
    }

    // Copy the transformation matrix from child object (offsets 0xe0 to 0x11c, 16 floats)
    matrixData[0] = *(undefined4 *)(childObj + 0xe0);
    matrixData[1] = *(undefined4 *)(childObj + 0xe4);
    matrixData[2] = *(undefined4 *)(childObj + 0xe8);
    matrixData[3] = *(undefined4 *)(childObj + 0xec);
    matrixData[4] = *(undefined4 *)(childObj + 0xf0);
    matrixData[5] = *(undefined4 *)(childObj + 0xf4);
    matrixData[6] = *(undefined4 *)(childObj + 0xf8);
    matrixData[7] = *(undefined4 *)(childObj + 0xfc);
    matrixData[8] = *(undefined4 *)(childObj + 0x100);
    matrixData[9] = *(undefined4 *)(childObj + 0x104);
    matrixData[10] = *(undefined4 *)(childObj + 0x108);
    matrixData[11] = *(undefined4 *)(childObj + 0x10c);
    matrixData[12] = *(undefined4 *)(childObj + 0x110);
    matrixData[13] = *(undefined4 *)(childObj + 0x114);
    matrixData[14] = *(undefined4 *)(childObj + 0x118);
    matrixData[15] = *(undefined4 *)(childObj + 0x11c);

    // Call virtual draw function on the renderable component located at childObj+0x10
    // vtable entry at +0x1c (IUnknown-like? This might be IDrawable::Draw)
    // Arguments: matrix, render target context (from this->+4->+0x6c->+4), output buffer
    (**(code (__thiscall **)(void *, void *, void *))(**(int **)(childObj + 0x10) + 0x1c))
              (matrixData, *(undefined4 *)(*(int *)(*(int *)((int)this + 4) + 0x6c) + 4), outputBuffer);

    // Call a cleanup or end-render function
    FUN_0053ea50(this, stackBuffer);
}