// FUNC_NAME: Sentient::setTarget
void __thiscall Sentient::setTarget(void* target) 
{
    // +0x208: pointer to current attention target (likely an entity handle or pointer)
    *(void**)(this + 0x208) = target;
}