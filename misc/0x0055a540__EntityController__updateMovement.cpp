// FUNC_NAME: EntityController::updateMovement
void __thiscall EntityController::updateMovement(float thisPtr, int* context) {
    // context is a pointer to a Context struct with many fields.
    // if context[8] == 1, skip processing.
    if (context[8] == 1) {
        return;
    }

    // Traverse the first linked list (context[0]) to get the last node.
    int nodeA = context[0];
    int lastA = nodeA;
    for (int next = *(int*)(nodeA + 0xc); next != 0; next = *(int*)(next + 0xc)) {
        lastA = next;
    }

    // Traverse the second linked list (context[1]) to get the last node.
    int nodeB = context[1];
    int lastB = nodeB;
    for (int next = *(int*)(nodeB + 0xc); next != 0; next = *(int*)(next + 0xc)) {
        lastB = next;
    }

    // Check flags: node->byteAt(0x10) gives a relative base? Then check flag at offset 0x80.
    char flagA = *(char*)(*(char*)(lastA + 0x10) + 0x80 + lastA);
    char flagB = *(char*)(*(char*)(lastB + 0x10) + 0x80 + lastB);
    if (flagA != '\x01' || flagB != '\x01') {
        return;
    }

    // Re-compute lastA from context[0]? Actually re-traverse to get last node again.
    int tempA = context[0];
    int lastNodeA = tempA;
    for (int next = *(int*)(tempA + 0xc); next != 0; next = *(int*)(next + 0xc)) {
        lastNodeA = next;
    }

    // Compare node base + byte at +0x10 with context[3].
    if (*(char*)(lastNodeA + 0x10) + lastNodeA == context[3]) {
        // Get last node of context[1] instead.
        tempA = context[1];
        lastNodeA = tempA;
        for (int next = *(int*)(tempA + 0xc); next != 0; next = *(int*)(next + 0xc)) {
            lastNodeA = next;
        }
    } else {
        // Recompute lastNodeA again by traversing context[0] from start.
        tempA = context[0];
        lastNodeA = tempA;
        for (int next = *(int*)(tempA + 0xc); next != 0; next = *(int*)(next + 0xc)) {
            lastNodeA = next;
        }
    }

    char state = *(char*)(*(char*)(lastNodeA + 0x10) + 0xd8 + lastNodeA);
    local_24 = thisPtr; // keep original this as float for later

    if (state == '\a' || state == '\x06') {
        // Get physics component from this+0x34
        int physicsComp = *(int*)((int)thisPtr + 0x34);
        // Extract velocity components (position/velocity vector at +0x1a0)
        float vx = *(float*)(physicsComp + 0x1a0);
        float vy = *(float*)(physicsComp + 0x1a4);
        float vz = *(float*)(physicsComp + 0x1a8);
        // Possibly w or padding
        // local_14 = *(int*)(physicsComp + 0x1ac);

        // Check flag at this+0x28 (enable clamp)
        if (*(int*)((int)thisPtr + 0x28) != 0) {
            float limit = *(float*)((int)thisPtr + 0x14);
            if (vy < limit) {
                // Clamp vx and vz based on min values from this+0x10 and this+0x18
                if (vx < *(float*)((int)thisPtr + 0x10)) {
                    vx = *(float*)((int)thisPtr + 0x10);
                }
                if (vx < *(float*)((int)thisPtr + 0x18)) {
                    vz = *(float*)((int)thisPtr + 0x18);
                }
                FUN_004b5cf0(&vx); // normalize or clamp vector
                vy = limit;
            }
        }

        float speed = vy; // local_1c used as speed

        // Check flags at this+0x2c and this+0x30
        if (*(int*)((int)thisPtr + 0x2c) != 0 || *(int*)((int)thisPtr + 0x30) != 0) {
            int moveInput = context[4];
            // Evaluate a masked float from moveInput+0x14
            float weight = *(float*)(moveInput + 0x14);
            // Mask: (uint)weight & DAT_00e44680 -> reinterpret as float
            float masked = *(float*)&((*(int*)&weight) & DAT_00e44680);

            if (*(int*)((int)thisPtr + 0x2c) == 0 || DAT_00e2cd54 < masked) {
                if (*(int*)((int)thisPtr + 0x30) == 0) {
                    return;
                }
                if (masked <= DAT_00e2cd54) {
                    return;
                }
                speed = *(float*)((int)thisPtr + 0x20);
            } else {
                speed = *(float*)((int)thisPtr + 0x1c);
            }

            // Use an index from context[6]+0xc to look up a table
            int idx = *(unsigned char*)(context[6] + 0xc);
            float tableValue = *(float*)(DAT_00d999b8 + idx * 4);
            // Compute angle or value: divide speed by context[3]+0x84
            float divisor = *(float*)(context[3] + 0x84);
            float ratio = speed / divisor;
            // FUN_00414a80 might be a math function (sqrt, sin, etc.)
            float scaled = (float)FUN_00414a80(ratio) * tableValue;
            local_24 = scaled; // store result
            FUN_00aaa340(&local_24); // clamp or saturate
        }
    } else {
        // For other states
        int component = *(int*)((int)thisPtr + 0x24);
        if (component != 0) {
            int type = (int)FUN_00541470(*(int*)(lastNodeA + 0x1c));
            if (type == 8) {
                FUN_009f66e0(
                    context[9],
                    *(int*)((int)local_24 + 0x34),
                    0, // upper half of type?,
                    *(int*)(context[0xb] + 4),
                    DAT_00e2b1a4 / *(float*)((int)local_24 + 8),
                    0x3f800000 // 1.0f
                );
                return;
            }
            if (component != 0) {
                type = (int)FUN_00541470(*(int*)(lastNodeA + 0x1c));
                if (type == 5) {
                    FUN_009f66e0(
                        context[9],
                        *(int*)((int)local_24 + 0x34),
                        0,
                        *(int*)(context[0xb] + 4),
                        DAT_00e2b1a4 / *(float*)((int)local_24 + 0xc),
                        0x3f800000
                    );
                    return;
                }
            }
        }
    }
}