// FUNC_NAME: GodfatherGameManager::setMemberFromGlobal
// Function at 0x0072d7c0: Simple setter that writes a global constant into a member field at offset +0x2190.
// The global DAT_01205228 is likely a configuration or timed value.
extern int g_someGlobal; // from DAT_01205228

class GodfatherGameManager {
public:
    // +0x2190: unknown member (possibly a timer, flag, or pointer)
    int field_2190;
};

void __thiscall GodfatherGameManager::setMemberFromGlobal() {
    this->field_2190 = g_someGlobal;
}