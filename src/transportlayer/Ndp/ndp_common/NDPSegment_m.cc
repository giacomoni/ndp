//
// Generated file, do not edit! Created by nedtool 5.6 from transportlayer/Ndp/ndp_common/NDPSegment.msg.
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
#include "NDPSegment_m.h"

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
namespace ndp {

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

NDPPayloadMessage::NDPPayloadMessage()
{
    this->endSequenceNo = 0;
    this->msg = nullptr;
}

void __doPacking(omnetpp::cCommBuffer *b, const NDPPayloadMessage& a)
{
    doParsimPacking(b,a.endSequenceNo);
    doParsimPacking(b,a.msg);
}

void __doUnpacking(omnetpp::cCommBuffer *b, NDPPayloadMessage& a)
{
    doParsimUnpacking(b,a.endSequenceNo);
    doParsimUnpacking(b,a.msg);
}

class NDPPayloadMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPPayloadMessageDescriptor();
    virtual ~NDPPayloadMessageDescriptor();

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

Register_ClassDescriptor(NDPPayloadMessageDescriptor)

NDPPayloadMessageDescriptor::NDPPayloadMessageDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPPayloadMessage", "")
{
    propertynames = nullptr;
}

NDPPayloadMessageDescriptor::~NDPPayloadMessageDescriptor()
{
    delete[] propertynames;
}

bool NDPPayloadMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPPayloadMessage *>(obj)!=nullptr;
}

const char **NDPPayloadMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPPayloadMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPPayloadMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPPayloadMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *NDPPayloadMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "endSequenceNo",
        "msg",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NDPPayloadMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "endSequenceNo")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msg")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPPayloadMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "cPacketPtr",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPPayloadMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPPayloadMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPPayloadMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPPayloadMessage *pp = (NDPPayloadMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPPayloadMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPPayloadMessage *pp = (NDPPayloadMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPPayloadMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPPayloadMessage *pp = (NDPPayloadMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->endSequenceNo);
        case 1: {std::stringstream out; out << pp->msg; return out.str();}
        default: return "";
    }
}

bool NDPPayloadMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPPayloadMessage *pp = (NDPPayloadMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->endSequenceNo = string2ulong(value); return true;
        default: return false;
    }
}

const char *NDPPayloadMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(cPacketPtr));
        default: return nullptr;
    };
}

void *NDPPayloadMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPPayloadMessage *pp = (NDPPayloadMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->msg); break;
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::ndp::NDPOptionNumbers");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::ndp::NDPOptionNumbers"));
    e->insert(NDPOPTION_END_OF_OPTION_LIST, "NDPOPTION_END_OF_OPTION_LIST");
    e->insert(NDPOPTION_NO_OPERATION, "NDPOPTION_NO_OPERATION");
    e->insert(NDPOPTION_MAXIMUM_SEGMENT_SIZE, "NDPOPTION_MAXIMUM_SEGMENT_SIZE");
    e->insert(NDPOPTION_WINDOW_SCALE, "NDPOPTION_WINDOW_SCALE");
    e->insert(NDPOPTION_SACK_PERMITTED, "NDPOPTION_SACK_PERMITTED");
    e->insert(NDPOPTION_SACK, "NDPOPTION_SACK");
    e->insert(NDPOPTION_TIMESTAMP, "NDPOPTION_TIMESTAMP");
)

Register_Class(SackItem)

SackItem::SackItem() : ::omnetpp::cObject()
{
    this->start_var = 0;
    this->end_var = 0;
}

SackItem::SackItem(const SackItem& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

SackItem::~SackItem()
{
}

SackItem& SackItem::operator=(const SackItem& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void SackItem::copy(const SackItem& other)
{
    this->start_var = other.start_var;
    this->end_var = other.end_var;
}

void SackItem::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->start_var);
    doParsimPacking(b,this->end_var);
}

void SackItem::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->start_var);
    doParsimUnpacking(b,this->end_var);
}

unsigned int SackItem::getStart() const
{
    return this->start_var;
}

void SackItem::setStart(unsigned int start)
{
    this->start_var = start;
}

unsigned int SackItem::getEnd() const
{
    return this->end_var;
}

void SackItem::setEnd(unsigned int end)
{
    this->end_var = end;
}

class SackItemDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SackItemDescriptor();
    virtual ~SackItemDescriptor();

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

Register_ClassDescriptor(SackItemDescriptor)

SackItemDescriptor::SackItemDescriptor() : omnetpp::cClassDescriptor("inet::ndp::SackItem", "omnetpp::cObject")
{
    propertynames = nullptr;
}

SackItemDescriptor::~SackItemDescriptor()
{
    delete[] propertynames;
}

bool SackItemDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SackItem *>(obj)!=nullptr;
}

const char **SackItemDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "fieldNameSuffix",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SackItemDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"fieldNameSuffix")) return "_var";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SackItemDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int SackItemDescriptor::getFieldTypeFlags(int field) const
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

const char *SackItemDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "start",
        "end",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int SackItemDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "start")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "end")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SackItemDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **SackItemDescriptor::getFieldPropertyNames(int field) const
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

const char *SackItemDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int SackItemDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SackItem *pp = (SackItem *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SackItemDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SackItem *pp = (SackItem *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SackItemDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SackItem *pp = (SackItem *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStart());
        case 1: return ulong2string(pp->getEnd());
        default: return "";
    }
}

bool SackItemDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SackItem *pp = (SackItem *)object; (void)pp;
    switch (field) {
        case 0: pp->setStart(string2ulong(value)); return true;
        case 1: pp->setEnd(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SackItemDescriptor::getFieldStructName(int field) const
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

void *SackItemDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SackItem *pp = (SackItem *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Sack_Base::Sack_Base() : ::inet::ndp::SackItem()
{
}

Sack_Base::Sack_Base(const Sack_Base& other) : ::inet::ndp::SackItem(other)
{
    copy(other);
}

Sack_Base::~Sack_Base()
{
}

Sack_Base& Sack_Base::operator=(const Sack_Base& other)
{
    if (this==&other) return *this;
    ::inet::ndp::SackItem::operator=(other);
    copy(other);
    return *this;
}

void Sack_Base::copy(const Sack_Base& other)
{
}

void Sack_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::SackItem::parsimPack(b);
}

void Sack_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::SackItem::parsimUnpack(b);
}

class SackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SackDescriptor();
    virtual ~SackDescriptor();

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

Register_ClassDescriptor(SackDescriptor)

SackDescriptor::SackDescriptor() : omnetpp::cClassDescriptor("inet::ndp::Sack", "inet::ndp::SackItem")
{
    propertynames = nullptr;
}

SackDescriptor::~SackDescriptor()
{
    delete[] propertynames;
}

bool SackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Sack_Base *>(obj)!=nullptr;
}

