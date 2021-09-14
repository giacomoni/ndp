//
// Generated file, do not edit! Created by nedtool 5.6 from transportlayer/Ndp/ndp_common/NdpHeader.msg.
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
#include "NdpHeader_m.h"

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
namespace ndp {

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::ndp::NdpConstants");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::ndp::NdpConstants"));
    e->insert(NDP_MAX_SACK_ENTRIES, "NDP_MAX_SACK_ENTRIES");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::ndp::NdpOptionNumbers");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::ndp::NdpOptionNumbers"));
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
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void SackItem::copy(const SackItem& other)
{
    this->start = other.start;
    this->end = other.end;
}

void SackItem::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->start);
    doParsimPacking(b,this->end);
}

void SackItem::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->start);
    doParsimUnpacking(b,this->end);
}

unsigned int SackItem::getStart() const
{
    return this->start;
}

void SackItem::setStart(unsigned int start)
{
    this->start = start;
}

unsigned int SackItem::getEnd() const
{
    return this->end;
}

void SackItem::setEnd(unsigned int end)
{
    this->end = end;
}

class SackItemDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_start,
        FIELD_end,
    };
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

SackItemDescriptor::SackItemDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::SackItem)), "omnetpp::cObject")
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
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SackItemDescriptor::getProperty(const char *propertyname) const
{
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
        FD_ISEDITABLE,    // FIELD_start
        FD_ISEDITABLE,    // FIELD_end
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
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
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SackItemDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "start") == 0) return base+0;
    if (fieldName[0] == 'e' && strcmp(fieldName, "end") == 0) return base+1;
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
        "unsigned int",    // FIELD_start
        "unsigned int",    // FIELD_end
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
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
        case FIELD_start: return ulong2string(pp->getStart());
        case FIELD_end: return ulong2string(pp->getEnd());
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
        case FIELD_start: pp->setStart(string2ulong(value)); return true;
        case FIELD_end: pp->setEnd(string2ulong(value)); return true;
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

Register_Class(Sack)

Sack::Sack() : ::inet::ndp::SackItem()
{
}

Sack::Sack(const Sack& other) : ::inet::ndp::SackItem(other)
{
    copy(other);
}

Sack::~Sack()
{
}

Sack& Sack::operator=(const Sack& other)
{
    if (this == &other) return *this;
    ::inet::ndp::SackItem::operator=(other);
    copy(other);
    return *this;
}

void Sack::copy(const Sack& other)
{
}

void Sack::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::SackItem::parsimPack(b);
}

void Sack::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::SackItem::parsimUnpack(b);
}

class SackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
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

SackDescriptor::SackDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::Sack)), "inet::ndp::SackItem")
{
    propertynames = nullptr;
}

SackDescriptor::~SackDescriptor()
{
    delete[] propertynames;
}

bool SackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Sack *>(obj)!=nullptr;
}

const char **SackDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SackDescriptor::getProperty(const char *propertyname) const
{
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
    Sack *pp = (Sack *)object; (void)pp;
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
    Sack *pp = (Sack *)object; (void)pp;
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
    Sack *pp = (Sack *)object; (void)pp;
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
    Sack *pp = (Sack *)object; (void)pp;
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
    Sack *pp = (Sack *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOption)

NdpOption::NdpOption() : ::omnetpp::cObject()
{
}

NdpOption::NdpOption(const NdpOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NdpOption::~NdpOption()
{
}

NdpOption& NdpOption::operator=(const NdpOption& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NdpOption::copy(const NdpOption& other)
{
    this->kind = other.kind;
    this->length = other.length;
}

void NdpOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->kind);
    doParsimPacking(b,this->length);
}

void NdpOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->kind);
    doParsimUnpacking(b,this->length);
}

inet::ndp::NdpOptionNumbers NdpOption::getKind() const
{
    return this->kind;
}

void NdpOption::setKind(inet::ndp::NdpOptionNumbers kind)
{
    this->kind = kind;
}

unsigned short NdpOption::getLength() const
{
    return this->length;
}

void NdpOption::setLength(unsigned short length)
{
    this->length = length;
}

class NdpOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_kind,
        FIELD_length,
    };
  public:
    NdpOptionDescriptor();
    virtual ~NdpOptionDescriptor();

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

Register_ClassDescriptor(NdpOptionDescriptor)

NdpOptionDescriptor::NdpOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOption)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NdpOptionDescriptor::~NdpOptionDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOption *>(obj)!=nullptr;
}

const char **NdpOptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "packetData")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NdpOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_kind
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NdpOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'k' && strcmp(fieldName, "kind") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "length") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ndp::NdpOptionNumbers",    // FIELD_kind
        "unsigned short",    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_kind: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NdpOptionDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_kind:
            if (!strcmp(propertyname, "enum")) return "inet::ndp::NdpOptionNumbers";
            return nullptr;
        default: return nullptr;
    }
}

int NdpOptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOption *pp = (NdpOption *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOption *pp = (NdpOption *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOption *pp = (NdpOption *)object; (void)pp;
    switch (field) {
        case FIELD_kind: return enum2string(pp->getKind(), "inet::ndp::NdpOptionNumbers");
        case FIELD_length: return ulong2string(pp->getLength());
        default: return "";
    }
}

bool NdpOptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOption *pp = (NdpOption *)object; (void)pp;
    switch (field) {
        case FIELD_kind: pp->setKind((inet::ndp::NdpOptionNumbers)string2enum(value, "inet::ndp::NdpOptionNumbers")); return true;
        case FIELD_length: pp->setLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpOptionDescriptor::getFieldStructName(int field) const
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

void *NdpOptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOption *pp = (NdpOption *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionEnd)

NdpOptionEnd::NdpOptionEnd() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_END_OF_OPTION_LIST);
    this->setLength(1);
}

NdpOptionEnd::NdpOptionEnd(const NdpOptionEnd& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionEnd::~NdpOptionEnd()
{
}

NdpOptionEnd& NdpOptionEnd::operator=(const NdpOptionEnd& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionEnd::copy(const NdpOptionEnd& other)
{
}

void NdpOptionEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
}

void NdpOptionEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
}

class NdpOptionEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NdpOptionEndDescriptor();
    virtual ~NdpOptionEndDescriptor();

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

Register_ClassDescriptor(NdpOptionEndDescriptor)

NdpOptionEndDescriptor::NdpOptionEndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionEnd)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionEndDescriptor::~NdpOptionEndDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionEnd *>(obj)!=nullptr;
}

