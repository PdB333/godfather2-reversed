// FUN_004cf7c0: SomeTextElement::setCaption

void SomeTextElement::setCaption(const char* newCaption)
{
    // Member at +0x50 is a string object (reference counted / internal buffer)
    // Member at +0x3c is an event dispatcher (callback list for text change)

    // Release any previous reference counting (decrement ref counts)
    StringObject::release(&m_text);
    StringObject::release(&m_text);
    // Deallocate internals (free buffer if unique)
    StringObject::deallocate(&m_text);

    if (newCaption != nullptr && *newCaption != '\0')
    {
        // Allocate a copy of the new string (returns pointer to character data)
        const char* textCopy = StringObject::allocateCopy(newCaption);
        // Assign the copy to our string member
        StringObject::assign(&m_text, textCopy);
        // If the string was set (non-null), notify listeners
        if (m_text.m_pBuffer != nullptr)
        {
            // Dispatch "textChanged" event with this string
            EventDispatcher::dispatch(&m_onTextChanged, &m_text);
        }
    }
    // If newCaption is null or empty, the string is reset to empty
}