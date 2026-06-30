// FUNC_NAME: Node::operator=
// Address: 0x006e03b0
// Role: Assignment operator for a doubly-linked list node.
//   Handles relinking of the next/prev pointers when the next pointer changes,
//   then copies all other fields from source to destination.
// Struct offsets:
//   +0x00: next (int*)
//   +0x04: prev (int*)
//   +0x08: byte field (flags/category)
//   +0x0C: int64 field (timestamp/id)
//   +0x14: int field
//   +0x18: byte field
//   +0x1C..+0x98: int fields (various data)
//   +0x98..+0xB8: int64 fields (multiple 8-byte values)

int* __thiscall Node::operator=(int* source)
{
    if (this != source) {
        int* oldNext = this->next;
        int* newNext = source->next;
        if (oldNext != newNext) {
            if (oldNext != 0) {
                releaseNode(oldNext); // FUN_004daf90 – releases the old successor
            }
            this->next = newNext; // update next pointer
            if (newNext != 0) {
                newNext->prev = this; // fix back link of new successor
            }
        }
    }

    // Copy all data fields after the linked list pointers
    *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 8) =
        *reinterpret_cast<char*>(reinterpret_cast<char*>(source) + 8);

    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 12) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 12);

    this->field5 = source->field5;        // +0x14
    *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 24) =
        *reinterpret_cast<char*>(reinterpret_cast<char*>(source) + 24); // +0x18

    this->field7 = source->field7;        // +0x1C
    this->field8 = source->field8;
    this->field9 = source->field9;
    this->field10 = source->field10;
    this->field11 = source->field11;
    this->field12 = source->field12;      // +0x30
    // Continue through fields up to +0x98 (index 0x26)
    for (int i = 13; i <= 0x25; ++i) {
        this->fields[i] = source->fields[i];
    }
    // Then copy 8-byte chunks from +0x98 to +0xB8
    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 0x98) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 0x98);
    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 0xA0) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 0xA0);
    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 0xA8) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 0xA8);
    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 0xB0) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 0xB0);
    *reinterpret_cast<__int64*>(reinterpret_cast<char*>(this) + 0xB8) =
        *reinterpret_cast<__int64*>(reinterpret_cast<char*>(source) + 0xB8);

    return this;
}