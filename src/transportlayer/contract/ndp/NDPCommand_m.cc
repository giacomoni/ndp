//
// Generated file, do not edit! Created by nedtool 5.6 from transportlayer/contract/ndp/NDPCommand.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "NDPCommand_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NDPCommandCode");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NDPCommandCode"));
    e->insert(NDP_C_OPEN_ACTIVE, "NDP_C_OPEN_ACTIVE");
    e->insert(NDP_C_OPEN_PASSIVE, "NDP_C_OPEN_PASSIVE");
    e->insert(NDP_C_ACCEPT, "NDP_C_ACCEPT");
    e->insert(NDP_C_SEND, "NDP_C_SEND");
    e->insert(NDP_C_CLOSE, "NDP_C_CLOSE");
    e->insert(NDP_C_ABORT, "NDP_C_ABORT");
    e->insert(NDP_C_STATUS, "NDP_C_STATUS");
    e->insert(NDP_C_QUEUE_BYTES_LIMIT, "NDP_C_QUEUE_BYTES_LIMIT");
    e->insert(NDP_C_READ, "NDP_C_READ");
    e->insert(NDP_C_DESTROY, "NDP_C_DESTROY");
    e->insert(NDP_SETOPTION, "NDP_SETOPTION");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NDPStatusInd");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NDPStatusInd"));
    e->insert(NDP_I_DATA, "NDP_I_DATA");
    e->insert(NDP_I_URGENT_DATA, "NDP_I_URGENT_DATA");
    e->insert(NDP_I_AVAILABLE, "NDP_I_AVAILABLE");
    e->insert(NDP_I_ESTABLISHED, "NDP_I_ESTABLISHED");
    e->insert(NDP_I_PEER_CLOSED, "NDP_I_PEER_CLOSED");
    e->insert(NDP_I_CLOSED, "NDP_I_CLOSED");
    e->insert(NDP_I_CONNECTION_REFUSED, "NDP_I_CONNECTION_REFUSED");
    e->insert(NDP_I_CONNECTION_RESET, "NDP_I_CONNECTION_RESET");
    e->insert(NDP_I_TIMED_OUT, "NDP_I_TIMED_OUT");
    e->insert(NDP_I_STATUS, "NDP_I_STATUS");
    e->insert(NDP_I_SEND_MSG, "NDP_I_SEND_MSG");
    e->insert(NDP_I_DATA_NOTIFICATION, "NDP_I_DATA_NOTIFICATION");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NDPErrorCode");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NDPErrorCode"));
)

Register_Class(NDPCommand)

NDPCommand::NDPCommand() : ::omnetpp::cObject()
{
}

NDPCommand::NDPCommand(const NDPCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NDPCommand::~NDPCommand()
{
}

NDPCommand& NDPCommand::operator=(const NDPCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NDPCommand::copy(const NDPCommand& other)
{
    this->userId = other.userId;
    this->numRcvTrimmedHeader = other.numRcvTrimmedHeader;
}

void NDPCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->userId);
    doParsimPacking(b,this->numRcvTrimmedHeader);
}

void NDPCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->userId);
    doParsimUnpacking(b,this->numRcvTrimmedHeader);
}

int NDPCommand::getUserId() const
{
    return this->userId;
}

void NDPCommand::setUserId(int userId)
{
    this->userId = userId;
}

unsigned int NDPCommand::getNumRcvTrimmedHeader() const
{
    return this->numRcvTrimmedHeader;
}

void NDPCommand::setNumRcvTrimmedHeader(unsigned int numRcvTrimmedHeader)
{
    this->numRcvTrimmedHeader = numRcvTrimmedHeader;
}

class NDPCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_userId,
        FIELD_numRcvTrimmedHeader,
    };
  public:
    NDPCommandDescriptor();
    virtual ~NDPCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPCommandDescriptor)

NDPCommandDescriptor::NDPCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPCommand)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPCommandDescriptor::~NDPCommandDescriptor()
{
    delete[] propertynames;
}

