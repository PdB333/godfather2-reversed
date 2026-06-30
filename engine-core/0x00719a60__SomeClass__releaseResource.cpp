// FUNC_NAME: SomeClass::releaseResource

class SomeClass
{
public:
    void releaseResource(); // 0x00719a60
private:
    void* m_pResource; // +0x18
};

// Forward declaration of resource release function
void releaseResourceInternal(void* resource);

void SomeClass::releaseResource()
{
    releaseResourceInternal(m_pResource);
}