// FUNC_NAME: packBoneTransforms (global helper)
// Address: 0x006b2470
// Purpose: Packs bone transform data (likely position + hash) from an array of source objects
//          into a compact output buffer. Each output element is 0x14 (20) bytes.
//          Source objects are referenced via an array of pointers (inPackInfo[0]) and count (inPackInfo[1]).
//          Each source has a Vector4 at offsets 0x20-0x2c (x,y,z,?).
//          A hash (from function 0x7914e0) is also stored.
// Returns the total bytes written (count * 0x14).

int __cdecl packBoneTransforms(int* outBuffer, int* inPackInfo)
{
    uint count = (uint)inPackInfo[1];
    uint idx = 0;

    if (count != 0)
    {
        // puVar3 starts at outBuffer + 0xc (three uint slots into buffer)
        // We'll use a pointer that advances by 5 uints each iteration.
        uint* dest = (uint*)(outBuffer + 3); // equivalent to outBuffer + 0xc/4
        int** srcArray = (int**)inPackInfo[0]; // array of pointers to source objects

        do {
            int* srcObj = srcArray[idx]; // each source object

            // Copy 4 floats from source offsets 0x20, 0x24, 0x28, 0x2c
            // These are stored as raw uint (undefined4*) in the output
            // dest[-3] = hash (offset -3 relative to dest = outBuffer + 0)
            // dest[-2] = float at +0x20 -> outBuffer[1]
            // dest[-1] = float at +0x24 -> outBuffer[2]
            // dest[0]  = float at +0x28 -> outBuffer[3]
            // dest[1]  = float at +0x2c -> outBuffer[4]
            dest[-3] = getBoneHash(); // FUN_007914e0 (likely computes bone ID hash)
            dest[-2] = *(uint*)(srcObj + 0x20/4); // float as uint
            dest[-1] = *(uint*)(srcObj + 0x24/4);
            dest[0]  = *(uint*)(srcObj + 0x28/4);
            dest[1]  = *(uint*)(srcObj + 0x2c/4);

            idx++;
            dest += 5; // move to next element (5 uints = 0x14 bytes)
        } while (idx < count);
    }

    return count * 0x14;
}