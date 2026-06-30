// FUN_004a45d0: ActiveObject::processUpdates
void __thiscall ActiveObject::processUpdates()
{
    bool somethingDone = false;

    // Check and clear flag in +0x80 bit 8 (0x80), then call handler (likely deactivate peripheral)
    if ((field_0x10 != 0) && ((flags80 & 0x0008) != 0)) {
        flags80 &= 0xFFF7;        // clear bit 3
        FUN_004a5bb0();           // e.g., stopSound()
    }

    // Check and clear flag in +0x82 bit 0, call handler
    if ((flags82 & 0x01) != 0) {
        flags82 &= 0xFE;
        FUN_004a67a0();           // e.g., deactivateChild()
    }

    // Process active bitmap (+0x40/+0x44) – 64-bit mask of indices in activeObjectArray (+0x5c)
    if ((flags82 & 0x20) != 0) {
        uint32_t bitmapLow = *(uint32_t*)(this + 0x40);
        uint32_t bitmapHigh = *(uint32_t*)(this + 0x44);
        if (bitmapLow != 0 || bitmapHigh != 0) {
            somethingDone = true;
            do {
                // Find lowest set bit via De Bruijn multiplication
                uint64_t bits = ((uint64_t)bitmapHigh << 32) | bitmapLow;
                uint64_t lowestBit = bits & -(int64_t)bits;
                // Compute index from lowestBit using magic constant 0x3f79d71b4cb0a89
                int index = (int)__aullshr(__allmul(lowestBit, 0xb4cb0a89, 0x3f79d71)); // high part of mul

                // Call virtual method at offset 0x2c on the object at activeObjectArray[index]
                void* obj = *(void**)(*(int*)(this + 0x5c) + index * 4);
                (**(void (__thiscall**)(void*))(*(int*)obj + 0x2c))(obj);

                // Clear the bit we just processed
                uint64_t shiftVal = __allshl(1, index, 0);
                bitmapLow &= ~(uint32_t)shiftVal;
                bitmapHigh &= ~(uint32_t)(shiftVal >> 32);
            } while (bitmapLow != 0 || bitmapHigh != 0);
        }
    }

    // Process entries in +0x74 array (8-byte structs, count at +0x78)
    if ((flags82 & 0x02) != 0 && *(int*)(this + 0x78) != 0) {
        for (uint32_t i = 0; i < *(uint32_t*)(this + 0x78); i++) {
            uint8_t* entry = (uint8_t*)(*(int*)(this + 0x74) + i * 8);
            void* obj = *(void**)entry;
            uint8_t flags = *(uint8_t*)(entry + 4);
            if ((flags & 0x08) != 0) {
                // Call virtual 0x2c on this object
                (**(void (__thiscall**)(void*))(*(int*)obj + 0x2c))(obj);
                somethingDone = true;

                // If extra flag (+0x82 bit 2) and childArray64 exists, check for matching callback
                if ((flags82 & 0x04) != 0 && *(int*)(this + 0x6c) != 0) {
                    for (uint32_t j = 0; j < *(uint32_t*)(this + 0x6c); j++) {
                        uint8_t* childEntry = (uint8_t*)(*(int*)(this + 0x68) + j * 0x10);
                        uint16_t childFlags = *(uint16_t*)(childEntry + 4);
                        if ((childFlags & 0x0002) != 0 && (childFlags & 0x0010) != 0) {
                            void* childObj = *(void**)childEntry;
                            // Virtual method at +0x80 returns something (maybe a parent pointer)
                            int returnVal = (**(int (__thiscall**)(void*))(*(int*)childObj + 0x80))(childObj);
                            if (returnVal == (int)obj) {
                                // Call virtual 0x30 on child
                                (**(void (__thiscall**)(void*))(*(int*)childObj + 0x30))(childObj);
                            }
                        }
                    }
                }
            }
        }
    }

    // Process children in +0x68 array with flag bit 3 (0x08)
    if ((flags82 & 0x08) != 0 && *(int*)(this + 0x6c) != 0) {
        for (uint32_t i = 0; i < *(uint32_t*)(this + 0x6c); i++) {
            uint8_t* entry = (uint8_t*)(*(int*)(this + 0x68) + i * 0x10);
            uint16_t childFlags = *(uint16_t*)(entry + 4);
            if ((childFlags & 0x0002) != 0 && (childFlags & 0x0008) != 0) {
                void* obj = *(void**)entry;
                (**(void (__thiscall**)(void*))(*(int*)obj + 0x2c))(obj);
                somethingDone = true;
            }
        }
    }

    // If no action was taken, remove this object from the global active list
    if (!somethingDone) {
        // Unlink doubly linked list (prev +0x84, next +0x88)
        if (*(int*)(this + 0x84) != 0) {
            *(int*)(*(int*)(this + 0x84) + 0x88) = *(int*)(this + 0x88);
        }
        if (*(int*)(this + 0x88) != 0) {
            *(int*)(*(int*)(this + 0x88) + 0x84) = *(int*)(this + 0x84);
        }
        if (g_ActiveListHead == this) {
            g_ActiveListHead = (ActiveObject*)*(int*)(this + 0x88);
        }
        if (g_ActiveListTail == this) {
            g_ActiveListTail = (ActiveObject*)*(int*)(this + 0x84);
        }
        *(int*)(this + 0x88) = 0;
        *(int*)(this + 0x84) = 0;
    }
}