// FUNC_NAME: GameObject::~GameObject
void __fastcall GameObject::~GameObject(int* this) {
    // Call base class destructor
    baseClassDestructor();
    
    // Release owned data pointer at offset 0x14 (this[5])
    release(reinterpret_cast<void*>(this[5]));
    
    // If first field (this[0]) is non-null, release its internal pointer at +8, then delete it
    int* child = reinterpret_cast<int*>(*this);
    if (child) {
        release(reinterpret_cast<void*>(child[2])); // +8 offset
        deleteChildObject(child);
    }
}