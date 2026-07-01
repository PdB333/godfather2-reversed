// FUNC_NAME: Destructible::~Destructible
void __fastcall Destructible::~Destructible(Destructible *this)
{
    Destructible *pChild;

    // Call base class destructor
    Destructible::baseDestructor();
    
    // Release pointer at offset 0x14 (likely a component or resource handle)
    releaseResource(*(void **)((int)this + 0x14));
    
    // Check if there is a child object at offset 0x00
    pChild = *(Destructible **)this;
    if (pChild != (Destructible *)0x0) {
        // Release child's internal resource at offset 0x14
        releaseResource(*(void **)((int)pChild + 0x14));
        // Destroy child object
        pChild->~Destructible();
    }
    return;
}