// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
class GodfatherGameManager {
public:
    // Vtable pointer (offset +0x00)
    void** m_vtable;

    // Global instance pointer
    static GodfatherGameManager* s_instance;

    // Constructor
    __fastcall GodfatherGameManager() {
        s_instance = this;                         // DAT_0112980c = param_1
        m_vtable = (void**)0x00d5a21c;             // *param_1 = &PTR_LAB_00d5a21c
        initializeComponents();                    // FUN_0068ac80
        // return this; implicit
    }

    // Sub‑initializer called by constructor
    void __fastcall initializeComponents();        // Defined at 0x0068ac80
};

GodfatherGameManager* GodfatherGameManager::s_instance = nullptr;