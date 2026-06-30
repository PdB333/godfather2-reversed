// FUNC_NAME: GodfatherGameManager::checkHashAndSubsystem
// Reconstructed from Ghidra decompile at 0x00713bb0
// This function checks a hash lookup via a provided interface, then validates against a global subsystem's component.

// Forward declarations for virtual interfaces
class IHashLookup {
public:
    virtual bool lookupHash(uint hash, int* outResult) = 0; // vtable+0x10
};

class ISubsystemChecker {
public:
    virtual bool validate(int param) = 0; // vtable+0x08
};

// Global pointer (EAX/ESI in asm) to a large manager (e.g., GodfatherGameManager)
// +0x22D8 is assumed to be a pointer to an ISubsystemChecker instance
extern GodfatherGameManager* g_pGameManager; // unaff_ESI

// Method belongs to a class with a field at +0x10 (e.g., an Entity or Component)
bool GodfatherGameManager::checkHashAndSubsystem(IHashLookup* lookup, int this_unknown) {
    int localResult = 0;
    bool hashOk = lookup->lookupHash(0x369ac561, &localResult); // virtual call
    if (hashOk && g_pGameManager != nullptr) {
        // Dereference subsystem pointer at offset 0x22D8
        ISubsystemChecker* pChecker = *(ISubsystemChecker**)((char*)g_pGameManager + 0x22D8);
        if (pChecker != nullptr) {
            // Use member at this+0x10 as argument to validate
            return pChecker->validate(*(int*)((char*)this + 0x10));
        }
    }
    return false;
}