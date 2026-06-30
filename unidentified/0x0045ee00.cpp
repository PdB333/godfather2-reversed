// FUN_0045ee00: GameObject::dispatchUpdate

class GameObject {
public:
    // Offset +0x218: m_pActiveCallback (non-zero indicates callbacks are active)
    void dispatchUpdate(void* param1, void* param2, void* param3);
};

void GameObject::dispatchUpdate(void* param1, void* param2, void* param3) {
    // param2 is unused
    if (*(int*)((char*)this + 0x218) != 0) {
        // Forward the call to the actual handler function
        FUN_00572db0(param3);
    }
}