const char **NdpOptionEndDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionEndDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NdpOptionEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NdpOptionEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NdpOptionEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NdpOptionEndDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionEndDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionEndDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionEnd *pp = (NdpOptionEnd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionEndDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionEnd *pp = (NdpOptionEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionEndDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionEnd *pp = (NdpOptionEnd *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NdpOptionEndDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionEnd *pp = (NdpOptionEnd *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NdpOptionEndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NdpOptionEndDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionEnd *pp = (NdpOptionEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionNop)

NdpOptionNop::NdpOptionNop() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_NO_OPERATION);
    this->setLength(1);
}

NdpOptionNop::NdpOptionNop(const NdpOptionNop& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionNop::~NdpOptionNop()
{
}

NdpOptionNop& NdpOptionNop::operator=(const NdpOptionNop& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionNop::copy(const NdpOptionNop& other)
{
}

void NdpOptionNop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
}

void NdpOptionNop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
}

class NdpOptionNopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NdpOptionNopDescriptor();
    virtual ~NdpOptionNopDescriptor();

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

Register_ClassDescriptor(NdpOptionNopDescriptor)

NdpOptionNopDescriptor::NdpOptionNopDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionNop)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionNopDescriptor::~NdpOptionNopDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionNopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionNop *>(obj)!=nullptr;
}

const char **NdpOptionNopDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionNopDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionNopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NdpOptionNopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NdpOptionNopDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NdpOptionNopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionNopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NdpOptionNopDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionNopDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionNopDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionNop *pp = (NdpOptionNop *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionNopDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionNop *pp = (NdpOptionNop *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionNopDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionNop *pp = (NdpOptionNop *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NdpOptionNopDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionNop *pp = (NdpOptionNop *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NdpOptionNopDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NdpOptionNopDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionNop *pp = (NdpOptionNop *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionMaxSegmentSize)

NdpOptionMaxSegmentSize::NdpOptionMaxSegmentSize() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_MAXIMUM_SEGMENT_SIZE);
    this->setLength(4);

}

NdpOptionMaxSegmentSize::NdpOptionMaxSegmentSize(const NdpOptionMaxSegmentSize& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionMaxSegmentSize::~NdpOptionMaxSegmentSize()
{
}

NdpOptionMaxSegmentSize& NdpOptionMaxSegmentSize::operator=(const NdpOptionMaxSegmentSize& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionMaxSegmentSize::copy(const NdpOptionMaxSegmentSize& other)
{
    this->maxSegmentSize = other.maxSegmentSize;
}

void NdpOptionMaxSegmentSize::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
    doParsimPacking(b,this->maxSegmentSize);
}

void NdpOptionMaxSegmentSize::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->maxSegmentSize);
}

uint16_t NdpOptionMaxSegmentSize::getMaxSegmentSize() const
{
    return this->maxSegmentSize;
}

void NdpOptionMaxSegmentSize::setMaxSegmentSize(uint16_t maxSegmentSize)
{
    this->maxSegmentSize = maxSegmentSize;
}

class NdpOptionMaxSegmentSizeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_maxSegmentSize,
    };
  public:
    NdpOptionMaxSegmentSizeDescriptor();
    virtual ~NdpOptionMaxSegmentSizeDescriptor();

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

Register_ClassDescriptor(NdpOptionMaxSegmentSizeDescriptor)

NdpOptionMaxSegmentSizeDescriptor::NdpOptionMaxSegmentSizeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionMaxSegmentSize)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionMaxSegmentSizeDescriptor::~NdpOptionMaxSegmentSizeDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionMaxSegmentSizeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionMaxSegmentSize *>(obj)!=nullptr;
}

const char **NdpOptionMaxSegmentSizeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionMaxSegmentSizeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionMaxSegmentSizeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NdpOptionMaxSegmentSizeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_maxSegmentSize
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionMaxSegmentSizeDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NdpOptionMaxSegmentSizeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "maxSegmentSize") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionMaxSegmentSizeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_maxSegmentSize
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionMaxSegmentSizeDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionMaxSegmentSizeDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionMaxSegmentSizeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionMaxSegmentSize *pp = (NdpOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionMaxSegmentSizeDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionMaxSegmentSize *pp = (NdpOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionMaxSegmentSizeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionMaxSegmentSize *pp = (NdpOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: return ulong2string(pp->getMaxSegmentSize());
        default: return "";
    }
}

bool NdpOptionMaxSegmentSizeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionMaxSegmentSize *pp = (NdpOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: pp->setMaxSegmentSize(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpOptionMaxSegmentSizeDescriptor::getFieldStructName(int field) const
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

void *NdpOptionMaxSegmentSizeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionMaxSegmentSize *pp = (NdpOptionMaxSegmentSize *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionWindowScale)

NdpOptionWindowScale::NdpOptionWindowScale() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_WINDOW_SCALE);
    this->setLength(3);

}

NdpOptionWindowScale::NdpOptionWindowScale(const NdpOptionWindowScale& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionWindowScale::~NdpOptionWindowScale()
{
}

NdpOptionWindowScale& NdpOptionWindowScale::operator=(const NdpOptionWindowScale& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionWindowScale::copy(const NdpOptionWindowScale& other)
{
    this->windowScale = other.windowScale;
}

void NdpOptionWindowScale::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
    doParsimPacking(b,this->windowScale);
}

void NdpOptionWindowScale::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->windowScale);
}

unsigned short NdpOptionWindowScale::getWindowScale() const
{
    return this->windowScale;
}

void NdpOptionWindowScale::setWindowScale(unsigned short windowScale)
{
    this->windowScale = windowScale;
}

class NdpOptionWindowScaleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_windowScale,
    };
  public:
    NdpOptionWindowScaleDescriptor();
    virtual ~NdpOptionWindowScaleDescriptor();

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

Register_ClassDescriptor(NdpOptionWindowScaleDescriptor)

NdpOptionWindowScaleDescriptor::NdpOptionWindowScaleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionWindowScale)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionWindowScaleDescriptor::~NdpOptionWindowScaleDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionWindowScaleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionWindowScale *>(obj)!=nullptr;
}

const char **NdpOptionWindowScaleDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionWindowScaleDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionWindowScaleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NdpOptionWindowScaleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_windowScale
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionWindowScaleDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NdpOptionWindowScaleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'w' && strcmp(fieldName, "windowScale") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionWindowScaleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_windowScale
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionWindowScaleDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionWindowScaleDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionWindowScaleDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionWindowScale *pp = (NdpOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionWindowScaleDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionWindowScale *pp = (NdpOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionWindowScaleDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionWindowScale *pp = (NdpOptionWindowScale *)object; (void)pp;
    switch (field) {
        case FIELD_windowScale: return ulong2string(pp->getWindowScale());
        default: return "";
    }
}

bool NdpOptionWindowScaleDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionWindowScale *pp = (NdpOptionWindowScale *)object; (void)pp;
    switch (field) {
        case FIELD_windowScale: pp->setWindowScale(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpOptionWindowScaleDescriptor::getFieldStructName(int field) const
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

void *NdpOptionWindowScaleDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionWindowScale *pp = (NdpOptionWindowScale *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionSackPermitted)

NdpOptionSackPermitted::NdpOptionSackPermitted() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_SACK_PERMITTED);
    this->setLength(2);
}

NdpOptionSackPermitted::NdpOptionSackPermitted(const NdpOptionSackPermitted& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionSackPermitted::~NdpOptionSackPermitted()
{
}

NdpOptionSackPermitted& NdpOptionSackPermitted::operator=(const NdpOptionSackPermitted& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionSackPermitted::copy(const NdpOptionSackPermitted& other)
{
}

void NdpOptionSackPermitted::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
}

void NdpOptionSackPermitted::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
}

class NdpOptionSackPermittedDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NdpOptionSackPermittedDescriptor();
    virtual ~NdpOptionSackPermittedDescriptor();

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

Register_ClassDescriptor(NdpOptionSackPermittedDescriptor)

NdpOptionSackPermittedDescriptor::NdpOptionSackPermittedDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionSackPermitted)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionSackPermittedDescriptor::~NdpOptionSackPermittedDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionSackPermittedDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionSackPermitted *>(obj)!=nullptr;
}

const char **NdpOptionSackPermittedDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionSackPermittedDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionSackPermittedDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NdpOptionSackPermittedDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NdpOptionSackPermittedDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NdpOptionSackPermittedDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionSackPermittedDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NdpOptionSackPermittedDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionSackPermittedDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionSackPermittedDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSackPermitted *pp = (NdpOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionSackPermittedDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSackPermitted *pp = (NdpOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionSackPermittedDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSackPermitted *pp = (NdpOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NdpOptionSackPermittedDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSackPermitted *pp = (NdpOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NdpOptionSackPermittedDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NdpOptionSackPermittedDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSackPermitted *pp = (NdpOptionSackPermitted *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionSack)

NdpOptionSack::NdpOptionSack() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_SACK);
    this->setLength(2);

}

NdpOptionSack::NdpOptionSack(const NdpOptionSack& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionSack::~NdpOptionSack()
{
    delete [] this->sackItem;
}

NdpOptionSack& NdpOptionSack::operator=(const NdpOptionSack& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionSack::copy(const NdpOptionSack& other)
{
    delete [] this->sackItem;
    this->sackItem = (other.sackItem_arraysize==0) ? nullptr : new SackItem[other.sackItem_arraysize];
    sackItem_arraysize = other.sackItem_arraysize;
    for (size_t i = 0; i < sackItem_arraysize; i++) {
        this->sackItem[i] = other.sackItem[i];
    }
}

void NdpOptionSack::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
    b->pack(sackItem_arraysize);
    doParsimArrayPacking(b,this->sackItem,sackItem_arraysize);
}

void NdpOptionSack::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
    delete [] this->sackItem;
    b->unpack(sackItem_arraysize);
    if (sackItem_arraysize == 0) {
        this->sackItem = nullptr;
    } else {
        this->sackItem = new SackItem[sackItem_arraysize];
        doParsimArrayUnpacking(b,this->sackItem,sackItem_arraysize);
    }
}

size_t NdpOptionSack::getSackItemArraySize() const
{
    return sackItem_arraysize;
}

const SackItem& NdpOptionSack::getSackItem(size_t k) const
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size sackItem_arraysize indexed by %lu", (unsigned long)k);
    return this->sackItem[k];
}

void NdpOptionSack::setSackItemArraySize(size_t newSize)
{
    SackItem *sackItem2 = (newSize==0) ? nullptr : new SackItem[newSize];
    size_t minSize = sackItem_arraysize < newSize ? sackItem_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sackItem2[i] = this->sackItem[i];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

void NdpOptionSack::setSackItem(size_t k, const SackItem& sackItem)
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    this->sackItem[k] = sackItem;
}

void NdpOptionSack::insertSackItem(size_t k, const SackItem& sackItem)
{
    if (k > sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = sackItem_arraysize + 1;
    SackItem *sackItem2 = new SackItem[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sackItem2[i] = this->sackItem[i];
    sackItem2[k] = sackItem;
    for (i = k + 1; i < newSize; i++)
        sackItem2[i] = this->sackItem[i-1];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

void NdpOptionSack::insertSackItem(const SackItem& sackItem)
{
    insertSackItem(sackItem_arraysize, sackItem);
}

void NdpOptionSack::eraseSackItem(size_t k)
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = sackItem_arraysize - 1;
    SackItem *sackItem2 = (newSize == 0) ? nullptr : new SackItem[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sackItem2[i] = this->sackItem[i];
    for (i = k; i < newSize; i++)
        sackItem2[i] = this->sackItem[i+1];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

class NdpOptionSackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sackItem,
    };
  public:
    NdpOptionSackDescriptor();
    virtual ~NdpOptionSackDescriptor();

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

Register_ClassDescriptor(NdpOptionSackDescriptor)

NdpOptionSackDescriptor::NdpOptionSackDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionSack)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionSackDescriptor::~NdpOptionSackDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionSackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionSack *>(obj)!=nullptr;
}

const char **NdpOptionSackDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionSackDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionSackDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NdpOptionSackDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_sackItem
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionSackDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NdpOptionSackDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sackItem") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionSackDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ndp::SackItem",    // FIELD_sackItem
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionSackDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionSackDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionSackDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSack *pp = (NdpOptionSack *)object; (void)pp;
    switch (field) {
        case FIELD_sackItem: return pp->getSackItemArraySize();
        default: return 0;
    }
}

const char *NdpOptionSackDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSack *pp = (NdpOptionSack *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionSackDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSack *pp = (NdpOptionSack *)object; (void)pp;
    switch (field) {
        case FIELD_sackItem: {std::stringstream out; out << pp->getSackItem(i); return out.str();}
        default: return "";
    }
}

bool NdpOptionSackDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSack *pp = (NdpOptionSack *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NdpOptionSackDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_sackItem: return omnetpp::opp_typename(typeid(SackItem));
        default: return nullptr;
    };
}