const char **SackDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SackDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SackDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int SackDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *SackDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int SackDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SackDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **SackDescriptor::getFieldPropertyNames(int field) const
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

const char *SackDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int SackDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Sack_Base *pp = (Sack_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *SackDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Sack_Base *pp = (Sack_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SackDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Sack_Base *pp = (Sack_Base *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SackDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Sack_Base *pp = (Sack_Base *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SackDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *SackDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Sack_Base *pp = (Sack_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOption)

NDPOption::NDPOption() : ::omnetpp::cObject()
{
    this->kind = -1;
    this->length = 1;
}

NDPOption::NDPOption(const NDPOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NDPOption::~NDPOption()
{
}

NDPOption& NDPOption::operator=(const NDPOption& other)
{
    if (this==&other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NDPOption::copy(const NDPOption& other)
{
    this->kind = other.kind;
    this->length = other.length;
}

void NDPOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->kind);
    doParsimPacking(b,this->length);
}

void NDPOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->kind);
    doParsimUnpacking(b,this->length);
}

unsigned short NDPOption::getKind() const
{
    return this->kind;
}

void NDPOption::setKind(unsigned short kind)
{
    this->kind = kind;
}

unsigned short NDPOption::getLength() const
{
    return this->length;
}

void NDPOption::setLength(unsigned short length)
{
    this->length = length;
}

class NDPOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionDescriptor();
    virtual ~NDPOptionDescriptor();

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

Register_ClassDescriptor(NDPOptionDescriptor)

NDPOptionDescriptor::NDPOptionDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOption", "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPOptionDescriptor::~NDPOptionDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOption *>(obj)!=nullptr;
}

const char **NDPOptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPOptionDescriptor::getFieldTypeFlags(int field) const
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

const char *NDPOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "kind",
        "length",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NDPOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='k' && strcmp(fieldName, "kind")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::ndp::NDPOptionNumbers";
            return nullptr;
        default: return nullptr;
    }
}

int NDPOptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOption *pp = (NDPOption *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOption *pp = (NDPOption *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOption *pp = (NDPOption *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getKind(), "inet::ndp::NDPOptionNumbers");
        case 1: return ulong2string(pp->getLength());
        default: return "";
    }
}

bool NDPOptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOption *pp = (NDPOption *)object; (void)pp;
    switch (field) {
        case 0: pp->setKind((inet::ndp::NDPOptionNumbers)string2enum(value, "inet::ndp::NDPOptionNumbers")); return true;
        case 1: pp->setLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPOptionDescriptor::getFieldStructName(int field) const
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

void *NDPOptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOption *pp = (NDPOption *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionEnd)

NDPOptionEnd::NDPOptionEnd() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_END_OF_OPTION_LIST);
    this->setLength(1);
}

NDPOptionEnd::NDPOptionEnd(const NDPOptionEnd& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionEnd::~NDPOptionEnd()
{
}

NDPOptionEnd& NDPOptionEnd::operator=(const NDPOptionEnd& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionEnd::copy(const NDPOptionEnd& other)
{
}

void NDPOptionEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
}

void NDPOptionEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
}

class NDPOptionEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionEndDescriptor();
    virtual ~NDPOptionEndDescriptor();

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

Register_ClassDescriptor(NDPOptionEndDescriptor)

NDPOptionEndDescriptor::NDPOptionEndDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionEnd", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionEndDescriptor::~NDPOptionEndDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionEnd *>(obj)!=nullptr;
}

