// FUNC_NAME: Entity::registerSelf
// Address: 0x006b1560
// This function is called from constructor (at 0x006ae7c0) to register the entity
// with a manager or registry. The field at +0x184 holds a key (e.g., pointer to a
// manager or an index) that is used to retrieve a writable slot via getRegistrationSlot().
// The 'this' pointer is then stored into that slot.

class Entity {
    // offset: +0x184  RegistrationKey m_regKey; // key into a registration table
public:
    void registerSelf() {
        int originalThis = (int)this;                        // save original 'this' pointer
        RegistrationKey key = *(RegistrationKey*)((char*)this + 0x184); // read the key
        int* slot = getRegistrationSlot(&key);               // obtain writable slot from manager
        *slot = originalThis;                                // store 'this' into the slot
    }

private:
    // Helper function (actually located at 0x006b1230)
    // Takes a pointer to a RegistrationKey, returns pointer to a slot where the entity pointer should be stored.
    int* getRegistrationSlot(RegistrationKey* key);
};