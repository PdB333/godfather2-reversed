// FUNC_NAME: GameObject::getComponentValue
class GameObject {
public:
    // +0x0: vtable pointer (4 bytes)
    // +0x4: unknown
    // +0x8: unknown
    // +0xC: pointer to component data (ComponentData*)
    ComponentData* m_pComponentData;

    // +0x1C in ComponentData: a 32-bit value (int, float, or pointer)
    int getComponentValue() const {
        if (m_pComponentData != nullptr) {
            return m_pComponentData->field_0x1C;
        }
        return 0;
    }
};