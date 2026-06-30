// FUNC_NAME: PathManager::updatePathSegment
bool __fastcall PathManager::updatePathSegment(float* currentPos, float* targetPos, int segmentId, PathSegmentData* segmentData, float accumulatedDistance) {
    float newDistance = accumulatedDistance + *(float*)(segmentData + 1); // Actually param_5 is passed separately, but the code adds *(param_3 + 4) to param_5? Wait, decompiled: param_5 = *(float *)(param_3 + 4) + param_5; So there is an offset: param_3 is segmentId pointer? Actually param_3 is an int pointer? The code: param_5 = *(float *)(param_3 + 4) + param_5; So param_3 is a pointer to something with a float at offset 4. That suggests param_3 is a structure (maybe a path segment) that has a float offset (like segment length?). So param_3 is a pointer to a segment structure. Let's adjust: param_3 is not just an id but a pointer to a segment (e.g., PathSegment*). It has a float at offset 4 (maybe segment length). So we should rename param_3 to `segment`. Then the code adds that segment's length to the accumulated distance.

Also param_4 is the output structure (segmentData) that gets updated.

So revise: param_1 (in_EAX) is `currentPos` (Vector3*), param_2 is `targetPos` (Vector3*), param_3 is `segment` (PathSegment*), param_4 is `segmentData` (PathSegmentData*), param_5 is `accumulatedDistance` (float).

The code: `param_5 = *(float *)(param_3 + 4) + param_5;` So segment has a length at offset 4 (float). So accumulatedDistance gets the segment length added.

Then condition: if ((segmentData->flags & 3) == 0) OR (newDistance < (float)segmentData->maxDistance) then update.

If condition true: segmentData->maxDistance = (int)newDistance; segmentData->currentSegmentId = segment; // sets the pointer? Actually *param_4 = param_3; so assigns the segment pointer to first int.

Then clear bit1 of flags: segmentData->flags &= 0xFD.

Then if (segmentData->flags & 1) == 0: call FUN_005f8a90() and return that value; else call FUN_005f8dc0 with sqrt(distance) + newDistance.

If condition false: return 1.

Note: The flags after clear bit1: if original had bit0 set, then (bit0 & 1) != 0, so call FUN_005f8dc0. If bit0 was 0, call FUN_005f8a90.

Also compute distance between currentPos and targetPos: sqrt(dx^2+dy^2+dz^2). That is used only when bit0 set (i.e., when we call FUN_005f8dc0) and passed as sqrt + newDistance.

Now produce final C++ with these meanings.

I'll define structs:

struct PathSegment {
    float length; // +4 (maybe offset 0 is something else? code uses +4 for float, so assume offset 0 is another field, maybe split?)
    // We'll just access through cast.
};

struct PathSegmentData {
    PathSegment* currentSegment; // +0
    int maxDistance; // +4
    uint8_t flags; // +10
    // padding
};

Now function.

I'll use appropriate types: float* for vectors, but better to use Vec3 struct. Since the code treats them as arrays, I'll use float* with indices 0,1,2 for x,y,z.

Write the function// FUN_005f80d0: PathManager::updatePathSegment
bool __fastcall PathManager::updatePathSegment(float* currentPos, float* targetPos, PathSegment* segment, PathSegmentData* segmentData, float accumulatedDist) {
    float newDist = segment->length + accumulatedDist; // segment->length at +4
    uint8_t flags = *(uint8_t*)((int)segmentData + 10);
    // Check if we should update: if no flags (bit0 and bit1 clear) OR distance less than threshold
    if ((flags & 3) == 0 || newDist < (float)segmentData->maxDistance) {
        segmentData->maxDistance = (int)newDist;
        segmentData->currentSegment = segment;
        // Clear bit1 (skip flag?)
        *(uint8_t*)((int)segmentData + 10) = flags & 0xFD;
        if (!(flags & 1)) {
            // Bit0 not set: return from other function (maybe false?)
            return FUN_005f8a90();
        } else {
            // Bit0 set: compute distance to target and add to newDist, call other function
            float dx = currentPos[0] - targetPos[0];
            float dy = currentPos[1] - targetPos[1];
            float dz = currentPos[2] - targetPos[2];
            float dist = sqrtf(dx*dx + dy*dy + dz*dz);
            FUN_005f8dc0(dist + newDist);
        }
    }
    return true;
}