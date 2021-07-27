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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

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
    e->insert(NDP_C_SEND, "NDP_C_SEND");
    e->insert(NDP_C_CLOSE, "NDP_C_CLOSE");
    e->insert(NDP_C_ABORT, "NDP_C_ABORT");
    e->insert(NDP_C_STATUS, "NDP_C_STATUS");
    e->insert(NDP_C_QUEUE_BYTES_LIMIT, "NDP_C_QUEUE_BYTES_LIMIT");
    e->insert(NDP_C_READ, "NDP_C_READ");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::NDPStatusInd");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::NDPStatusInd"));
    e->insert(NDP_I_DATA, "NDP_I_DATA");
    e->insert(NDP_I_URGENT_DATA, "NDP_I_URGENT_DATA");
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
    this->connId = -1;
    this->userId = -1;
    this->numRcvTrimmedHeader = 0;
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
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NDPCommand::copy(const NDPCommand& other)
{
    this->connId = other.connId;
    this->userId = other.userId;
    this->numRcvTrimmedHeader = other.numRcvTrimmedHeader;
}

void NDPCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->connId);
    doParsimPacking(b,this->userId);
    doParsimPacking(b,this->numRcvTrimmedHeader);
}

void NDPCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->connId);
    doParsimUnpacking(b,this->userId);
    doParsimUnpacking(b,this->numRcvTrimmedHeader);
}

int NDPCommand::getConnId() const
{
    return this->connId;
}

void NDPCommand::setConnId(int connId)
{
    this->connId = connId;
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

NDPCommandDescriptor::NDPCommandDescriptor() : omnetpp::cClassDescriptor("inet::NDPCommand", "omnetpp::cObject")
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
    return basedesc ? 3+basedesc->getFieldCount() : 3;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
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
        "connId",
        "userId",
        "numRcvTrimmedHeader",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int NDPCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "connId")==0) return base+0;
    if (fieldName[0]=='u' && strcmp(fieldName, "userId")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "numRcvTrimmedHeader")==0) return base+2;
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
        "int",
        "int",
        "unsigned int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
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
        case 0: return long2string(pp->getConnId());
        case 1: return long2string(pp->getUserId());
        case 2: return ulong2string(pp->getNumRcvTrimmedHeader());
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
        case 0: pp->setConnId(string2long(value)); return true;
        case 1: pp->setUserId(string2long(value)); return true;
        case 2: pp->setNumRcvTrimmedHeader(string2ulong(value)); return true;
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
    this->errorCode = 0;
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
    if (this==&other) return *this;
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

int NDPErrorInfo::getErrorCode() const
{
    return this->errorCode;
}

void NDPErrorInfo::setErrorCode(int errorCode)
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

NDPErrorInfoDescriptor::NDPErrorInfoDescriptor() : omnetpp::cClassDescriptor("inet::NDPErrorInfo", "inet::NDPCommand")
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
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
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NDPErrorInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "errorCode")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageText")==0) return base+1;
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
        "int",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
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
        case 0: {
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
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::NDPErrorCode";
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
        case 0: return enum2string(pp->getErrorCode(), "inet::NDPErrorCode");
        case 1: return oppstring2string(pp->getMessageText());
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
        case 0: pp->setErrorCode((inet::NDPErrorCode)string2enum(value, "inet::NDPErrorCode")); return true;
        case 1: pp->setMessageText((value)); return true;
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
    this->localPort = -1;
    this->remotePort = -1;
    this->priorityValue = 0;
    this->numPacketsToSend = 0;
    this->isLongFlow = false;
    this->isSender = false;
    this->isReceiver = false;
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
    if (this==&other) return *this;
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
    this->ndpAlgorithmClass = other.ndpAlgorithmClass;
    this->priorityValue = other.priorityValue;
    this->numPacketsToSend = other.numPacketsToSend;
    this->isLongFlow = other.isLongFlow;
    this->isSender = other.isSender;
    this->isReceiver = other.isReceiver;
}

void NDPOpenCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NDPCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->ndpAlgorithmClass);
    doParsimPacking(b,this->priorityValue);
    doParsimPacking(b,this->numPacketsToSend);
    doParsimPacking(b,this->isLongFlow);
    doParsimPacking(b,this->isSender);
    doParsimPacking(b,this->isReceiver);
}

void NDPOpenCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NDPCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->ndpAlgorithmClass);
    doParsimUnpacking(b,this->priorityValue);
    doParsimUnpacking(b,this->numPacketsToSend);
    doParsimUnpacking(b,this->isLongFlow);
    doParsimUnpacking(b,this->isSender);
    doParsimUnpacking(b,this->isReceiver);
}

L3Address& NDPOpenCommand::getLocalAddr()
{
    return this->localAddr;
}

void NDPOpenCommand::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

L3Address& NDPOpenCommand::getRemoteAddr()
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

bool NDPOpenCommand::getIsLongFlow() const
{
    return this->isLongFlow;
}

void NDPOpenCommand::setIsLongFlow(bool isLongFlow)
{
    this->isLongFlow = isLongFlow;
}

bool NDPOpenCommand::getIsSender() const
{
    return this->isSender;
}

void NDPOpenCommand::setIsSender(bool isSender)
{
    this->isSender = isSender;
}

bool NDPOpenCommand::getIsReceiver() const
{
    return this->isReceiver;
}

void NDPOpenCommand::setIsReceiver(bool isReceiver)
{
    this->isReceiver = isReceiver;
}

class NDPOpenCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
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

NDPOpenCommandDescriptor::NDPOpenCommandDescriptor() : omnetpp::cClassDescriptor("inet::NDPOpenCommand", "inet::NDPCommand")
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
    return basedesc ? 10+basedesc->getFieldCount() : 10;
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
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
        "ndpAlgorithmClass",
        "priorityValue",
        "numPacketsToSend",
        "isLongFlow",
        "isSender",
        "isReceiver",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int NDPOpenCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "localAddr")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteAddr")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "localPort")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "remotePort")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "ndpAlgorithmClass")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityValue")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "numPacketsToSend")==0) return base+6;
    if (fieldName[0]=='i' && strcmp(fieldName, "isLongFlow")==0) return base+7;
    if (fieldName[0]=='i' && strcmp(fieldName, "isSender")==0) return base+8;
    if (fieldName[0]=='i' && strcmp(fieldName, "isReceiver")==0) return base+9;
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
        "L3Address",
        "L3Address",
        "int",
        "int",
        "string",
        "unsigned int",
        "unsigned int",
        "bool",
        "bool",
        "bool",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
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
        case 0: {std::stringstream out; out << pp->getLocalAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getRemoteAddr(); return out.str();}
        case 2: return long2string(pp->getLocalPort());
        case 3: return long2string(pp->getRemotePort());
        case 4: return oppstring2string(pp->getNdpAlgorithmClass());
        case 5: return ulong2string(pp->getPriorityValue());
        case 6: return ulong2string(pp->getNumPacketsToSend());
        case 7: return bool2string(pp->getIsLongFlow());
        case 8: return bool2string(pp->getIsSender());
        case 9: return bool2string(pp->getIsReceiver());
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
        case 2: pp->setLocalPort(string2long(value)); return true;
        case 3: pp->setRemotePort(string2long(value)); return true;
        case 4: pp->setNdpAlgorithmClass((value)); return true;
        case 5: pp->setPriorityValue(string2ulong(value)); return true;
        case 6: pp->setNumPacketsToSend(string2ulong(value)); return true;
        case 7: pp->setIsLongFlow(string2bool(value)); return true;
        case 8: pp->setIsSender(string2bool(value)); return true;
        case 9: pp->setIsReceiver(string2bool(value)); return true;
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
        case 0: return omnetpp::opp_typename(typeid(L3Address));
        case 1: return omnetpp::opp_typename(typeid(L3Address));
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
        case 0: return (void *)(&pp->getLocalAddr()); break;
        case 1: return (void *)(&pp->getRemoteAddr()); break;
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
    if (this==&other) return *this;
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