void *NdpOptionSackDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionSack *pp = (NdpOptionSack *)object; (void)pp;
    switch (field) {
        case FIELD_sackItem: return toVoidPtr(&pp->getSackItem(i)); break;
        default: return nullptr;
    }
}

Register_Class(NdpOptionTimestamp)

NdpOptionTimestamp::NdpOptionTimestamp() : ::inet::ndp::NdpOption()
{
    this->setKind(NDPOPTION_TIMESTAMP);
    this->setLength(10);

}

NdpOptionTimestamp::NdpOptionTimestamp(const NdpOptionTimestamp& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionTimestamp::~NdpOptionTimestamp()
{
}

NdpOptionTimestamp& NdpOptionTimestamp::operator=(const NdpOptionTimestamp& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionTimestamp::copy(const NdpOptionTimestamp& other)
{
    this->senderTimestamp = other.senderTimestamp;
    this->echoedTimestamp = other.echoedTimestamp;
}

void NdpOptionTimestamp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
    doParsimPacking(b,this->senderTimestamp);
    doParsimPacking(b,this->echoedTimestamp);
}

void NdpOptionTimestamp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->senderTimestamp);
    doParsimUnpacking(b,this->echoedTimestamp);
}

uint32_t NdpOptionTimestamp::getSenderTimestamp() const
{
    return this->senderTimestamp;
}

void NdpOptionTimestamp::setSenderTimestamp(uint32_t senderTimestamp)
{
    this->senderTimestamp = senderTimestamp;
}

uint32_t NdpOptionTimestamp::getEchoedTimestamp() const
{
    return this->echoedTimestamp;
}

void NdpOptionTimestamp::setEchoedTimestamp(uint32_t echoedTimestamp)
{
    this->echoedTimestamp = echoedTimestamp;
}

class NdpOptionTimestampDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_senderTimestamp,
        FIELD_echoedTimestamp,
    };
  public:
    NdpOptionTimestampDescriptor();
    virtual ~NdpOptionTimestampDescriptor();

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

Register_ClassDescriptor(NdpOptionTimestampDescriptor)

NdpOptionTimestampDescriptor::NdpOptionTimestampDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionTimestamp)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionTimestampDescriptor::~NdpOptionTimestampDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionTimestampDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionTimestamp *>(obj)!=nullptr;
}

const char **NdpOptionTimestampDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionTimestampDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionTimestampDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NdpOptionTimestampDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderTimestamp
        FD_ISEDITABLE,    // FIELD_echoedTimestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionTimestampDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NdpOptionTimestampDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "senderTimestamp") == 0) return base+0;
    if (fieldName[0] == 'e' && strcmp(fieldName, "echoedTimestamp") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionTimestampDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_senderTimestamp
        "uint32_t",    // FIELD_echoedTimestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionTimestampDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionTimestampDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionTimestampDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionTimestamp *pp = (NdpOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpOptionTimestampDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionTimestamp *pp = (NdpOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionTimestampDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionTimestamp *pp = (NdpOptionTimestamp *)object; (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: return ulong2string(pp->getSenderTimestamp());
        case FIELD_echoedTimestamp: return ulong2string(pp->getEchoedTimestamp());
        default: return "";
    }
}

bool NdpOptionTimestampDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionTimestamp *pp = (NdpOptionTimestamp *)object; (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: pp->setSenderTimestamp(string2ulong(value)); return true;
        case FIELD_echoedTimestamp: pp->setEchoedTimestamp(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpOptionTimestampDescriptor::getFieldStructName(int field) const
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

void *NdpOptionTimestampDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionTimestamp *pp = (NdpOptionTimestamp *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpOptionUnknown)

NdpOptionUnknown::NdpOptionUnknown() : ::inet::ndp::NdpOption()
{
    this->setKind(static_cast<NdpOptionNumbers>(-1));

}

NdpOptionUnknown::NdpOptionUnknown(const NdpOptionUnknown& other) : ::inet::ndp::NdpOption(other)
{
    copy(other);
}

NdpOptionUnknown::~NdpOptionUnknown()
{
    delete [] this->bytes;
}

NdpOptionUnknown& NdpOptionUnknown::operator=(const NdpOptionUnknown& other)
{
    if (this == &other) return *this;
    ::inet::ndp::NdpOption::operator=(other);
    copy(other);
    return *this;
}

void NdpOptionUnknown::copy(const NdpOptionUnknown& other)
{
    delete [] this->bytes;
    this->bytes = (other.bytes_arraysize==0) ? nullptr : new uint8_t[other.bytes_arraysize];
    bytes_arraysize = other.bytes_arraysize;
    for (size_t i = 0; i < bytes_arraysize; i++) {
        this->bytes[i] = other.bytes[i];
    }
}

void NdpOptionUnknown::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndp::NdpOption::parsimPack(b);
    b->pack(bytes_arraysize);
    doParsimArrayPacking(b,this->bytes,bytes_arraysize);
}

void NdpOptionUnknown::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndp::NdpOption::parsimUnpack(b);
    delete [] this->bytes;
    b->unpack(bytes_arraysize);
    if (bytes_arraysize == 0) {
        this->bytes = nullptr;
    } else {
        this->bytes = new uint8_t[bytes_arraysize];
        doParsimArrayUnpacking(b,this->bytes,bytes_arraysize);
    }
}

size_t NdpOptionUnknown::getBytesArraySize() const
{
    return bytes_arraysize;
}

uint8_t NdpOptionUnknown::getBytes(size_t k) const
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size bytes_arraysize indexed by %lu", (unsigned long)k);
    return this->bytes[k];
}

void NdpOptionUnknown::setBytesArraySize(size_t newSize)
{
    uint8_t *bytes2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = bytes_arraysize < newSize ? bytes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        bytes2[i] = this->bytes[i];
    for (size_t i = minSize; i < newSize; i++)
        bytes2[i] = 0;
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

void NdpOptionUnknown::setBytes(size_t k, uint8_t bytes)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    this->bytes[k] = bytes;
}