bool NDPCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPCommand *>(obj)!=nullptr;
}

const char **NDPCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_userId
        FD_ISEDITABLE,    // FIELD_numRcvTrimmedHeader
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NDPCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "userId",
        "numRcvTrimmedHeader",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NDPCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'u' && strcmp(fieldName, "userId") == 0) return base+0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numRcvTrimmedHeader") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_userId
        "unsigned int",    // FIELD_numRcvTrimmedHeader
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPCommand *pp = (NDPCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPCommand *pp = (NDPCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPCommand *pp = (NDPCommand *)object; (void)pp;
    switch (field) {
        case FIELD_userId: return long2string(pp->getUserId());
        case FIELD_numRcvTrimmedHeader: return ulong2string(pp->getNumRcvTrimmedHeader());
        default: return "";
    }
}

bool NDPCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPCommand *pp = (NDPCommand *)object; (void)pp;
    switch (field) {
        case FIELD_userId: pp->setUserId(string2long(value)); return true;
        case FIELD_numRcvTrimmedHeader: pp->setNumRcvTrimmedHeader(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPCommand *pp = (NDPCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPErrorInfo)

NDPErrorInfo::NDPErrorInfo() : ::inet::NDPCommand()
{
}

NDPErrorInfo::NDPErrorInfo(const NDPErrorInfo& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPErrorInfo::~NDPErrorInfo()
{
}

NDPErrorInfo& NDPErrorInfo::operator=(const NDPErrorInfo& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPErrorInfo::copy(const NDPErrorInfo& other)
{
    this->errorCode = other.errorCode;
    this->messageText = other.messageText;
}

void NDPErrorInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->errorCode);
    doParsimPacking(b,this->messageText);
}

void NDPErrorInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->errorCode);
    doParsimUnpacking(b,this->messageText);
}

inet::NDPErrorCode NDPErrorInfo::getErrorCode() const
{
    return this->errorCode;
}

void NDPErrorInfo::setErrorCode(inet::NDPErrorCode errorCode)
{
    this->errorCode = errorCode;
}

const char * NDPErrorInfo::getMessageText() const
{
    return this->messageText.c_str();
}

void NDPErrorInfo::setMessageText(const char * messageText)
{
    this->messageText = messageText;
}

class NDPErrorInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_errorCode,
        FIELD_messageText,
    };
  public:
    NDPErrorInfoDescriptor();
    virtual ~NDPErrorInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPErrorInfoDescriptor)

NDPErrorInfoDescriptor::NDPErrorInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPErrorInfo)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPErrorInfoDescriptor::~NDPErrorInfoDescriptor()
{
    delete[] propertynames;
}

bool NDPErrorInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPErrorInfo *>(obj)!=nullptr;
}

const char **NDPErrorInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPErrorInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPErrorInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPErrorInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_errorCode
        FD_ISEDITABLE,    // FIELD_messageText
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NDPErrorInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "errorCode",
        "messageText",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NDPErrorInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'e' && strcmp(fieldName, "errorCode") == 0) return base+0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "messageText") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPErrorInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::NDPErrorCode",    // FIELD_errorCode
        "string",    // FIELD_messageText
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPErrorInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_errorCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NDPErrorInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_errorCode:
            if (!strcmp(propertyname, "enum")) return "inet::NDPErrorCode";
            return nullptr;
        default: return nullptr;
    }
}

int NDPErrorInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPErrorInfo *pp = (NDPErrorInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPErrorInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPErrorInfo *pp = (NDPErrorInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPErrorInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPErrorInfo *pp = (NDPErrorInfo *)object; (void)pp;
    switch (field) {
        case FIELD_errorCode: return enum2string(pp->getErrorCode(), "inet::NDPErrorCode");
        case FIELD_messageText: return oppstring2string(pp->getMessageText());
        default: return "";
    }
}

bool NDPErrorInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPErrorInfo *pp = (NDPErrorInfo *)object; (void)pp;
    switch (field) {
        case FIELD_errorCode: pp->setErrorCode((inet::NDPErrorCode)string2enum(value, "inet::NDPErrorCode")); return true;
        case FIELD_messageText: pp->setMessageText((value)); return true;
        default: return false;
    }
}

