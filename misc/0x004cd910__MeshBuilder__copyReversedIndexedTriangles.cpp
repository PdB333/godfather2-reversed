// FUNC_NAME: MeshBuilder::copyReversedIndexedTriangles
void __fastcall MeshBuilder::copyReversedIndexedTriangles(MeshBuilder* this, short* outBuffer)
{
    int count = *(int*)((char*)this + 0x0C);  // +0x0C: number of indices / triangles to copy
    if (count <= 0)
        return;

    count--;  // convert to last index in zero-based array
    int basePtr = *(int*)((char*)this + 0x10);  // +0x10: pointer to triangle data (each triangle = 3 shorts = 6 bytes)
    short* dst = outBuffer + 2;  // destination starts at outBuffer[2] to allow writing [-2],[-1],[0]
    ushort* srcIndices = (ushort*)(*(int*)((char*)this + 0x18) + count * 4);  // +0x18: pointer to index array (each entry 4 bytes, low 16 bits used)

    do {
        unsigned int idx = *srcIndices;  // low 16 bits of entry
        int srcPos = basePtr + idx * 6;  // each triangle vertex = 6 bytes (3 shorts)
        dst[-2] = *(short*)srcPos;       // first short (e.g. vertex index or coord)
        dst[-1] = *(short*)(srcPos + 2); // second short
        *dst = *(short*)(srcPos + 4);    // third short
        count--;
        dst += 3;          // advance 3 shorts per triangle
        srcIndices -= 2;   // move backward one 4‑byte entry (ushort decrement by 2 = 4 bytes)
    } while (count >= 0);
}