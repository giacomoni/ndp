//
// Generated file, do not edit! Created by nedtool 5.6 from application/ndpapp/GenericAppMsgNdp.msg.
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
#include "GenericAppMsgNdp_m.h"

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

Register_Class(GenericAppMsgNdp)

GenericAppMsgNdp::GenericAppMsgNdp() : ::inet::FieldsChunk()
{
}

GenericAppMsgNdp::GenericAppMsgNdp(const GenericAppMsgNdp& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

GenericAppMsgNdp::~GenericAppMsgNdp()
{
}

GenericAppMsgNdp& GenericAppMsgNdp::operator=(const GenericAppMsgNdp& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void GenericAppMsgNdp::copy(const GenericAppMsgNdp& other)
{
    this->numPaketToSend = other.numPaketToSend;
    this->isSender_ = other.isSender_;
    this->isReceiver_ = other.isReceiver_;
    this->isLongFlow_ = other.isLongFlow_;
    this->serverClose = other.serverClose;
}

void GenericAppMsgNdp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->numPaketToSend);
    doParsimPacking(b,this->isSender_);
    doParsimPacking(b,this->isReceiver_);
    doParsimPacking(b,this->isLongFlow_);
    doParsimPacking(b,this->serverClose);
}

void GenericAppMsgNdp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->numPaketToSend);
    doParsimUnpacking(b,this->isSender_);
    doParsimUnpacking(b,this->isReceiver_);
    doParsimUnpacking(b,this->isLongFlow_);
    doParsimUnpacking(b,this->serverClose);
}

int GenericAppMsgNdp::getNumPaketToSend() const
{
    return this->numPaketToSend;
}

void GenericAppMsgNdp::setNumPaketToSend(int numPaketToSend)
{
    handleChange();
    this->numPaketToSend = numPaketToSend;
}

bool GenericAppMsgNdp::isSender() const
{
    return this->isSender_;
}

void GenericAppMsgNdp::setIsSender(bool isSender)
{
    handleChange();
    this->isSender_ = isSender;
}

bool GenericAppMsgNdp::isReceiver() const
{
    return this->isReceiver_;
}

void GenericAppMsgNdp::setIsReceiver(bool isReceiver)
{
    handleChange();
    this->isReceiver_ = isReceiver;
}

bool GenericAppMsgNdp::isLongFlow() const
{
    return this->isLongFlow_;
}

void GenericAppMsgNdp::setIsLongFlow(bool isLongFlow)
{
    handleChange();
    this->isLongFlow_ = isLongFlow;
}

bool GenericAppMsgNdp::getServerClose() const
{
    return this->serverClose;
}

void GenericAppMsgNdp::setServerClose(bool serverClose)
{
    handleChange();
    this->serverClose = serverClose;
}

class GenericAppMsgNdpDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_numPaketToSend,
        FIELD_isSender,
        FIELD_isReceiver,
        FIELD_isLongFlow,
        FIELD_serverClose,
    };
  public:
    GenericAppMsgNdpDescriptor();
    virtual ~GenericAppMsgNdpDescriptor();

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

Register_ClassDescriptor(GenericAppMsgNdpDescriptor)

GenericAppMsgNdpDescriptor::GenericAppMsgNdpDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GenericAppMsgNdp)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

GenericAppMsgNdpDescriptor::~GenericAppMsgNdpDescriptor()
{
    delete[] propertynames;
}

bool GenericAppMsgNdpDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenericAppMsgNdp *>(obj)!=nullptr;
}

const char **GenericAppMsgNdpDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GenericAppMsgNdpDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GenericAppMsgNdpDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int GenericAppMsgNdpDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_numPaketToSend
        FD_ISEDITABLE,    // FIELD_isSender
        FD_ISEDITABLE,    // FIELD_isReceiver
        FD_ISEDITABLE,    // FIELD_isLongFlow
        FD_ISEDITABLE,    // FIELD_serverClose
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *GenericAppMsgNdpDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numPaketToSend",
        "isSender",
        "isReceiver",
        "isLongFlow",
        "serverClose",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int GenericAppMsgNdpDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPaketToSend") == 0) return base+0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isSender") == 0) return base+1;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isReceiver") == 0) return base+2;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isLongFlow") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "serverClose") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GenericAppMsgNdpDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_numPaketToSend
        "bool",    // FIELD_isSender
        "bool",    // FIELD_isReceiver
        "bool",    // FIELD_isLongFlow
        "bool",    // FIELD_serverClose
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **GenericAppMsgNdpDescriptor::getFieldPropertyNames(int field) const
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

const char *GenericAppMsgNdpDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int GenericAppMsgNdpDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GenericAppMsgNdp *pp = (GenericAppMsgNdp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *GenericAppMsgNdpDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GenericAppMsgNdp *pp = (GenericAppMsgNdp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GenericAppMsgNdpDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GenericAppMsgNdp *pp = (GenericAppMsgNdp *)object; (void)pp;
    switch (field) {
        case FIELD_numPaketToSend: return long2string(pp->getNumPaketToSend());
        case FIELD_isSender: return bool2string(pp->isSender());
        case FIELD_isReceiver: return bool2string(pp->isReceiver());
        case FIELD_isLongFlow: return bool2string(pp->isLongFlow());
        case FIELD_serverClose: return bool2string(pp->getServerClose());
        default: return "";
    }
}

bool GenericAppMsgNdpDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GenericAppMsgNdp *pp = (GenericAppMsgNdp *)object; (void)pp;
    switch (field) {
        case FIELD_numPaketToSend: pp->setNumPaketToSend(string2long(value)); return true;
        case FIELD_isSender: pp->setIsSender(string2bool(value)); return true;
        case FIELD_isReceiver: pp->setIsReceiver(string2bool(value)); return true;
        case FIELD_isLongFlow: pp->setIsLongFlow(string2bool(value)); return true;
        case FIELD_serverClose: pp->setServerClose(string2bool(value)); return true;
        default: return false;
    }
}

const char *GenericAppMsgNdpDescriptor::getFieldStructName(int field) const
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

void *GenericAppMsgNdpDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GenericAppMsgNdp *pp = (GenericAppMsgNdp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet

