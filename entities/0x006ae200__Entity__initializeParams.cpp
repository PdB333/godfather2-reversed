// FUNC_NAME: Entity::initializeParams
// Function address: 0x006ae200
// This appears to be a member function that initializes internal state
// using a global structure and a provided command table. Always returns 0.

// The function builds a temporary structure on the stack and calls a helper
// (likely an initializer or constructor for a subsystem).

// Known class hierarchy: EARS::Framework::Entity has a member at offset 0x180
// (likely a pointer to a subobject or configuration).

undefined1 __thiscall Entity::initializeParams(int thisPtr, uint param2, uint param3)

{
  // Local stack variables forming a structure for FUN_00408a00
  uint dataRef;                  // local_10 - loaded from thisPtr+0x180
  undefined4 globalConst;        // local_20 - DAT_0112a610, an external global
  uint p2Copy;                   // local_c - copy of param2
  undefined*** stackPtr;         // local_1c - pointer to local struct
  undefined1 dummyByte1;         // local_18 - unused
  undefined** commandTable;      // local_14 - pointer to command table at 0x00d5dbb4
  uint p3Copy;                   // local_8 - copy of param3
  undefined1 result;             // local_4 - return value (always 0)

  // Read value from this+0x180 (likely a cached pointer or ID)
  dataRef = *(uint *)(thisPtr + 0x180);

  // Prepare stack structure for the initializer call
  globalConst = DAT_0112a610;            // Some global constant/object
  p2Copy = param2;                       // Second parameter
  stackPtr = &commandTable;              // Address of commandTable
  commandTable = (undefined**)&PTR_LAB_00d5dbb4;  // Point to a global table
  p3Copy = param3;                       // Third parameter
  result = 0;                            // Always return false/0
  dummyByte1 = 0;

  // Call initializer with a pointer to the local structure and a zero argument
  FUN_00408a00(&globalConst, 0);

  return result;
}