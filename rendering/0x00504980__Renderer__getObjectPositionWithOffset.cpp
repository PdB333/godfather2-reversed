// FUNC_NAME: Renderer::getObjectPositionWithOffset
// Address: 0x00504980
// Reads a position from thread-local render data (likely camera-relative or view-space position)
// and optionally adds a world-space offset from the object if certain flags are not set.
// Parameters:
//   ECX - outVec4 (float[4]) - destination for position (likely x,y,z,1)
//   EDX - objectPtr (int)    - pointer to a game object with offset +8 (index?), +0x20 (transform/flags struct)
void __fastcall Renderer::getObjectPositionWithOffset(float *outVec4, int objectPtr)
{
    // Access thread-local storage: FS:0x2C points to a TLS structure.
    // Dereference twice to get a base pointer, then add 0x80 and an index from objectPtr+8.
    int tlsBase = *(int*)(*(int*)(*(int**)(__readfsdword(0x2C)) + 8)); // reads from TLS, then +8 for some table
    float *sourcePos = (float*)(tlsBase + 0x80 + *(int*)(objectPtr + 8)); // source position (4 floats)

    // Copy source to output
    outVec4[0] = sourcePos[0];
    outVec4[1] = sourcePos[1];
    outVec4[2] = sourcePos[2];
    outVec4[3] = sourcePos[3];

    // Get additional transform structure from object at offset 0x20
    int transformPtr = *(int*)(objectPtr + 0x20);
    // Check flags at offset 0x14 (bits 1 and 2 clear means no offset applied?)
    if ((*(unsigned char*)(transformPtr + 0x14) & 6) == 0) {
        // Apply world-space offset (translation) to x,y,z only
        outVec4[0] += *(float*)(transformPtr + 0x30);
        outVec4[1] += *(float*)(transformPtr + 0x34);
        outVec4[2] += *(float*)(transformPtr + 0x38);
    }
}