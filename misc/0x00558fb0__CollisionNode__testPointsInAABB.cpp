// FUNC_NAME: CollisionNode::testPointsInAABB

// Reconstructed from 0x00558fb0
// Tests whether any points in an array lie inside an axis-aligned bounding box
// param_1: pointer to CollisionNode (this)
// param_2: float[8] - input/output point/pair of points (min and max? actually two points)
// param_3: unknown context (passed to child test)
// param_4: array of uint structures describing points to test
// Returns: OR of param_4->flags for points that intersect/are inside

uint CollisionNode::testPointsInAABB(float* ioPoint, uint param3, uint* pointArray)
{
    uint resultFlags = 0;
    
    // Bail if null array
    if (pointArray == nullptr)
        return 0xFFFFFFFF;
    
    // Build local transform matrix from globals
    // DAT_00e2b1a4 is likely identity matrix, _DAT_00ef3a9c is some global transform
    Matrix44 localMatrix = DAT_00e2b1a4;           // +0x00
    MultiplyMatrix(&localMatrix, _DAT_00ef3a9c);   // FUN_00a66df0
    
    // Initialize some context (probably for recursion/iteration)
    uint context2 = 0xFFFFFFFF;                   // local_4c
    uint context3 = 0xFFFFFFFF;                   // local_40
    
    do {
        // Extract point data from array into a buffer (local_90)
        // FUN_00558db0 fills local_90 with node pointers and geometry
        CollisionNode** nodeBuffer = (CollisionNode**)buffer; // local_90
        ExtractPointData(nodeBuffer, pointArray, this);      // FUN_00558db0
        
        // Subtract translation from ioPoint (so it becomes relative to node's center)
        // local_c0, local_bc, local_b8, local_b4 are the node's center offsets
        ioPoint[0] -= nodeCenterX;   // local_c0
        ioPoint[1] -= nodeCenterY;   // local_bc
        ioPoint[2] -= nodeCenterZ;   // local_b8
        ioPoint[3] -= nodeCenterW;   // local_b4 (usually 0 or 1)
        ioPoint[5] -= nodeCenterY;
        ioPoint[6] -= nodeCenterZ;
        ioPoint[7] -= nodeCenterW;
        ioPoint[4] -= nodeCenterX;
        
        // Call virtual method on first node in buffer: isPointInside
        // Node::isPointInside returns bool in local_c5, and may fill local_60 with additional data
        bool inside = nodeBuffer[0]->isPointInside(ioPoint, tempBuffer); // +0x20 virtual
        
        if (!inside) {
            // Convert point to absolute coordinates using some function (likely sqrt or abs)
            float absX = SomeAbsFunction(ioPoint[0]);   // FUN_0040f220
            float absY = SomeAbsFunction(ioPoint[1]);
            float absZ = SomeAbsFunction(ioPoint[2]);
            float absW = SomeAbsFunction(ioPoint[3]);
            
            // Check if point lies beyond the axis-aligned half-extents of the node
            // fStack_70, fStack_6c, fStack_68 are node's half-extents (maxX, maxY, maxZ)
            uint maskX = (nodeHalfExtentX < absX) ? 0 : 8;   // bVar4
            uint maskY = (nodeHalfExtentY < absY) ? 0 : 4;   // bVar5
            uint maskZ = (nodeHalfExtentZ < absZ) ? 0 : 2;   // bVar3
            uint combinedMask = maskX | maskY | maskZ;
            
            // If all three exceeded (0xE = 8|4|2), treat as inside
            if (combinedMask == 0xE) {
                inside = true;
            }
        }
        
        if (inside) {
            // If point is inside, OR the array element's flags into result
            resultFlags |= *pointArray;
        }
        
        // Restore ioPoint to original by adding back translation
        ioPoint[0] += nodeCenterX;
        ioPoint[1] += nodeCenterY;
        ioPoint[2] += nodeCenterZ;
        ioPoint[3] += nodeCenterW;
        ioPoint[5] += nodeCenterY;
        ioPoint[6] += nodeCenterZ;
        ioPoint[7] += nodeCenterW;
        ioPoint[4] += nodeCenterX;
        
        // Advance array pointer by sizeof(uint)*4 (each element is 16 bytes? +0x10?)
        pointArray += 4;
        
        // Check termination flag at offset 0xB of the next element
        // If it's non-zero, we're done
        char* termByte = (char*)(pointArray + 0xB - (int)pointArray / 4); // messy; original: pcVar1 = (char *)((int)param_4 + 0xb);
        // Actually simpler: treat pointArray as byte pointer
        if (*((char*)pointArray + 0xB) != 0) {
            SomeCleanupFunction();   // FUN_00a66870
            return resultFlags;
        }
        
    } while (true);
}