NDPSendCommandDescriptor::NDPSendCommandDescriptor() : omnetpp::cClassDescriptor("inet::NDPSendCommand", "inet::NDPCommand")
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

Register_Class(NDPConnectInfo)

NDPConnectInfo::NDPConnectInfo() : ::inet::NDPCommand()
{
    this->localPort = 0;
    this->remotePort = 0;
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
    if (this==&other) return *this;
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

L3Address& NDPConnectInfo::getLocalAddr()
{
    return this->localAddr;
}

void NDPConnectInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

L3Address& NDPConnectInfo::getRemoteAddr()
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

NDPConnectInfoDescriptor::NDPConnectInfoDescriptor() : omnetpp::cClassDescriptor("inet::NDPConnectInfo", "inet::NDPCommand")
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
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
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int NDPConnectInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "localAddr")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteAddr")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "localPort")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "remotePort")==0) return base+3;
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
        "L3Address",
        "L3Address",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
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
        case 0: {std::stringstream out; out << pp->getLocalAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getRemoteAddr(); return out.str();}
        case 2: return long2string(pp->getLocalPort());
        case 3: return long2string(pp->getRemotePort());
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
        case 2: pp->setLocalPort(string2long(value)); return true;
        case 3: pp->setRemotePort(string2long(value)); return true;
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
        case 0: return omnetpp::opp_typename(typeid(L3Address));
        case 1: return omnetpp::opp_typename(typeid(L3Address));
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
        case 0: return (void *)(&pp->getLocalAddr()); break;
        case 1: return (void *)(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

Register_Class(NDPStatusInfo)

NDPStatusInfo::NDPStatusInfo() : ::inet::NDPCommand()
{
    this->state = 0;
    this->localPort = 0;
    this->remotePort = 0;
    this->snd_mss = 0;
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
    if (this==&other) return *this;
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

L3Address& NDPStatusInfo::getLocalAddr()
{
    return this->localAddr;
}

void NDPStatusInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

L3Address& NDPStatusInfo::getRemoteAddr()
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

NDPStatusInfoDescriptor::NDPStatusInfoDescriptor() : omnetpp::cClassDescriptor("inet::NDPStatusInfo", "inet::NDPCommand")
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
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
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int NDPStatusInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "state")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "stateName")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "localAddr")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteAddr")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "localPort")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "remotePort")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "snd_mss")==0) return base+6;
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
        "int",
        "string",
        "L3Address",
        "L3Address",
        "int",
        "int",
        "unsigned int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
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
        case 0: return long2string(pp->getState());
        case 1: return oppstring2string(pp->getStateName());
        case 2: {std::stringstream out; out << pp->getLocalAddr(); return out.str();}
        case 3: {std::stringstream out; out << pp->getRemoteAddr(); return out.str();}
        case 4: return long2string(pp->getLocalPort());
        case 5: return long2string(pp->getRemotePort());
        case 6: return ulong2string(pp->getSnd_mss());
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
        case 0: pp->setState(string2long(value)); return true;
        case 1: pp->setStateName((value)); return true;
        case 4: pp->setLocalPort(string2long(value)); return true;
        case 5: pp->setRemotePort(string2long(value)); return true;
        case 6: pp->setSnd_mss(string2ulong(value)); return true;
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
        case 2: return omnetpp::opp_typename(typeid(L3Address));
        case 3: return omnetpp::opp_typename(typeid(L3Address));
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
        case 2: return (void *)(&pp->getLocalAddr()); break;
        case 3: return (void *)(&pp->getRemoteAddr()); break;
        default: return nullptr;
    }
}

} // namespace inet

