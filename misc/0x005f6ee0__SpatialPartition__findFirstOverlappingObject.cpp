// FUNC_NAME: SpatialPartition::findFirstOverlappingObject
// Function at 0x005f6ee0: core spatial overlap query against a collection of objects.
// Finds the first object whose bounding volume (sphere/box) overlaps the given query ray/segment,
// subject to a mask filter and optional exclusion ID.

int __thiscall SpatialPartition::findFirstOverlappingObject(
    int thisPtr,                // this: pointer to SpatialPartition (holds object array)
    float *rayStart,            // start of query ray/segment
    float *rayEnd,              // end of query ray/segment
    int excludeId,              // ID to skip (e.g., self)
    SpatialQueryDesc *queryDesc,// query parameters: pointer arrays, counts, radius, extra radius, bitmask
    float defaultRadius         // a default radius compared against object radius
)
{
    float diffX, diffY, diffZ;
    uint index, objectCount;
    int *objPtr, *objArrayEnd;
    int currentObj;
    uint j, subCount;
    int *subList;
    int subHash;
    float dx1, dy1, dx2, dy2;
    float ex, ey, ez;          // object position / radius
    float segDx, segDy;        // delta along segment
    float queryRadiusSq;       // squared query radius
    float projDist;
    float closestDistSq;

    uint filterMask = queryDesc->bitmask;            // param_5[4]
    objectCount = *(uint *)(thisPtr + 8);            // +0x8: number of objects
    index = 0;

    if (objectCount != 0) {
        objArrayEnd = *(int **)(thisPtr + 4);         // +0x4: pointer to object array
        do {
            currentObj = *objArrayEnd;
            // Skip excluded object and objects that do not match filter mask
            if ((currentObj != excludeId) && ((*(uint *)(currentObj + 8) & filterMask) != 0)) {
                // Object position (x,y,z) at offsets +0x10, +0x14, +0x18
                ex = *(float *)(currentObj + 0x10);
                ey = *(float *)(currentObj + 0x14);
                ez = *(float *)(currentObj + 0x18);   // radius or half-size? Actually used as radius later

                // Deltas from ray start to object
                dx1 = *rayStart - ex;
                dy1 = rayStart[1] - ey;
                dx2 = *rayEnd - ex;
                dy2 = rayEnd[1] - ey;

                float objRadius = ez; // base object radius
                // If there is an extra radius from queryDesc->extraVolume (param_5[3]), add it
                if (queryDesc->extraVolume != 0) {
                    objRadius += *(float *)(queryDesc->extraVolume + 0x18);
                }

                // Check against exclusion list: param_5[0] points to array of IDs, param_5[1] is count
                subCount = queryDesc->exclusionCount; // param_5[1]
                j = 0;
                if (subCount != 0) {
                    subList = (int *)*queryDesc->exclusionArrayPtr; // param_5[0]
                    do {
                        // Helper function that returns some hash/ID of the object? Probably returns object ID.
                        subHash = FUN_005f6280(); // returns hash? or maybe just currentObj? Unclear.
                        if (subHash == *subList) {
                            goto SKIP_OBJECT; // skip this object
                        }
                        j++;
                        subList++;
                    } while (j < subCount);
                }

                // ---------- Core overlap test (likely AABB vs segment) ----------
                float segLenSq = dy1 * dy1 + dx1 * dx1; // squared distance from ray start to object center in XY plane
                float queryRadius = queryDesc->radius; // param_5[2]
                // First major test: if segment start is within query radius from object?
                if ((segLenSq <= queryRadius * queryRadius) &&
                    // Then check if absolute x differences within object radius (using sign-masking)
                    ((fabs(dx1) <= objRadius /* via masking sign bit */) ||
                     (fabs(dx2) <= objRadius) ||
                     (dx2 * dx1 <= 0.0f))) && // product <=0 means points are on different sides of object center
                    // Similar for Y
                    ((fabs(dy1) <= objRadius) ||
                     (fabs(dy2) <= objRadius) ||
                     (dy2 * dy1 <= 0.0f)) &&
                    // Check if object's own radius (with some offset) passes a threshold
                    (fabs(*(float *)(currentObj + 0x0C) - defaultRadius) <= 0.0f) // DAT_00e2b04c likely 0.0
                   )
                {
                    // Second level: test squared distances against objRadius^2
                    float distSq;
                    objRadius = objRadius * objRadius; // square object radius
                    if ((segLenSq < objRadius) ||
                        (dy2 * dy2 + dx2 * dx2 < objRadius) ||
                        // If product signs indicate segment straddles object center, perform dot-projection test
                        ((dx2 * dx1 < 0.0f) || (dy2 * dy1 < 0.0f))) 
                    {
                        // Compute projection of segment onto line perpendicular to vector from object to segment start?
                        // This is a typical point-to-line distance test variant.
                        float startY = rayStart[1];
                        float endY = rayEnd[1];
                        float deltaY = endY - startY;
                        float diffX = ex - *rayStart;
                        float diffY = ey - startY;
                        // Project onto segment direction
                        projDist = ((ey - startY) * deltaY + (ex - *rayStart) * (*rayEnd - *rayStart)) /
                                   ((*rayStart - *rayEnd) * (*rayStart - *rayEnd) + deltaY * deltaY);
                        // Reconstruct closest point on segment
                        float closestX = (*rayEnd - *rayStart) * projDist + *rayStart; // actually formula reversed? 
                        float closestY = deltaY * projDist + startY;
                        float closestDistSq = (closestY - ey) * (closestY - ey) + (closestX - ex) * (closestX - ex);
                        if (closestDistSq - objRadius < 0.0f) {
                            return currentObj; // intersection found
                        }
                    }
                }
            }
SKIP_OBJECT:
            index++;
            objArrayEnd++;
        } while (index < objectCount);
    }
    return 0; // no intersection
}