const char **NDPOptionEndDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionEndDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPOptionEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPOptionEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPOptionEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPOptionEndDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionEndDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionEndDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionEnd *pp = (NDPOptionEnd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionEndDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionEnd *pp = (NDPOptionEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionEndDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionEnd *pp = (NDPOptionEnd *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPOptionEndDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionEnd *pp = (NDPOptionEnd *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPOptionEndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPOptionEndDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionEnd *pp = (NDPOptionEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionNop)

NDPOptionNop::NDPOptionNop() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_NO_OPERATION);
    this->setLength(1);
}

NDPOptionNop::NDPOptionNop(const NDPOptionNop& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionNop::~NDPOptionNop()
{
}

NDPOptionNop& NDPOptionNop::operator=(const NDPOptionNop& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionNop::copy(const NDPOptionNop& other)
{
}

void NDPOptionNop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
}

void NDPOptionNop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
}

class NDPOptionNopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionNopDescriptor();
    virtual ~NDPOptionNopDescriptor();

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

Register_ClassDescriptor(NDPOptionNopDescriptor)

NDPOptionNopDescriptor::NDPOptionNopDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionNop", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionNopDescriptor::~NDPOptionNopDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionNopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionNop *>(obj)!=nullptr;
}

const char **NDPOptionNopDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionNopDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionNopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPOptionNopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPOptionNopDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPOptionNopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionNopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPOptionNopDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionNopDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionNopDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionNop *pp = (NDPOptionNop *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionNopDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionNop *pp = (NDPOptionNop *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionNopDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionNop *pp = (NDPOptionNop *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPOptionNopDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionNop *pp = (NDPOptionNop *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPOptionNopDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPOptionNopDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionNop *pp = (NDPOptionNop *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionMaxSegmentSize)

NDPOptionMaxSegmentSize::NDPOptionMaxSegmentSize() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_MAXIMUM_SEGMENT_SIZE);
    this->setLength(4);

    this->maxSegmentSize = 0;
}

NDPOptionMaxSegmentSize::NDPOptionMaxSegmentSize(const NDPOptionMaxSegmentSize& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionMaxSegmentSize::~NDPOptionMaxSegmentSize()
{
}

NDPOptionMaxSegmentSize& NDPOptionMaxSegmentSize::operator=(const NDPOptionMaxSegmentSize& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionMaxSegmentSize::copy(const NDPOptionMaxSegmentSize& other)
{
    this->maxSegmentSize = other.maxSegmentSize;
}

void NDPOptionMaxSegmentSize::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
    doParsimPacking(b,this->maxSegmentSize);
}

void NDPOptionMaxSegmentSize::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
    doParsimUnpacking(b,this->maxSegmentSize);
}

uint16_t NDPOptionMaxSegmentSize::getMaxSegmentSize() const
{
    return this->maxSegmentSize;
}

void NDPOptionMaxSegmentSize::setMaxSegmentSize(uint16_t maxSegmentSize)
{
    this->maxSegmentSize = maxSegmentSize;
}

class NDPOptionMaxSegmentSizeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionMaxSegmentSizeDescriptor();
    virtual ~NDPOptionMaxSegmentSizeDescriptor();

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

Register_ClassDescriptor(NDPOptionMaxSegmentSizeDescriptor)

NDPOptionMaxSegmentSizeDescriptor::NDPOptionMaxSegmentSizeDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionMaxSegmentSize", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionMaxSegmentSizeDescriptor::~NDPOptionMaxSegmentSizeDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionMaxSegmentSizeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionMaxSegmentSize *>(obj)!=nullptr;
}

const char **NDPOptionMaxSegmentSizeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionMaxSegmentSizeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionMaxSegmentSizeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NDPOptionMaxSegmentSizeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NDPOptionMaxSegmentSizeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "maxSegmentSize",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NDPOptionMaxSegmentSizeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "maxSegmentSize")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionMaxSegmentSizeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionMaxSegmentSizeDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionMaxSegmentSizeDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionMaxSegmentSizeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionMaxSegmentSize *pp = (NDPOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionMaxSegmentSizeDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionMaxSegmentSize *pp = (NDPOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionMaxSegmentSizeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionMaxSegmentSize *pp = (NDPOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getMaxSegmentSize());
        default: return "";
    }
}

bool NDPOptionMaxSegmentSizeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionMaxSegmentSize *pp = (NDPOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        case 0: pp->setMaxSegmentSize(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPOptionMaxSegmentSizeDescriptor::getFieldStructName(int field) const
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

void *NDPOptionMaxSegmentSizeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionMaxSegmentSize *pp = (NDPOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionWindowScale)

NDPOptionWindowScale::NDPOptionWindowScale() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_WINDOW_SCALE);
    this->setLength(3);

    this->windowScale = 0;
}

NDPOptionWindowScale::NDPOptionWindowScale(const NDPOptionWindowScale& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionWindowScale::~NDPOptionWindowScale()
{
}

NDPOptionWindowScale& NDPOptionWindowScale::operator=(const NDPOptionWindowScale& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionWindowScale::copy(const NDPOptionWindowScale& other)
{
    this->windowScale = other.windowScale;
}

void NDPOptionWindowScale::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
    doParsimPacking(b,this->windowScale);
}

void NDPOptionWindowScale::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
    doParsimUnpacking(b,this->windowScale);
}

unsigned short NDPOptionWindowScale::getWindowScale() const
{
    return this->windowScale;
}

void NDPOptionWindowScale::setWindowScale(unsigned short windowScale)
{
    this->windowScale = windowScale;
}

class NDPOptionWindowScaleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionWindowScaleDescriptor();
    virtual ~NDPOptionWindowScaleDescriptor();

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

Register_ClassDescriptor(NDPOptionWindowScaleDescriptor)

NDPOptionWindowScaleDescriptor::NDPOptionWindowScaleDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionWindowScale", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionWindowScaleDescriptor::~NDPOptionWindowScaleDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionWindowScaleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionWindowScale *>(obj)!=nullptr;
}

const char **NDPOptionWindowScaleDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionWindowScaleDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionWindowScaleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NDPOptionWindowScaleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NDPOptionWindowScaleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "windowScale",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NDPOptionWindowScaleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='w' && strcmp(fieldName, "windowScale")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionWindowScaleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionWindowScaleDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionWindowScaleDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionWindowScaleDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionWindowScale *pp = (NDPOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionWindowScaleDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionWindowScale *pp = (NDPOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionWindowScaleDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionWindowScale *pp = (NDPOptionWindowScale *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getWindowScale());
        default: return "";
    }
}

bool NDPOptionWindowScaleDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionWindowScale *pp = (NDPOptionWindowScale *)object; (void)pp;
    switch (field) {
        case 0: pp->setWindowScale(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPOptionWindowScaleDescriptor::getFieldStructName(int field) const
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

void *NDPOptionWindowScaleDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionWindowScale *pp = (NDPOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionSackPermitted)

NDPOptionSackPermitted::NDPOptionSackPermitted() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_SACK_PERMITTED);
    this->setLength(2);
}

NDPOptionSackPermitted::NDPOptionSackPermitted(const NDPOptionSackPermitted& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionSackPermitted::~NDPOptionSackPermitted()
{
}

NDPOptionSackPermitted& NDPOptionSackPermitted::operator=(const NDPOptionSackPermitted& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionSackPermitted::copy(const NDPOptionSackPermitted& other)
{
}

void NDPOptionSackPermitted::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
}

void NDPOptionSackPermitted::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
}

class NDPOptionSackPermittedDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionSackPermittedDescriptor();
    virtual ~NDPOptionSackPermittedDescriptor();

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

Register_ClassDescriptor(NDPOptionSackPermittedDescriptor)

NDPOptionSackPermittedDescriptor::NDPOptionSackPermittedDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionSackPermitted", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionSackPermittedDescriptor::~NDPOptionSackPermittedDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionSackPermittedDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionSackPermitted *>(obj)!=nullptr;
}

const char **NDPOptionSackPermittedDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionSackPermittedDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionSackPermittedDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPOptionSackPermittedDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPOptionSackPermittedDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPOptionSackPermittedDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionSackPermittedDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPOptionSackPermittedDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionSackPermittedDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionSackPermittedDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSackPermitted *pp = (NDPOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionSackPermittedDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSackPermitted *pp = (NDPOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionSackPermittedDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSackPermitted *pp = (NDPOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPOptionSackPermittedDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSackPermitted *pp = (NDPOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPOptionSackPermittedDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPOptionSackPermittedDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSackPermitted *pp = (NDPOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionSack)

NDPOptionSack::NDPOptionSack() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_SACK);
    this->setLength(2);

    sackItem_arraysize = 0;
    this->sackItem = 0;
}

NDPOptionSack::NDPOptionSack(const NDPOptionSack& other) : ::inet::ndp::NDPOption(other)
{
    sackItem_arraysize = 0;
    this->sackItem = 0;
    copy(other);
}

NDPOptionSack::~NDPOptionSack()
{
    delete [] this->sackItem;
}

NDPOptionSack& NDPOptionSack::operator=(const NDPOptionSack& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionSack::copy(const NDPOptionSack& other)
{
    delete [] this->sackItem;
    this->sackItem = (other.sackItem_arraysize==0) ? nullptr : new SackItem[other.sackItem_arraysize];
    sackItem_arraysize = other.sackItem_arraysize;
    for (unsigned int i=0; i<sackItem_arraysize; i++)
        this->sackItem[i] = other.sackItem[i];
}

void NDPOptionSack::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
    b->pack(sackItem_arraysize);
    doParsimArrayPacking(b,this->sackItem,sackItem_arraysize);
}

void NDPOptionSack::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
    delete [] this->sackItem;
    b->unpack(sackItem_arraysize);
    if (sackItem_arraysize==0) {
        this->sackItem = 0;
    } else {
        this->sackItem = new SackItem[sackItem_arraysize];
        doParsimArrayUnpacking(b,this->sackItem,sackItem_arraysize);
    }
}

void NDPOptionSack::setSackItemArraySize(unsigned int size)
{
    SackItem *sackItem2 = (size==0) ? nullptr : new SackItem[size];
    unsigned int sz = sackItem_arraysize < size ? sackItem_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        sackItem2[i] = this->sackItem[i];
    sackItem_arraysize = size;
    delete [] this->sackItem;
    this->sackItem = sackItem2;
}

unsigned int NDPOptionSack::getSackItemArraySize() const
{
    return sackItem_arraysize;
}

SackItem& NDPOptionSack::getSackItem(unsigned int k)
{
    if (k>=sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sackItem_arraysize, k);
    return this->sackItem[k];
}

void NDPOptionSack::setSackItem(unsigned int k, const SackItem& sackItem)
{
    if (k>=sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", sackItem_arraysize, k);
    this->sackItem[k] = sackItem;
}

class NDPOptionSackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionSackDescriptor();
    virtual ~NDPOptionSackDescriptor();

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

Register_ClassDescriptor(NDPOptionSackDescriptor)

NDPOptionSackDescriptor::NDPOptionSackDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionSack", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionSackDescriptor::~NDPOptionSackDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionSackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionSack *>(obj)!=nullptr;
}

const char **NDPOptionSackDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionSackDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionSackDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NDPOptionSackDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NDPOptionSackDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sackItem",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NDPOptionSackDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sackItem")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionSackDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "SackItem",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionSackDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionSackDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionSackDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSack *pp = (NDPOptionSack *)object; (void)pp;
    switch (field) {
        case 0: return pp->getSackItemArraySize();
        default: return 0;
    }
}

const char *NDPOptionSackDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSack *pp = (NDPOptionSack *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionSackDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSack *pp = (NDPOptionSack *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSackItem(i); return out.str();}
        default: return "";
    }
}

bool NDPOptionSackDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSack *pp = (NDPOptionSack *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPOptionSackDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(SackItem));
        default: return nullptr;
    };
}

void *NDPOptionSackDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionSack *pp = (NDPOptionSack *)object; (void)pp;
    switch (field) {
        case 0: return (void *)static_cast<omnetpp::cObject *>(&pp->getSackItem(i)); break;
        default: return nullptr;
    }
}

Register_Class(NDPOptionTimestamp)

NDPOptionTimestamp::NDPOptionTimestamp() : ::inet::ndp::NDPOption()
{
    this->setKind(NDPOPTION_TIMESTAMP);
    this->setLength(10);

    this->senderTimestamp = 0;
    this->echoedTimestamp = 0;
}

NDPOptionTimestamp::NDPOptionTimestamp(const NDPOptionTimestamp& other) : ::inet::ndp::NDPOption(other)
{
    copy(other);
}

NDPOptionTimestamp::~NDPOptionTimestamp()
{
}

NDPOptionTimestamp& NDPOptionTimestamp::operator=(const NDPOptionTimestamp& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionTimestamp::copy(const NDPOptionTimestamp& other)
{
    this->senderTimestamp = other.senderTimestamp;
    this->echoedTimestamp = other.echoedTimestamp;
}

void NDPOptionTimestamp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
    doParsimPacking(b,this->senderTimestamp);
    doParsimPacking(b,this->echoedTimestamp);
}

void NDPOptionTimestamp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
    doParsimUnpacking(b,this->senderTimestamp);
    doParsimUnpacking(b,this->echoedTimestamp);
}

uint32_t NDPOptionTimestamp::getSenderTimestamp() const
{
    return this->senderTimestamp;
}

void NDPOptionTimestamp::setSenderTimestamp(uint32_t senderTimestamp)
{
    this->senderTimestamp = senderTimestamp;
}

uint32_t NDPOptionTimestamp::getEchoedTimestamp() const
{
    return this->echoedTimestamp;
}

void NDPOptionTimestamp::setEchoedTimestamp(uint32_t echoedTimestamp)
{
    this->echoedTimestamp = echoedTimestamp;
}

class NDPOptionTimestampDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionTimestampDescriptor();
    virtual ~NDPOptionTimestampDescriptor();

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

Register_ClassDescriptor(NDPOptionTimestampDescriptor)

NDPOptionTimestampDescriptor::NDPOptionTimestampDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionTimestamp", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionTimestampDescriptor::~NDPOptionTimestampDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionTimestampDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionTimestamp *>(obj)!=nullptr;
}

