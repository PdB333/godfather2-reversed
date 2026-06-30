// FUNC_NAME: SimObject::getComponent
// Address: 0x006b2160
// Role: Returns a pointer to an embedded component at offset +0xE0, lazily initializing it if the flag at +0xE4 is zero.
// The initializer uses a parameter stored at offset +0xDC.

class SimObject {
public:
    // Returns pointer to component (embedded at this+0xE0)
    void* getComponent() {
        // +0xE4: initialization flag (0 = uninitialized)
        if (m_componentInitFlag == 0) {
            // +0xDC: parameter for initialization (e.g., allocator or manager)
            // +0xE0: address of embedded component
            InitComponent(m_componentParam, &m_component);
            m_componentInitFlag = 1;  // mark as initialized (implied by InitComponent)
        }
        return &m_component;
    }

private:
    // +0xDC (4 bytes): parameter used by init function
    int m_componentParam;

    // +0xE0 (size unknown): embedded component object
    char m_component[4]; // placeholder; actual size depends on component type

    // +0xE4 (4 bytes): flag; 0 = not yet initialized
    int m_componentInitFlag;
};

// External function at 0x00603330: initializes the component given a parameter and its address
void InitComponent(int param, void* component);