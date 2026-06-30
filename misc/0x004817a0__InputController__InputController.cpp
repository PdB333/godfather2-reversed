// FUNC_NAME: InputController::InputController
// Function address: 0x4817a0 (constructor)
// Initializes an InputController object with vtable and internal pointers.
// The function takes an implicit this pointer in ESI, and possibly another argument in EAX (parent object?).
// It sets up dual vtable pointers (base and derived) and registers a callback.

struct InputController {
    void** vtable;          // +0x00: vtable pointer (initially set to base vtable, later changed to derived vtable)
    uint32_t field_4;       // +0x04: 0
    uint32_t field_8;       // +0x08: 0
    uint32_t field_C;       // +0x0C: 1 (default value)
    uint32_t field_10;      // +0x10: 1
    void* selfRef;          // +0x14: pointer to &field_28 (self-reference for subobject)
    uint32_t field_18;      // +0x18: 0
    // padding (0x1C, 0x20)
    uint32_t field_24;      // +0x24: 1
    void** vtable2;         // +0x28: pointer to secondary vtable (PTR_LAB_00e33608)
    void* callback;         // +0x2C: pointer to callback function (LAB_00482430)
    uint32_t field_34;      // +0x34: 0
};

// Forward declaration of helper function (sets up internal structures)
void FUN_00452df0(uint32_t param);

void __thiscall InputController::InputController(InputController* thisPtr, int param_EAX)
{
    uint32_t uVar1;

    // param_EAX is the value in EAX (might be another object, e.g., the parent)
    if (param_EAX == 0) {
        uVar1 = 0;
    } else {
        uVar1 = *(uint32_t*)(param_EAX + 0xc);
    }

    thisPtr->field_4 = 0;
    thisPtr->field_8 = 0;
    thisPtr->field_10 = 1;
    thisPtr->field_C = 1;
    thisPtr->vtable = (void**)&PTR_LAB_00e317dc; // Set base class vtable
    thisPtr->field_18 = 0;

    FUN_00452df0(uVar1); // Register/initialize with the derived value

    thisPtr->field_24 = 1;
    thisPtr->vtable = (void**)&PTR_LAB_00e335dc; // Switch to derived class vtable
    thisPtr->vtable2 = (void**)&PTR_LAB_00e33608; // Secondary vtable
    thisPtr->callback = &LAB_00482430;            // Store function pointer
    thisPtr->field_34 = 0;
    thisPtr->selfRef = &thisPtr->field_28;        // Self-pointer to subobject (offset 0x28)
}