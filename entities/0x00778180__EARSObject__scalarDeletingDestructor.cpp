// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Address: 0x00778180
// Role: Scalar deleting destructor – calls the class destructor and optionally deallocates memory.

class EARSObject {
public:
    void destructor();          // Actual destructor (calls FUN_007774b0)
    void* scalarDeletingDestructor(unsigned char deletingFlag);
};

void operatorDelete(void* p);   // Memory deallocation function (calls FUN_00624da0)

// The scalar deleting destructor always runs the destructor body.
// If the low bit of deletingFlag is set, it also frees the object's memory.
void* EARSObject::scalarDeletingDestructor(unsigned char deletingFlag)
{
    this->destructor();

    if (deletingFlag & 1) {
        operatorDelete(this);
    }

    return this;
}