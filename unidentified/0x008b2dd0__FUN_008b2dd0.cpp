// FUNC_NAME: SomeClass::initializeComponent
// Function address: 0x008b2dd0
// Lazy initialization of a component at offset +0x74 using context at +0x64

void __thiscall SomeClass::initializeComponent() {
    if (m_component == nullptr) {
        m_component = FUN_00446100(m_context, 0); // +0x64 = context, +0x74 = component pointer
    }
}