const char *NDPErrorInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPErrorInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPErrorInfo *pp = (NDPErrorInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOpenCommand)

NDPOpenCommand::NDPOpenCommand() : ::inet::NDPCommand()
{
}

NDPOpenCommand::NDPOpenCommand(const NDPOpenCommand& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPOpenCommand::~NDPOpenCommand()
{
}

NDPOpenCommand& NDPOpenCommand::operator=(const NDPOpenCommand& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPOpenCommand::copy(const NDPOpenCommand& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->fork = other.fork;
    this->ndpAlgorithmClass = other.ndpAlgorithmClass;
    this->priorityValue = other.priorityValue;
    this->numPacketsToSend = other.numPacketsToSend;
    this->isLongFlow_ = other.isLongFlow_;
    this->isSender_ = other.isSender_;
    this->isReceiver_ = other.isReceiver_;
}

void NDPOpenCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->fork);
    doParsimPacking(b,this->ndpAlgorithmClass);
    doParsimPacking(b,this->priorityValue);
    doParsimPacking(b,this->numPacketsToSend);
    doParsimPacking(b,this->isLongFlow_);
    doParsimPacking(b,this->isSender_);
    doParsimPacking(b,this->isReceiver_);
}

void NDPOpenCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->fork);
    doParsimUnpacking(b,this->ndpAlgorithmClass);
    doParsimUnpacking(b,this->priorityValue);
    doParsimUnpacking(b,this->numPacketsToSend);
    doParsimUnpacking(b,this->isLongFlow_);
    doParsimUnpacking(b,this->isSender_);
    doParsimUnpacking(b,this->isReceiver_);
}

const L3Address& NDPOpenCommand::getLocalAddr() const
{
    return this->localAddr;
}

void NDPOpenCommand::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& NDPOpenCommand::getRemoteAddr() const
{
    return this->remoteAddr;
}

void NDPOpenCommand::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int NDPOpenCommand::getLocalPort() const
{
    return this->localPort;
}

void NDPOpenCommand::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int NDPOpenCommand::getRemotePort() const
{
    return this->remotePort;
}

void NDPOpenCommand::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

bool NDPOpenCommand::getFork() const
{
    return this->fork;
}

void NDPOpenCommand::setFork(bool fork)
{
    this->fork = fork;
}

const char * NDPOpenCommand::getNdpAlgorithmClass() const
{
    return this->ndpAlgorithmClass.c_str();
}

void NDPOpenCommand::setNdpAlgorithmClass(const char * ndpAlgorithmClass)
{
    this->ndpAlgorithmClass = ndpAlgorithmClass;
}

unsigned int NDPOpenCommand::getPriorityValue() const
{
    return this->priorityValue;
}

void NDPOpenCommand::setPriorityValue(unsigned int priorityValue)
{
    this->priorityValue = priorityValue;
}

unsigned int NDPOpenCommand::getNumPacketsToSend() const
{
    return this->numPacketsToSend;
}

void NDPOpenCommand::setNumPacketsToSend(unsigned int numPacketsToSend)
{
    this->numPacketsToSend = numPacketsToSend;
}

bool NDPOpenCommand::isLongFlow() const
{
    return this->isLongFlow_;
}

void NDPOpenCommand::setIsLongFlow(bool isLongFlow)
{
    this->isLongFlow_ = isLongFlow;
}

bool NDPOpenCommand::isSender() const
{
    return this->isSender_;
}

void NDPOpenCommand::setIsSender(bool isSender)
{
    this->isSender_ = isSender;
}

bool NDPOpenCommand::isReceiver() const
{
    return this->isReceiver_;
}

