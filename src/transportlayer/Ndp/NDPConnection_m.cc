//
// Generated file, do not edit! Created by nedtool 5.6 from transportlayer/Ndp/NDPConnection.msg.
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
#include "NDPConnection_m.h"

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

class NDPAlgorithmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NDPAlgorithmDescriptor();
    virtual ~NDPAlgorithmDescriptor();

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

Register_ClassDescriptor(NDPAlgorithmDescriptor)

NDPAlgorithmDescriptor::NDPAlgorithmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NDPAlgorithm)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPAlgorithmDescriptor::~NDPAlgorithmDescriptor()
{
    delete[] propertynames;
}

bool NDPAlgorithmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPAlgorithm *>(obj)!=nullptr;
}

const char **NDPAlgorithmDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPAlgorithmDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPAlgorithmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NDPAlgorithmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NDPAlgorithmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NDPAlgorithmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPAlgorithmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NDPAlgorithmDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPAlgorithmDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPAlgorithmDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPAlgorithm *pp = (NDPAlgorithm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPAlgorithmDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAlgorithm *pp = (NDPAlgorithm *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPAlgorithmDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPAlgorithm *pp = (NDPAlgorithm *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NDPAlgorithmDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPAlgorithm *pp = (NDPAlgorithm *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPAlgorithmDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NDPAlgorithmDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPAlgorithm *pp = (NDPAlgorithm *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

class NdpStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_active,
        FIELD_request_id,
        FIELD_internal_request_id,
        FIELD_isLongFlow,
        FIELD_isHeader,
        FIELD_IW,
        FIELD_connFinished,
        FIELD_numPacketsToGet,
        FIELD_numPacketsToSend,
        FIELD_isSender,
        FIELD_isReceiver,
        FIELD_priorityValue,
        FIELD_numRcvdPkt,
        FIELD_numRcvTrimmedHeader,
        FIELD_numberReceivedPackets,
        FIELD_numberSentPackets,
        FIELD_request_rexmit_count,
        FIELD_request_rexmit_timeout,
        FIELD_numPullsTimeOuts,
        FIELD_connNotAddedYet,
        FIELD_isfinalReceivedPrintedOut,
        FIELD_snd_mss,
        FIELD_iss,
        FIELD_irs,
        FIELD_syn_rexmit_count,
        FIELD_syn_rexmit_timeout,
    };
  public:
    NdpStateVariablesDescriptor();
    virtual ~NdpStateVariablesDescriptor();

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

Register_ClassDescriptor(NdpStateVariablesDescriptor)

NdpStateVariablesDescriptor::NdpStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NdpStateVariables)), "")
{
    propertynames = nullptr;
}

NdpStateVariablesDescriptor::~NdpStateVariablesDescriptor()
{
    delete[] propertynames;
}

bool NdpStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NdpStateVariables *>(obj)!=nullptr;
}

const char **NdpStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NdpStateVariablesDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    if (!strcmp(propertyname, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NdpStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 26+basedesc->getFieldCount() : 26;
}

unsigned int NdpStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_active
        0,    // FIELD_request_id
        0,    // FIELD_internal_request_id
        0,    // FIELD_isLongFlow
        0,    // FIELD_isHeader
        0,    // FIELD_IW
        0,    // FIELD_connFinished
        0,    // FIELD_numPacketsToGet
        0,    // FIELD_numPacketsToSend
        0,    // FIELD_isSender
        0,    // FIELD_isReceiver
        0,    // FIELD_priorityValue
        0,    // FIELD_numRcvdPkt
        0,    // FIELD_numRcvTrimmedHeader
        0,    // FIELD_numberReceivedPackets
        0,    // FIELD_numberSentPackets
        0,    // FIELD_request_rexmit_count
        0,    // FIELD_request_rexmit_timeout
        0,    // FIELD_numPullsTimeOuts
        0,    // FIELD_connNotAddedYet
        0,    // FIELD_isfinalReceivedPrintedOut
        0,    // FIELD_snd_mss
        0,    // FIELD_iss
        0,    // FIELD_irs
        0,    // FIELD_syn_rexmit_count
        0,    // FIELD_syn_rexmit_timeout
    };
    return (field >= 0 && field < 26) ? fieldTypeFlags[field] : 0;
}

