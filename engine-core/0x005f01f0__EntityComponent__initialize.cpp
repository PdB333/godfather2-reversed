// FUNC_NAME: EntityComponent::initialize
// Address: 0x005f01f0
// Initializes an entity component with a type byte (stored at +0x600), clears a sub-object at +0x08,
// constructs it (FUN_005dbc10), and runs a secondary init (FUN_005f1350). Returns 1 on success, 0 on failure.

struct SubObject12 {
    int field_0;      // +0x00
    int field_4;      // +0x04
    short field_8;    // +0x08 (originally at overall +0x10)
    short field_A;    // +0x0A (originally at overall +0x12)
    // total 0x0C bytes
};

bool __fastcall EntityComponent::initialize(int this, char type) // type passed in AL (low byte of EAX)
{
    *(char *)(this + 0x600) = type;  // +0x600: component type/mode

    char checkResult = FUN_005f0840();  // validate prerequisites
    if (checkResult == 0) {
        return false;
    }

    SubObject12 *subObj = (SubObject12 *)(this + 8);  // +0x08: sub-object

    *(int *)(this + 4) = 0;  // +0x04: clear separate field

    if (subObj != nullptr) {
        subObj->field_0 = 0;
        subObj->field_4 = 0;
        subObj->field_8 = 0;
        subObj->field_A = 0;
        FUN_005dbc10(subObj, 0);  // construct sub-object with argument 0
        char finalInitResult = FUN_005f1350();  // complete initialization
        if (finalInitResult != 0) {
            return true;
        }
    }
    return false;
}