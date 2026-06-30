// FUNC_NAME: SmartPtr::operator=
// Address: 0x006bf990
// This function implements assignment for a smart pointer with intrusive reference counting.
// The smart pointer holds a pointer to a reference-counted object (at +0x00) and a "next reference" link (at +0x04)
// for a doubly-linked list of all smart pointers referencing the same object.
// When assigned, it releases the old reference, acquires the new one, and inserts itself into the object's reference list.

class SmartPtr {
public:
    // +0x00: pointer to the referenced object (which also has a 'next' link at +0x04)
    RefCountedObject* m_pObject;
    // +0x04: next smart pointer in the object's reference list (intrusive list node)
    SmartPtr* m_pNext;

    SmartPtr& operator=(const SmartPtr& other) {
        // Self-assignment check
        if (this == &other) {
            return *this;
        }

        RefCountedObject* newObject = other.m_pObject;

        // Only proceed if the pointer actually changes
        if (m_pObject != newObject) {
            // Release the old reference if it exists
            if (m_pObject != nullptr) {
                releaseCurrentRef(m_pObject);
            }

            // Take over the new object pointer
            m_pObject = newObject;

            // If the new object is not null, link this smart pointer into its reference list
            if (newObject != nullptr) {
                // The object has a 'next' pointer at offset +0x04 for the reference list
                m_pNext = newObject->m_pNextRef;
                newObject->m_pNextRef = this;
            }
        }
        return *this;
    }

private:
    // Release a reference to the object (decrements ref count, possibly deletes)
    // Called when this smart pointer previously pointed to an object and is being reassigned.
    void releaseCurrentRef(RefCountedObject* obj);
};

// Forward declaration of the reference-counted object base class
class RefCountedObject {
public:
    // +0x04: head of the intrusive list of SmartPtr instances referencing this object
    SmartPtr* m_pNextRef;
};