const char *NdpStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "active",
        "request_id",
        "internal_request_id",
        "isLongFlow",
        "isHeader",
        "IW",
        "connFinished",
        "numPacketsToGet",
        "numPacketsToSend",
        "isSender",
        "isReceiver",
        "priorityValue",
        "numRcvdPkt",
        "numRcvTrimmedHeader",
        "numberReceivedPackets",
        "numberSentPackets",
        "request_rexmit_count",
        "request_rexmit_timeout",
        "numPullsTimeOuts",
        "connNotAddedYet",
        "isfinalReceivedPrintedOut",
        "snd_mss",
        "iss",
        "irs",
        "syn_rexmit_count",
        "syn_rexmit_timeout",
    };
    return (field >= 0 && field < 26) ? fieldNames[field] : nullptr;
}

int NdpStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "active") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "request_id") == 0) return base+1;
    if (fieldName[0] == 'i' && strcmp(fieldName, "internal_request_id") == 0) return base+2;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isLongFlow") == 0) return base+3;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isHeader") == 0) return base+4;
    if (fieldName[0] == 'I' && strcmp(fieldName, "IW") == 0) return base+5;
    if (fieldName[0] == 'c' && strcmp(fieldName, "connFinished") == 0) return base+6;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPacketsToGet") == 0) return base+7;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPacketsToSend") == 0) return base+8;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isSender") == 0) return base+9;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isReceiver") == 0) return base+10;
    if (fieldName[0] == 'p' && strcmp(fieldName, "priorityValue") == 0) return base+11;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numRcvdPkt") == 0) return base+12;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numRcvTrimmedHeader") == 0) return base+13;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numberReceivedPackets") == 0) return base+14;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numberSentPackets") == 0) return base+15;
    if (fieldName[0] == 'r' && strcmp(fieldName, "request_rexmit_count") == 0) return base+16;
    if (fieldName[0] == 'r' && strcmp(fieldName, "request_rexmit_timeout") == 0) return base+17;
    if (fieldName[0] == 'n' && strcmp(fieldName, "numPullsTimeOuts") == 0) return base+18;
    if (fieldName[0] == 'c' && strcmp(fieldName, "connNotAddedYet") == 0) return base+19;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isfinalReceivedPrintedOut") == 0) return base+20;
    if (fieldName[0] == 's' && strcmp(fieldName, "snd_mss") == 0) return base+21;
    if (fieldName[0] == 'i' && strcmp(fieldName, "iss") == 0) return base+22;
    if (fieldName[0] == 'i' && strcmp(fieldName, "irs") == 0) return base+23;
    if (fieldName[0] == 's' && strcmp(fieldName, "syn_rexmit_count") == 0) return base+24;
    if (fieldName[0] == 's' && strcmp(fieldName, "syn_rexmit_timeout") == 0) return base+25;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NdpStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_active
        "unsigned int",    // FIELD_request_id
        "unsigned int",    // FIELD_internal_request_id
        "bool",    // FIELD_isLongFlow
        "bool",    // FIELD_isHeader
        "uint32",    // FIELD_IW
        "bool",    // FIELD_connFinished
        "uint32",    // FIELD_numPacketsToGet
        "uint32",    // FIELD_numPacketsToSend
        "bool",    // FIELD_isSender
        "bool",    // FIELD_isReceiver
        "unsigned int",    // FIELD_priorityValue
        "unsigned int",    // FIELD_numRcvdPkt
        "unsigned int",    // FIELD_numRcvTrimmedHeader
        "uint32",    // FIELD_numberReceivedPackets
        "uint32",    // FIELD_numberSentPackets
        "int",    // FIELD_request_rexmit_count
        "omnetpp::simtime_t",    // FIELD_request_rexmit_timeout
        "uint32",    // FIELD_numPullsTimeOuts
        "bool",    // FIELD_connNotAddedYet
        "bool",    // FIELD_isfinalReceivedPrintedOut
        "uint32",    // FIELD_snd_mss
        "uint32",    // FIELD_iss
        "uint32",    // FIELD_irs
        "int",    // FIELD_syn_rexmit_count
        "omnetpp::simtime_t",    // FIELD_syn_rexmit_timeout
    };
    return (field >= 0 && field < 26) ? fieldTypeStrings[field] : nullptr;
}

