// FUNC_NAME: PlayerFamilyTree::setupActionPointers
void __thiscall PlayerFamilyTree::setupActionPointers(uint *this, bool enableExtras)
{
    uint *in_EAX;
    uint uVar1;

    // Setup action pointers based on tree level (first element of array is level count?)
    if (7 < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x158) = &LAB_004e9870;  // +0x158: action pointer
        *(uint *)(uVar1 + 0x160) = (uint)this;       // +0x160: context pointer
        if (7 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x170) = &LAB_004e9980;
            *(uint *)(uVar1 + 0x178) = (uint)this;
        }
    }

    if (8 < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x188) = &LAB_004e9870;
        *(uint *)(uVar1 + 400) = (uint)this;         // +0x190
        if (8 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x1a4) = &LAB_004e9960;
            *(uint *)(uVar1 + 0x1ac) = (uint)this;
        }
    }

    if (10 < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x1e8) = &LAB_004e9870;
        *(uint *)(uVar1 + 0x1f0) = (uint)this;
        if (10 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x204) = &LAB_004e9960;
            *(uint *)(uVar1 + 0x20c) = (uint)this;
        }
    }

    if (0xd < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x274) = &LAB_004e9870;
        *(uint *)(uVar1 + 0x27c) = (uint)this;
    }

    if (0xd < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x290) = &LAB_004e98a0;
        *(uint *)(uVar1 + 0x298) = (uint)this;
    }

    if (enableExtras) {
        if (2 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x80) = FUN_004e99d0;
            *(uint *)(uVar1 + 0x88) = (uint)this;
        }
        if (0x10 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 800) = &LAB_004e99c0;  // +0x320
            *(uint *)(uVar1 + 0x328) = (uint)this;
        }
        if (0x12 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x364) = &LAB_004e98b0;
            *(uint *)(uVar1 + 0x36c) = (uint)this;
        }
        if (0x13 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x394) = &LAB_004e98c0;
            *(uint *)(uVar1 + 0x39c) = (uint)this;
        }
        if (0x14 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x3c4) = &LAB_004e98e0;
            *(uint *)(uVar1 + 0x3cc) = (uint)this;
            if (0x14 < *this) {
                uVar1 = this[1];
                *(void **)(uVar1 + 0x3e0) = &LAB_004e9900;
                *(uint *)(uVar1 + 1000) = (uint)this;  // +0x3e8
            }
        }
        if (0x15 < *this) {
            uVar1 = this[1];
            *(void **)(uVar1 + 0x3f4) = &LAB_004e9930;
            *(uint *)(uVar1 + 0x3fc) = (uint)this;
            if (0x15 < *this) {
                uVar1 = this[1];
                *(void **)(uVar1 + 0x410) = &LAB_004e9940;
                *(uint *)(uVar1 + 0x418) = (uint)this;
            }
        }
    }

    if (0x19 < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x4b4) = &LAB_004e9950;
        *(uint *)(uVar1 + 0x4bc) = (uint)this;
    }

    if (0x17 < *this) {
        uVar1 = this[1];
        *(void **)(uVar1 + 0x470) = &LAB_004e9960;
        *(uint *)(uVar1 + 0x478) = (uint)this;
    }
}