void NDPOpenCommand::setIsReceiver(bool isReceiver)
{
    this->isReceiver_ = isReceiver;
}

class NDPOpenCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_fork,
        FIELD_ndpAlgorithmClass,
        FIELD_priorityValue,
        FIELD_numPacketsToSend,
        FIELD_isLongFlow,
        FIELD_isSender,
        FIELD_isReceiver,
    };
  public:
    NDPOpenCommandDescriptor();
    virtual ~NDPOpenCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPOpenCommandDescriptor)

NDPOpenCommandDescriptor::NDPOpenCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPOpenCommand)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPOpenCommandDescriptor::~NDPOpenCommandDescriptor()
{
    delete[] propertynames;
}

bool NDPOpenCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOpenCommand *>(obj)!=nullptr;
}

const char **NDPOpenCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOpenCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOpenCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int NDPOpenCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_fork
        FD_ISEDITABLE,    // FIELD_ndpAlgorithmClass
        FD_ISEDITABLE,    // FIELD_priorityValue
        FD_ISEDITABLE,    // FIELD_numPacketsToSend
        FD_ISEDITABLE,    // FIELD_isLongFlow
        FD_ISEDITABLE,    // FIELD_isSender
        FD_ISEDITABLE,    // FIELD_isReceiver
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *NDPOpenCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "fork",
        "ndpAlgorithmClass",
        "priorityValue",
        "numPacketsToSend",
        "isLongFlow",
        "isSender",
        "isReceiver",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int NDPOpenCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localAddr") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remoteAddr") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remotePort") == 0) return base+3;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fork") == 0) return base+4;
    if (fieldName[0] == 'n' && strcmp(fieldName, "ndpAlgorithmClass") == 0) return base+5;
    if (fieldName[0] == 'p' && strcmp(fieldName, "priorityValue") == 0) return base+6;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPacketsToSend") == 0) return base+7;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isLongFlow") == 0) return base+8;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isSender") == 0) return base+9;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isReceiver") == 0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOpenCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "bool",    // FIELD_fork
        "string",    // FIELD_ndpAlgorithmClass
        "unsigned int",    // FIELD_priorityValue
        "unsigned int",    // FIELD_numPacketsToSend
        "bool",    // FIELD_isLongFlow
        "bool",    // FIELD_isSender
        "bool",    // FIELD_isReceiver
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOpenCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPOpenCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPOpenCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOpenCommand *pp = (NDPOpenCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOpenCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOpenCommand *pp = (NDPOpenCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOpenCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOpenCommand *pp = (NDPOpenCommand *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_fork: return bool2string(pp->getFork());
        case FIELD_ndpAlgorithmClass: return oppstring2string(pp->getNdpAlgorithmClass());
        case FIELD_priorityValue: return ulong2string(pp->getPriorityValue());
        case FIELD_numPacketsToSend: return ulong2string(pp->getNumPacketsToSend());
        case FIELD_isLongFlow: return bool2string(pp->isLongFlow());
        case FIELD_isSender: return bool2string(pp->isSender());
        case FIELD_isReceiver: return bool2string(pp->isReceiver());
        default: return "";
    }
}

bool NDPOpenCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOpenCommand *pp = (NDPOpenCommand *)object; (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); return true;
        case FIELD_fork: pp->setFork(string2bool(value)); return true;
        case FIELD_ndpAlgorithmClass: pp->setNdpAlgorithmClass((value)); return true;
        case FIELD_priorityValue: pp->setPriorityValue(string2ulong(value)); return true;
        case FIELD_numPacketsToSend: pp->setNumPacketsToSend(string2ulong(value)); return true;
        case FIELD_isLongFlow: pp->setIsLongFlow(string2bool(value)); return true;
        case FIELD_isSender: pp->setIsSender(string2bool(value)); return true;
        case FIELD_isReceiver: pp->setIsReceiver(string2bool(value)); return true;
        default: return false;
    }
}

