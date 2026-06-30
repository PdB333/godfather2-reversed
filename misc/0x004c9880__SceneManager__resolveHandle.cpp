// FUNC_NAME: SceneManager::resolveHandle

// Function address: 0x004c9880
// Role: Given an object handle (int), resolves to an object pointer from the scene manager's active object list.
// Uses a lookup helper (FUN_004c9f20) that writes two values (objectIndex and objectPtr) into the stack area 
// via the handle's address (buffer overflow from callee). This is a common pattern in EA EARS engine.
// Error function (FUN_00b97aea) is called on validity checks.

// Class layout:
// SceneManager:
//   +0x10: m_pObjectList (pointer to ObjectList)
// ObjectList:
//   +0x1c: m_currentIndex (int)

int __thiscall SceneManager::resolveHandle(int handle) {
    int errorDummy;
    int objectIndex;         // local_10
    int objectPtr;           // local_c

    // Validate handle and m_pObjectList
    if (handle != 0) {
        if (*(int *)(this + 0x10) != 0) {
            // Lookup: writes objectIndex and objectPtr into the stack 
            // by treating &handle as start of a small struct
            lookupObject(&handle);  // FUN_004c9f20

            int currentIndex = *(int *)(*(int *)(this + 0x10) + 0x1c);

            if ((objectIndex == 0) || (objectIndex != *(int *)(this + 0x10))) {
                assertFail();  // FUN_00b97aea
            }

            if (objectPtr != currentIndex) {
                if (objectIndex == 0) {
                    assertFail();
                }
                if (objectPtr == *(int *)(objectIndex + 0x1c)) {
                    assertFail();
                }
                // Return pointer from object's data offset +0x10
                return *(int *)(objectPtr + 0x10);
            }
        }
    }
    return 0;
}