const char **NDPOptionTimestampDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionTimestampDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionTimestampDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPOptionTimestampDescriptor::getFieldTypeFlags(int field) const
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

const char *NDPOptionTimestampDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderTimestamp",
        "echoedTimestamp",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NDPOptionTimestampDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderTimestamp")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "echoedTimestamp")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionTimestampDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",
        "uint32_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionTimestampDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionTimestampDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionTimestampDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionTimestamp *pp = (NDPOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPOptionTimestampDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionTimestamp *pp = (NDPOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionTimestampDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionTimestamp *pp = (NDPOptionTimestamp *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSenderTimestamp());
        case 1: return ulong2string(pp->getEchoedTimestamp());
        default: return "";
    }
}

bool NDPOptionTimestampDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionTimestamp *pp = (NDPOptionTimestamp *)object; (void)pp;
    switch (field) {
        case 0: pp->setSenderTimestamp(string2ulong(value)); return true;
        case 1: pp->setEchoedTimestamp(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPOptionTimestampDescriptor::getFieldStructName(int field) const
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

void *NDPOptionTimestampDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionTimestamp *pp = (NDPOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NDPOptionUnknown)

NDPOptionUnknown::NDPOptionUnknown() : ::inet::ndp::NDPOption()
{
    this->setKind(-1);

    bytes_arraysize = 0;
    this->bytes = 0;
}

NDPOptionUnknown::NDPOptionUnknown(const NDPOptionUnknown& other) : ::inet::ndp::NDPOption(other)
{
    bytes_arraysize = 0;
    this->bytes = 0;
    copy(other);
}

NDPOptionUnknown::~NDPOptionUnknown()
{
    delete [] this->bytes;
}

NDPOptionUnknown& NDPOptionUnknown::operator=(const NDPOptionUnknown& other)
{
    if (this==&other) return *this;
    ::inet::ndp::NDPOption::operator=(other);
    copy(other);
    return *this;
}

void NDPOptionUnknown::copy(const NDPOptionUnknown& other)
{
    delete [] this->bytes;
    this->bytes = (other.bytes_arraysize==0) ? nullptr : new uint8_t[other.bytes_arraysize];
    bytes_arraysize = other.bytes_arraysize;
    for (unsigned int i=0; i<bytes_arraysize; i++)
        this->bytes[i] = other.bytes[i];
}

void NDPOptionUnknown::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NDPOption::parsimPack(b);
    b->pack(bytes_arraysize);
    doParsimArrayPacking(b,this->bytes,bytes_arraysize);
}

void NDPOptionUnknown::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NDPOption::parsimUnpack(b);
    delete [] this->bytes;
    b->unpack(bytes_arraysize);
    if (bytes_arraysize==0) {
        this->bytes = 0;
    } else {
        this->bytes = new uint8_t[bytes_arraysize];
        doParsimArrayUnpacking(b,this->bytes,bytes_arraysize);
    }
}

void NDPOptionUnknown::setBytesArraySize(unsigned int size)
{
    uint8_t *bytes2 = (size==0) ? nullptr : new uint8_t[size];
    unsigned int sz = bytes_arraysize < size ? bytes_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        bytes2[i] = this->bytes[i];
    for (unsigned int i=sz; i<size; i++)
        bytes2[i] = 0;
    bytes_arraysize = size;
    delete [] this->bytes;
    this->bytes = bytes2;
}

unsigned int NDPOptionUnknown::getBytesArraySize() const
{
    return bytes_arraysize;
}

uint8_t NDPOptionUnknown::getBytes(unsigned int k) const
{
    if (k>=bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", bytes_arraysize, k);
    return this->bytes[k];
}

void NDPOptionUnknown::setBytes(unsigned int k, uint8_t bytes)
{
    if (k>=bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", bytes_arraysize, k);
    this->bytes[k] = bytes;
}

class NDPOptionUnknownDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPOptionUnknownDescriptor();
    virtual ~NDPOptionUnknownDescriptor();

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

Register_ClassDescriptor(NDPOptionUnknownDescriptor)

NDPOptionUnknownDescriptor::NDPOptionUnknownDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPOptionUnknown", "inet::ndp::NDPOption")
{
    propertynames = nullptr;
}

NDPOptionUnknownDescriptor::~NDPOptionUnknownDescriptor()
{
    delete[] propertynames;
}

bool NDPOptionUnknownDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPOptionUnknown *>(obj)!=nullptr;
}

const char **NDPOptionUnknownDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPOptionUnknownDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPOptionUnknownDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NDPOptionUnknownDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NDPOptionUnknownDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "bytes",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NDPOptionUnknownDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "bytes")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPOptionUnknownDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPOptionUnknownDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPOptionUnknownDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPOptionUnknownDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPOptionUnknown *pp = (NDPOptionUnknown *)object; (void)pp;
    switch (field) {
        case 0: return pp->getBytesArraySize();
        default: return 0;
    }
}

const char *NDPOptionUnknownDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionUnknown *pp = (NDPOptionUnknown *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPOptionUnknownDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionUnknown *pp = (NDPOptionUnknown *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getBytes(i));
        default: return "";
    }
}

