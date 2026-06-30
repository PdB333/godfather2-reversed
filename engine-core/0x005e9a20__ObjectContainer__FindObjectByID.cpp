// FUNC_NAME: ObjectContainer::FindObjectByID
// Address: 0x005e9a20
// Searches an array of object pointers for an object with a specific ID (offset +0x24).
// Container structure: +0xA8 = pointer to array of object pointers, +0xAC = count.
struct Object {
    char pad_0x00[0x24];
    int id; // +0x24
};

struct ObjectContainer {
    char pad_0x00[0xA8];
    Object** objectArray; // +0xA8
    unsigned int count; // +0xAC
};

Object* __fastcall ObjectContainer::FindObjectByID(void* unusedThis, ObjectContainer* container, int targetID) {
    Object* found = 0;
    unsigned int index = 0;

    if (container->count != 0) {
        Object** array = container->objectArray; // +0xA8
        while (array[index] == 0 || array[index]->id != targetID) {
            index++;
            if (container->count <= index) {
                return found;
            }
        }
        found = array[index];
    }
    return found;
}