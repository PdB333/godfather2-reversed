// FUNC_NAME: RagdollComponent::processContact

class RagdollComponent {
public:
    // fields (estimated)
    // +0x4: some pointer (e.g., vtable or manager)
    int* somePtr;
    // +0x10: pointer to transform workspace (matrix base)
    float* transformBase; 
    // +0x14: unknown offset/parameter
    float localParam;
    // +0x24: pointer to the contact data (stored)
    const ContactData* currentContact;
    // +0x28: zeros
    int field_28;
    // +0x2c: zeros
    int field_2c;
    // +0x30: constant (probably 1.0f)
    float constVal;
    // +0x34: contact's extra float
    float contactExtra;
};

struct ContactData {
    // +0x4: flags
    uint32_t flags;
    // +0x14: contact delta vector (3 floats)
    float delta[3];
    // +0x20: additional contact data (e.g., normal component)
    float extra;
};

// External: process the contact after transform setup
extern void processContactResponse(RagdollComponent* self, const ContactData* contact,
                                   int param3, float* transformBase, float localParam);

void RagdollComponent::processContact(const ContactData* contact)
{
    // Global constant (probably 1.0f)
    float identityVal = DAT_00e2b1a4; // e.g., 1.0f

    // Get thread-local storage pointer (FS:[0x2c])
    ThreadInfo* threadInfo = *reinterpret_cast<ThreadInfo**>(__readfsdword(0x2c));
    int stackOffset = threadInfo->stackOffset; // +0x8

    // Point to a per-thread temporary 3x4 affine matrix (12 floats)
    float* matrix = reinterpret_cast<float*>(transformBase + 0x10 + stackOffset); // +0x10 base

    // Initialize matrix to identity (only set diagonal elements to identityVal, others zero)
    matrix[0]  = identityVal; // row0 col0
    matrix[1]  = 0.0f;       // row0 col1
    matrix[2]  = 0.0f;       // row0 col2
    matrix[3]  = 0.0f;       // row0 col3 (translation x)
    matrix[4]  = 0.0f;       // row1 col0
    matrix[5]  = identityVal; // row1 col1
    matrix[6]  = 0.0f;       // row1 col2
    matrix[7]  = 0.0f;       // row1 col3 (translation y)
    matrix[8]  = 0.0f;       // row2 col0
    matrix[9]  = 0.0f;       // row2 col1
    matrix[10] = identityVal; // row2 col2
    matrix[11] = 0.0f;       // row2 col3 (translation z)

    // Get pointer to a per-thread delta vector at +0x40 from transform base
    float* deltaVec = reinterpret_cast<float*>(transformBase + 0x40 + stackOffset);

    if ((contact->flags & 1) == 0) {
        // Non-additive mode: if bit2 set, replace delta
        if ((contact->flags & 2) != 0) {
            deltaVec[0] = contact->delta[0];
            deltaVec[1] = contact->delta[1];
            deltaVec[2] = contact->delta[2];
        }
    } else {
        // Additive mode: add contact delta to current delta vector
        deltaVec[0] += contact->delta[0];
        deltaVec[1] += contact->delta[1];
        deltaVec[2] += contact->delta[2];
    }

    // Store contact pointer for later use
    currentContact = contact;
    field_28 = 0;
    field_2c = 0;
    constVal = identityVal;
    contactExtra = contact->extra; // +0x20

    // Finalize processing with the temporary workspace
    processContactResponse(this, contact,
                           *(reinterpret_cast<int*>(somePtr) + 0x10), // some derived pointer
                           transformBase,
                           localParam);
}

extern float DAT_00e2b1a4; // global constant (probably 1.0f)