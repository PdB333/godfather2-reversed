// FUNC_NAME: ActionFactory::createAction
// Function address: 0x00481d20
// Role: Creates an action object (size 0x40) when condition object's flag bit 1 is set,
//        assigns a parameter to offset +0x38, then notifies the condition object.

#include <cstdint>

// Forward declarations
class ConditionObject;
class ActionObject;

class ActionFactory {
public:
    // Member at +0x0c: pointer to condition object controlling action creation
    ConditionObject* m_pCondition; // +0x0c

    void __thiscall createAction(uint32_t param2);
};

class ConditionObject {
public:
    // Flags at +0x30; bit 1 (0x2) indicates action creation is allowed
    uint32_t m_flags; // +0x30

    void __thiscall notify(); // FUN_0064d980 – alerts the condition object (e.g., ref count or state update)
};

class ActionObject {
public:
    void* __thiscall operator new(size_t size); // Custom allocator (FUN_009c8e50)
    ActionObject* __thiscall ActionObject(); // Constructor (FUN_00481c20)

    uint32_t m_field38; // +0x38 – stores the value passed from param2
};

// External functions (declared as weak symbols for reconstruction)
extern "C" {
    void* __cdecl customAlloc(size_t size); // FUN_009c8e50
    ActionObject* __thiscall constructActionObject(); // FUN_00481c20
    void __thiscall conditionNotify(ConditionObject* cond); // FUN_0064d980
}

void __thiscall ActionFactory::createAction(uint32_t param2) {
    // Check if condition object exists and its flag bit 1 (0x2) is set
    if (m_pCondition != nullptr && ((m_pCondition->m_flags >> 1) & 1) != 0) {
        ActionObject* obj = (ActionObject*)customAlloc(0x40); // Allocate 64-byte block
        if (obj != nullptr) {
            obj = constructActionObject(); // Call constructor on the allocated memory
            obj->m_field38 = param2; // Store the parameter at offset +0x38
        }
        if (m_pCondition != nullptr) {
            conditionNotify(m_pCondition); // Notify condition object
        }
    }
}