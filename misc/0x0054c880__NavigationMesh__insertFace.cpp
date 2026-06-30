// FUNC_NAME: NavigationMesh::insertFace
void __thiscall NavigationMesh::insertFace(NavigationMesh* this, int* faceData)
{
    int oldCount = *(int*)((char*)this + 0x14); // old number of faces
    // Process the input data; may modify faceData or increase face count
    processFaceData(faceData);
    if (*(int*)((char*)this + 0x14) != oldCount) {
        int* arrayBase = *(int**)((char*)this + 0x10); // +0x10: base pointer to face array (each face 0x30 bytes)
        int newCount = *(int*)((char*)this + 0x14);
        int byteOffset = newCount * 0x30;
        // Address of the newly added face (last element)
        char* newFace = (char*)(byteOffset - 0x30 + (int)arrayBase);
        // Copy first 9 dwords from input (first 8 are floats, 9th is a pointer used later)
        for (int i = 0; i < 9; i++) {
            *(int*)(newFace + i * 4) = faceData[i];
        }
        // Find the tail of the linked list starting at faceData[8]
        int* listHead1 = (int*)faceData[8];
        int* tail1 = listHead1;
        while (*(int*)((char*)tail1 + 0xC) != 0) {  // +0xC: next node pointer
            tail1 = (int*)*(int*)((char*)tail1 + 0xC);
        }
        *(int**)(newFace + 0x20) = tail1; // store tail of first list

        // Find the tail of the linked list starting at faceData[9]
        int* listHead2 = (int*)faceData[9];
        int* tail2 = listHead2;
        while (*(int*)((char*)tail2 + 0xC) != 0) {
            tail2 = (int*)*(int*)((char*)tail2 + 0xC);
        }
        *(int**)(newFace + 0x28) = tail2; // store tail of second list

        // Extract flag bits and set initial flag
        unsigned int flag = *(unsigned int*)((char*)tail2 + 4) & 0x3FFFFFFF;
        *(unsigned int*)(newFace + 0x2C) = flag;

        // If the first node of the second list has type == 4 (i.e., a triangle edge)
        if (*(int*)(*(int*)((char*)listHead2) + 0xC) == 4) {
            *(unsigned int*)(newFace + 0x2C) = flag | 0x80000000; // set high bit

            // Calculate normalized cross product for normal
            // Positions are stored with offsets relative to the node structure
            int* node = (int*)*listHead2; // dereference to get node pointer
            float p1x = *(float*)((char*)node + 0x20);
            float p1y = *(float*)((char*)node + 0x24);
            float p1z = *(float*)((char*)node + 0x28);
            float p2x = *(float*)((char*)node + 0x30);
            float p2y = *(float*)((char*)node + 0x34);
            float p2z = *(float*)((char*)node + 0x38);
            float p3x = *(float*)((char*)node + 0x40);
            float p3y = *(float*)((char*)node + 0x44);
            float p3z = *(float*)((char*)node + 0x48);

            float dx1 = p2x - p1x;
            float dy1 = p2y - p1y;
            float dz1 = p2z - p1z;
            float dx2 = p3x - p2x;
            float dy2 = p3y - p2y;
            float dz2 = p3z - p2z;

            // Cross product
            float crossX = dy1 * dz2 - dz1 * dy2;
            float crossY = dz1 * dx2 - dx1 * dz2;
            float crossZ = dx1 * dy2 - dy1 * dx2;

            float lenSq = crossX * crossX + crossY * crossY + crossZ * crossZ;
            float normalX, normalY, normalZ, w;
            if (lenSq <= FLT_EPSILON) { // _DAT_00e448e0 likely 0.0 or epsilon
                normalX = 0.0f;
                normalY = 1.0f; // DAT_00e2b1a4 = 1.0f?
                normalZ = 0.0f;
                w = 0.0f;
            } else {
                float invLen = invSqrt(lenSq); // FUN_00414a80: sqrt or invsqrt? Use invSqrt
                normalX = crossX * invLen;
                normalY = crossY * invLen;
                normalZ = crossZ * invLen;
                w = invLen * 1.0f; // DAT_00e2b05c likely 1.0
            }
            // Set the node's rotation using the computed quaternion (normal + w)
            setQuaternion((float*)(node[0x2]), &normalX); // FUN_00aa2cd0: node[2] is pointer to quaternion

            // Check orientation relative to the face's existing direction (first 3 floats of the element)
            float* faceDir = (float*)(newFace + 0x10); // actually offsets 0x10, 0x14, 0x18? They used +0x10,+0x14,+0x18 in dot product
            float dot = faceDir[0] * normalX + faceDir[1] * normalY + faceDir[2] * normalZ;
            if (dot < 0.0f) {
                // Negate normal
                normalX = DAT_00e44564 - normalX; // likely -normalX
                normalY = DAT_00e44564 - normalY; // likely -normalY
                normalZ = DAT_00e44564 - normalZ; // likely -normalZ
            }

            // Test dot product against threshold to set another flag
            float dot2 = faceDir[0] * normalX + faceDir[1] * normalY + faceDir[2] * normalZ;
            if (_DAT_00e448dc < dot2) { // _DAT_00e448dc likely 0.0 or threshold
                *(unsigned int*)(newFace + 0x2C) = *(unsigned int*)(newFace + 0x2C) & 0x3FFFFFFF | 0x40000000;
            }
        }
    }
}