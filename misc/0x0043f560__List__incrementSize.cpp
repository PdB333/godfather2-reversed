// FUNC_NAME: List::incrementSize
void List::incrementSize()
{
    // +0x1c: mSize (uint32, length of list)
    constexpr unsigned int kMaxSize = 0x3fffffff;
    
    if (mSize == kMaxSize)
    {
        // EA STL exception for over-long list
        throw std::exception("list<T> too long");
    }
    ++mSize;
}