void NdpOptionUnknown::insertBytes(size_t k, uint8_t bytes)
{
    if (k > bytes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = bytes_arraysize + 1;
    uint8_t *bytes2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bytes2[i] = this->bytes[i];
    bytes2[k] = bytes;
    for (i = k + 1; i < newSize; i++)
        bytes2[i] = this->bytes[i-1];
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

void NdpOptionUnknown::insertBytes(uint8_t bytes)
{
    insertBytes(bytes_arraysize, bytes);
}

void NdpOptionUnknown::eraseBytes(size_t k)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = bytes_arraysize - 1;
    uint8_t *bytes2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bytes2[i] = this->bytes[i];
    for (i = k; i < newSize; i++)
        bytes2[i] = this->bytes[i+1];
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

class NdpOptionUnknownDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_bytes,
    };
  public:
    NdpOptionUnknownDescriptor();
    virtual ~NdpOptionUnknownDescriptor();

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

Register_ClassDescriptor(NdpOptionUnknownDescriptor)

NdpOptionUnknownDescriptor::NdpOptionUnknownDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpOptionUnknown)), "inet::ndp::NdpOption")
{
    propertynames = nullptr;
}

NdpOptionUnknownDescriptor::~NdpOptionUnknownDescriptor()
{
    delete[] propertynames;
}

bool NdpOptionUnknownDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpOptionUnknown *>(obj)!=nullptr;
}

const char **NdpOptionUnknownDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpOptionUnknownDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpOptionUnknownDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NdpOptionUnknownDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_bytes
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NdpOptionUnknownDescriptor::getFieldName(int field) const
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
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NdpOptionUnknownDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'b' && strcmp(fieldName, "bytes") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpOptionUnknownDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_bytes
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpOptionUnknownDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpOptionUnknownDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpOptionUnknownDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpOptionUnknown *pp = (NdpOptionUnknown *)object; (void)pp;
    switch (field) {
        case FIELD_bytes: return pp->getBytesArraySize();
        default: return 0;
    }
}

const char *NdpOptionUnknownDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionUnknown *pp = (NdpOptionUnknown *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpOptionUnknownDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionUnknown *pp = (NdpOptionUnknown *)object; (void)pp;
    switch (field) {
        case FIELD_bytes: return ulong2string(pp->getBytes(i));
        default: return "";
    }
}

bool NdpOptionUnknownDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpOptionUnknown *pp = (NdpOptionUnknown *)object; (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpOptionUnknownDescriptor::getFieldStructName(int field) const
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

void *NdpOptionUnknownDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpOptionUnknown *pp = (NdpOptionUnknown *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NdpHeader)

NdpHeader::NdpHeader() : ::inet::TransportHeaderBase()
{
    this->setChunkLength(NDP_MIN_HEADER_LENGTH);

}

NdpHeader::NdpHeader(const NdpHeader& other) : ::inet::TransportHeaderBase(other)
{
    copy(other);
}

NdpHeader::~NdpHeader()
{
    for (size_t i = 0; i < headerOption_arraysize; i++)
        delete this->headerOption[i];
    delete [] this->headerOption;
}

NdpHeader& NdpHeader::operator=(const NdpHeader& other)
{
    if (this == &other) return *this;
    ::inet::TransportHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void NdpHeader::copy(const NdpHeader& other)
{
    this->srcPort = other.srcPort;
    this->destPort = other.destPort;
    this->ackNo = other.ackNo;
    this->nackNo = other.nackNo;
    this->isHeader_ = other.isHeader_;
    this->isPullPacket_ = other.isPullPacket_;
    this->isDataPacket_ = other.isDataPacket_;
    this->isLongFlow_ = other.isLongFlow_;
    this->priorityValue = other.priorityValue;
    this->numPacketsToSend = other.numPacketsToSend;
    this->pullSequenceNumber = other.pullSequenceNumber;
    this->dataSequenceNumber = other.dataSequenceNumber;
    this->isLastPktToSend_ = other.isLastPktToSend_;
    this->ackBit = other.ackBit;
    this->nackBit = other.nackBit;
    this->headerLength = other.headerLength;
    this->urgBit = other.urgBit;
    this->pshBit = other.pshBit;
    this->rstBit = other.rstBit;
    this->synBit = other.synBit;
    this->finBit = other.finBit;
    this->window = other.window;
    this->urgentPointer = other.urgentPointer;
    for (size_t i = 0; i < headerOption_arraysize; i++)
        delete this->headerOption[i];
    delete [] this->headerOption;
    this->headerOption = (other.headerOption_arraysize==0) ? nullptr : new NdpOption *[other.headerOption_arraysize];
    headerOption_arraysize = other.headerOption_arraysize;
    for (size_t i = 0; i < headerOption_arraysize; i++) {
        this->headerOption[i] = other.headerOption[i];
        if (this->headerOption[i] != nullptr) {
            this->headerOption[i] = this->headerOption[i]->dup();
        }
    }
}

void NdpHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TransportHeaderBase::parsimPack(b);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->destPort);
    doParsimPacking(b,this->ackNo);
    doParsimPacking(b,this->nackNo);
    doParsimPacking(b,this->isHeader_);
    doParsimPacking(b,this->isPullPacket_);
    doParsimPacking(b,this->isDataPacket_);
    doParsimPacking(b,this->isLongFlow_);
    doParsimPacking(b,this->priorityValue);
    doParsimPacking(b,this->numPacketsToSend);
    doParsimPacking(b,this->pullSequenceNumber);
    doParsimPacking(b,this->dataSequenceNumber);
    doParsimPacking(b,this->isLastPktToSend_);
    doParsimPacking(b,this->ackBit);
    doParsimPacking(b,this->nackBit);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->urgBit);
    doParsimPacking(b,this->pshBit);
    doParsimPacking(b,this->rstBit);
    doParsimPacking(b,this->synBit);
    doParsimPacking(b,this->finBit);
    doParsimPacking(b,this->window);
    doParsimPacking(b,this->urgentPointer);
    b->pack(headerOption_arraysize);
    doParsimArrayPacking(b,this->headerOption,headerOption_arraysize);
}

void NdpHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TransportHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->destPort);
    doParsimUnpacking(b,this->ackNo);
    doParsimUnpacking(b,this->nackNo);
    doParsimUnpacking(b,this->isHeader_);
    doParsimUnpacking(b,this->isPullPacket_);
    doParsimUnpacking(b,this->isDataPacket_);
    doParsimUnpacking(b,this->isLongFlow_);
    doParsimUnpacking(b,this->priorityValue);
    doParsimUnpacking(b,this->numPacketsToSend);
    doParsimUnpacking(b,this->pullSequenceNumber);
    doParsimUnpacking(b,this->dataSequenceNumber);
    doParsimUnpacking(b,this->isLastPktToSend_);
    doParsimUnpacking(b,this->ackBit);
    doParsimUnpacking(b,this->nackBit);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->urgBit);
    doParsimUnpacking(b,this->pshBit);
    doParsimUnpacking(b,this->rstBit);
    doParsimUnpacking(b,this->synBit);
    doParsimUnpacking(b,this->finBit);
    doParsimUnpacking(b,this->window);
    doParsimUnpacking(b,this->urgentPointer);
    delete [] this->headerOption;
    b->unpack(headerOption_arraysize);
    if (headerOption_arraysize == 0) {
        this->headerOption = nullptr;
    } else {
        this->headerOption = new NdpOption *[headerOption_arraysize];
        doParsimArrayUnpacking(b,this->headerOption,headerOption_arraysize);
    }
}

unsigned short NdpHeader::getSrcPort() const
{
    return this->srcPort;
}

void NdpHeader::setSrcPort(unsigned short srcPort)
{
    handleChange();
    this->srcPort = srcPort;
}

unsigned short NdpHeader::getDestPort() const
{
    return this->destPort;
}

void NdpHeader::setDestPort(unsigned short destPort)
{
    handleChange();
    this->destPort = destPort;
}

unsigned int NdpHeader::getAckNo() const
{
    return this->ackNo;
}

void NdpHeader::setAckNo(unsigned int ackNo)
{
    handleChange();
    this->ackNo = ackNo;
}

unsigned int NdpHeader::getNackNo() const
{
    return this->nackNo;
}

void NdpHeader::setNackNo(unsigned int nackNo)
{
    handleChange();
    this->nackNo = nackNo;
}

bool NdpHeader::isHeader() const
{
    return this->isHeader_;
}

void NdpHeader::setIsHeader(bool isHeader)
{
    handleChange();
    this->isHeader_ = isHeader;
}

bool NdpHeader::isPullPacket() const
{
    return this->isPullPacket_;
}

void NdpHeader::setIsPullPacket(bool isPullPacket)
{
    handleChange();
    this->isPullPacket_ = isPullPacket;
}

bool NdpHeader::isDataPacket() const
{
    return this->isDataPacket_;
}

void NdpHeader::setIsDataPacket(bool isDataPacket)
{
    handleChange();
    this->isDataPacket_ = isDataPacket;
}

bool NdpHeader::isLongFlow() const
{
    return this->isLongFlow_;
}

void NdpHeader::setIsLongFlow(bool isLongFlow)
{
    handleChange();
    this->isLongFlow_ = isLongFlow;
}

unsigned int NdpHeader::getPriorityValue() const
{
    return this->priorityValue;
}

void NdpHeader::setPriorityValue(unsigned int priorityValue)
{
    handleChange();
    this->priorityValue = priorityValue;
}

unsigned int NdpHeader::getNumPacketsToSend() const
{
    return this->numPacketsToSend;
}

void NdpHeader::setNumPacketsToSend(unsigned int numPacketsToSend)
{
    handleChange();
    this->numPacketsToSend = numPacketsToSend;
}

unsigned int NdpHeader::getPullSequenceNumber() const
{
    return this->pullSequenceNumber;
}

void NdpHeader::setPullSequenceNumber(unsigned int pullSequenceNumber)
{
    handleChange();
    this->pullSequenceNumber = pullSequenceNumber;
}

unsigned int NdpHeader::getDataSequenceNumber() const
{
    return this->dataSequenceNumber;
}

void NdpHeader::setDataSequenceNumber(unsigned int dataSequenceNumber)
{
    handleChange();
    this->dataSequenceNumber = dataSequenceNumber;
}

bool NdpHeader::isLastPktToSend() const
{
    return this->isLastPktToSend_;
}

void NdpHeader::setIsLastPktToSend(bool isLastPktToSend)
{
    handleChange();
    this->isLastPktToSend_ = isLastPktToSend;
}

bool NdpHeader::getAckBit() const
{
    return this->ackBit;
}

void NdpHeader::setAckBit(bool ackBit)
{
    handleChange();
    this->ackBit = ackBit;
}

bool NdpHeader::getNackBit() const
{
    return this->nackBit;
}

void NdpHeader::setNackBit(bool nackBit)
{
    handleChange();
    this->nackBit = nackBit;
}

B NdpHeader::getHeaderLength() const
{
    return this->headerLength;
}

void NdpHeader::setHeaderLength(B headerLength)
{
    handleChange();
    this->headerLength = headerLength;
}

bool NdpHeader::getUrgBit() const
{
    return this->urgBit;
}

void NdpHeader::setUrgBit(bool urgBit)
{
    handleChange();
    this->urgBit = urgBit;
}

bool NdpHeader::getPshBit() const
{
    return this->pshBit;
}

void NdpHeader::setPshBit(bool pshBit)
{
    handleChange();
    this->pshBit = pshBit;
}

bool NdpHeader::getRstBit() const
{
    return this->rstBit;
}

void NdpHeader::setRstBit(bool rstBit)
{
    handleChange();
    this->rstBit = rstBit;
}

bool NdpHeader::getSynBit() const
{
    return this->synBit;
}

void NdpHeader::setSynBit(bool synBit)
{
    handleChange();
    this->synBit = synBit;
}

bool NdpHeader::getFinBit() const
{
    return this->finBit;
}

void NdpHeader::setFinBit(bool finBit)
{
    handleChange();
    this->finBit = finBit;
}

unsigned short NdpHeader::getWindow() const
{
    return this->window;
}

void NdpHeader::setWindow(unsigned short window)
{
    handleChange();
    this->window = window;
}

unsigned short NdpHeader::getUrgentPointer() const
{
    return this->urgentPointer;
}

void NdpHeader::setUrgentPointer(unsigned short urgentPointer)
{
    handleChange();
    this->urgentPointer = urgentPointer;
}

size_t NdpHeader::getHeaderOptionArraySize() const
{
    return headerOption_arraysize;
}

const NdpOption * NdpHeader::getHeaderOption(size_t k) const
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size headerOption_arraysize indexed by %lu", (unsigned long)k);
    return this->headerOption[k];
}