bool NDPOptionUnknownDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPOptionUnknown *pp = (NDPOptionUnknown *)object; (void)pp;
    switch (field) {
        case 0: pp->setBytes(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPOptionUnknownDescriptor::getFieldStructName(int field) const
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

void *NDPOptionUnknownDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPOptionUnknown *pp = (NDPOptionUnknown *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

NDPSegment_Base::NDPSegment_Base(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->srcPort_var = 0;
    this->destPort_var = 0;
    this->ackNo_var = 0;
    this->nackNo_var = 0;
    this->isHeader_var = false;
    this->isPullPacket_var = false;
    this->isDataPacket_var = false;
    this->isLongFlow_var = false;
    this->priorityValue_var = 0;
    this->numPacketsToSend_var = 0;
    this->pullSequenceNumber_var = 0;
    this->dataSequenceNumber_var = 0;
    this->isLastPktToSend_var = false;
    this->ackBit_var = false;
    this->nackBit_var = false;
    this->headerLength_var = NDP_HEADER_OCTETS;
    this->urgBit_var = false;
    this->pshBit_var = false;
    this->rstBit_var = false;
    this->synBit_var = false;
    this->finBit_var = false;
    this->window_var = 0;
    this->urgentPointer_var = 0;
    this->payloadLength_var = 0;
}

NDPSegment_Base::NDPSegment_Base(const NDPSegment_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

NDPSegment_Base::~NDPSegment_Base()
{
}

NDPSegment_Base& NDPSegment_Base::operator=(const NDPSegment_Base& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void NDPSegment_Base::copy(const NDPSegment_Base& other)
{
    this->srcPort_var = other.srcPort_var;
    this->destPort_var = other.destPort_var;
    this->ackNo_var = other.ackNo_var;
    this->nackNo_var = other.nackNo_var;
    this->isHeader_var = other.isHeader_var;
    this->isPullPacket_var = other.isPullPacket_var;
    this->isDataPacket_var = other.isDataPacket_var;
    this->isLongFlow_var = other.isLongFlow_var;
    this->priorityValue_var = other.priorityValue_var;
    this->numPacketsToSend_var = other.numPacketsToSend_var;
    this->pullSequenceNumber_var = other.pullSequenceNumber_var;
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
    this->isLastPktToSend_var = other.isLastPktToSend_var;
    this->ackBit_var = other.ackBit_var;
    this->nackBit_var = other.nackBit_var;
    this->headerLength_var = other.headerLength_var;
    this->urgBit_var = other.urgBit_var;
    this->pshBit_var = other.pshBit_var;
    this->rstBit_var = other.rstBit_var;
    this->synBit_var = other.synBit_var;
    this->finBit_var = other.finBit_var;
    this->window_var = other.window_var;
    this->urgentPointer_var = other.urgentPointer_var;
    this->payloadLength_var = other.payloadLength_var;
    this->byteArray_var = other.byteArray_var;
}

void NDPSegment_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcPort_var);
    doParsimPacking(b,this->destPort_var);
    doParsimPacking(b,this->ackNo_var);
    doParsimPacking(b,this->nackNo_var);
    doParsimPacking(b,this->isHeader_var);
    doParsimPacking(b,this->isPullPacket_var);
    doParsimPacking(b,this->isDataPacket_var);
    doParsimPacking(b,this->isLongFlow_var);
    doParsimPacking(b,this->priorityValue_var);
    doParsimPacking(b,this->numPacketsToSend_var);
    doParsimPacking(b,this->pullSequenceNumber_var);
    doParsimPacking(b,this->dataSequenceNumber_var);
    doParsimPacking(b,this->isLastPktToSend_var);
    doParsimPacking(b,this->ackBit_var);
    doParsimPacking(b,this->nackBit_var);
    doParsimPacking(b,this->headerLength_var);
    doParsimPacking(b,this->urgBit_var);
    doParsimPacking(b,this->pshBit_var);
    doParsimPacking(b,this->rstBit_var);
    doParsimPacking(b,this->synBit_var);
    doParsimPacking(b,this->finBit_var);
    doParsimPacking(b,this->window_var);
    doParsimPacking(b,this->urgentPointer_var);
    // field headerOption is abstract -- please do packing in customized class
    doParsimPacking(b,this->payloadLength_var);
    // field payload is abstract -- please do packing in customized class
    doParsimPacking(b,this->byteArray_var);
}

void NDPSegment_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcPort_var);
    doParsimUnpacking(b,this->destPort_var);
    doParsimUnpacking(b,this->ackNo_var);
    doParsimUnpacking(b,this->nackNo_var);
    doParsimUnpacking(b,this->isHeader_var);
    doParsimUnpacking(b,this->isPullPacket_var);
    doParsimUnpacking(b,this->isDataPacket_var);
    doParsimUnpacking(b,this->isLongFlow_var);
    doParsimUnpacking(b,this->priorityValue_var);
    doParsimUnpacking(b,this->numPacketsToSend_var);
    doParsimUnpacking(b,this->pullSequenceNumber_var);
    doParsimUnpacking(b,this->dataSequenceNumber_var);
    doParsimUnpacking(b,this->isLastPktToSend_var);
    doParsimUnpacking(b,this->ackBit_var);
    doParsimUnpacking(b,this->nackBit_var);
    doParsimUnpacking(b,this->headerLength_var);
    doParsimUnpacking(b,this->urgBit_var);
    doParsimUnpacking(b,this->pshBit_var);
    doParsimUnpacking(b,this->rstBit_var);
    doParsimUnpacking(b,this->synBit_var);
    doParsimUnpacking(b,this->finBit_var);
    doParsimUnpacking(b,this->window_var);
    doParsimUnpacking(b,this->urgentPointer_var);
    // field headerOption is abstract -- please do unpacking in customized class
    doParsimUnpacking(b,this->payloadLength_var);
    // field payload is abstract -- please do unpacking in customized class
    doParsimUnpacking(b,this->byteArray_var);
}

unsigned short NDPSegment_Base::getSrcPort() const
{
    return this->srcPort_var;
}

void NDPSegment_Base::setSrcPort(unsigned short srcPort)
{
    this->srcPort_var = srcPort;
}

unsigned short NDPSegment_Base::getDestPort() const
{
    return this->destPort_var;
}

void NDPSegment_Base::setDestPort(unsigned short destPort)
{
    this->destPort_var = destPort;
}

unsigned int NDPSegment_Base::getAckNo() const
{
    return this->ackNo_var;
}

void NDPSegment_Base::setAckNo(unsigned int ackNo)
{
    this->ackNo_var = ackNo;
}

unsigned int NDPSegment_Base::getNackNo() const
{
    return this->nackNo_var;
}

void NDPSegment_Base::setNackNo(unsigned int nackNo)
{
    this->nackNo_var = nackNo;
}

bool NDPSegment_Base::getIsHeader() const
{
    return this->isHeader_var;
}

void NDPSegment_Base::setIsHeader(bool isHeader)
{
    this->isHeader_var = isHeader;
}

bool NDPSegment_Base::getIsPullPacket() const
{
    return this->isPullPacket_var;
}

void NDPSegment_Base::setIsPullPacket(bool isPullPacket)
{
    this->isPullPacket_var = isPullPacket;
}

bool NDPSegment_Base::getIsDataPacket() const
{
    return this->isDataPacket_var;
}

void NDPSegment_Base::setIsDataPacket(bool isDataPacket)
{
    this->isDataPacket_var = isDataPacket;
}

bool NDPSegment_Base::getIsLongFlow() const
{
    return this->isLongFlow_var;
}

void NDPSegment_Base::setIsLongFlow(bool isLongFlow)
{
    this->isLongFlow_var = isLongFlow;
}

unsigned int NDPSegment_Base::getPriorityValue() const
{
    return this->priorityValue_var;
}

void NDPSegment_Base::setPriorityValue(unsigned int priorityValue)
{
    this->priorityValue_var = priorityValue;
}

unsigned int NDPSegment_Base::getNumPacketsToSend() const
{
    return this->numPacketsToSend_var;
}

void NDPSegment_Base::setNumPacketsToSend(unsigned int numPacketsToSend)
{
    this->numPacketsToSend_var = numPacketsToSend;
}

unsigned int NDPSegment_Base::getPullSequenceNumber() const
{
    return this->pullSequenceNumber_var;
}

void NDPSegment_Base::setPullSequenceNumber(unsigned int pullSequenceNumber)
{
    this->pullSequenceNumber_var = pullSequenceNumber;
}

unsigned int NDPSegment_Base::getDataSequenceNumber() const
{
    return this->dataSequenceNumber_var;
}

void NDPSegment_Base::setDataSequenceNumber(unsigned int dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

bool NDPSegment_Base::getIsLastPktToSend() const
{
    return this->isLastPktToSend_var;
}

void NDPSegment_Base::setIsLastPktToSend(bool isLastPktToSend)
{
    this->isLastPktToSend_var = isLastPktToSend;
}

bool NDPSegment_Base::getAckBit() const
{
    return this->ackBit_var;
}

void NDPSegment_Base::setAckBit(bool ackBit)
{
    this->ackBit_var = ackBit;
}

bool NDPSegment_Base::getNackBit() const
{
    return this->nackBit_var;
}

void NDPSegment_Base::setNackBit(bool nackBit)
{
    this->nackBit_var = nackBit;
}

unsigned short NDPSegment_Base::getHeaderLength() const
{
    return this->headerLength_var;
}

void NDPSegment_Base::setHeaderLength(unsigned short headerLength)
{
    this->headerLength_var = headerLength;
}

bool NDPSegment_Base::getUrgBit() const
{
    return this->urgBit_var;
}

void NDPSegment_Base::setUrgBit(bool urgBit)
{
    this->urgBit_var = urgBit;
}

bool NDPSegment_Base::getPshBit() const
{
    return this->pshBit_var;
}

void NDPSegment_Base::setPshBit(bool pshBit)
{
    this->pshBit_var = pshBit;
}

bool NDPSegment_Base::getRstBit() const
{
    return this->rstBit_var;
}

void NDPSegment_Base::setRstBit(bool rstBit)
{
    this->rstBit_var = rstBit;
}

bool NDPSegment_Base::getSynBit() const
{
    return this->synBit_var;
}

void NDPSegment_Base::setSynBit(bool synBit)
{
    this->synBit_var = synBit;
}

bool NDPSegment_Base::getFinBit() const
{
    return this->finBit_var;
}

void NDPSegment_Base::setFinBit(bool finBit)
{
    this->finBit_var = finBit;
}

unsigned short NDPSegment_Base::getWindow() const
{
    return this->window_var;
}

void NDPSegment_Base::setWindow(unsigned short window)
{
    this->window_var = window;
}

unsigned short NDPSegment_Base::getUrgentPointer() const
{
    return this->urgentPointer_var;
}

void NDPSegment_Base::setUrgentPointer(unsigned short urgentPointer)
{
    this->urgentPointer_var = urgentPointer;
}

unsigned long NDPSegment_Base::getPayloadLength() const
{
    return this->payloadLength_var;
}

void NDPSegment_Base::setPayloadLength(unsigned long payloadLength)
{
    this->payloadLength_var = payloadLength;
}

ByteArray& NDPSegment_Base::getByteArray()
{
    return this->byteArray_var;
}

void NDPSegment_Base::setByteArray(const ByteArray& byteArray)
{
    this->byteArray_var = byteArray;
}

class NDPSegmentDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NDPSegmentDescriptor();
    virtual ~NDPSegmentDescriptor();

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

Register_ClassDescriptor(NDPSegmentDescriptor)

NDPSegmentDescriptor::NDPSegmentDescriptor() : omnetpp::cClassDescriptor("inet::ndp::NDPSegment", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

NDPSegmentDescriptor::~NDPSegmentDescriptor()
{
    delete[] propertynames;
}

bool NDPSegmentDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPSegment_Base *>(obj)!=nullptr;
}

const char **NDPSegmentDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize", "fieldNameSuffix",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPSegmentDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    if (!strcmp(propertyname,"fieldNameSuffix")) return "_var";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPSegmentDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 27+basedesc->getFieldCount() : 27;
}

unsigned int NDPSegmentDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<27) ? fieldTypeFlags[field] : 0;
}

