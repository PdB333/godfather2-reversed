// FUNC_NAME: Sentient::Sentient
undefined4 __thiscall Sentient::Sentient(undefined4 this, byte flag)
{
    Entity::Entity(); // call base class constructor (0x006e9690)
    if ((flag & 1) != 0) {
        this->postConstruct(); // optional post-construction initialization (0x009c8eb0)
    }
    return this;
}