// FUNC_NAME: ComponentBase::setInitialState
// Function address: 0x005671b0
// Sets three fields: m_state (0x10), m_subState (0x14), m_data (0x18)
class ComponentBase {
public:
    int32_t m_state;    // +0x10
    uint8_t m_subState; // +0x14
    int32_t m_data;     // +0x18

    void setInitialState(int32_t data);
};

void __thiscall ComponentBase::setInitialState(int32_t data) {
    m_data = data;      // +0x18
    m_subState = 2;     // +0x14
    m_state = 9;        // +0x10
}