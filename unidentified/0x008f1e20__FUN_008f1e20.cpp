// FUNC_NAME: SomeGameObject::setParameters
void __thiscall SomeGameObject::setParameters(int this, int paramA, float paramB, float paramC)
{
    // +0x0C: pointer to some data / first parameter
    *(int *)(this + 0x0C) = paramA;
    // +0x30: float parameter
    *(float *)(this + 0x30) = *(float *)&paramB;
    // +0x34: float parameter
    *(float *)(this + 0x34) = *(float *)&paramC;
}