const char **NdpStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *NdpStateVariablesDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NdpStateVariablesDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NdpStateVariables *pp = (NdpStateVariables *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NdpStateVariablesDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpStateVariables *pp = (NdpStateVariables *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NdpStateVariablesDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NdpStateVariables *pp = (NdpStateVariables *)object; (void)pp;
    switch (field) {
        case FIELD_active: return bool2string(pp->active);
        case FIELD_request_id: return ulong2string(pp->request_id);
        case FIELD_internal_request_id: return ulong2string(pp->internal_request_id);
        case FIELD_isLongFlow: return bool2string(pp->isLongFlow);
        case FIELD_isHeader: return bool2string(pp->isHeader);
        case FIELD_IW: return ulong2string(pp->IW);
        case FIELD_connFinished: return bool2string(pp->connFinished);
        case FIELD_numPacketsToGet: return ulong2string(pp->numPacketsToGet);
        case FIELD_numPacketsToSend: return ulong2string(pp->numPacketsToSend);
        case FIELD_isSender: return bool2string(pp->isSender);
        case FIELD_isReceiver: return bool2string(pp->isReceiver);
        case FIELD_priorityValue: return ulong2string(pp->priorityValue);
        case FIELD_numRcvdPkt: return ulong2string(pp->numRcvdPkt);
        case FIELD_numRcvTrimmedHeader: return ulong2string(pp->numRcvTrimmedHeader);
        case FIELD_numberReceivedPackets: return ulong2string(pp->numberReceivedPackets);
        case FIELD_numberSentPackets: return ulong2string(pp->numberSentPackets);
        case FIELD_request_rexmit_count: return long2string(pp->request_rexmit_count);
        case FIELD_request_rexmit_timeout: return simtime2string(pp->request_rexmit_timeout);
        case FIELD_numPullsTimeOuts: return ulong2string(pp->numPullsTimeOuts);
        case FIELD_connNotAddedYet: return bool2string(pp->connNotAddedYet);
        case FIELD_isfinalReceivedPrintedOut: return bool2string(pp->isfinalReceivedPrintedOut);
        case FIELD_snd_mss: return ulong2string(pp->snd_mss);
        case FIELD_iss: return ulong2string(pp->iss);
        case FIELD_irs: return ulong2string(pp->irs);
        case FIELD_syn_rexmit_count: return long2string(pp->syn_rexmit_count);
        case FIELD_syn_rexmit_timeout: return simtime2string(pp->syn_rexmit_timeout);
        default: return "";
    }
}

bool NdpStateVariablesDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NdpStateVariables *pp = (NdpStateVariables *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NdpStateVariablesDescriptor::getFieldStructName(int field) const
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

void *NdpStateVariablesDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NdpStateVariables *pp = (NdpStateVariables *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

class NDPSendQueueDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_dataToSendQueue,
        FIELD_sentDataQueue,
    };
  public:
    NDPSendQueueDescriptor();
    virtual ~NDPSendQueueDescriptor();

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

Register_ClassDescriptor(NDPSendQueueDescriptor)

NDPSendQueueDescriptor::NDPSendQueueDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NDPSendQueue)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPSendQueueDescriptor::~NDPSendQueueDescriptor()
{
    delete[] propertynames;
}

bool NDPSendQueueDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPSendQueue *>(obj)!=nullptr;
}

