// FUNC_NAME: ConsoleVariable::ConsoleVariable
// Address: 0x008a7d80
// Constructor for a console variable node in a global linked list.
// Stores name (max 63 chars), three parameters (type, default, flags?), and links into global list.

class ConsoleVariable {
public:
    // Vtable pointer at +0x00
    void* vtable;

    // +0x04: param_3 (likely type or flags)
    int field_04;

    // +0x08: param_5 (likely default value or min)
    int field_08;

    // +0x0C: param_4 (likely max or current value)
    int field_0C;

    // +0x10 to +0x1C: zeroed fields (maybe padding or unused)
    int field_10;
    int field_14;
    int field_18;
    int field_1C;

    // +0x20: name string (63 chars + null)
    char name[64];

    // +0x60 to +0x6C: more fields? (not set here)
    // +0x70: next pointer in global list
    ConsoleVariable* next;

    // Global head of the linked list
    static ConsoleVariable* head; // DAT_012059ec

    ConsoleVariable(const char* varName, int param3, int param4, int param5) {
        // Call base constructor (likely virtual base or common init)
        FUN_0064cc90();

        // Set vtable
        this->vtable = &PTR_LAB_00d79c00;

        // Copy name with max length 63
        strncpy(this->name, varName, 63);
        this->name[63] = '\0';

        // Store parameters
        this->field_04 = param3;
        this->field_0C = param4;
        this->field_08 = param5;

        // Zero out fields at +0x10 to +0x1C
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Link into global list (insert at head)
        this->next = ConsoleVariable::head;
        ConsoleVariable::head = this;
    }
};

// Global head pointer (initialized to null elsewhere)
ConsoleVariable* ConsoleVariable::head = nullptr;