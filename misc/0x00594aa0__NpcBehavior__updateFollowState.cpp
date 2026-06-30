// FUNC_NAME: NpcBehavior::updateFollowState
void NpcBehavior::updateFollowState(void) {
    // +0x24: float posX, +0x26: float posZ, +0x2c: float detectionRange
    // +0x1f: byte flags (0x40 = hasTarget, 0x80 = debugDraw, 0x10 = something)
    // +0x2d: float someRadius, +0x2e: Entity* target
    // +0x5: Interface* with flags at offset 0x10
    // Offsets 0x44-0x4b: behavior state data
    // +0x6, +0x7, +0x8, +0x9, +0x1e: state machine fields

    float *dx, *dy; // unused
    char *debugString;
    int color, enable, count;
    float scale;
    float dot;
    char *text;
    int *ptr;
    float *fptr;
    int i1, i2, i3;
    float f1, f2, f3;
    char *cptr;
    float *f4;
    float *f5;
    int *i4;
    float *f6;
    char *c2;
    char *c3;
    char array[4]; // dummy arrays for debug drawing
    char array2[4];
    char array3[8];
    float array4[2];
    float array5[4];
    char array6[4];
    char array7[4];
    float array8[2];
    char array9[4];
    char array10[4];
    float someFloat1, someFloat2, someFloat3, someFloat4;
    char dummy[4];
    float currentPosX, currentPosZ; // from virtual call
    float distanceSquared;

    // Call virtual function to update current position (likely stores into member variables)
    (this->vtable[0x10 / 4])();

    // Compute squared distance to target or point
    distanceSquared = (currentPosX - (float)this->posX) * (currentPosX - (float)this->posX) +
                      (currentPosZ - (float)this->posZ) * (currentPosZ - (float)this->posZ);
    if (distanceSquared <= (float)this->detectionRange) {
        // Within detection range - start behavior
        debugString = array; // placeholder for debug text buffer
        this->flags |= 0x40;

        // Setup debug drawing parameters
        color = 0x3f800000; // RGBA? 1.0f alpha?
        enable = 0;
        scale = 1.0f;
        count = 0;
        text = (char*)0x594e28; // debug string "within range"
        // Call debug draw manager method (offset 0x4: beginDraw)
        (debugDrawManager->vtable[0x04 / 4])();

        // More debug drawing setup
        text = &debugString;
        c3 = array2;
        // Call method to set debug text origin (offset 0x1c)
        (debugDrawManager->vtable[0x1c / 4])();

        if ((this->flags & 0x10) != 0) {
            enable = 0;
        }

        c2 = array3;
        f4 = &scale;
        // Call method to set color (offset 0x24)
        (debugDrawManager->vtable[0x24 / 4])();

        // Draw line or sphere
        f4 = &text;
        // Call method to draw (offset 0x10)
        (debugDrawManager->vtable[0x10 / 4])();

        f4 = &scale;
        i4 = &color;
        // Call method to set transform (offset 0x2c)
        (debugDrawManager->vtable[0x2c / 4])();

        i4 = &enable;
        text = &c3;
        // Call method to push matrix (offset 0x24)
        (debugDrawManager->vtable[0x24 / 4])();

        text = &c2;
        // Call method to draw (offset 0x10)
        (debugDrawManager->vtable[0x10 / 4])();

        // Draw another line
        i3 = count;
        // Call method to set color (offset 0x24?)
        (debugDrawManager->vtable[0x10 / 4])(); // Actually offset 0x10 again? Might be different overload

        // Finalize debug drawing
        // Call method to end draw (offset 0x40)
        (debugDrawManager->vtable[0x40 / 4])();

        // Pop matrices etc.
        (debugDrawManager->vtable[0x0c / 4])(&ptr, array4);
        (debugDrawManager->vtable[0x0c / 4])(&count, array5);
        (debugDrawManager->vtable[0x0c / 4])(&text, array6);
        (debugDrawManager->vtable[0x68 / 4])(array7, &f4);
        (debugDrawManager->vtable[0x28 / 4])(&ptr, &enable);
        (debugDrawManager->vtable[0x10 / 4])(&count, &text);
        (debugDrawManager->vtable[0x28 / 4])(&i3, this + 0x28); // +0x28: unknown
        this->flags |= 0x40;
    } else {
        // Outside detection range - handle target pointer
        text = (char*)this->target;
        this->flags &= ~0x40;
        if (text != nullptr) {
            // Call a virtual function? Actually it's a method of another object
            i1 = (*(code **)(*DAT_01205590 + 0x28))(); // Some singleton function
            if (i1 != 0) {
                scale = 1.0f;
                (this->vtable[0x2c / 4])(); // virtual function
                color = this->field_0x52; // +0x52
                enable = this->field_0x51; // +0x51
                scale = (float)this->field_0x50; // +0x50
                count = this->field_0x4f; // +0x4f
                text = (char*)this->target;
                // Some operation on flags
                i3 = (int)((uint)this->flags >> 0xc) & 0xffffff01; // unknown
                (this->vtable[0x5c / 4])(); // virtual function
            }
        }
        if ((this->flags & 0x80) != 0) {
            // Debug drawing when debug flag set
            float unknownVal = (float)this->posX + DAT_00e2b04c; // Global constant
            debugString = array;
            color = 0x3f800000;
            enable = this->posZ;
            count = *this->posPtr; // +0x24
            text = (char*)0x594bb1; // debug string
            (debugDrawManager->vtable[0x04 / 4])();

            // Another line
            float val = (float)this->posX - DAT_00e2afb8; // Global constant
            text = (char*)array5;
            c3 = (char*)0x3f800000;
            color = this->posZ;
            enable = *this->posPtr;
            count = 0x594bf1; // string
            (debugDrawManager->vtable[0x04 / 4])();

            // Query interface pointer
            ptr = (int*)&someFloat1;
            i4 = &text;
            f4 = (float*)array4;
            i1 = (int**)array7;
            c2 = (char*)0x594c0e; // string
            char result = (this->vtable[0x38 / 4])(); // virtual function returning bool
            if (result == 0) {
                c2 = (char*)f4;
                i4 = (int*)0x3f800000;
                text = (char*)this->posZ;
                c3 = (char*)this->posX;
                ptr = (int*)*this->posPtr;
                i3 = (int*)0x594c46; // string
                (debugDrawManager->vtable[0x04 / 4])();
            }
            if (DAT_00e2b05c < (float)this->someRadius) {
                c2 = (char*)&text;
                i4 = (int*)0x594c69; // string
                (this->vtable[0x10 / 4])(); // virtual function
                if ((this->interfacePtr != nullptr) && ((*(byte*)this->interfacePtr & 4) != 0)) {
                    i4 = (int*)&someFloat2;
                    text = (char*)0x594c8a; // string
                    (debugDrawManager->vtable[0x40 / 4])();
                    text = (char*)&someFloat3;
                    c3 = (char*)(this->interfacePtr + 0x10);
                    ptr = (int*)0x594ca6; // string
                    (debugDrawManager->vtable[0x48 / 4])();
                    ptr = &text;
                    i3 = (int*)array9;
                    f4 = f5;
                    i1 = (int**)0x594cc5; // string
                    (debugDrawManager->vtable[0x18 / 4])();
                    i1 = (int**)&text;
                    c2 = array5;
                    (debugDrawManager->vtable[0x18 / 4])(&f4);
                }
                // Save state
                this->field_0x48 = this->someRadius;
                this->field_0x45 = (int)c3;
                this->field_0x46 = (int)text;
                this->field_0x47 = count;
                this->field_0x49 = (int)ptr;
                this->field_0x4a = (int)f4;
                this->field_0x44 = 0;
                this->field_0x4b = (int)f5;
                this->field_6 = 0;
                *(short*)(this + 0x1c) = 1; // +0x7 as short
                *(short*)((int)this + 0x1e) = 2;
                this->field_9 = (int)(this + 0x44);
                *(short*)(this + 0x20) = 1; // +0x8 as short
                this->flags_base &= 0xfffffffc; // +0x4
                return;
            }
            // Second debug path
            if ((this->interfacePtr != nullptr) && ((*(byte*)this->interfacePtr & 4) != 0)) {
                ptr = (int*)&someFloat1;
                i4 = (int*)0x594d99; // string
                (debugDrawManager->vtable[0x40 / 4])();
                i4 = &someFloat2;
                text = (char*)(this->interfacePtr + 0x10);
                c3 = (char*)0x594db5; // string
                (debugDrawManager->vtable[0x48 / 4])();
                c3 = (char*)&count;
                ptr = (int*)&someFloat4;
                i3 = &f4;
                i1 = (int**)0x594dd4; // string
                (debugDrawManager->vtable[0x18 / 4])();
                i1 = (int**)i4;
                i3 = &color;
                c2 = (char*)0x594deb; // string
                (debugDrawManager->vtable[0x10 / 4])();
            }
            ptr = (int*)f4;
            i4 = (int*)0x594df9; // string
            (this->vtable[0x14 / 4])(); // virtual function
            return;
        }
    }
}