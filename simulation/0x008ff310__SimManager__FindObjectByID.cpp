// FUNC_NAME: SimManager::FindObjectByID
// Address: 0x008ff310
// Role: Looks up a managed object by its ID (offset +0x58) from the internal array (+0x10/0x14).
//        Performs two state checks before returning the object pointer.

class SimManager {
private:
    int** m_objects;      // +0x10 pointer to array of pointers to managed objects
    int   m_objectCount;  // +0x14 number of objects in the array

    // These are assumed member functions of SimManager that check global state.
    // Returns true if the manager is in a shutdown/unavailable state.
    bool IsShuttingDown();
    // Returns true if the manager is active and can serve requests.
    bool IsActive();

public:
    // Finds an object with the given ID (stored at +0x58 within each object).
    // Returns nullptr if not found or if manager state prevents lookup.
    int* FindObjectByID(int id) {
        if (m_objectCount == 0) {
            return nullptr;
        }

        for (int i = 0; i < m_objectCount; ++i) {
            int* obj = m_objects[i];
            int objID = *(int*)((uint8_t*)obj + 0x58); // +0x58: object ID field

            if (objID == id) {
                // Guard checks – both must pass for a valid result.
                if (IsShuttingDown()) {
                    return nullptr;
                }
                if (!IsActive()) {
                    return nullptr;
                }
                return obj;
            }
        }

        return nullptr;
    }
};