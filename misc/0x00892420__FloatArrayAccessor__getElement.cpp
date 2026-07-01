// FUNC_NAME: FloatArrayAccessor::getElement
float __thiscall FloatArrayAccessor::getElement(int index) const
{
    // This accessor treats the object's first member as a float array.
    // The array starts at offset 0 from 'this'.
    // Returns the float at the given index (index * 4 bytes).
    return reinterpret_cast<float*>(this)[index];
}