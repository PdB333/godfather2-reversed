// FUN_0042ed50: CollisionManager::checkSphereOverlap
// Iterates over 6 collision layers (offset +0x1230, each size 0x6A0).
// For each active object in a layer, checks sphere collision against a set of external spheres (global array at 0x1194b88).
// If overlap detected, calls handleCollision(object, sphereIndex).
// param_2 = number of external spheres.

uint __thiscall CollisionManager::checkSphereOverlap(int externalSphereCount) {
    // Global external sphere array: each entry = 4 floats (x, y, z, radius)
    float* gExternalSpheres = (float*)0x01194b88; // static array

    for (uint layerIdx = 0; layerIdx < 6; ++layerIdx) {
        // Skip layers where bit 2 is set (1 << layerIdx) & 4 != 0
        if ((1 << layerIdx) & 4) {
            continue;
        }

        // Pointer to layer data at this+0x1230 + layerIdx*0x6a0
        LayerData* layer = (LayerData*)((char*)this + 0x1230 + layerIdx * 0x6A0);

        // Iterate over active indices in this layer
        for (int i = 0; i < layer->activeCount; ++i) {
            unsigned short objIdx = layer->activeIndices[i];
            void* object = (char*)layer->objectArray + objIdx * 0x20; // each object is 0x20 bytes

            // For layers other than 0, require object type byte at (*(char**)(object+0x10))[4] == 2
            if (layerIdx != 0) {
                char* typeInfo = *(char**)((char*)object + 0x10); // pointer to type descriptor
                if (typeInfo[4] != 2) {
                    continue;
                }
            }

            // Get sphere data for this object from layer's sphere array at +4
            float* objSphere = (float*)((char*)layer->sphereData + objIdx * 0x10); // each sphere = 4 floats
            float objX = objSphere[0];
            float objY = objSphere[1];
            float objZ = objSphere[2];
            float objRadius = objSphere[3];

            // Check against all external spheres
            for (int j = 0; j < externalSphereCount; ++j) {
                float* extSphere = gExternalSpheres + j * 4; // each external sphere = 4 floats
                float extX = extSphere[0];
                float extY = extSphere[1];
                float extZ = extSphere[2];
                float extRadius = extSphere[3];

                float dx = objX - extX;
                float dy = objY - extY;
                float dz = objZ - extZ;
                float distSq = dx*dx + dy*dy + dz*dz;
                float sumRadius = objRadius + extRadius;

                if (distSq < sumRadius * sumRadius) {
                    // Collision detected, call the callback
                    handleCollision(object, j); // FUN_00524880
                }
            }
        }
    }

    return 0; // original return value was uint, likely ignored
}