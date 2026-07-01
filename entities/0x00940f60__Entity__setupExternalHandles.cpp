// FUNC_NAME: Entity::setupExternalHandles
// 0x00940f60 - Sets two external handles (primary and secondary) and registers entity if primary is valid.

// Forward declarations
class Entity;
extern void Entity::registerSelf(int entityID); // 0x00422770

class Entity {
public:
    int m_entityID;            // +0x00, first member
    // ... other members ...
    int m_externalHandlePrimary;   // +0x2018 (index 0x806)
    int m_externalHandleSecondary; // +0x2020 (index 0x808)

    void __thiscall setupExternalHandles(int primaryHandle, int secondaryHandle);
};

void __thiscall Entity::setupExternalHandles(int primaryHandle, int secondaryHandle)
{
    if (primaryHandle != 0) {
        this->m_externalHandlePrimary = primaryHandle;     // +0x2018
        Entity::registerSelf(this->m_entityID);
    }
    if (secondaryHandle != 0) {
        this->m_externalHandleSecondary = secondaryHandle; // +0x2020
    }
    return;
}