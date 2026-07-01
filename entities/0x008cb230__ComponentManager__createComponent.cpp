// FUNC_NAME: ComponentManager::createComponent
// Reconstructed C++ function at 0x008cb230
// This function acts as a factory/dispatcher for component creation.
// It checks a global component manager state and decides which subclass to instantiate.

// Constants for component lookups (likely hashes/type IDs)
static const uint32_t kComponentHash = 0xa7039c8;        // e.g., "PlayerComponent"
static const uint32_t kInterfaceHash = 0x77a210a2;      // e.g., "NPCComponent"

// Global component manager pointer (set from DAT_01223484)
extern ComponentManager* g_pComponentManager;

// Forward declarations of helper functions
int getComponentTypeID();                    // FUN_004b5d30
int defaultCreateComponent(int* pOut, int param2); // FUN_004b5d40
int allocateMemory(int size);                // FUN_004b5930
int findComponentInterface(void* pObj, uint32_t hash); // FUN_004f7730

// Component constructors (size in bytes)
int createComponentA(int* pOut, int param2); // FUN_008cb030 (size 0x50)
int createComponentB(int* pOut, int param2); // FUN_008cb0e0 (size 0x60)
int createComponentC(int* pOut, int param2); // FUN_008cc6d0 (size ?)

// Vtable offsets for the component interface (from param2+8)
#define VTBL_OBJECT_GET  0x20  // Get first object (probably a singleton manager)
#define VTBL_COMPONENT   0x24  // Get component container from that object
#define VTBL_FIND_COMP   0x10  // Find component by hash

// Main function
int ComponentManager::createComponent(int* pComponentOut, int param2)
{
    int* pObject;               // piVar5 – derived object pointer
    int   typeId;               // iVar4 – type ID from registry
    int   initialId;            // iVar7 – initial value from pComponentOut
    int   result;               // iVar2 – unused (assigned from param2)
    int   found;                // cVar3 – success flag from vtable call
    int   localOut;             // Used as temporary for component lookup

    pObject = pComponentOut;
    initialId = *pComponentOut;
    typeId = getComponentTypeID();
    result = param2; // not used

    if (initialId == typeId) {
        // Path A: initial type matches registry
        pObject = (int*)(**(code**)(**(int**)(param2 + 8) + VTBL_OBJECT_GET))();
        pObject = (int*)(**(code**)(*pObject + VTBL_COMPONENT))();

        if (pObject == nullptr) {
            goto defaultCase;
        }

        if (g_pComponentManager == nullptr || *(int*)(g_pComponentManager + 0xc) == 0) {
            // Global manager not active or has no player component
            localOut = 0;
            found = (**(code**)(*pObject + VTBL_FIND_COMP))(kComponentHash, &localOut);
            if (found && localOut != 0) {
                // Found existing component – allocate 0x60 bytes and construct type B
                result = allocateMemory(0x60);
                if (result != 0) {
                    return createComponentB(pComponentOut, param2);
                }
                return 0;
            }

            // Try to find another interface
            if (findComponentInterface(pObject, kInterfaceHash) != 0) {
                result = allocateMemory(0x50);
                if (result != 0) {
                    return createComponentA(pComponentOut, param2);
                }
            }
            goto defaultCase;
        }
        else {
            // Global manager active – get vtable pointer
            initialId = *pObject;
        }
    }
    else {
        // Path B: initial type does not match
        if (g_pComponentManager == nullptr || *(int*)(g_pComponentManager + 0xc) == 0) {
            // Global manager inactive
            pObject = (int*)(**(code**)(**(int**)(param2 + 8) + VTBL_OBJECT_GET))();
            pObject = (int*)(**(code**)(*pObject + VTBL_COMPONENT))();

            localOut = 0;
            found = (**(code**)(*pObject + VTBL_FIND_COMP))(kComponentHash, &localOut);
            if (found && localOut != 0) {
                // Found component – allocate 0x60 bytes and construct type B
                result = allocateMemory(0x60);
                if (result != 0) {
                    return createComponentB(pComponentOut, param2);
                }
            }
            goto defaultCase;
        }
        else {
            // Global manager active
            pObject = (int*)(**(code**)(**(int**)(param2 + 8) + VTBL_OBJECT_GET))();
            pObject = (int*)(**(code**)(*pObject + VTBL_COMPONENT))();
            initialId = *pObject; // vtable pointer
        }
    }

    // Common code for paths where initialId == typeId (manager active) and else (manager active)
    localOut = 0;
    found = (**(code**)(initialId + VTBL_FIND_COMP))(kComponentHash, &localOut);
    if (found && localOut != 0) {
        // Found component – allocate and construct type C
        result = allocateMemory(0x60); // size not explicitly shown, assume 0x60
        if (result != 0) {
            return createComponentC(pComponentOut, param2);
        }
        return 0;
    }

defaultCase:
    return defaultCreateComponent(pComponentOut, param2);
}