void NdpHeader::setHeaderOptionArraySize(size_t newSize)
{
    handleChange();
    NdpOption * *headerOption2 = (newSize==0) ? nullptr : new NdpOption *[newSize];
    size_t minSize = headerOption_arraysize < newSize ? headerOption_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        headerOption2[i] = this->headerOption[i];
    for (size_t i = minSize; i < newSize; i++)
        headerOption2[i] = nullptr;
    for (size_t i = newSize; i < headerOption_arraysize; i++)
        delete headerOption[i];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

void NdpHeader::setHeaderOption(size_t k, NdpOption * headerOption)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    if (this->headerOption[k] != nullptr) throw omnetpp::cRuntimeError("setHeaderOption(): a value is already set, remove it first with dropHeaderOption()");
    this->headerOption[k] = headerOption;
}

NdpOption * NdpHeader::dropHeaderOption(size_t k)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    NdpOption * retval = this->headerOption[k];
    this->headerOption[k] = nullptr;
    return retval;
}

void NdpHeader::insertHeaderOption(size_t k, NdpOption * headerOption)
{
    handleChange();
    if (k > headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = headerOption_arraysize + 1;
    NdpOption * *headerOption2 = new NdpOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        headerOption2[i] = this->headerOption[i];
    headerOption2[k] = headerOption;
    for (i = k + 1; i < newSize; i++)
        headerOption2[i] = this->headerOption[i-1];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

void NdpHeader::insertHeaderOption(NdpOption * headerOption)
{
    insertHeaderOption(headerOption_arraysize, headerOption);
}

void NdpHeader::eraseHeaderOption(size_t k)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = headerOption_arraysize - 1;
    NdpOption * *headerOption2 = (newSize == 0) ? nullptr : new NdpOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        headerOption2[i] = this->headerOption[i];
    for (i = k; i < newSize; i++)
        headerOption2[i] = this->headerOption[i+1];
    delete this->headerOption[k];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

class NdpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_srcPort,
        FIELD_destPort,
        FIELD_ackNo,
        FIELD_nackNo,
        FIELD_isHeader,
        FIELD_isPullPacket,
        FIELD_isDataPacket,
        FIELD_isLongFlow,
        FIELD_priorityValue,
        FIELD_numPacketsToSend,
        FIELD_pullSequenceNumber,
        FIELD_dataSequenceNumber,
        FIELD_isLastPktToSend,
        FIELD_ackBit,
        FIELD_nackBit,
        FIELD_headerLength,
        FIELD_urgBit,
        FIELD_pshBit,
        FIELD_rstBit,
        FIELD_synBit,
        FIELD_finBit,
        FIELD_window,
        FIELD_urgentPointer,
        FIELD_headerOption,
    };
  public:
    NdpHeaderDescriptor();
    virtual ~NdpHeaderDescriptor();

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

Register_ClassDescriptor(NdpHeaderDescriptor)

NdpHeaderDescriptor::NdpHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpHeader)), "inet::TransportHeaderBase")
{
    propertynames = nullptr;
}

NdpHeaderDescriptor::~NdpHeaderDescriptor()
{
    delete[] propertynames;
}

bool NdpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpHeader *>(obj)!=nullptr;
}

const char **NdpHeaderDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpHeaderDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 24+basedesc->getFieldCount() : 24;
}

unsigned int NdpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISEDITABLE,    // FIELD_destPort
        FD_ISEDITABLE,    // FIELD_ackNo
        FD_ISEDITABLE,    // FIELD_nackNo
        FD_ISEDITABLE,    // FIELD_isHeader
        FD_ISEDITABLE,    // FIELD_isPullPacket
        FD_ISEDITABLE,    // FIELD_isDataPacket
        FD_ISEDITABLE,    // FIELD_isLongFlow
        FD_ISEDITABLE,    // FIELD_priorityValue
        FD_ISEDITABLE,    // FIELD_numPacketsToSend
        FD_ISEDITABLE,    // FIELD_pullSequenceNumber
        FD_ISEDITABLE,    // FIELD_dataSequenceNumber
        FD_ISEDITABLE,    // FIELD_isLastPktToSend
        FD_ISEDITABLE,    // FIELD_ackBit
        FD_ISEDITABLE,    // FIELD_nackBit
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_urgBit
        FD_ISEDITABLE,    // FIELD_pshBit
        FD_ISEDITABLE,    // FIELD_rstBit
        FD_ISEDITABLE,    // FIELD_synBit
        FD_ISEDITABLE,    // FIELD_finBit
        FD_ISEDITABLE,    // FIELD_window
        FD_ISEDITABLE,    // FIELD_urgentPointer
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_headerOption
    };
    return (field >= 0 && field < 24) ? fieldTypeFlags[field] : 0;
}

const char *NdpHeaderDescriptor::getFieldName(int field) const
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
    };
    return (field >= 0 && field < 24) ? fieldNames[field] : nullptr;
}

int NdpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "srcPort") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destPort") == 0) return base+1;
    if (fieldName[0] == 'a' && strcmp(fieldName, "ackNo") == 0) return base+2;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nackNo") == 0) return base+3;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isHeader") == 0) return base+4;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isPullPacket") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isDataPacket") == 0) return base+6;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isLongFlow") == 0) return base+7;
    if (fieldName[0] == 'p' && strcmp(fieldName, "priorityValue") == 0) return base+8;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPacketsToSend") == 0) return base+9;
    if (fieldName[0] == 'p' && strcmp(fieldName, "pullSequenceNumber") == 0) return base+10;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dataSequenceNumber") == 0) return base+11;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isLastPktToSend") == 0) return base+12;
    if (fieldName[0] == 'a' && strcmp(fieldName, "ackBit") == 0) return base+13;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nackBit") == 0) return base+14;
    if (fieldName[0] == 'h' && strcmp(fieldName, "headerLength") == 0) return base+15;
    if (fieldName[0] == 'u' && strcmp(fieldName, "urgBit") == 0) return base+16;
    if (fieldName[0] == 'p' && strcmp(fieldName, "pshBit") == 0) return base+17;
    if (fieldName[0] == 'r' && strcmp(fieldName, "rstBit") == 0) return base+18;
    if (fieldName[0] == 's' && strcmp(fieldName, "synBit") == 0) return base+19;
    if (fieldName[0] == 'f' && strcmp(fieldName, "finBit") == 0) return base+20;
    if (fieldName[0] == 'w' && strcmp(fieldName, "window") == 0) return base+21;
    if (fieldName[0] == 'u' && strcmp(fieldName, "urgentPointer") == 0) return base+22;
    if (fieldName[0] == 'h' && strcmp(fieldName, "headerOption") == 0) return base+23;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_srcPort
        "unsigned short",    // FIELD_destPort
        "unsigned int",    // FIELD_ackNo
        "unsigned int",    // FIELD_nackNo
        "bool",    // FIELD_isHeader
        "bool",    // FIELD_isPullPacket
        "bool",    // FIELD_isDataPacket
        "bool",    // FIELD_isLongFlow
        "unsigned int",    // FIELD_priorityValue
        "unsigned int",    // FIELD_numPacketsToSend
        "unsigned int",    // FIELD_pullSequenceNumber
        "unsigned int",    // FIELD_dataSequenceNumber
        "bool",    // FIELD_isLastPktToSend
        "bool",    // FIELD_ackBit
        "bool",    // FIELD_nackBit
        "inet::B",    // FIELD_headerLength
        "bool",    // FIELD_urgBit
        "bool",    // FIELD_pshBit
        "bool",    // FIELD_rstBit
        "bool",    // FIELD_synBit
        "bool",    // FIELD_finBit
        "unsigned short",    // FIELD_window
        "unsigned short",    // FIELD_urgentPointer
        "inet::ndp::NdpOption",    // FIELD_headerOption
    };
    return (field >= 0 && field < 24) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_headerOption: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NdpHeaderDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_headerOption:
            if (!strcmp(propertyname, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int NdpHeaderDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpHeader *pp = (NdpHeader *)object; (void)pp;
    switch (field) {
        case FIELD_headerOption: return pp->getHeaderOptionArraySize();
        default: return 0;
    }
}

const char *NdpHeaderDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpHeader *pp = (NdpHeader *)object; (void)pp;
    switch (field) {
        case FIELD_headerOption: { const NdpOption * value = pp->getHeaderOption(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string NdpHeaderDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpHeader *pp = (NdpHeader *)object; (void)pp;
    switch (field) {
        case FIELD_srcPort: return ulong2string(pp->getSrcPort());
        case FIELD_destPort: return ulong2string(pp->getDestPort());
        case FIELD_ackNo: return ulong2string(pp->getAckNo());
        case FIELD_nackNo: return ulong2string(pp->getNackNo());
        case FIELD_isHeader: return bool2string(pp->isHeader());
        case FIELD_isPullPacket: return bool2string(pp->isPullPacket());
        case FIELD_isDataPacket: return bool2string(pp->isDataPacket());
        case FIELD_isLongFlow: return bool2string(pp->isLongFlow());
        case FIELD_priorityValue: return ulong2string(pp->getPriorityValue());
        case FIELD_numPacketsToSend: return ulong2string(pp->getNumPacketsToSend());
        case FIELD_pullSequenceNumber: return ulong2string(pp->getPullSequenceNumber());
        case FIELD_dataSequenceNumber: return ulong2string(pp->getDataSequenceNumber());
        case FIELD_isLastPktToSend: return bool2string(pp->isLastPktToSend());
        case FIELD_ackBit: return bool2string(pp->getAckBit());
        case FIELD_nackBit: return bool2string(pp->getNackBit());
        case FIELD_headerLength: return unit2string(pp->getHeaderLength());
        case FIELD_urgBit: return bool2string(pp->getUrgBit());
        case FIELD_pshBit: return bool2string(pp->getPshBit());
        case FIELD_rstBit: return bool2string(pp->getRstBit());
        case FIELD_synBit: return bool2string(pp->getSynBit());
        case FIELD_finBit: return bool2string(pp->getFinBit());
        case FIELD_window: return ulong2string(pp->getWindow());
        case FIELD_urgentPointer: return ulong2string(pp->getUrgentPointer());
        case FIELD_headerOption: {std::stringstream out; out << pp->getHeaderOption(i); return out.str();}
        default: return "";
    }
}

bool NdpHeaderDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpHeader *pp = (NdpHeader *)object; (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(string2ulong(value)); return true;
        case FIELD_destPort: pp->setDestPort(string2ulong(value)); return true;
        case FIELD_ackNo: pp->setAckNo(string2ulong(value)); return true;
        case FIELD_nackNo: pp->setNackNo(string2ulong(value)); return true;
        case FIELD_isHeader: pp->setIsHeader(string2bool(value)); return true;
        case FIELD_isPullPacket: pp->setIsPullPacket(string2bool(value)); return true;
        case FIELD_isDataPacket: pp->setIsDataPacket(string2bool(value)); return true;
        case FIELD_isLongFlow: pp->setIsLongFlow(string2bool(value)); return true;
        case FIELD_priorityValue: pp->setPriorityValue(string2ulong(value)); return true;
        case FIELD_numPacketsToSend: pp->setNumPacketsToSend(string2ulong(value)); return true;
        case FIELD_pullSequenceNumber: pp->setPullSequenceNumber(string2ulong(value)); return true;
        case FIELD_dataSequenceNumber: pp->setDataSequenceNumber(string2ulong(value)); return true;
        case FIELD_isLastPktToSend: pp->setIsLastPktToSend(string2bool(value)); return true;
        case FIELD_ackBit: pp->setAckBit(string2bool(value)); return true;
        case FIELD_nackBit: pp->setNackBit(string2bool(value)); return true;
        case FIELD_headerLength: pp->setHeaderLength(B(string2long(value))); return true;
        case FIELD_urgBit: pp->setUrgBit(string2bool(value)); return true;
        case FIELD_pshBit: pp->setPshBit(string2bool(value)); return true;
        case FIELD_rstBit: pp->setRstBit(string2bool(value)); return true;
        case FIELD_synBit: pp->setSynBit(string2bool(value)); return true;
        case FIELD_finBit: pp->setFinBit(string2bool(value)); return true;
        case FIELD_window: pp->setWindow(string2ulong(value)); return true;
        case FIELD_urgentPointer: pp->setUrgentPointer(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NdpHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_headerOption: return omnetpp::opp_typename(typeid(NdpOption));
        default: return nullptr;
    };
}

void *NdpHeaderDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpHeader *pp = (NdpHeader *)object; (void)pp;
    switch (field) {
        case FIELD_headerOption: return toVoidPtr(pp->getHeaderOption(i)); break;
        default: return nullptr;
    }
}

} // namespace ndp
} // namespace inet

