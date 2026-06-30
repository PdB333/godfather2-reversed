// FUNC_NAME: ComponentBase::~ComponentBase
void __fastcall ComponentBase::~ComponentBase(ComponentBase* this)
{
    ComponentBase::cleanupBase(); // base class destructor (0x0071d610)
    if (this->m_childComponent != nullptr) { // offset +0x14
        delete this->m_childComponent; // calls operator delete (0x004daf90)
    }
    ComponentBase::cleanupFinal(); // final cleanup (0x0071caa0)
}