// FUNC_NAME: releaseGlobalSingletons

// Forward declaration of a class with a virtual release method (likely from EARS engine)
class ISingleton {
public:
    virtual void release(int deleteFlag) = 0; // +0x00 vtable entry
};

// Global singleton pointers at absolute addresses 0x0112fdd4 and 0x0112fdd8
extern ISingleton* g_pSingletonA;
extern ISingleton* g_pSingletonB;

// Releases both singletons and clears pointers
void releaseGlobalSingletons()
{
    if (g_pSingletonA != nullptr) {
        g_pSingletonA->release(1); // 1 indicates "delete this"
    }
    if (g_pSingletonB != nullptr) {
        g_pSingletonB->release(1);
    }
    g_pSingletonA = nullptr;
    g_pSingletonB = nullptr;
}