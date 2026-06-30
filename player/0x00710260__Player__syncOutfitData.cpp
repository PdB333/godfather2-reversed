// FUNC_NAME: Player::syncOutfitData
void Player::syncOutfitData(int *outfitData, bool forceUpdate)
{
    // Check debug/feature toggle
    int *globalPtr = *(int **)(DAT_012233a0 + 4);
    if (globalPtr != 0 && globalPtr != (int *)0x1f30)
    {
        int hashCheck = FUN_00625050(0xc4bc3ce7, 0);
        if (hashCheck != 0)
        {
            FUN_007e3d30(this); // likely debug update
        }
    }

    FUN_00898360(this); // base update

    // Update previous outfit index (offset 0x1F98)
    int newIndex = outfitData[0x25];
    if (newIndex != 0 && newIndex != *(int *)(this + 0x1f98))
    {
        *(int *)(this + 0x1f98) = newIndex;
    }

    // Handle outfit locked flag (byte at 0x8E6, bit0)
    if ((*(byte *)(this + 0x8e6) & 1) == 0 && 1 < (uint)outfitData[0x28])
    {
        char *namePtr = (char *)outfitData[0x27];
        if (namePtr == 0)
            namePtr = &DAT_0120546e; // default name
        FUN_00733f20(namePtr); // likely assign outfit name
    }

    // Update flags at 0x1F54 based on bits in outfitData[0x26]
    if ((*(byte *)(outfitData + 0x26) & 1) == 0)
    {
        if (((uint)outfitData[0x26] >> 2 & 1) != 0)
            *(uint *)(this + 0x1f54) &= 0xfeffffff; // clear bit 24
    }
    else
    {
        *(uint *)(this + 0x1f54) |= 0x1000000; // set bit 24
    }

    if (((uint)outfitData[0x26] >> 1 & 1) == 0)
    {
        if (((uint)outfitData[0x26] >> 3 & 1) != 0)
            *(uint *)(this + 0x1f54) &= 0xfdffffff; // clear bit 25
    }
    else
    {
        *(uint *)(this + 0x1f54) |= 0x2000000; // set bit 25
    }

    // Helper to update a resource handle at a given offset
    auto updateHandle = [this, forceUpdate](int offset, int newHandle)
    {
        int *handlePtr = (int *)(this + offset);
        if (newHandle != 0 || forceUpdate)
        {
            if (*handlePtr != 0)
                FUN_00408310(handlePtr); // release old handle
            FUN_00408260(handlePtr, newHandle); // assign new handle
        }
    };

    // Update 12 outfit item handles (indices 0-11) stored at offsets
    updateHandle(0x1fc0, outfitData[0]);
    updateHandle(0x1fc8, outfitData[1]);
    updateHandle(0x1fd0, outfitData[2]);
    updateHandle(0x1fd8, outfitData[3]);
    updateHandle(0x1fe0, outfitData[4]);
    updateHandle(0x1ff8, outfitData[5]); // note gap, likely another slot
    updateHandle(0x20d0, outfitData[6]);
    updateHandle(0x20d8, outfitData[7]);
    updateHandle(0x20e0, outfitData[8]);
    updateHandle(0x20e8, outfitData[9]);
    updateHandle(0x20f0, outfitData[10]);
    updateHandle(0x20f8, outfitData[11]);

    // Get the outfit manager singleton
    int outfitMgr = FUN_0043b870(DAT_01131018); // offsets 0x54, 0x5c
    updateHandle(outfitMgr + 0x54, outfitData[12]); // some global handle
    updateHandle(outfitMgr + 0x5c, outfitData[13]);

    // Update accessory handles (indices 14-15? Actually indices 0xE,0xF,0x10 on this)
    updateHandle(0x1cc0, outfitData[0x0e]);
    updateHandle(0x1cc8, outfitData[0x0f]);
    updateHandle(0x1cd0, outfitData[0x10]);

    // Get another manager (e.g., color/pattern manager)
    int colorMgr = FUN_0043b870(DAT_0112a9fc);
    // Update four groups of four ints (colors/patterns?) at offsets in colorMgr
    if (outfitData[0x11] != 0 || outfitData[0x12] != 0 || outfitData[0x13] != 0 || outfitData[0x14] != 0 || forceUpdate)
    {
        *(int *)(colorMgr + 0x14) = outfitData[0x11];
        *(int *)(colorMgr + 0x18) = outfitData[0x12];
        *(int *)(colorMgr + 0x1c) = outfitData[0x13];
        *(int *)(colorMgr + 0x20) = outfitData[0x14];
    }

    if (outfitData[0x15] != 0 || outfitData[0x16] != 0 || outfitData[0x17] != 0 || outfitData[0x18] != 0 || forceUpdate)
    {
        *(int *)(colorMgr + 0x48) = outfitData[0x15];
        *(int *)(colorMgr + 0x4c) = outfitData[0x16];
        *(int *)(colorMgr + 0x50) = outfitData[0x17];
        *(int *)(colorMgr + 0x54) = outfitData[0x18];
    }

    if (outfitData[0x19] != 0 || outfitData[0x1a] != 0 || outfitData[0x1b] != 0 || outfitData[0x1c] != 0 || forceUpdate)
    {
        *(int *)(colorMgr + 0x7c) = outfitData[0x19];
        *(int *)(colorMgr + 0x80) = outfitData[0x1a];
        *(int *)(colorMgr + 0x84) = outfitData[0x1b];
        *(int *)(colorMgr + 0x88) = outfitData[0x1c];
    }

    if (outfitData[0x1d] != 0 || outfitData[0x1e] != 0 || outfitData[0x1f] != 0 || outfitData[0x20] != 0 || forceUpdate)
    {
        *(int *)(colorMgr + 0xb0) = outfitData[0x1d];
        *(int *)(colorMgr + 0xb4) = outfitData[0x1e];
        *(int *)(colorMgr + 0xb8) = outfitData[0x1f];
        *(int *)(colorMgr + 0xbc) = outfitData[0x20];
    }

    // Special override if certain colors are set and a specific flag is true
    if ((outfitData[0x21] != 0 || outfitData[0x22] != 0 || outfitData[0x23] != 0 || outfitData[0x24] != 0) &&
        (colorMgr != 0 && (int *)(colorMgr + 0xe4) != 0))
    {
        int *overideColors = (int *)(colorMgr + 0xe4);
        int *obj = FUN_00446100(overideColors, 0);
        if (obj != 0)
        {
            int *subObj = FUN_00446100(obj + 0x50, 0);
            if (subObj != 0 && *(char *)(subObj + 0x1a5) != 0) // check some flag
            {
                int localColors[4];
                FUN_008e5b20(localColors, *(undefined4 *)(colorMgr + 0xe4));
                char isOnline = FUN_004209a0();
                if (isOnline == 0) // not online
                {
                    *(int *)(colorMgr + 0xb0) = localColors[0];
                    *(int *)(colorMgr + 0xb4) = localColors[1];
                    *(int *)(colorMgr + 0xb8) = localColors[2];
                    *(int *)(colorMgr + 0xbc) = localColors[3];
                }
            }
        }
    }

    // Set pose mode based on outfitData[0x2B]
    switch (outfitData[0x2b])
    {
    case 0:
        *(uint *)(this + 0x1f5c) &= 0xfffff9ff; // clear bits 9 and 10
        break;
    case 1:
        *(uint *)(this + 0x1f5c) = (*(uint *)(this + 0x1f5c) | 0x200) & 0xfffffbff; // set bit9, clear bit10
        break;
    case 2:
        *(uint *)(this + 0x1f5c) = (*(uint *)(this + 0x1f5c) & 0xfffffdff) | 0x400; // clear bit9, set bit10
        break;
    }
}