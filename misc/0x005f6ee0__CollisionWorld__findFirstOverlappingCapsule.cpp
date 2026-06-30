// FUNC_NAME: CollisionWorld::findFirstOverlappingCapsule
int __thiscall CollisionWorld::findFirstOverlappingCapsule(
    void* thisPtr,
    float* pointA,        // param_2 - one end of capsule axis (x,y)
    float* pointB,        // param_3 - other end of capsule axis (x,y)
    int excludeId,        // param_4 - object ID to skip
    CapsuleQueryFilter* filter, // param_5 - query parameters
    float queryHalfHeight // param_6 - half-height expansion for capsule
) {
    uint32_t filterMask = filter->mask; // param_5[4]
    uint32_t objCount = *(uint32_t*)((uint8_t*)thisPtr + 8);
    uint32_t i = 0;

    if (objCount != 0) {
        int** objArray = *(int***)((uint8_t*)thisPtr + 4); // pointer to array of object pointers
        do {
            int* curObj = *objArray;
            int curObjHandle = curObj; // pointer used as handle
            if (curObjHandle != excludeId) {
                uint32_t objFlags = *(uint32_t*)(curObj + 8);
                if ((objFlags & filterMask) != 0) {
                    float objX = *(float*)(curObj + 0x10);
                    float objY = *(float*)(curObj + 0x14);
                    float objZ = *(float*)(curObj + 0x18);

                    float ax = *pointB;
                    float bx = *pointA;
                    float dx = bx - objX;
                    float cx = ax - objX;
                    float localDistZ = objZ; // initially, but modified later

                    float dy = pointA[1] - objY;
                    float cy = pointB[1] - objY;

                    if (filter->extendedShape != nullptr) {
                        localDistZ = *(float*)(filter->extendedShape + 0x18) + localDistZ;
                    }

                    uint32_t excludeArrayCount = filter->excludeCount; // param_5[1]
                    uint32_t j = 0;
                    if (excludeArrayCount != 0) {
                        int* excludeArray = *((int**)filter); // param_5[0]
                        do {
                            int excludeVal = FUN_005f6280(); // likely get object ID
                            if (excludeVal == *excludeArray) {
                                goto skipObject; // LAB_005f71c6
                            }
                            j++;
                            excludeArray++;
                        } while (j < excludeArrayCount);
                    }

                    float radiusSq = filter->radius * filter->radius; // param_5[2] squared
                    float distSq = dy * dy + dx * dx;
                    if (
                        // Check if within horizontal distance
                        (distSq <= radiusSq) &&
                        // Check if z-extent condition (using some magic constants)
                        ((((float)((uint32_t)dx & kSomeConstant) <= localDistZ) ||
                          ((float)((uint32_t)cx & kSomeConstant) <= localDistZ)) ||
                         (cx * dx <= kAnotherConstant)) &&
                        ((((float)((uint32_t)dy & kSomeConstant) <= localDistZ) ||
                          ((float)((uint32_t)cy & kSomeConstant) <= localDistZ)) ||
                         (cy * dy <= kAnotherConstant)) &&
                        ((float)((uint32_t)(*(float*)(curObj + 0x0c) - queryHalfHeight) & kSomeConstant) <= kHeightEpsilon))
                    {
                        float zDistSq = localDistZ * localDistZ;
                        // Check if actually overlapping the capsule (vertical extent)
                        if (
                            (distSq < zDistSq) ||
                            (cy * cy + cx * cx < zDistSq) ||
                            // Check orientation of axis and points for penetration
                            ((cx * dx < 0.0f || cy * dy < 0.0f) &&
                             (cx = pointA[1],
                              cy = cx - pointB[1],
                              dx = pointB[1] - cx,
                              cy = ((objY - cx) * dx + (objX - bx) * (ax - bx)) /
                                   ((bx - ax) * (bx - ax) + cy * cy),
                              dy = (dx * cy + cx) - objY,
                              cx = ((ax - bx) * cy + bx) - objX,
                              (dy * dy + cx * cx) - zDistSq < 0.0f))
                        ) {
                            return (int)curObj;
                        }
                    }
skipObject:;
                    i++;
                    objArray++;
                }
            }
        } while (i < objCount);
    }
    return 0;
}