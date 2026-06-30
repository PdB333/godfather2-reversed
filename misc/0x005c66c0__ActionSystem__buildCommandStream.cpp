// FUNC_NAME: ActionSystem::buildCommandStream
void ActionSystem::buildCommandStream(int context) {
    // Save global state for later restoration
    float savedState0 = _DAT_0119d0bc;
    float saved1 = _DAT_0119d0b0;
    float saved2 = _DAT_0119d0b4;
    float saved3 = _DAT_0119d0b8;
    float saved4 = DAT_0119d0bc;
    float saved5 = DAT_0119d0c0;
    float saved6 = _DAT_0119d0c4;
    float saved7 = _DAT_0119d0c8;
    float saved8 = _DAT_0119d0cc;
    char savedFlag = PTR_DAT_00f17650->_0_1;

    beginCommandBuffer(); // FUN_005d8020

    if (DAT_0119d0ac == 1) {
        // Branch for cutscene/cinematic mode
        if (1 < DAT_01205684) {
            uint* streamPos = (uint*)(DAT_01206880 + 0x14);
            **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08; // Command header A
            *streamPos = *streamPos + 4;
            *(undefined1*)*streamPos = 0;
            *streamPos = *streamPos + 4 & 0xfffffffc; // Align to 4
        }
        int streamBase = DAT_01206880;
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8; // Command header B
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
        **(undefined4**)(streamBase + 0x14) = 8;
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;

        streamBase = DAT_01206880;
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18; // Command header C
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
        int* posPtr = (int*)(streamBase + 0x14);
        undefined4* aligned = (undefined4*)(*(int*)(streamBase + 0x14) + 3U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 1;
        aligned = (undefined4*)(*posPtr + 7U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 1;
        aligned = (undefined4*)(*posPtr + 7U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 5;
        *posPtr = *posPtr + 4;

        flushCommandBuffer(context); // FUN_005c6d40

        if (1 < DAT_01205684) {
            uint* streamPos = (uint*)(DAT_01206880 + 0x14);
            **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08;
            *streamPos = *streamPos + 4;
            *(undefined1*)*streamPos = 1;
            *streamPos = *streamPos + 4 & 0xfffffffc;
        }
        streamBase = DAT_01206880;
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8;
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
        **(undefined4**)(streamBase + 0x14) = 7;
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;

        streamBase = DAT_01206880;
        **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18;
        *(int*)(streamBase + 0x14) = *(int*)(streamBase + 0x14) + 4;
        posPtr = (int*)(streamBase + 0x14);
        aligned = (undefined4*)(*(int*)(streamBase + 0x14) + 3U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 1;
        aligned = (undefined4*)(*posPtr + 7U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 7;
        aligned = (undefined4*)(*posPtr + 7U & 0xfffffffc);
        *posPtr = (int)aligned;
        *aligned = 8;
        *posPtr = *posPtr + 4;
    }
    else if (DAT_01163cf7 != 0) {
        // Branch for interpolation update
        float factor = DAT_0119d0bc * DAT_00e3ac58;
        PTR_DAT_00f17650->_0_1 = 0;
        if (DAT_0119d0bc < DAT_00e2b1a4) {
            DAT_0119d0bc = DAT_0119d0bc - factor;
        }

        flushCommandBuffer(context);

        float* targetPos = (float*)(PTR_DAT_00f17654 + 0x30); // +0x30 = x, +0x34 = y (relative to object)
        float origX = *targetPos;
        float origY = *(float*)(PTR_DAT_00f17654 + 0x34);
        float newY = origY + DAT_00f17674;
        DAT_0119d0bc = factor;
        *(float*)(PTR_DAT_00f17654 + 0x30) = origX + DAT_00f17670;
        *(float*)(PTR_DAT_00f17654 + 0x34) = newY;

        flushCommandBuffer(context);

        float adjustedFactor = DAT_00f17670 * DAT_00e2b04c;
        *(float*)(PTR_DAT_00f17654 + 0x30) = *(float*)(PTR_DAT_00f17654 + 0x30) - adjustedFactor;

        flushCommandBuffer(context);

        *(float*)(PTR_DAT_00f17654 + 0x34) = *(float*)(PTR_DAT_00f17654 + 0x34) - DAT_00f17674 * DAT_00e2b04c;

        flushCommandBuffer(context);

        *(float*)(PTR_DAT_00f17654 + 0x30) = *(float*)(PTR_DAT_00f17654 + 0x30) + adjustedFactor;

        flushCommandBuffer(context);

        // Restore saved global state
        _DAT_0119d0b0 = saved1;
        _DAT_0119d0b4 = saved2;
        _DAT_0119d0b8 = saved3;
        DAT_0119d0bc = saved4;
        DAT_0119d0c0 = saved5;
        _DAT_0119d0c4 = saved6;
        _DAT_0119d0c8 = saved7;
        _DAT_0119d0cc = saved8;
        *(float*)(PTR_DAT_00f17654 + 0x30) = origX;
        PTR_DAT_00f17650->_0_1 = savedFlag;
        *(float*)(PTR_DAT_00f17654 + 0x34) = origY;
        return;
    }

    flushCommandBuffer(context);
}