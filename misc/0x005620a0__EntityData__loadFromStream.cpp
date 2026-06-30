// FUNC_NAME: EntityData::loadFromStream
void __thiscall EntityData::loadFromStream(void* this, void* stream)
{
    // Stream reader initialization with a hash/ID (0xbaa03366 likely identifies this data type)
    FUN_0043aff0(stream, 0xbaa03366);

    bool hasData = false;
    void** currentNode = local_1c; // linked list node pointer
    uint index = local_6c; // current index in array mode
    uint someGlobal = DAT_00e2b1a4; // global constant (likely a default value)

    while (true) {
        bool endReached;
        if (local_78 == '\0') {
            // Linked list mode: check if current node is null
            endReached = (*currentNode == nullptr);
        } else {
            // Array mode: check if index equals count
            endReached = (index == local_68);
        }
        if (endReached) break;

        hasData = true;
        void** itemPtr = &local_64; // default to local_64
        if (local_78 == '\0') {
            itemPtr = currentNode; // use linked list node
        }

        // Determine the type of the current item
        void* type;
        if (*(short*)((int)itemPtr + 6) == 0x25e3) {
            // Inline short type: type is stored as a ushort at offset 4
            type = (void*)(uint)*(ushort*)(itemPtr + 1);
        } else {
            type = itemPtr[1]; // type is a pointer
        }

        switch ((int)type) {
        case 0: // Type 0: set field at +0x40 (count?)
            if (local_78 == '\0') itemPtr = currentNode;
            *(int*)((int)this + 0x40) = (int)itemPtr[2] + 1;
            break;
        case 1: // Type 1: set byte field at +0x24
            if (local_78 == '\0') itemPtr = currentNode;
            *(uint*)((int)this + 0x24) = (uint)*(byte*)(itemPtr + 2);
            break;
        case 2: // Type 2: set field at +0x3c (count?)
            if (local_78 == '\0') itemPtr = currentNode;
            *(int*)((int)this + 0x3c) = (int)itemPtr[2] + 1;
            break;
        case 3: // Type 3: set byte field at +0x28, and if non-zero set flags
            if (local_78 == '\0') itemPtr = currentNode;
            byte b = *(byte*)(itemPtr + 2);
            *(uint*)((int)this + 0x28) = (uint)b;
            if (b != 0) {
                *(int*)((int)this + 0x44) = 1;
                *(int*)((int)this + 0x60) = 1;
            }
            break;
        case 4: // Type 4: set a vector/color at +0x50 (3 pointers + value)
            *(int*)((int)this + 0x44) = 1;
            if (local_78 == '\0') itemPtr = currentNode;
            // Handle inline vs pointer data for the vector
            if (*(short*)((int)itemPtr + 6) == 0x25e3) {
                if (*itemPtr == nullptr) {
                    itemPtr = (void**)&DAT_00e2e5d0; // default data
                } else {
                    itemPtr = (void**)((int)itemPtr[2] + (int)*itemPtr);
                }
            } else {
                itemPtr = itemPtr + 2;
            }
            void* v0 = itemPtr[0];
            void* v1 = itemPtr[1];
            void* v2 = itemPtr[2];
            *(void**)((int)this + 0x50) = v0;
            *(void**)((int)this + 0x54) = v1;
            *(void**)((int)this + 0x58) = v2;
            *(uint*)((int)this + 0x5c) = someGlobal; // default value
            break;
        case 5: // Type 5: set another vector/color at +0x70
            *(int*)((int)this + 0x60) = 1;
            if (local_78 == '\0') itemPtr = currentNode;
            if (*(short*)((int)itemPtr + 6) == 0x25e3) {
                if (*itemPtr == nullptr) {
                    itemPtr = (void**)&DAT_00e2e5d0;
                } else {
                    itemPtr = (void**)((int)itemPtr[2] + (int)*itemPtr);
                }
            } else {
                itemPtr = itemPtr + 2;
            }
            v0 = itemPtr[0];
            v1 = itemPtr[1];
            v2 = itemPtr[2];
            *(void**)((int)this + 0x70) = v0;
            *(void**)((int)this + 0x74) = v1;
            *(void**)((int)this + 0x78) = v2;
            *(uint*)((int)this + 0x7c) = someGlobal;
            break;
        case 6: // Type 6: set byte field at +0x2c
            if (local_78 == '\0') itemPtr = currentNode;
            *(uint*)((int)this + 0x2c) = (uint)*(byte*)(itemPtr + 2);
            break;
        case 7: // Type 7: set pointer field at +0x14
            if (local_78 == '\0') itemPtr = currentNode;
            *(void**)((int)this + 0x14) = itemPtr[2];
            break;
        case 8: // Type 8: set pointer field at +0x18
            if (local_78 == '\0') itemPtr = currentNode;
            *(void**)((int)this + 0x18) = itemPtr[2];
            break;
        case 9: // Type 9: set byte field at +0x30
            if (local_78 == '\0') itemPtr = currentNode;
            *(uint*)((int)this + 0x30) = (uint)*(byte*)(itemPtr + 2);
            break;
        case 0xa: // Type 10: set pointer field at +0x10
            if (local_78 == '\0') itemPtr = currentNode;
            *(void**)((int)this + 0x10) = itemPtr[2];
            break;
        case 0xb: // Type 11: set byte field at +0x34
            if (local_78 == '\0') itemPtr = currentNode;
            *(uint*)((int)this + 0x34) = (uint)*(byte*)(itemPtr + 2);
            break;
        case 0xc: // Type 12: read a sub-object (stored in local variables for later processing)
            if (local_78 == '\0') itemPtr = currentNode;
            if (*(short*)((int)itemPtr + 6) == 0x25e3) {
                if (*itemPtr == nullptr) {
                    itemPtr = (void**)&DAT_00e2e5d0;
                } else {
                    itemPtr = (void**)((int)itemPtr[2] + (int)*itemPtr);
                }
            } else {
                itemPtr = itemPtr + 2;
            }
            local_8c = itemPtr[1];
            local_88 = itemPtr[2];
            local_90 = itemPtr[0];
            local_84 = someGlobal;
            break;
        case 0xd: // Type 13: set byte field at +0x38
            if (local_78 == '\0') itemPtr = currentNode;
            *(uint*)((int)this + 0x38) = (uint)*(byte*)(itemPtr + 2);
            break;
        case 0xe: // Type 14: set pointer field at +0x1c
            if (local_78 == '\0') itemPtr = currentNode;
            *(void**)((int)this + 0x1c) = itemPtr[2];
            break;
        case 0xf: // Type 15: set pointer field at +0x20
            if (local_78 == '\0') itemPtr = currentNode;
            *(void**)((int)this + 0x20) = itemPtr[2];
            break;
        }

        // Advance to next item
        if (local_78 == '\0') {
            // Linked list mode: follow next pointer
            if ((int)index < 0) {
                local_1c = (void**)((int)currentNode + (int)*currentNode);
                FUN_0043b140(); // advance stream?
                currentNode = local_1c;
                index = local_6c;
            } else if ((int)index < (int)(local_68 - 1)) {
                local_6c = index + 1;
                local_1c = (void**)((int)currentNode + (int)*currentNode);
                currentNode = (void**)((int)currentNode + (int)*currentNode);
                index = local_6c;
            } else {
                local_1c = (void**)&DAT_01163cf8; // end marker
                currentNode = (void**)&DAT_01163cf8;
            }
        } else {
            // Array mode: advance index and read next item from bitfield
            local_6c = index + 1;
            index = local_6c;
            if (local_6c != local_68) {
                local_60 = (short)local_6c;
                if ((*(byte*)((local_6c >> 3) + local_74) & (1 << (local_6c & 7))) == 0) {
                    // Item present: read from data array
                    local_5c = *local_70;
                    local_64 = local_70;
                    local_70 = local_70 + 1;
                } else {
                    // Item absent: set to null
                    local_64 = nullptr;
                    local_5c = 0;
                }
            }
        }
    }

    // Mark as loaded
    *(int*)((int)this + 0x80) = 1;

    // If any data was read, process the sub-object from case 0xc
    if (hasData) {
        FUN_005624d0(&local_90); // likely loads sub-object into this
    }

    // Call a virtual function on the stream (likely finalize)
    (**(code**)(*(int*)((int)this + 0x8c) + 0x14))(stream);

    // Mark as fully initialized
    *(int*)((int)this + 0x84) = 1;
}