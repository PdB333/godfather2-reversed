// FUNC_NAME: ArrayBase::sort
void __thiscall ArrayBase::sort(_PtFuncCompare comp)
{
    // Sort the 4-byte element array if more than one element
    if (this->count > 1) {
        _qsort(this->data, this->count, 4, comp);
    }
}