const char *NDPOpenCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPOpenCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOpenCommand *pp = (NDPOpenCommand *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return toVoidPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return toVoidPtr(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

Register_Class(NDPAcceptCommand)

NDPAcceptCommand::NDPAcceptCommand() : ::inet::NDPCommand()
{
}

NDPAcceptCommand::NDPAcceptCommand(const NDPAcceptCommand& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPAcceptCommand::~NDPAcceptCommand()
{
}

NDPAcceptCommand& NDPAcceptCommand::operator=(const NDPAcceptCommand& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPAcceptCommand::copy(const NDPAcceptCommand& other)
{
}

void NDPAcceptCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
}

void NDPAcceptCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
}

class NDPAcceptCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NDPAcceptCommandDescriptor();
    virtual ~NDPAcceptCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPAcceptCommandDescriptor)

NDPAcceptCommandDescriptor::NDPAcceptCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPAcceptCommand)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPAcceptCommandDescriptor::~NDPAcceptCommandDescriptor()
{
    delete[] propertynames;
}

bool NDPAcceptCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPAcceptCommand *>(obj)!=nullptr;
}

const char **NDPAcceptCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPAcceptCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPAcceptCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPAcceptCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPAcceptCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPAcceptCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPAcceptCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPAcceptCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPAcceptCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPAcceptCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPAcceptCommand *pp = (NDPAcceptCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPAcceptCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAcceptCommand *pp = (NDPAcceptCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPAcceptCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAcceptCommand *pp = (NDPAcceptCommand *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPAcceptCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPAcceptCommand *pp = (NDPAcceptCommand *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPAcceptCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPAcceptCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPAcceptCommand *pp = (NDPAcceptCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPSendCommand)

NDPSendCommand::NDPSendCommand() : ::inet::NDPCommand()
{
}

NDPSendCommand::NDPSendCommand(const NDPSendCommand& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPSendCommand::~NDPSendCommand()
{
}

NDPSendCommand& NDPSendCommand::operator=(const NDPSendCommand& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPSendCommand::copy(const NDPSendCommand& other)
{
}

void NDPSendCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
}

void NDPSendCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
}

class NDPSendCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NDPSendCommandDescriptor();
    virtual ~NDPSendCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPSendCommandDescriptor)

NDPSendCommandDescriptor::NDPSendCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPSendCommand)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPSendCommandDescriptor::~NDPSendCommandDescriptor()
{
    delete[] propertynames;
}

bool NDPSendCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPSendCommand *>(obj)!=nullptr;
}

const char **NDPSendCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPSendCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPSendCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPSendCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPSendCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPSendCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPSendCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPSendCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPSendCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPSendCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPSendCommand *pp = (NDPSendCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPSendCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSendCommand *pp = (NDPSendCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPSendCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSendCommand *pp = (NDPSendCommand *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPSendCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPSendCommand *pp = (NDPSendCommand *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPSendCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPSendCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPSendCommand *pp = (NDPSendCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPAvailableInfo)

NDPAvailableInfo::NDPAvailableInfo() : ::inet::NDPCommand()
{
}

NDPAvailableInfo::NDPAvailableInfo(const NDPAvailableInfo& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPAvailableInfo::~NDPAvailableInfo()
{
}

NDPAvailableInfo& NDPAvailableInfo::operator=(const NDPAvailableInfo& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPAvailableInfo::copy(const NDPAvailableInfo& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->newSocketId = other.newSocketId;
}

void NDPAvailableInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->newSocketId);
}

void NDPAvailableInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->newSocketId);
}

const L3Address& NDPAvailableInfo::getLocalAddr() const
{
    return this->localAddr;
}

void NDPAvailableInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& NDPAvailableInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void NDPAvailableInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int NDPAvailableInfo::getLocalPort() const
{
    return this->localPort;
}

void NDPAvailableInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int NDPAvailableInfo::getRemotePort() const
{
    return this->remotePort;
}

void NDPAvailableInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

int NDPAvailableInfo::getNewSocketId() const
{
    return this->newSocketId;
}

void NDPAvailableInfo::setNewSocketId(int newSocketId)
{
    this->newSocketId = newSocketId;
}

class NDPAvailableInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_newSocketId,
    };
  public:
    NDPAvailableInfoDescriptor();
    virtual ~NDPAvailableInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPAvailableInfoDescriptor)

NDPAvailableInfoDescriptor::NDPAvailableInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPAvailableInfo)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPAvailableInfoDescriptor::~NDPAvailableInfoDescriptor()
{
    delete[] propertynames;
}

