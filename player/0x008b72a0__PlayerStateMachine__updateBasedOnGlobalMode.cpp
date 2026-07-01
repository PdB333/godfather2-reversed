// FUNC_NAME: PlayerStateMachine::updateBasedOnGlobalMode

// Function address: 0x008b72a0
// Role: Sets the state and range of a PlayerStateMachine object depending on global game mode.
// Compares the object's field at offset +0x194 with an identifier read from a global data structure.
// Uses virtual function calls at vtable offsets 0x54 (setState) and 0x5c (setRange).

#include <cstdint>

// Global pointer to a structure containing game mode data (DAT_012233a0)
extern int g_globalDataBase; // placeholder for actual address
extern int* g_globalData;    // assumed to be pointer to structure at DAT_012233a0

// Unknown class; we only know the vtable layout and one field offset.
class PlayerStateMachine {
public:
    // Vtable at offset 0
    // Virtual function at offset 0x54: setState(int state)
    virtual void setState(int state) = 0;
    // Virtual function at offset 0x5c: setRange(int min, int max)
    virtual void setRange(int min, int max) = 0;

    // Known fields:
    // +0x194: some identifier (compared with global data)
    int field_0x194;
};

// __thiscall member function
void PlayerStateMachine::updateBasedOnGlobalMode()
{
    // Read pointer from global structure (at offset +4 from g_globalData)
    // Equivalent to: iVar1 = **(int**)(DAT_012233a0 + 4);
    int** ppData = reinterpret_cast<int**>(g_globalData + 1); // offset +4 bytes (1 int)
    int* pData = *ppData;
    int iVar1 = *pData;

    int* objPtr = reinterpret_cast<int*>(iVar1);

    // Check that the pointer is valid and not a sentinel (0x1f30)
    if (objPtr != nullptr && reinterpret_cast<int>(objPtr) != 0x1f30)
    {
        // Compare this->field_0x194 with the value at objPtr - 0x48 (i.e., 0x12 ints before)
        if (field_0x194 == *(objPtr - 0x12))
        {
            // Matched: set state to 2 and range (0x40, 0xC0)
            setState(2);
            setRange(0x40, 0xC0);
            return;
        }
    }

    // Default: set state to 1 and range (0x80, 0xC0)
    setState(1);
    setRange(0x80, 0xC0);
}