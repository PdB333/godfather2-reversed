// FUN_006c85d0: SomeClass::clearState
void SomeClass::clearState() {
    // +0x74 field1
    *reinterpret_cast<int*>(this + 0x74) = 0; 
    // +0x78 field2
    *reinterpret_cast<int*>(this + 0x78) = 0; 
}