bool NDPAvailableInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPAvailableInfo *>(obj)!=nullptr;
}

const char **NDPAvailableInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPAvailableInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPAvailableInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int NDPAvailableInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_newSocketId
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *NDPAvailableInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "newSocketId",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int NDPAvailableInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localAddr") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remoteAddr") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remotePort") == 0) return base+3;
    if (fieldName[0] == 'n' && strcmp(fieldName, "newSocketId") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPAvailableInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "int",    // FIELD_newSocketId
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPAvailableInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPAvailableInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPAvailableInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPAvailableInfo *pp = (NDPAvailableInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPAvailableInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAvailableInfo *pp = (NDPAvailableInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPAvailableInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAvailableInfo *pp = (NDPAvailableInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_newSocketId: return long2string(pp->getNewSocketId());
        default: return "";
    }
}

bool NDPAvailableInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPAvailableInfo *pp = (NDPAvailableInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); return true;
        case FIELD_newSocketId: pp->setNewSocketId(string2long(value)); return true;
        default: return false;
    }
}

const char *NDPAvailableInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPAvailableInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPAvailableInfo *pp = (NDPAvailableInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return toVoidPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return toVoidPtr(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

Register_Class(NDPConnectInfo)

NDPConnectInfo::NDPConnectInfo() : ::inet::NDPCommand()
{
}

NDPConnectInfo::NDPConnectInfo(const NDPConnectInfo& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPConnectInfo::~NDPConnectInfo()
{
}

NDPConnectInfo& NDPConnectInfo::operator=(const NDPConnectInfo& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPConnectInfo::copy(const NDPConnectInfo& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
}

void NDPConnectInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
}

void NDPConnectInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
}

const L3Address& NDPConnectInfo::getLocalAddr() const
{
    return this->localAddr;
}

void NDPConnectInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& NDPConnectInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void NDPConnectInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int NDPConnectInfo::getLocalPort() const
{
    return this->localPort;
}

void NDPConnectInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int NDPConnectInfo::getRemotePort() const
{
    return this->remotePort;
}

void NDPConnectInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

class NDPConnectInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
    };
  public:
    NDPConnectInfoDescriptor();
    virtual ~NDPConnectInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPConnectInfoDescriptor)

NDPConnectInfoDescriptor::NDPConnectInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPConnectInfo)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPConnectInfoDescriptor::~NDPConnectInfoDescriptor()
{
    delete[] propertynames;
}

bool NDPConnectInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPConnectInfo *>(obj)!=nullptr;
}

const char **NDPConnectInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPConnectInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPConnectInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int NDPConnectInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *NDPConnectInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int NDPConnectInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localAddr") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remoteAddr") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remotePort") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPConnectInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPConnectInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPConnectInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPConnectInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPConnectInfo *pp = (NDPConnectInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPConnectInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPConnectInfo *pp = (NDPConnectInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPConnectInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPConnectInfo *pp = (NDPConnectInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        default: return "";
    }
}

bool NDPConnectInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPConnectInfo *pp = (NDPConnectInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); return true;
        default: return false;
    }
}