const char **NDPSendQueueDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPSendQueueDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    if (!strcmp(propertyname, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPSendQueueDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NDPSendQueueDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_dataToSendQueue
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_sentDataQueue
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NDPSendQueueDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dataToSendQueue",
        "sentDataQueue",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NDPSendQueueDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dataToSendQueue") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sentDataQueue") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPSendQueueDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ChunkQueue",    // FIELD_dataToSendQueue
        "inet::ChunkQueue",    // FIELD_sentDataQueue
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPSendQueueDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPSendQueueDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPSendQueueDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPSendQueue *pp = (NDPSendQueue *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPSendQueueDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSendQueue *pp = (NDPSendQueue *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPSendQueueDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPSendQueue *pp = (NDPSendQueue *)object; (void)pp;
    switch (field) {
        case FIELD_dataToSendQueue: {std::stringstream out; out << pp->getDataToSendQueue(); return out.str();}
        case FIELD_sentDataQueue: {std::stringstream out; out << pp->getSentDataQueue(); return out.str();}
        default: return "";
    }
}

bool NDPSendQueueDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPSendQueue *pp = (NDPSendQueue *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPSendQueueDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_dataToSendQueue: return omnetpp::opp_typename(typeid(ChunkQueue));
        case FIELD_sentDataQueue: return omnetpp::opp_typename(typeid(ChunkQueue));
        default: return nullptr;
    };
}

void *NDPSendQueueDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPSendQueue *pp = (NDPSendQueue *)object; (void)pp;
    switch (field) {
        case FIELD_dataToSendQueue: return toVoidPtr(&pp->getDataToSendQueue()); break;
        case FIELD_sentDataQueue: return toVoidPtr(&pp->getSentDataQueue()); break;
        default: return nullptr;
    }
}

class NDPReceiveQueueDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_reorderBuffer,
    };
  public:
    NDPReceiveQueueDescriptor();
    virtual ~NDPReceiveQueueDescriptor();

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

Register_ClassDescriptor(NDPReceiveQueueDescriptor)

NDPReceiveQueueDescriptor::NDPReceiveQueueDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NDPReceiveQueue)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPReceiveQueueDescriptor::~NDPReceiveQueueDescriptor()
{
    delete[] propertynames;
}

bool NDPReceiveQueueDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPReceiveQueue *>(obj)!=nullptr;
}

const char **NDPReceiveQueueDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPReceiveQueueDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    if (!strcmp(propertyname, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPReceiveQueueDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NDPReceiveQueueDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_reorderBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NDPReceiveQueueDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reorderBuffer",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NDPReceiveQueueDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "reorderBuffer") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPReceiveQueueDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ReorderBuffer",    // FIELD_reorderBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPReceiveQueueDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPReceiveQueueDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPReceiveQueueDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPReceiveQueue *pp = (NDPReceiveQueue *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPReceiveQueueDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPReceiveQueue *pp = (NDPReceiveQueue *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NDPReceiveQueueDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPReceiveQueue *pp = (NDPReceiveQueue *)object; (void)pp;
    switch (field) {
        case FIELD_reorderBuffer: {std::stringstream out; out << pp->getReorderBuffer(); return out.str();}
        default: return "";
    }
}

bool NDPReceiveQueueDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPReceiveQueue *pp = (NDPReceiveQueue *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPReceiveQueueDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_reorderBuffer: return omnetpp::opp_typename(typeid(ReorderBuffer));
        default: return nullptr;
    };
}

void *NDPReceiveQueueDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPReceiveQueue *pp = (NDPReceiveQueue *)object; (void)pp;
    switch (field) {
        case FIELD_reorderBuffer: return toVoidPtr(&pp->getReorderBuffer()); break;
        default: return nullptr;
    }
}

class NDPConnectionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_socketId,
        FIELD_listeningSocketId,
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_state,
        FIELD_sendQueue,
        FIELD_receiveQueue,
        FIELD_ndpAlgorithm,
        FIELD_fsmState,
    };
  public:
    NDPConnectionDescriptor();
    virtual ~NDPConnectionDescriptor();

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

Register_ClassDescriptor(NDPConnectionDescriptor)

NDPConnectionDescriptor::NDPConnectionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndp::NDPConnection)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NDPConnectionDescriptor::~NDPConnectionDescriptor()
{
    delete[] propertynames;
}

bool NDPConnectionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NDPConnection *>(obj)!=nullptr;
}

