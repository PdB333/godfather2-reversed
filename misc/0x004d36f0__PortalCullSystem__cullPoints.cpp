// FUNC_NAME: PortalCullSystem::cullPoints
void PortalCullSystem::cullPoints(Vector4* points, uint8_t* outMasks, int pointCount)
{
    // fGlobalConstant is used as a scaling factor in plane equations (maybe w component or FOV coefficient)
    const float fGlobalConstant = *(float*)0x00e2b1a4;

    // Copy portal mask bytes from the object (stored at increasing offsets spaced 0xC0 bytes apart)
    uint8_t portalMasks[8];
    portalMasks[0] = *(uint8_t*)(this + 0x60);
    portalMasks[1] = *(uint8_t*)(this + 0x120);
    portalMasks[2] = *(uint8_t*)(this + 0x1e0);
    portalMasks[3] = *(uint8_t*)(this + 0x2a0);
    portalMasks[4] = *(uint8_t*)(this + 0x360);
    portalMasks[5] = *(uint8_t*)(this + 0x420);
    portalMasks[6] = *(uint8_t*)(this + 0x4e0);
    portalMasks[7] = *(uint8_t*)(this + 0x5a0);

    // Process each point
    for (int iPoint = 0; iPoint < pointCount; iPoint++)
    {
        // Each point is a 4D vector (x,y,z,w) from the input array.
        // The array is accessed with a stride of 16 bytes (4 floats).
        float x = points[iPoint].x;
        float y = points[iPoint].y;
        float z = points[iPoint].z;
        float w = points[iPoint].w;

        uint8_t resultMask = 0;

        // Outer loop iterates over 8 portal entries (plane sets).
        // Each portal entry is 0x30 bytes (48 bytes) and starts at this->planesBase + index * 0x30
        // planesBase = *(float**)(this + 0x20)  (implicit in the code, pfVar8 starts at this+0x20)
        float* portalPlanes = (float*)(this + 0x20);

        for (int iPortal = 0; iPortal < 8; iPortal++)
        {
            // Current portal's plane data (each set includes 6 planes? Actually planes at negative offsets and positive offsets)
            float* entry = portalPlanes + iPortal * 12; // 0x30 / sizeof(float) = 12

            // There are four explicit plane test results packed into a 4-bit mask (auVar5)
            // The point's w coordinate is compared against each plane equation:
            //   w < (planeA.x * x + planeA.y * y + planeA.z * z + planeA.w * fGlobalConstant)
            // (Note: each plane is stored as 4 floats: A, B, C, D)
            // The plane data is located at offsets relative to the current entry:
            // Plane 0: entry[-8]..entry[-5]  (32 bytes before entry start)
            // Plane 1: entry[-4]..entry[-1]  (16 bytes before entry start)
            // Plane 2: entry[0]..entry[3]    (entry start)
            // Plane 3: entry[4]..entry[7]    (16 bytes into entry)
            // Additionally, two more dot products are computed from entry[8..11] and entry[12..15]
            // (note: entry[12..15] might be beyond the entry size, but are still accessed; likely the structure is larger)

            // __m128 is used to pack four comparison results into a mask via movmskps
            // The following uses SSE intrinsics patterns.

            // First set of four plane tests (planes -8..-5, -4..-1, 0..3, 4..7)
            int mask4 = 0;
            // Each comparison: w < (plane[i].x*x + plane[i].y*y + plane[i].z*z + plane[i].w*fGlobalConstant)
            // If true, resulting float is -1.0 (sign bit set), else +0.0 (sign bit clear)
            // movmskps extracts the sign bits into a 4-bit mask.

            // Simulate with scalar code for clarity:
            float planeVal[4];
            planeVal[0] = entry[-8]*x + entry[-7]*y + entry[-6]*z + entry[-5]*fGlobalConstant;
            planeVal[1] = entry[-4]*x + entry[-3]*y + entry[-2]*z + entry[-1]*fGlobalConstant;
            planeVal[2] = entry[0]*x  + entry[1]*y  + entry[2]*z  + entry[3]*fGlobalConstant;
            planeVal[3] = entry[4]*x  + entry[5]*y  + entry[6]*z  + entry[7]*fGlobalConstant;

            for (int i = 0; i < 4; i++)
            {
                if (w < planeVal[i])
                    mask4 |= (1 << i);
            }

            // Second set: two additional plane tests using entry[8..11] and entry[12..15]
            // They are computed as two dot products and then compared to w (like before)
            float dot1 = entry[8]*x  + entry[9]*y  + entry[10]*z + entry[11]*fGlobalConstant;
            float dot2 = entry[12]*x + entry[13]*y + entry[14]*z + entry[15]*fGlobalConstant;

            // The comparisons are duplicated (same condition packed into two positions in the SSE mask)
            int mask2 = 0;
            if (w < dot1)
                mask2 |= (1 << 0); // Also bit 1 would be set due to duplication, but we only care about OR later
            if (w < dot2)
                mask2 |= (1 << 2); // Similar duplication

            // Combine both masks (OR). If any comparison passed (any bit set), the portal contributes its mask.
            if ((mask4 | mask2) != 0)
            {
                resultMask |= portalMasks[iPortal];
            }

            // Move to next portal entry (0x30 bytes forward)
            portalPlanes += 12; // Increment by 12 floats = 48 bytes = 0x30
        }

        // Write result byte for this point to output buffer
        outMasks[iPoint] = resultMask;
    }
}