const char *NDPConnectInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPConnectInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPConnectInfo *pp = (NDPConnectInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return toVoidPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return toVoidPtr(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

Register_Class(NDPStatusInfo)

NDPStatusInfo::NDPStatusInfo() : ::inet::NDPCommand()
{
}

NDPStatusInfo::NDPStatusInfo(const NDPStatusInfo& other) : ::inet::NDPCommand(other)
{
    copy(other);
}

NDPStatusInfo::~NDPStatusInfo()
{
}

NDPStatusInfo& NDPStatusInfo::operator=(const NDPStatusInfo& other)
{
    if (this == &other) return *this;
    ::inet::NDPCommand::operator=(other);
    copy(other);
    return *this;
}

void NDPStatusInfo::copy(const NDPStatusInfo& other)
{
    this->state = other.state;
    this->stateName = other.stateName;
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->snd_mss = other.snd_mss;
}

void NDPStatusInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->stateName);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->snd_mss);
}

void NDPStatusInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->stateName);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->snd_mss);
}

int NDPStatusInfo::getState() const
{
    return this->state;
}

void NDPStatusInfo::setState(int state)
{
    this->state = state;
}

const char * NDPStatusInfo::getStateName() const
{
    return this->stateName.c_str();
}

void NDPStatusInfo::setStateName(const char * stateName)
{
    this->stateName = stateName;
}

const L3Address& NDPStatusInfo::getLocalAddr() const
{
    return this->localAddr;
}

void NDPStatusInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& NDPStatusInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void NDPStatusInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int NDPStatusInfo::getLocalPort() const
{
    return this->localPort;
}

void NDPStatusInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int NDPStatusInfo::getRemotePort() const
{
    return this->remotePort;
}

void NDPStatusInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

unsigned int NDPStatusInfo::getSnd_mss() const
{
    return this->snd_mss;
}

void NDPStatusInfo::setSnd_mss(unsigned int snd_mss)
{
    this->snd_mss = snd_mss;
}

class NDPStatusInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_state,
        FIELD_stateName,
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_snd_mss,
    };
  public:
    NDPStatusInfoDescriptor();
    virtual ~NDPStatusInfoDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NDPStatusInfoDescriptor)

NDPStatusInfoDescriptor::NDPStatusInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NDPStatusInfo)), "inet::NDPCommand")
{
    propertynames = nullptr;
}

NDPStatusInfoDescriptor::~NDPStatusInfoDescriptor()
{
    delete[] propertynames;
}

bool NDPStatusInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPStatusInfo *>(obj)!=nullptr;
}

const char **NDPStatusInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPStatusInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPStatusInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int NDPStatusInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_state
        FD_ISEDITABLE,    // FIELD_stateName
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_snd_mss
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *NDPStatusInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "state",
        "stateName",
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "snd_mss",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int NDPStatusInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "state") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "stateName") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localAddr") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remoteAddr") == 0) return base+3;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remotePort") == 0) return base+5;
    if (fieldName[0] == 's' && strcmp(fieldName, "snd_mss") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPStatusInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_state
        "string",    // FIELD_stateName
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "unsigned int",    // FIELD_snd_mss
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPStatusInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NDPStatusInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NDPStatusInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPStatusInfo *pp = (NDPStatusInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPStatusInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPStatusInfo *pp = (NDPStatusInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPStatusInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPStatusInfo *pp = (NDPStatusInfo *)object; (void)pp;
    switch (field) {
        case FIELD_state: return long2string(pp->getState());
        case FIELD_stateName: return oppstring2string(pp->getStateName());
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_snd_mss: return ulong2string(pp->getSnd_mss());
        default: return "";
    }
}

bool NDPStatusInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPStatusInfo *pp = (NDPStatusInfo *)object; (void)pp;
    switch (field) {
        case FIELD_state: pp->setState(string2long(value)); return true;
        case FIELD_stateName: pp->setStateName((value)); return true;
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); return true;
        case FIELD_snd_mss: pp->setSnd_mss(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPStatusInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NDPStatusInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPStatusInfo *pp = (NDPStatusInfo *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return toVoidPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return toVoidPtr(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

} // namespace inet

