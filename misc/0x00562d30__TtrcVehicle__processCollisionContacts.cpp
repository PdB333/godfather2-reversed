// FUNC_NAME: TtrcVehicle::processCollisionContacts
void __thiscall TtrcVehicle::processCollisionContacts(int param_2, int param_3, CollisionResult* result) {
    // TLS profiling start
    LPVOID tls = TlsGetValue(DAT_01139830);
    if (*(undefined4**)((int)tls + 4) < *(undefined4**)((int)tls + 0xc)) {
        **(undefined4**)((int)tls + 4) = "TtrcVehicle";
        unsigned __int64 timestamp = rdtsc();
        *(*(undefined4**)((int)tls + 4) + 1) = (int)timestamp;
        *(undefined4**)((int)tls + 4) += 3;
    }

    // Get collision node from vehicle component
    VehicleComponent* comp = *(VehicleComponent**)(this + 0x10);
    CollisionNode* node = nullptr;
    int nodeBase = *(int*)(*(int*)(comp + 8) + 0x70);
    if (nodeBase != 0) {
        node = (CollisionNode*)(nodeBase + 0x10);
    }

    int compFlags = *(int*)(this + 0xc);
    CollisionShape** shapeList = *(CollisionShape***)(comp + 0xc0);
    int shapeCount = *(int*)(comp + 0xc4) - 1;  // last index
    int collisionCounter = 0;
    int bestShapeIndex = 0;
    int bestUserData = 0;

    // Outer loop over collision shapes
    for (int i = shapeCount; i >= 0; --i) {
        CollisionShape* shape = *shapeList;
        if (shape != nullptr) {
            // Get the shape's transformation matrix (float[4][4])
            float* shapeMatrix = (float*)(*(int*)(*shapeList) + 8);

            // Transform input position (param_2 + 0x30-0x38) into object local space
            float dx = *(float*)(param_2 + 0x38) - shapeMatrix[0xe];
            float dy = *(float*)(param_2 + 0x30) - shapeMatrix[0xc];
            float dz = *(float*)(param_2 + 0x34) - shapeMatrix[0xd];
            float localX = shapeMatrix[0] * dy + dx * shapeMatrix[2] + dz * shapeMatrix[1];
            float localY = shapeMatrix[6] * dx + shapeMatrix[5] * dz + shapeMatrix[4] * dy;
            float localZ = shapeMatrix[10] * dx + shapeMatrix[9] * dz + shapeMatrix[8] * dy;

            // Transform second position (param_2 + 0x40-0x48) similarly
            float dx2 = *(float*)(param_2 + 0x48) - shapeMatrix[0xe];
            float dy2 = *(float*)(param_2 + 0x40) - shapeMatrix[0xc];
            float dz2 = *(float*)(param_2 + 0x44) - shapeMatrix[0xd];
            float localX2 = shapeMatrix[0] * dy2 + dx2 * shapeMatrix[2] + dz2 * shapeMatrix[1];
            float localY2 = shapeMatrix[6] * dx2 + shapeMatrix[5] * dz2 + shapeMatrix[4] * dy2;
            float localZ2 = shapeMatrix[10] * dx2 + shapeMatrix[9] * dz2 + shapeMatrix[8] * dy2;

            // Shape type check: 0xB = 11 (probably convex hull/box)
            if (shape->type == 0xB) {
                // Inner loop over user data (already associated with this shape)
                int userDataCount = *(int*)(this + 0x28);
                int* userDataArray = *(int**)(this + 0x24);
                for (int j = 0; j < userDataCount; ++j) {
                    int* userEntry = userDataArray + j * 3;  // 12 bytes per entry
                    if (*userEntry == *shapeList) {
                        int userBase = userEntry[1];
                        int userOffset = (userBase != 0) ? (userBase + 0x10) : 0;
                        bool hit = node->vtable->checkCollision(&localX, userBase, userOffset, userEntry[2]);
                        if (hit) {
                            int* collisionPair = (int*)(nodeBase + 0x10)->vtable->getCollisionPair(userEntry[2], collisionList);
                            result->collisionCount++;
                            collisionPair[0x20 + result->collisionCount * 4] = userEntry[2];  // store user data
                            result->bestShape = *shapeList;
                            bestUserData = userEntry[2];
                            bestShapeIndex = *shapeList;
                        }
                    }
                }
            } else {
                // Direct shape-level collision test
                bool hit = shape->vtable->testCollision(&localX, result);
                if (hit) {
                    result->bestShape = *shapeList;
                }
            }
        }
        ++shapeList;
    }

    // If best shape was found during inner loop, record it
    if (bestShapeIndex != 0) {
        result->collisionArray[result->collisionCount] = bestUserData;
        result->bestShape = bestShapeIndex;
    }

    // If we have a best shape, finalize collision
    if (result->bestShape != 0) {
        FUN_00aa2cd0(*(int*)(result->bestShape + 8), result);
    }

    // TLS profiling end
    LPVOID tls2 = TlsGetValue(DAT_01139830);
    if (*(undefined4**)((int)tls2 + 4) < *(undefined4**)((int)tls2 + 0xc)) {
        **(undefined4**)((int)tls2 + 4) = &DAT_00e39c6c;
        unsigned __int64 timestamp2 = rdtsc();
        *(*(undefined4**)((int)tls2 + 4) + 1) = (int)timestamp2;
        *(undefined4**)((int)tls2 + 4) += 3;
    }
}