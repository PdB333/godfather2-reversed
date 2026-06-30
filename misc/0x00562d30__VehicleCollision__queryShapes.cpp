// FUNC_NAME: VehicleCollision::queryShapes

void __thiscall VehicleCollision::queryShapes( VehicleCollision *thisPtr, const CollisionAABB *aabb, int unusedParam, CollisionResults *results )
{
    // Profiling scope for vehicle collision detection
    LPVOID tlsValue = TlsGetValue( DAT_01139830 );
    uint *tlsData = *(uint **)( tlsValue + 4 );
    if ( tlsData < *(uint **)( tlsValue + 0xC ) )
    {
        *tlsData = (uint)"TtrcVehicle";
        unsigned long long startCycle = rdtsc();
        tlsData[1] = (uint)startCycle;
        *(uint **)( tlsValue + 4 ) = tlsData + 3;
    }

    int thisAddr = (int)thisPtr;  // saved because this might be modified

    // Get the physics world or collision manager from this+0x10
    int worldData = *(int *)( *(int *)( thisPtr + 0x10 ) + 8 );
    void *worldRoot = ( worldData != 0 ) ? (void *)( worldData + 0x10 ) : 0;

    int collisionBufferIndex = *(int *)( thisPtr + 0xC );  // +0xC

    // Shapes list: pointer and count (count-1)
    int **shapeListArray = *(int ***)( *(int *)( thisPtr + 0x10 ) + 0xC0 );
    int shapeListCount = *(int *)( *(int *)( thisPtr + 0x10 ) + 0xC4 ) - 1;

    int bestShapeNodePtr = 0;
    int bestShapeListIdx = 0;
    int foundShapeIdx = 0;

    for ( int shapeIdx = shapeListCount; shapeIdx >= 0; shapeIdx-- )
    {
        int *shapeListItem = *shapeListArray;  // shapeListItem points to a ShapeNode*
        if ( shapeListItem != 0 )
        {
            ShapeNode *shapeNode = (ShapeNode *)*shapeListItem;  // dereference once more
            float *shapeTransform = (float *)( (int *)shapeNode[2] ); // +8

            // Transform the two points of the AABB into shape's local space
            float dx1 = aabb->mMax.x - shapeTransform[0xE];
            float dx2 = aabb->mMin.x - shapeTransform[0xC];
            float dy  = aabb->mMax.y - shapeTransform[0xD];  // Actually careful: mMax.y - shapeTransform[0xD]? The original code uses param_2+0x34 - pfVar2[0xd] but then later uses pfVar2[1]? Let's re-check: original has fVar10 = *(float *)(param_2+0x30) - pfVar2[0xc]; fVar11 = *(float *)(param_2+0x34) - pfVar2[0xd]; fVar12 = *(float *)(param_2+0x38) - pfVar2[0xe]; So it uses both points? Actually first block uses pos at 0x30,0x34,0x38 (likely min) and second block uses 0x40,0x44,0x48 (max). So we need two sets.

            // First point (min)
            float px = aabb->mMin.x - shapeTransform[0xC];
            float py = aabb->mMin.y - shapeTransform[0xD];
            float pz = aabb->mMin.z - shapeTransform[0xE];

            // Second point (max)
            float qx = aabb->mMax.x - shapeTransform[0xC];
            float qy = aabb->mMax.y - shapeTransform[0xD];
            float qz = aabb->mMax.z - shapeTransform[0xE];

            // Transform to local space using shapeTransform (3x4 rotation+translation matrix)
            // The original code uses:
            // fStack_240 = *pfVar2 * fVar10 + fVar12 * pfVar2[2] + fVar11 * pfVar2[1];  (for first point)
            // fStack_23c = pfVar2[6] * fVar12 + pfVar2[5] * fVar11 + pfVar2[4] * fVar10;
            // fStack_238 = pfVar2[10] * fVar12 + pfVar2[9] * fVar11 + pfVar2[8] * fVar10;
            // And similar for second point. So the matrix order is:
            // row0: pfVar2[0], pfVar2[1], pfVar2[2]  (note: original uses pfVar2[1] for y)
            // row1: pfVar2[4], pfVar2[5], pfVar2[6]
            // row2: pfVar2[8], pfVar2[9], pfVar2[10]
            // Actually careful: For first point they use *pfVar2 * fVar10 (x), pfVar2[2] * fVar12 (z), pfVar2[1] * fVar11 (y). So it's row0: [0], [1], [2] mapping to (x, y, z)? Wait order: fStack_240 = *pfVar2 * fVar10 + pfVar2[2] * fVar12 + pfVar2[1] * fVar11. So coefficients: [0] for x, [2] for z, [1] for y. That is unusual. Possibly the matrix is column-major or the transform is from local to world? Actually the subtraction is (world - shapeTransform[0xC..E]) which gives world position relative to shape origin, then multiply by matrix. If the matrix is shape-to-world rotation, then local = inv(rot) * (world - pos). But the pattern shows something else. Given the complexity, I'll just replicate the formula.

            float localPx = shapeTransform[0] * px + shapeTransform[2] * pz + shapeTransform[1] * py;
            float localPy = shapeTransform[6] * pz + shapeTransform[5] * py + shapeTransform[4] * px;
            float localPz = shapeTransform[10] * pz + shapeTransform[9] * py + shapeTransform[8] * px;
            float localQx = shapeTransform[0] * qx + shapeTransform[2] * qz + shapeTransform[1] * qy;
            float localQy = shapeTransform[6] * qz + shapeTransform[5] * qy + shapeTransform[4] * qx;
            float localQz = shapeTransform[10] * qz + shapeTransform[9] * qy + shapeTransform[8] * qx;

            // Check shape type
            if ( shapeNode->type == 0xB ) // e.g., kShapeTypeTerrain
            {
                // More complex search: iterate over a separate list of "registry" entries
                int registryCount = *(int *)( thisPtr + 0x28 );
                for ( int i = 0; i < registryCount; i++ )
                {
                    int *registryEntry = (int *)( *(int *)( thisPtr + 0x24 ) + i * 0xC );
                    if ( registryEntry[0] == (int)shapeListArray ) // pointer comparison?
                    {
                        int entryData = registryEntry[1];
                        void *entryVtable = entryData ? (void *)( entryData + 0x10 ) : 0;
                        char earlyOut = 0;
                        // Call virtual function on worldRoot: (**(code **)*worldRoot)( &earlyOut, &localP, entryData, entryVtable, registryEntry[2] );
                        bool hit = ( (int (__thiscall *)( void *, CollisionAABB_Transformed *, int, void *, int )) ( *(int **)worldRoot )[0] )
                                    ( worldRoot, &localAABB, entryData, entryVtable, registryEntry[2] );

                        thisPtr = (VehicleCollision *)thisAddr; // restore this after call

                        if ( hit )
                        {
                            // Get collision shape from entry
                            void *shapeData = (void *)( *(int (__thiscall *)( int, char * )) ( *(int *)( entryData + 0x10 ) + 0x14 ) )
                                                ( registryEntry[2], localBuffer );
                            results->mCollisionCount++;
                            // Call virtual on shapeData: (**(code **)(*shapeData + 0x20))( &hitResult, &shapeIdx, results );
                            ((int (__thiscall *)( void *, int *, CollisionResults * )) ( *(int **)shapeData )[8] ( shapeData, &shapeIdx, results );

                            if ( earlyOut )
                            {
                                bestShapeNodePtr = registryEntry[2];
                                bestShapeListIdx = *shapeListArray;  // store pointer
                            }
                            results->mCollisionCount--;
                            thisPtr = (VehicleCollision *)thisAddr;
                        }
                    }
                }
            }
            else
            {
                // Direct collision query against shape using virtual function at +0x20
                char collisionResult = 0;
                ( (int (__thiscall *)( ShapeNode *, CollisionAABB_Transformed *, CollisionResults * )) ( *(int **)shapeNode )[8] )
                    ( shapeNode, &localAABB, results );

                shapeIdx = shapeListCount; // unused? Actually the original code sets iStack_248 = iVar8 after call
                if ( collisionResult )
                {
                    results->mFirstHitShapePtr = *shapeListArray;
                }
            }
        }
        shapeListArray++;
        shapeListCount = shapeIdx;
    }

    // If a specific best shape was found, store it in results
    if ( foundShapeIdx != 0 )
    {
        results->mHitList[ results->mCollisionCount ] = bestShapeNodePtr;
        results->mFirstHitShapePtr = bestShapeListIdx;
    }

    // Finalize collision response if any shape was hit
    if ( results->mFirstHitShapePtr != 0 )
    {
        FUN_00aa2cd0( *(int *)( results->mFirstHitShapePtr + 8 ), results );
    }

    // Exit profiling scope
    tlsValue = TlsGetValue( DAT_01139830 );
    tlsData = *(uint **)( tlsValue + 4 );
    if ( tlsData < *(uint **)( tlsValue + 0xC ) )
    {
        *tlsData = (uint)&DAT_00e39c6c;   // end marker
        unsigned long long endCycle = rdtsc();
        tlsData[1] = (uint)endCycle;
        *(uint **)( tlsValue + 4 ) = tlsData + 3;
    }
}