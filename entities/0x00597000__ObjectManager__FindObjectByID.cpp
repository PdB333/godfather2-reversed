// FUNC_NAME: ObjectManager::FindObjectByID
// Address: 0x00597000
// This function searches a global array of objects (s_objects) for an object whose ID (+0x08) matches the given objectID.
// If a slot is empty, it lazily creates an object via a virtual function on the global factory (s_pFactory).
// Returns pointer to the matching object, or 0 if not found.

// Global data:
// s_objectCount (0x01205594): number of slots in the array.
// s_objects (0x0119c6d0): array of pointers to objects.
// s_pFactory (0x01205590): pointer to a factory object whose vtable + 0x04 is a creation function.

// Reconstructed as a static member function of an internal manager class.
class ObjectManager {
public:
    static int FindObjectByID(int objectID);
};

int __stdcall ObjectManager::FindObjectByID(int objectID)
{
    int i = 0;
    if (0 < s_objectCount) {
        do {
            // If the slot is empty, call the factory to create a new object
            if (s_objects[i] == 0) {
                // Call virtual function at vtable+4 on the factory object
                (**(code **)(*s_pFactory + 4))();
            }
            // Check if this object's ID field (+0x08) matches the requested ID
            if (*(int *)(s_objects[i] + 8) == objectID) {
                return s_objects[i];
            }
            i = i + 1;
        } while (i < s_objectCount);
    }
    return 0;
}