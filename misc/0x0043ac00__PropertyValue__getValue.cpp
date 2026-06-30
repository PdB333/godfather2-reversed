// FUNC_NAME: PropertyValue::getValue
// 0043ac00: Retrieves a Value struct (8-byte data + 4-byte extra) from this PropertyValue.
// If the type at +0x06 is 0x25e3, it treats this as an array: reads value from basePtr[offset]
// where offset is at +0x00 and basePtr at +0x08.
// Otherwise, it reads the value directly from +0x08 and +0x10.

// Value structure: 12 bytes total
struct Value {
    uint64_t data;   // +0x00: 8-byte value (int64, double, or pointer)
    int32_t extra;   // +0x08: 4-byte extra field (type, flags, or secondary value)
};

// PropertyValue layout (if type != 0x25e3):
//   +0x00: ? (not used here)
//   +0x04: ? (not used)
//   +0x06: type (short)
//   +0x08: Value::data
//   +0x10: Value::extra
// If type == 0x25e3:
//   +0x00: offset (byte offset into array of Value)
//   +0x04: ? (not used)
//   +0x06: type (short; always 0x25e3)
//   +0x08: basePtr (pointer to contiguous array of Value structures)

void __thiscall PropertyValue::getValue(int *this, Value *out)
{
    short type = *(short *)((int)this + 6);
    if (type != 0x25e3) {
        // Direct value stored inline
        out->data = *(uint64_t *)(this + 2);       // +0x08
        out->extra = this[4];                       // +0x10
        return;
    }
    // Array access: offset at +0x00, base pointer at +0x08
    int offset = *this;                             // +0x00
    if (offset != 0) {
        int basePtr = this[2];                      // +0x08 (pointer to Value array)
        // Read Value at basePtr + offset (offset is byte offset, not element index)
        out->data = *(uint64_t *)(basePtr + offset);
        out->extra = *(int32_t *)(basePtr + offset + 8);
        return;
    }
    // offset is zero → return empty value
    out->data = 0;
    out->extra = 0;
}