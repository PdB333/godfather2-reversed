// FUNC_NAME: Variable::setValue
// Function address: 0x00417280
// Role: Sets the value stored in a Variable object, updating both previous and current fields, and logs the change to a global event buffer if logging is enabled and the value actually changed.

class Variable {
    // Offsets:
    // +0x58: previousValue (int)
    // +0x5c: currentValue (int)
    // +0x62: flags (byte, bit 2 = logChanges)
public:
    void setValue(int newValue) {
        int oldValue = *(int*)((char*)this + 0x5c);
        *(int*)((char*)this + 0x58) = newValue;
        *(int*)((char*)this + 0x5c) = newValue;

        if ((*(unsigned char*)((char*)this + 0x62) & 0x4) != 0 && oldValue != newValue) {
            // Log the change: write an entry to the global event buffer
            // The buffer is managed through a write pointer stored at DAT_01206880 + 0x14
            uint** writePtr = (uint**)(DAT_01206880 + 0x14);   // pointer to current buffer position
            uint* buffer = *writePtr;

            // Write log entry structure:
            //   [0]: vtable pointer (PTR_LAB_011246e0)
            //   [1]: object pointer (this)
            //   [2]: new value as 16-bit short, padded to 4 bytes
            *(void**)buffer = (void*)&PTR_LAB_011246e0;
            buffer++;
            *(int*)buffer = (int)this;
            buffer++;
            *(short*)buffer = (short)newValue;

            // Advance write pointer by 5 bytes from after the short, then align down to 4
            *writePtr = (uint*)(((uint)(buffer + 1) + 5) & 0xfffffffc);
        }
    }
};

// External symbols used:
// - DAT_01206880: global structure, offset 0x14 holds a pointer to the current write position in the event log buffer.
// - PTR_LAB_011246e0: vtable address for a log entry class.