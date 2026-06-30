// FUNC_NAME: FrustumCullNode::update
byte FrustumCullNode::update(float* this, Camera* pCamera) {
    float fCameraX;    // From pCamera +0x70
    float fCameraY;    // From pCamera +0x78
    float fCameraZ;    // From pCamera +0x74
    float fCountdown;  // this[0xb] (+0x2C)
    int iTestResult;
    float *pfChild;
    int iChildIndex;
    byte bFinalVisible;
    int iLoopIndex;     // Used as float in loop, but integer increment
    float fChildCount;  // Actually used as float, but holds integer

    // Global cull count (profile)
    g_CullTotalCount++;

    // Decrement the node's own visibility timeout (if >0)
    fCountdown = this[0x0B]; // +0x2C
    if ((int)fCountdown > 0) {
        this[0x0B] = (float)((int)fCountdown - 1);
        g_CullTimeoutDecrements++;
    }

    bFinalVisible = 1; // Assume visible initially

    // Only cull the node itself if it contains sub-objects? 
    // Actually the condition checks if child count != 0 (this[0x13] != 0.0)
    // If no children, skip the immediate frustum test
    if (this[0x13] != 0.0) {
        // Test if camera position is outside the node's bounding box
        // Bounding box stored as: minX (this[0]), minZ (this[1]), minY (this[2]),
        //                       maxX (this[4]), maxZ (this[5]), maxY (this[6])
        fCameraX = *(float *)(pCamera + 0x70);
        fCameraY = *(float *)(pCamera + 0x78);
        fCameraZ = *(float *)(pCamera + 0x74);

        // Check if camera is outside the box (including on the boundary)
        if (fCameraX < this[0] || fCameraX == this[0] || this[4] <= fCameraX ||
            fCameraY < this[2] || fCameraY == this[2] || this[6] <= fCameraY ||
            fCameraZ < this[1] || fCameraZ == this[1] || this[5] <= fCameraZ) {
            // Outside frustum
            iTestResult = FUN_004bdde0(pCamera + 0x80); // Camera state check
            if (iTestResult != 2) {
                // If no forced visibility and the node's timeout has expired
                if ((int)fCountdown <= 0) {
                    bFinalVisible = FUN_00427f70() & 1; // Possibly get global visibility override
                }
                // NOTE: If timeout still positive, node remains visible even though outside
            }
        } else {
            // Inside frustum
            g_CullInsideCount++;
            this[0x0C] = -NAN; // +0x30: reset "last visible" timestamp

            // If the node has an active flag ( +0x24 ), call an activation function
            if (*(char *)(this + 9) != '\0') {
                FUN_00427e80(this, 0); // Mark as visible/active
            }

            // Clear a global table entry associated with this node's ID
            fCountdown = this[0x0A]; // +0x28: maybe "visibility ID"
            if (((uint)fCountdown < 0x200) && (g_VisibilityTable[(int)fCountdown] - 1 < 2)) {
                g_VisibilityTable[(int)fCountdown] = 0;
            }
            this[0x0A] = -NAN; // Reset ID
        }
    }

    // If the global "process children" flag is set, recurse into children
    if (g_ProcessChildren) {
        fChildCount = 0.0f;
        if (this[0x13] != 0.0) { // Has children
            iLoopIndex = 0;
            do {
                // Global cull count for child processing
                g_CullTotalCount++;

                pfChild = (float *)((int)this[0x12] + iLoopIndex); // +0x48: pointer to children array
                // Each child struct is 0x50 bytes

                // Decrement child's own countdown
                fCountdown = pfChild[0x0B];
                if ((int)fCountdown > 0) {
                    pfChild[0x0B] = (float)((int)fCountdown - 1);
                    g_CullTimeoutDecrements++;
                }

                // Frustum test for child (same logic as parent)
                fCameraX = *(float *)(pCamera + 0x70);
                fCameraY = *(float *)(pCamera + 0x78);
                fCameraZ = *(float *)(pCamera + 0x74);

                if (fCameraX < pfChild[0] || fCameraX == pfChild[0] || pfChild[4] <= fCameraX ||
                    fCameraY < pfChild[2] || fCameraY == pfChild[2] || pfChild[6] <= fCameraY ||
                    fCameraZ < pfChild[1] || fCameraZ == pfChild[1] || pfChild[5] <= fCameraZ) {
                    // Outside
                    iTestResult = FUN_004bdde0(pCamera + 0x80);
                    if (iTestResult == 2) {
                        goto LAB_0042816c; // Inside forced
                    }
                    if ((int)fCountdown <= 0) {
                        byte bTemp = FUN_00427f70();
                        bFinalVisible = bFinalVisible & bTemp;
                    }
                } else {
                    LAB_0042816c:
                    // Inside frustum
                    g_CullInsideCount++;
                    pfChild[0x0C] = -NAN; // +0x30
                    if (*(char *)(pfChild + 9) != '\0') {
                        *(char *)(pfChild + 9) = 0; // Clear active flag
                        FUN_0049fad0(pfChild[0x10], 0); // Deactivate some resource
                    }
                    fCountdown = pfChild[0x0A];
                    if (((uint)fCountdown < 0x200) && (g_VisibilityTable[(int)fCountdown] - 1 < 2)) {
                        g_VisibilityTable[(int)fCountdown] = 0;
                    }
                    pfChild[0x0A] = -NAN;
                }

                iLoopIndex += 0x50;
                fChildCount = (float)((int)fChildCount + 1);
            } while ((uint)fChildCount < (uint)this[0x13]);
        }
    }

    return bFinalVisible;
}