// FUNC_NAME: Material::applyEnvironmentColors

void __fastcall Material::applyEnvironmentColors(void *thisPtr)
{
    byte objectTypeFlags;          // byte at object+0x88
    int timeOfDayIndex;            // return from getTimeOfDayIndex
    int objectTypeCode;            // derived from objectTypeFlags or call to getObjectTypeCode
    int objectData;                // pointer to some global object data

    // Set default color0 (probably a default ambient color)
    *(uint32_t *)((char *)thisPtr + 0x7c) = 0xc7293f9a;

    // Get the current time-of-day / lighting mode (e.g., 1=day, 2=night, etc.)
    timeOfDayIndex = getTimeOfDayIndex();

    // Dereference: this->unknown5c is a pointer to a global environment or game manager
    // Then offset +0x21dc points to an object that holds flags/per-object data
    objectData = *(int32_t *)(*(int32_t *)((char *)thisPtr + 0x5c) + 0x21dc);
    objectTypeFlags = *(uint8_t *)(objectData + 0x88);

    if ((objectTypeFlags & 1) == 0) {
        // Bit0 not set: handle based on flags 2 or 4, or deduce via function call
        if (objectTypeFlags == 2) {
            objectTypeCode = 1;
        }
        else if (objectTypeFlags == 4) {
            objectTypeCode = 2;
        }
        else {
            // Query for a subtype code using the object data
            objectTypeCode = getObjectTypeCode(objectData, *(int32_t *)((char *)thisPtr + 0x5c));
        }

        // Now set the four RGBA colors based on timeOfDayIndex and objectTypeCode
        if (timeOfDayIndex == 1) {
            if (objectTypeCode == 2) {
                *(uint32_t *)((char *)thisPtr + 0x80) = 0xf80a54f;
                *(uint32_t *)((char *)thisPtr + 0x7c) = 0x8e33704;
                *(uint32_t *)((char *)thisPtr + 0x84) = 0x3f9f0940;
                *(uint32_t *)((char *)thisPtr + 0x88) = 0xf8d3e417;
                return;
            }
            *(uint32_t *)((char *)thisPtr + 0x80) = 0x3debe12e;
            *(uint32_t *)((char *)thisPtr + 0x7c) = 0x6521b1e3;
            *(uint32_t *)((char *)thisPtr + 0x84) = 0xfcd4e3a1;
            *(uint32_t *)((char *)thisPtr + 0x88) = 0x606dc178;
            return;
        }

        // timeOfDayIndex != 1
        if (objectTypeCode == 2) {
            *(uint32_t *)((char *)thisPtr + 0x80) = 0x83594c84;
            if (timeOfDayIndex == 2) {
                *(uint32_t *)((char *)thisPtr + 0x7c) = 0x341c45fa;
            }
            else if (timeOfDayIndex == 3) {
                *(uint32_t *)((char *)thisPtr + 0x7c) = 0x880621a2;
                *(uint32_t *)((char *)thisPtr + 0x84) = 0x53646ecb;
                *(uint32_t *)((char *)thisPtr + 0x88) = 0xf1cd124a;
                return;
            }
            else if (timeOfDayIndex == 4) {
                *(uint32_t *)((char *)thisPtr + 0x7c) = 0xe4f7c3a4;
                *(uint32_t *)((char *)thisPtr + 0x84) = 0x53646ecb;
                *(uint32_t *)((char *)thisPtr + 0x88) = 0xf1cd124a;
                return;
            }
            // Default path for objectTypeCode==2 and timeOfDayIndex not 2,3,4
            *(uint32_t *)((char *)thisPtr + 0x84) = 0x53646ecb;
            *(uint32_t *)((char *)thisPtr + 0x88) = 0xf1cd124a;
            return;
        }

        // objectTypeCode != 2
        *(uint32_t *)((char *)thisPtr + 0x80) = 0x5ed1cb9;
        if (timeOfDayIndex == 2) {
            *(uint32_t *)((char *)thisPtr + 0x7c) = 0x341c45fa;
        }
        else if (timeOfDayIndex == 3) {
            *(uint32_t *)((char *)thisPtr + 0x7c) = 0x880621a2;
        }
        else if (timeOfDayIndex == 4) {
            *(uint32_t *)((char *)thisPtr + 0x7c) = 0xe4f7c3a4;
        }
        *(uint32_t *)((char *)thisPtr + 0x84) = 0x85266b56;
        *(uint32_t *)((char *)thisPtr + 0x88) = 0xf1cd124a;
    }
    else {
        // Bit0 set: different set of colors for specific time-of-day values
        if (timeOfDayIndex == 1) {
            *(uint32_t *)((char *)thisPtr + 0x80) = 0x224f1da7;
            *(uint32_t *)((char *)thisPtr + 0x7c) = 0x3bf594b6;
            *(uint32_t *)((char *)thisPtr + 0x84) = 0xeb7aae8;
            *(uint32_t *)((char *)thisPtr + 0x88) = 0x29224d6e;
            return;
        }
        if (timeOfDayIndex == 2 || timeOfDayIndex == 3 || timeOfDayIndex == 4) {
            // Compute color0 conditionally: if not timeOfDay==2, invert? (conditional subtract)
            *(uint32_t *)((char *)thisPtr + 0x7c) = (-(uint32_t)(timeOfDayIndex != 2) & 0x37f5f6f2) + 0xeac53cd8;
            *(uint32_t *)((char *)thisPtr + 0x80) = 0x13765508;
            *(uint32_t *)((char *)thisPtr + 0x84) = 0x88b50d47;
            *(uint32_t *)((char *)thisPtr + 0x88) = 0xd86dde49;
            return;
        }
    }
    // Fall-through: no changes to colors beyond the default
}