const char *NDPSegmentDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcPort",
        "destPort",
        "ackNo",
        "nackNo",
        "isHeader",
        "isPullPacket",
        "isDataPacket",
        "isLongFlow",
        "priorityValue",
        "numPacketsToSend",
        "pullSequenceNumber",
        "dataSequenceNumber",
        "isLastPktToSend",
        "ackBit",
        "nackBit",
        "headerLength",
        "urgBit",
        "pshBit",
        "rstBit",
        "synBit",
        "finBit",
        "window",
        "urgentPointer",
        "headerOption",
        "payloadLength",
        "payload",
        "byteArray",
    };
    return (field>=0 && field<27) ? fieldNames[field] : nullptr;
}

int NDPSegmentDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcPort")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPort")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackNo")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nackNo")==0) return base+3;
    if (fieldName[0]=='i' && strcmp(fieldName, "isHeader")==0) return base+4;
    if (fieldName[0]=='i' && strcmp(fieldName, "isPullPacket")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "isDataPacket")==0) return base+6;
    if (fieldName[0]=='i' && strcmp(fieldName, "isLongFlow")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityValue")==0) return base+8;
    if (fieldName[0]=='n' && strcmp(fieldName, "numPacketsToSend")==0) return base+9;
    if (fieldName[0]=='p' && strcmp(fieldName, "pullSequenceNumber")==0) return base+10;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+11;
    if (fieldName[0]=='i' && strcmp(fieldName, "isLastPktToSend")==0) return base+12;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackBit")==0) return base+13;
    if (fieldName[0]=='n' && strcmp(fieldName, "nackBit")==0) return base+14;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+15;
    if (fieldName[0]=='u' && strcmp(fieldName, "urgBit")==0) return base+16;
    if (fieldName[0]=='p' && strcmp(fieldName, "pshBit")==0) return base+17;
    if (fieldName[0]=='r' && strcmp(fieldName, "rstBit")==0) return base+18;
    if (fieldName[0]=='s' && strcmp(fieldName, "synBit")==0) return base+19;
    if (fieldName[0]=='f' && strcmp(fieldName, "finBit")==0) return base+20;
    if (fieldName[0]=='w' && strcmp(fieldName, "window")==0) return base+21;
    if (fieldName[0]=='u' && strcmp(fieldName, "urgentPointer")==0) return base+22;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerOption")==0) return base+23;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+24;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+25;
    if (fieldName[0]=='b' && strcmp(fieldName, "byteArray")==0) return base+26;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPSegmentDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
        "unsigned int",
        "unsigned int",
        "bool",
        "bool",
        "bool",
        "bool",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "bool",
        "bool",
        "bool",
        "unsigned short",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "unsigned short",
        "unsigned short",
        "NDPOptionPtr",
        "unsigned long",
        "NDPPayloadMessage",
        "ByteArray",
    };
    return (field>=0 && field<27) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPSegmentDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPSegmentDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPSegmentDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPSegment_Base *pp = (NDPSegment_Base *)object; (void)pp;
    switch (field) {
        case 23: return pp->getHeaderOptionArraySize();
        case 25: return pp->getPayloadArraySize();
        default: return 0;
    }
}