const char **NDPConnectionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NDPConnectionDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    if (!strcmp(propertyname, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NDPConnectionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int NDPConnectionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_socketId
        0,    // FIELD_listeningSocketId
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        0,    // FIELD_localPort
        0,    // FIELD_remotePort
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_state
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_sendQueue
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_receiveQueue
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_ndpAlgorithm
        0,    // FIELD_fsmState
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *NDPConnectionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "socketId",
        "listeningSocketId",
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "state",
        "sendQueue",
        "receiveQueue",
        "ndpAlgorithm",
        "fsmState",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int NDPConnectionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "socketId") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "listeningSocketId") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localAddr") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remoteAddr") == 0) return base+3;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "remotePort") == 0) return base+5;
    if (fieldName[0] == 's' && strcmp(fieldName, "state") == 0) return base+6;
    if (fieldName[0] == 's' && strcmp(fieldName, "sendQueue") == 0) return base+7;
    if (fieldName[0] == 'r' && strcmp(fieldName, "receiveQueue") == 0) return base+8;
    if (fieldName[0] == 'n' && strcmp(fieldName, "ndpAlgorithm") == 0) return base+9;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fsmState") == 0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NDPConnectionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_socketId
        "int",    // FIELD_listeningSocketId
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "inet::ndp::NdpStateVariables",    // FIELD_state
        "inet::ndp::NDPSendQueue",    // FIELD_sendQueue
        "inet::ndp::NDPReceiveQueue",    // FIELD_receiveQueue
        "inet::ndp::NDPAlgorithm",    // FIELD_ndpAlgorithm
        "int",    // FIELD_fsmState
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **NDPConnectionDescriptor::getFieldPropertyNames(int field) const
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

const char *NDPConnectionDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NDPConnectionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NDPConnection *pp = (NDPConnection *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NDPConnectionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPConnection *pp = (NDPConnection *)object; (void)pp;
    switch (field) {
        case FIELD_state: { const NdpStateVariables * value = pp->getState(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_sendQueue: { const NDPSendQueue * value = pp->getSendQueue(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_receiveQueue: { const NDPReceiveQueue * value = pp->getReceiveQueue(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_ndpAlgorithm: { const NDPAlgorithm * value = pp->getNdpAlgorithm(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string NDPConnectionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NDPConnection *pp = (NDPConnection *)object; (void)pp;
    switch (field) {
        case FIELD_socketId: return long2string(pp->getSocketId());
        case FIELD_listeningSocketId: return long2string(pp->getListeningSocketId());
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_state: {std::stringstream out; out << pp->getState(); return out.str();}
        case FIELD_sendQueue: {std::stringstream out; out << pp->getSendQueue(); return out.str();}
        case FIELD_receiveQueue: {std::stringstream out; out << pp->getReceiveQueue(); return out.str();}
        case FIELD_ndpAlgorithm: {std::stringstream out; out << pp->getNdpAlgorithm(); return out.str();}
        case FIELD_fsmState: return long2string(pp->getFsmState());
        default: return "";
    }
}

bool NDPConnectionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NDPConnection *pp = (NDPConnection *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NDPConnectionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_state: return omnetpp::opp_typename(typeid(NdpStateVariables));
        case FIELD_sendQueue: return omnetpp::opp_typename(typeid(NDPSendQueue));
        case FIELD_receiveQueue: return omnetpp::opp_typename(typeid(NDPReceiveQueue));
        case FIELD_ndpAlgorithm: return omnetpp::opp_typename(typeid(NDPAlgorithm));
        default: return nullptr;
    };
}

void *NDPConnectionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NDPConnection *pp = (NDPConnection *)object; (void)pp;
    switch (field) {
        case FIELD_localAddr: return toVoidPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return toVoidPtr(&pp->getRemoteAddr()); break;
        case FIELD_state: return toVoidPtr(pp->getState()); break;
        case FIELD_sendQueue: return toVoidPtr(pp->getSendQueue()); break;
        case FIELD_receiveQueue: return toVoidPtr(pp->getReceiveQueue()); break;
        case FIELD_ndpAlgorithm: return toVoidPtr(pp->getNdpAlgorithm()); break;
        default: return nullptr;
    }
}

} // namespace ndp
} // namespace inet

