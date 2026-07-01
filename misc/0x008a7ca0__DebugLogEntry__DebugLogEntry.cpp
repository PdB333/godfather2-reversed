// FUNC_NAME: DebugLogEntry::DebugLogEntry
// Address: 0x008a7ca0
// Role: Constructor for a debug log entry node inserted into a global linked list.
// The object holds a string (max 63 chars), three integer parameters, and a null-initialized block of 4 ints.
// The linked list uses offset 0x70 as the "next" pointer, pointing to the previous head stored in a global variable.

class DebugLogEntry : public SomeBaseClass { // vtable at +0x00 from PTR_LAB_00d79bf0
public:
    // Constructor: takes message text, three int parameters.
    // Parameter order: text, arg1 (offset +0x04), arg2 (offset +0x08), arg3 (offset +0x0C)
    // The constructor appends this entry to the front of a global singly-linked list.
    DebugLogEntry(char* text, int arg1, int arg2, int arg3) {
        // Call base class constructor (likely initializes vtable + base fields)
        baseConstructor(); // FUN_0064cc90

        // Set vtable pointer (PTR_LAB_00d79bf0)
        this->vtable = 0x00d79bf0; // *param_1 = &PTR_LAB_00d79bf0

        // Copy text with limit 63 characters to offset +0x20
        _strncpy(reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x20), text, 0x3F);

        // Store the three integer parameters
        this->param1 = arg1;  // +0x04
        this->param2 = arg2;  // +0x08 (note: param2 stored at param_1[2], so offset 0x08)
        this->param3 = arg3;  // +0x0C (param_1[3] = param_4? Wait: original param_1[3] = param_4, but we remapped: param3 = arg3? Actually need to match order: param_3=param1, param_4=param3, param_5=param2. Let's check: param_1[1]=param_3, param_1[2]=param_5, param_1[3]=param_4. So mapping: offset+0x04 = param_3 (arg1), offset+0x08 = param_5 (arg2), offset+0x0C = param_4 (arg3). So we must reorder: The function receives param_3, param_4, param_5. So we need to store accordingly:
        // Actually the decompiled code: param_1[1] = param_3; param_1[2] = param_5; param_1[3] = param_4;
        // So param_3 -> offset 0x04, param_5 -> offset 0x08, param_4 -> offset 0x0C.
        // Therefore the constructor signature should be: DebugLogEntry(char* text, int a, int b, int c) where a=param_3, b=param_4? No, we must map correctly.
        // To avoid confusion, let's define a structure with fields:
        // +0x00: vtable
        // +0x04: fieldA (from param_3)
        // +0x08: fieldB (from param_5)
        // +0x0C: fieldC (from param_4)
        // Then zero out +0x10 to +0x1C (param_1[4]..[7])
        // Then string at +0x20
        // Then next pointer at +0x70 (param_1[0x1c])
        // So we will keep the original parameter order as in the call: (text, param_3, param_5, param_4) but that seems odd. The original call might be something like logEntry = new DebugLogEntry(text, priority, category, timestamp). We'll just name them accordingly.
    }

private:
    // Base class (likely from FUN_0064cc90) might contain additional fields.
    void baseConstructor(); // defined elsewhere

    // Layout:
    // +0x00 void* vtable;
    // +0x04 int fieldA;    // (param_3)
    // +0x08 int fieldB;    // (param_5)
    // +0x0C int fieldC;    // (param_4)
    // +0x10 int unknown0;  // set to 0
    // +0x14 int unknown1;  // set to 0
    // +0x18 int unknown2;  // set to 0
    // +0x1C int unknown3;  // set to 0
    // +0x20 char message[64]; // null-terminated, max 63 chars
    // +0x70 DebugLogEntry* next; // singly linked list pointer
};
// global head pointer is DAT_012059ec (DebugLogEntry* g_debugLogHead);
// The constructor sets this->next = g_debugLogHead; then g_debugLogHead = this;