const char *NDPSegmentDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSegment_Base *pp = (NDPSegment_Base *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPSegmentDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSegment_Base *pp = (NDPSegment_Base *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSrcPort());
        case 1: return ulong2string(pp->getDestPort());
        case 2: return ulong2string(pp->getAckNo());
        case 3: return ulong2string(pp->getNackNo());
        case 4: return bool2string(pp->getIsHeader());
        case 5: return bool2string(pp->getIsPullPacket());
        case 6: return bool2string(pp->getIsDataPacket());
        case 7: return bool2string(pp->getIsLongFlow());
        case 8: return ulong2string(pp->getPriorityValue());
        case 9: return ulong2string(pp->getNumPacketsToSend());
        case 10: return ulong2string(pp->getPullSequenceNumber());
        case 11: return ulong2string(pp->getDataSequenceNumber());
        case 12: return bool2string(pp->getIsLastPktToSend());
        case 13: return bool2string(pp->getAckBit());
        case 14: return bool2string(pp->getNackBit());
        case 15: return ulong2string(pp->getHeaderLength());
        case 16: return bool2string(pp->getUrgBit());
        case 17: return bool2string(pp->getPshBit());
        case 18: return bool2string(pp->getRstBit());
        case 19: return bool2string(pp->getSynBit());
        case 20: return bool2string(pp->getFinBit());
        case 21: return ulong2string(pp->getWindow());
        case 22: return ulong2string(pp->getUrgentPointer());
        case 23: {std::stringstream out; out << pp->getHeaderOption(i); return out.str();}
        case 24: return ulong2string(pp->getPayloadLength());
        case 25: {std::stringstream out; out << pp->getPayload(i); return out.str();}
        case 26: {std::stringstream out; out << pp->getByteArray(); return out.str();}
        default: return "";
    }
}

bool NDPSegmentDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPSegment_Base *pp = (NDPSegment_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcPort(string2ulong(value)); return true;
        case 1: pp->setDestPort(string2ulong(value)); return true;
        case 2: pp->setAckNo(string2ulong(value)); return true;
        case 3: pp->setNackNo(string2ulong(value)); return true;
        case 4: pp->setIsHeader(string2bool(value)); return true;
        case 5: pp->setIsPullPacket(string2bool(value)); return true;
        case 6: pp->setIsDataPacket(string2bool(value)); return true;
        case 7: pp->setIsLongFlow(string2bool(value)); return true;
        case 8: pp->setPriorityValue(string2ulong(value)); return true;
        case 9: pp->setNumPacketsToSend(string2ulong(value)); return true;
        case 10: pp->setPullSequenceNumber(string2ulong(value)); return true;
        case 11: pp->setDataSequenceNumber(string2ulong(value)); return true;
        case 12: pp->setIsLastPktToSend(string2bool(value)); return true;
        case 13: pp->setAckBit(string2bool(value)); return true;
        case 14: pp->setNackBit(string2bool(value)); return true;
        case 15: pp->setHeaderLength(string2ulong(value)); return true;
        case 16: pp->setUrgBit(string2bool(value)); return true;
        case 17: pp->setPshBit(string2bool(value)); return true;
        case 18: pp->setRstBit(string2bool(value)); return true;
        case 19: pp->setSynBit(string2bool(value)); return true;
        case 20: pp->setFinBit(string2bool(value)); return true;
        case 21: pp->setWindow(string2ulong(value)); return true;
        case 22: pp->setUrgentPointer(string2ulong(value)); return true;
        case 24: pp->setPayloadLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NDPSegmentDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 23: return omnetpp::opp_typename(typeid(NDPOptionPtr));
        case 25: return omnetpp::opp_typename(typeid(NDPPayloadMessage));
        case 26: return omnetpp::opp_typename(typeid(ByteArray));
        default: return nullptr;
    };
}

void *NDPSegmentDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPSegment_Base *pp = (NDPSegment_Base *)object; (void)pp;
    switch (field) {
        case 23: return (void *)(&pp->getHeaderOption(i)); break;
        case 25: return (void *)(&pp->getPayload(i)); break;
        case 26: return (void *)(&pp->getByteArray()); break;
        default: return nullptr;
    }
}

} // namespace ndp
} // namespace inet

