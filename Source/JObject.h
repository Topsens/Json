#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#define JO_MAX(a, b)    ((a) > (b) ? (a) : (b))
#define JO_OFFSET(t, m) ((std::size_t)&reinterpret_cast<char const volatile&>(static_cast<JField&>(((t*)0)->m)))
#define JOBJECT(CLASS)      public:\
                                CLASS& operator=(std::nullptr_t) override\
                                {\
                                    return (CLASS&)JField::operator=(nullptr);\
                                }\
                                bool IsUndefined() const override\
                                {\
                                    if (this->nul)\
                                    {\
                                        return false;\
                                    }\
                                    for (auto& pair : FieldOffsets)\
                                    {\
                                        auto field = (JField*)((char*)(this) + pair.second);\
                                        if (!field->IsUndefined())\
                                        {\
                                            return false;\
                                        }\
                                    }\
                                    return true;\
                                }\
                                JField* GetField(const std::string& name) override\
                                {\
                                    std::map<std::string, std::size_t>::const_iterator itr;\
                                    itr = FieldOffsets.find(name);\
                                    if(itr != FieldOffsets.end())\
                                    {\
                                        return JObject::GetField(this, itr->second);\
                                    }\
                                    return nullptr;\
                                }\
                                const JField* GetField(const std::string& name) const override\
                                {\
                                    std::map<std::string, std::size_t>::const_iterator itr;\
                                    itr = FieldOffsets.find(name);\
                                    if(itr != FieldOffsets.end())\
                                    {\
                                        return JObject::GetField(this, itr->second);\
                                    }\
                                    return nullptr;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, const JField& field)>& cb) const override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            const auto& field = *(const JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, const JField& field, void* param)>& cb, void* param) const override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            const auto& field = *(const JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field, param))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, JField& field)>& cb) override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            auto& field = *(JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, JField& field, void* param)>& cb, void* param) override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            auto& field = *(JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field, param))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                    }\
                                    return false;\
                                }\
                                void Clear() override\
                                {\
                                    for (auto& pair : FieldOffsets)\
                                    {\
                                        auto field = (JField*)((char*)(this) + pair.second);\
                                        field->Clear();\
                                    }\
                                    JField::Clear();\
                                }\
                                static const std::map<std::string, std::size_t> FieldOffsets;\
                            private:\
                                typedef CLASS _SELF_

#define JOBJECT_INHERIT(CLASS, BASE)\
                            public:\
                                CLASS& operator=(std::nullptr_t) override\
                                {\
                                    return (CLASS&)JField::operator=(nullptr);\
                                }\
                                bool IsUndefined() const override\
                                {\
                                    if (this->nul)\
                                    {\
                                        return false;\
                                    }\
                                    for (auto& pair : FieldOffsets)\
                                    {\
                                        auto field = (JField*)((char*)(this) + pair.second);\
                                        if (!field->IsUndefined())\
                                        {\
                                            return false;\
                                        }\
                                    }\
                                    return BASE::IsUndefined();\
                                }\
                                JField* GetField(const std::string& name) override\
                                {\
                                    std::map<std::string, std::size_t>::const_iterator itr;\
                                    itr = FieldOffsets.find(name);\
                                    if(itr != FieldOffsets.end())\
                                    {\
                                        return JObject::GetField(this, itr->second);\
                                    }\
                                    return BASE::GetField(name);\
                                }\
                                const JField* GetField(const std::string& name) const override\
                                {\
                                    std::map<std::string, std::size_t>::const_iterator itr;\
                                    itr = FieldOffsets.find(name);\
                                    if(itr != FieldOffsets.end())\
                                    {\
                                        return JObject::GetField(this, itr->second);\
                                    }\
                                    return BASE::GetField(name);\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, const JField& field)>& cb) const override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            const auto& field = *(const JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                        if (BASE::ForEach(cb))\
                                        {\
                                            return true;\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, const JField& field, void* param)>& cb, void* param) const override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            const auto& field = *(const JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field, param))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                        if (BASE::ForEach(cb, param))\
                                        {\
                                            return true;\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, JField& field)>& cb) override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            auto& field = *(JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                        if (BASE::ForEach(cb))\
                                        {\
                                            return true;\
                                        }\
                                    }\
                                    return false;\
                                }\
                                bool ForEach(const std::function<bool(const std::string& name, JField& field, void* param)>& cb, void* param) override\
                                {\
                                    if (cb)\
                                    {\
                                        for (auto& pair : FieldOffsets)\
                                        {\
                                            auto& field = *(JField*)((char*)(this) + pair.second);\
                                            if (cb(pair.first, field, param))\
                                            {\
                                                return true;\
                                            }\
                                        }\
                                        if (BASE::ForEach(cb, param))\
                                        {\
                                            return true;\
                                        }\
                                    }\
                                    return false;\
                                }\
                                void Clear() override\
                                {\
                                    for (auto& pair : FieldOffsets)\
                                    {\
                                        auto field = (JField*)((char*)(this) + pair.second);\
                                        field->Clear();\
                                    }\
                                    BASE::Clear();\
                                }\
                                static const std::map<std::string, std::size_t> FieldOffsets;\
                            private:\
                                typedef CLASS _SELF_

#define BEG_JFIELDS(CLASS)  const std::map<std::string, std::size_t> CLASS::FieldOffsets = {
#define JFIELD(FIELD)           std::make_pair(std::string(#FIELD), JO_OFFSET(_SELF_, FIELD))
#define JFIELD_KEY(FIELD, KEY)  std::make_pair(std::string(KEY),    JO_OFFSET(_SELF_, FIELD))
#define END_JFIELDS         };

#ifdef JOBJECT_NS
namespace JOBJECT_NS {
#endif

enum class JType
{
    BOOL,
    INT,
    NUM,
    STR,
    OBJ,
    ARR,
    VAR
};

struct JBase
{
    virtual void Set(const bool&) = 0;
    virtual void Set(const int64_t&) = 0;
    virtual void Set(const double&) = 0;
    virtual void Set(const std::string&) = 0;
    virtual void Set(std::nullptr_t) = 0;

    virtual bool    GetB() const = 0;
    virtual int64_t GetI() const = 0;
    virtual double  GetN() const = 0;
    virtual const std::string& GetS() const = 0;
};

class JField : protected JBase
{
public:
    JField() : und(true), nul(false) {}
    JField(std::nullptr_t) : und(false), nul(true) {}

    virtual JType Type() const = 0;

    virtual void Clear()
    {
        this->und = true;
        this->nul = false;
    }

    virtual bool IsUndefined() const
    {
        return this->und;
    }

    virtual bool IsNull() const
    {
        return this->nul;
    }

    virtual bool IsArr() const
    {
        return false;
    }

    virtual bool IsObj() const
    {
        return false;
    }

    virtual bool HasValue() const
    {
        return !(this->IsNull() || this->IsUndefined());
    }

    virtual JField& operator=(std::nullptr_t)
    {
        this->Clear();
        this->und = false;
        this->nul  = true;
        return *this;
    }

    std::string Serialize() const;
    bool Serialize(std::ostream&  json) const;
    bool Serialize(std::ostream&& json) const;
    bool Deserialize(std::istream&  json);
    bool Deserialize(std::istream&& json);
    bool Deserialize(std::istream&  json, std::string& error, std::size_t& where);
    bool Deserialize(std::istream&& json, std::string& error, std::size_t& where);
    bool Deserialize(const std::string& json);
    bool Deserialize(std::string&& json);
    bool Deserialize(const std::string& json, std::string& error, std::size_t& where);
    bool Deserialize(std::string&& json, std::string& error, std::size_t& where);

protected:
    void Set(const bool& value) override
    {
        throw std::runtime_error("Invalid field type");
    }
    void Set(const int64_t& value) override
    {
        throw std::runtime_error("Invalid field type");
    }
    void Set(const double& value) override
    {
        throw std::runtime_error("Invalid field type");
    }
    void Set(const std::string& value) override
    {
        throw std::runtime_error("Invlaid field type");
    }
    void Set(std::nullptr_t) override
    {
        this->operator=(nullptr);
    }

    bool    GetB() const override
    {
        throw std::runtime_error("Invlaid field type");
    }
    int64_t GetI() const override
    {
        throw std::runtime_error("Invlaid field type");
    }
    double  GetN() const override
    {
        throw std::runtime_error("Invlaid field type");
    }
    const std::string& GetS() const override
    {
        throw std::runtime_error("Invlaid field type");
    }

protected:
    bool und;
    bool nul;
};

template<typename T, typename U, JType V>
class JValue : public JField
{
public:
    JValue() = default;
    JValue(const T& value) : Value(value)
    {
        this->und = false;
        this->nul = false;
    }
    explicit JValue(std::nullptr_t) : JField(nullptr) {}

    JType Type() const override
    {
        return V;
    }

    const T& ValueOrDefault(const T& defVal) const
    {
        return this->HasValue() ? this->Value : defVal;
    }

    virtual U& operator=(const T& value)
    {
        this->Value = value;
        this->und = false;
        this->nul = false;
        return (U&)*this;
    }

    JValue& operator=(std::nullptr_t) override
    {
        return (JValue&)JField::operator=(nullptr);
    }

    bool operator==(const JValue& other)
    {
        if (this->und && other.und)
        {
            return true;
        }

        if (this->und != other.und)
        {
            return false;
        }

        if (this->nul && other.nul)
        {
            return true;
        }

        if (this->nul != other.nul)
        {
            return false;
        }

        return this->Value == other.Value;
    }

    operator const T&() const
    {
        return this->Value;
    }

    const T& operator()() const
    {
        return this->Value;
    }

    const T& operator()(const T& defVal) const
    {
        return this->ValueOrDefault(defVal);
    }

    T Value;

protected:
    void Set(const T& value) override
    {
        this->operator=(value);
    }
};

#define JVALUE(T, U, V) U() = default;\
                        U(T t) : JValue<T, U, V>(t) {}\
                        explicit U(std::nullptr_t) : JValue<T, U, V>(nullptr) {}\
                        U& operator=(const T& value) override { return (U&)JValue<T, U, V>::operator=(value); }\
                        U& operator=(std::nullptr_t) override { return (U&)JValue<T, U, V>::operator=(nullptr); }

class JBool : public JValue<bool, JBool, JType::BOOL>
{
public:
    JVALUE(bool, JBool, JType::BOOL);

protected:
    bool GetB() const override
    {
        return this->Value;
    }
};

class JInt : public JValue<int64_t, JInt, JType::INT>
{
public:
    JVALUE(int64_t, JInt, JType::INT);

    JInt& operator=(int32_t v)
    {
        return this->operator=((int64_t)v);
    }
    JInt& operator=(uint32_t v)
    {
        return this->operator=((int64_t)v);
    }

protected:
    int64_t GetI() const override
    {
        return this->Value;
    }
};

class JNum : public JValue<double, JNum, JType::NUM>
{
public:
    JVALUE(double, JNum, JType::NUM);

protected:
    double GetN() const override
    {
        return this->Value;
    }
};

class JStr : public JValue<std::string, JStr, JType::STR>
{
public:
    JVALUE(std::string, JStr, JType::STR);

    void Clear() override
    {
        this->Value.clear();
        JValue<std::string, JStr, JType::STR>::Clear();
    }

protected:
    const std::string& GetS() const override
    {
        return this->Value;
    }
};

class JTime : public JStr
{
public:
    operator time_t() const
    {
        return this->time;
    }

    const time_t& operator()() const
    {
        return this->time;
    }
    const time_t& operator()(time_t& defVal) const
    {
        return this->HasValue() ? this->time : defVal;
    }

    JTime& operator=(const std::string& value) override
    {
        this->nul = false;
        this->und = !ToTime(value, this->time);
        return *this;
    }
    JTime& operator=(time_t value)
    {
        this->nul = false;
        this->und = false;
        this->time = value;
        return *this;
    }

protected:
    static bool ToTime(const std::string& value, time_t& time);
    static std::string ToString(time_t time);

protected:
    time_t time;
};

class JObject : public JField
{
public:
    JType Type() const override
    {
        return JType::OBJ;
    }

    bool IsObj() const override
    {
        return true;
    }

    virtual JField* GetField(const std::string&) = 0;
    virtual const JField* GetField(const std::string&) const = 0;

    // ForEach() stops and returns true if any callback returns true.
    virtual bool ForEach(const std::function<bool(const std::string& name, const JField& field)>& cb) const = 0;
    virtual bool ForEach(const std::function<bool(const std::string& name, const JField& field, void*)>& cb, void*) const = 0;
    virtual bool ForEach(const std::function<bool(const std::string& name, JField& field)>& cb) = 0;
    virtual bool ForEach(const std::function<bool(const std::string& name, JField& field, void*)>& cb, void*) = 0;

protected:
    static JField* GetField(JObject* object, std::size_t offset)
    {
        return (JField*)((char*)object + offset);
    }
    static const JField* GetField(const JObject* object, std::size_t offset)
    {
        return (const JField*)((char*)object + offset);
    }
};

class JArray : public JField
{
public:
    virtual JField* NewItem() = 0;
    virtual bool ForEach(const std::function<bool(const JField& field)>& cb) const = 0;

    JType Type() const override
    {
        return JType::ARR;
    }

    bool IsArr() const override
    {
        return true;
    }
};

template<typename T>
class JArr : public JArray
{
    static_assert(std::is_base_of<JField, T>::value, "" /*T must inherit from JField*/);

public:
    JArr() {}
    JArr(const std::initializer_list<T>& list)
    {
        this->Value = list;
    }

    void Clear() override
    {
        this->Value.clear();
        JArray::Clear();
    }

    bool IsUndefined() const override
    {
        return !this->nul && this->Value.empty();
    }

    bool IsNull() const override
    {
        return this->nul && !this->Length();
    }

    std::size_t Length() const
    {
        return this->Value.size();
    }

    void Insert(const T& item, std::size_t before)
    {
        auto itr = this->Value.begin() + (before > this->Value.size() ? this->Value.size() : before);
        this->Value.insert(itr, item);
    }

    void Insert(const JArr<T>& items, std::size_t before)
    {
        auto itr = this->Value.begin() + (before > this->Value.size() ? this->Value.size() : before);
        this->Value.insert(itr, items.Value.begin(), items.Value.end());
    }

    void Push(const T& item)
    {
        this->Value.push_back(item);
    }

    void Unshift(const T& item)
    {
        this->Value.insert(this->Value.begin(), item);
    }

    void RemoveAt(size_t index)
    {
        if (index < this->Value.size())
        {
            this->Value.erase(this->Value.begin() + index);
        }
    }

    void RemoveIf(const std::function<bool(size_t index, const T& item)>& pred)
    {
        if (pred)
        {
            size_t index = 0;
            this->Value.erase(std::remove_if(this->Value.begin(), this->Value.end(), [&index, &pred](const T& item)
            {
                return pred(index++, item);
            }));
        }
    }

    T* NewItem() override // Caution: Returned pointer may become invalid after subsequent call due to reallocation.
    {
        this->Value.push_back(T());
        return &this->Value.back();
    }

    bool ForEach(const std::function<bool(const JField& field)>& cb) const override
    {
        if (cb)
        {
            for (auto& field : this->Value)
            {
                if (cb(field))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool ForEachItem(const std::function<bool(const T& item)>& cb) const
    {
        if (cb)
        {
            return this->ForEach([&](const JField& field)
            {
                return cb((const T&)field);
            });
        }
        return false;
    }

    const std::vector<T>& ValueOrDefault(const std::vector<T>& defVal) const
    {
        return this->HasValue() ? this->Value : defVal;
    }

    T& operator[](std::size_t index)
    {
        return this->Value[index];
    }

    const T& operator[](std::size_t index) const
    {
        return this->Value[index];
    }

    const std::vector<T>& operator()() const
    {
        return this->Value;
    }

    const std::vector<T>& operator()(const std::vector<T>& defVal) const
    {
        return this->ValueOrDefault(defVal);
    }

    JArr& operator=(std::nullptr_t) override
    {
        JField::operator=(nullptr);
        return *this;
    }

    std::vector<T> Value;
};

class JVariant : public JField
{
public:
    virtual JType Subtype() const = 0;

    virtual JVariant* NewItem() = 0;
    virtual JVariant* GetField(const std::string&) = 0;

    virtual bool ToArr(JArray&, std::string&) const = 0;
    virtual bool ToObj(JObject&, std::string&) const = 0;

    virtual void ForEach(const std::function<void(const std::string&, const JVariant&)>&) const = 0;
    virtual void ForEach(const std::function<void(const JVariant&)>&) const = 0;
};

class JVar : public JVariant
{
    using jmap = std::map<std::string, JVar>;
    using jstr = std::string;
    using jvec = std::vector<JVar>;

public:
    JVar() : subtype(JType::VAR) {}
    JVar(const JVar& other) : JVar()
    {
        this->Subtype(other.subtype);
        this->und = other.und;
        this->nul = other.nul;

        switch (this->subtype)
        {
            case JType::ARR:
            {
                *(jvec*)this->val = *(jvec*)other.val;
                break;
            }

            case JType::STR:
            {
                *(jstr*)this->val = *(jstr*)other.val;
                break;
            }

            case JType::OBJ:
            {
                *(jmap*)this->val = *(jmap*)other.val;
                break;
            }

            default:
            {
                if (other.HasValue())
                {
                    memcpy(this->val, other.val, sizeof(this->val));
                }
                break;
            }
        }
    }
    JVar(JVar&& other) : JVar()
    {
        this->Subtype(other.subtype);
        this->und = other.und;
        this->nul = other.nul;

        switch (this->subtype)
        {
            case JType::ARR:
            {
                *(jvec*)this->val = std::move(*(jvec*)other.val);
                break;
            }

            case JType::STR:
            {
                *(jstr*)this->val = std::move(*(jstr*)other.val);
                break;
            }

            case JType::OBJ:
            {
                *(jmap*)this->val = std::move(*(jmap*)other.val);
                break;
            }

            default:
            {
                if (other.HasValue())
                {
                    memcpy(this->val, other.val, sizeof(this->val));
                }
                break;
            }
        }
    }
    JVar(std::nullptr_t) : JVar()
    {
        *this = nullptr;
    }
    JVar(bool value) : JVar()
    {
        *this = value;
    }
    JVar(int64_t value) : JVar()
    {
        *this = value;
    }
    JVar(double value) : JVar()
    {
        *this = value;
    }
    JVar(const std::string& value) : JVar()
    {
        *this = value;
    }
    JVar(int value) : JVar((int64_t)value)
    {
    }
    JVar(const char* value) : JVar(std::string(value))
    {
    }
   ~JVar()
    {
        switch (this->subtype)
        {
            case JType::ARR:
            {
                ((jvec*)this->val)->~vector();
                break;
            }

            case JType::STR:
            {
                ((jstr*)this->val)->~basic_string();
                break;
            }

            case JType::OBJ:
            {
                ((jmap*)this->val)->~map();
                break;
            }

            default: break;
        }
    }

    bool IsUndefined() const override
    {
        if (this->nul)
        {
            return false;
        }
        else if (JType::ARR == this->subtype)
        {
            return ((jvec*)this->val)->empty();
        }
        else if (JType::OBJ == this->subtype)
        {
            for (auto& var : *(jmap*)this->val)
            {
                if (!var.second.IsUndefined())
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            return this->und;
        }
    }

    bool IsArr() const override
    {
        return JType::ARR == this->subtype;
    }

    bool IsObj() const override
    {
        return JType::OBJ == this->subtype;
    }

    void Clear() override
    {
        switch (this->subtype)
        {
            case JType::ARR:
            {
                ((jvec*)this->val)->~vector();
                break;
            }

            case JType::STR:
            {
                ((jstr*)this->val)->~basic_string();
                break;
            }

            case JType::OBJ:
            {
                ((jmap*)this->val)->~map();
                break;
            }

            default: break;
        }

        JField::Clear();
        this->subtype = JType::VAR;
    }

    JType Type() const override
    {
        return JType::VAR;
    }

    JType Subtype() const override
    {
        return this->subtype;
    }

    std::size_t Length() const
    {
        if (JType::ARR == this->subtype)
        {
            return ((jvec*)this->val)->size();
        }
        if (JType::STR == this->subtype)
        {
            return ((jstr*)this->val)->length();
        }
        else if (JType::OBJ == this->subtype)
        {
            return ((jmap*)this->val)->size();
        }
        else
        {
            return 0;
        }
    }

    bool HasField(const std::string& name) const
    {
        auto fields = (jmap*)this->val;
        return (JType::OBJ == this->subtype ? fields->end() != fields->find(name) : false);
    }

    // Array operations
    void Insert(const JVar& item, std::size_t before)
    {
        this->Subtype(JType::ARR);
        auto items = (jvec*)this->val;
        auto itr = items->begin() + (before > items->size() ? items->size() : before);
        items->insert(itr, item);
    }
    void Push(const JVar& item)
    {
        this->Subtype(JType::ARR);
        ((jvec*)this->val)->push_back(item);
    }
    void Unshift(const JVar& item)
    {
        this->Subtype(JType::ARR);
        auto items = (jvec*)this->val;
        items->insert(items->begin(), item);
    }
    void RemoveAt(size_t index)
    {
        auto items = (jvec*)this->val;
        if (JType::ARR == this->subtype && index < items->size())
        {
            items->erase(items->begin() + index);
        }
    }
    void RemoveIf(const std::function<bool(size_t index, const JVar& item)>& pred)
    {
        if (JType::ARR == this->subtype && pred)
        {
            auto items = (jvec*)this->val;

            size_t index = 0;
            items->erase(std::remove_if(items->begin(), items->end(), [&index, &pred](const JVar& item)
            {
                return pred(index++, item);
            }));
        }
    }

    // ForEachField()/ForEachItem() stops and returns true if any callback returns true
    bool ForEachField(const std::function<bool(const std::string& name, const JVar& var)>& cb) const
    {
        if (JType::OBJ == this->subtype && cb)
        {
            for (auto& pair : *(jmap*)this->val)
            {
                if (cb(pair.first, pair.second))
                {
                    return true;
                }
            }
        }

        return false;
    }
    bool ForEachField(const std::function<bool(const std::string& name, const JVar& var, void* param)>& cb, void* param) const
    {
        if (JType::OBJ == this->subtype && cb)
        {
            for (auto& pair : *(jmap*)this->val)
            {
                if (cb(pair.first, pair.second, param))
                {
                    return true;
                }
            }
        }

        return false;
    }
    bool ForEachField(const std::function<bool(const std::string& name, JVar& var)>& cb)
    {
        if (JType::OBJ == this->subtype && cb)
        {
            for (auto& pair : *(jmap*)this->val)
            {
                if (cb(pair.first, pair.second))
                {
                    return true;
                }
            }
        }

        return false;
    }
    bool ForEachField(const std::function<bool(const std::string& name, JVar& var, void* param)>& cb, void* param)
    {
        if (JType::OBJ == this->subtype && cb)
        {
            for (auto& pair : *(jmap*)this->val)
            {
                if (cb(pair.first, pair.second, param))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool ForEachItem(const std::function<bool(const JVar& var)>& cb) const
    {
        if (JType::ARR == this->subtype && cb)
        {
            for (auto& item : *(jvec*)this->val)
            {
                if (cb(item))
                {
                    return true;
                }
            }
        }

        return false;
    }
    bool ForEachItem(const std::function<bool(JVar& var)>& cb)
    {
        if (JType::ARR == this->subtype && cb)
        {
            for (auto& item : *(jvec*)this->val)
            {
                if (cb(item))
                {
                    return true;
                }
            }
        }

        return false;
    }

    JVar* NewItem() override
    {
        this->Subtype(JType::ARR);

        auto items = (jvec*)this->val;
        items->resize(items->size() + 1);
        return &items->back();
    }
    JVar* GetField(const std::string& name) override
    {
        this->Subtype(JType::OBJ);

        auto fields = (jmap*)this->val;
        auto itr = fields->find(name);
        if (fields->end() != itr)
        {
            return &itr->second;
        }

        return &(fields->operator[](name) = JVar());
    }

    bool ToArr(JArray& arr, std::string& err) const override;
    bool ToObj(JObject& obj, std::string& err) const override;
    bool ToArr(JArray& arr) const
    {
        std::string e;
        return this->ToArr(arr, e);
    }
    bool ToObj(JObject& obj) const
    {
        std::string err;
        return this->ToObj(obj, err);
    }

    void ForEach(const std::function<void(const std::string&, const JVariant&)>& cb) const override
    {
        if (JType::OBJ == this->subtype && cb)
        {
            for (auto& pair : *(jmap*)this->val)
            {
                cb(pair.first, pair.second);
            }
        }
    }
    void ForEach(const std::function<void(const JVariant&)>& cb) const override
    {
        if (JType::ARR == this->subtype && cb)
        {
            for (auto& item : *(jvec*)this->val)
            {
                cb(item);
            }
        }
    }

    JVar& operator[](std::size_t index)
    {
        if (JType::ARR != this->subtype)
        {
            throw std::out_of_range("Is not an array");
        }

        return (*(jvec*)this->val)[index];
    }
    const JVar& operator[](std::size_t index) const
    {
        if (JType::ARR != this->subtype)
        {
            throw std::out_of_range("Is not an array");
        }

        return (*(jvec*)this->val)[index];
    }
    JVar& operator[](const std::string& field)
    {
        this->Subtype(JType::OBJ);
        return (*(jmap*)this->val)[field];
    }
    const JVar& operator[](const std::string& field) const
    {
        static const JVar undefined;

        if (JType::OBJ != this->subtype)
        {
            throw std::runtime_error("Is not an object");
        }

        if (!this->HasValue() || !this->HasField(field))
        {
            return undefined;
        }

        return (*(jmap*)this->val)[field];
    }

    JVar& operator=(std::nullptr_t) override
    {
        JField::operator=(nullptr);
        return *this;
    }

    JVar& operator=(int64_t value)
    {
        this->Subtype(JType::INT);
        this->und = false;
        this->nul = false;

        *(int64_t*)this->val = value;

        return *this;
    }

    JVar& operator=(int32_t value)
    {
        return this->operator=((int64_t)value);
    }

    JVar& operator=(double value)
    {
        this->Subtype(JType::NUM);
        this->und = false;
        this->nul = false;

        *(double*)this->val = value;

        return *this;
    }

    JVar& operator=(float value)
    {
        return this->operator=((double)value);
    }

    JVar& operator=(bool value)
    {
        this->Subtype(JType::BOOL);
        this->und = false;
        this->nul = false;

        *(bool*)this->val = value;

        return *this;
    }

    JVar& operator=(const std::string& value)
    {
        this->Subtype(JType::STR);
        this->und = false;
        this->nul = false;

        *(jstr*)this->val = value;

        return *this;
    }

    JVar& operator=(const char* value)
    {
        this->Subtype(JType::STR);
        this->und = false;
        this->nul = false;

        *(jstr*)this->val = value;

        return *this;
    }

    JVar& operator=(const JVar& var)
    {
        return this->operator=((JField&)var);
    }

    JVar& operator=(const JField& field);

    int64_t Int() const
    {
        return *(int64_t*)this->val;
    }

    int64_t Int(int64_t defVal) const
    {
        return (JType::INT == this->subtype && this->HasValue()) ? this->Int() : defVal;
    }

    double Num() const
    {
        return *(double*)this->val;
    }

    double Num(double defVal) const
    {
        return (JType::NUM == this->subtype && this->HasValue()) ? this->Num() : defVal;
    }

    bool Bool() const
    {
        return *(bool*)this->val;
    }

    bool Bool(bool defVal) const
    {
        return (JType::BOOL == this->subtype && this->HasValue()) ? this->Bool() : defVal;
    }

    const std::string& Str() const
    {
        static const std::string empty;
        return JType::STR == this->subtype ? *(jstr*)this->val : empty;
    }

    const std::string& Str(const std::string& defVal) const
    {
        return (JType::STR == this->subtype && this->HasValue()) ? this->Str() : defVal;
    }

protected:
    void Subtype(JType subtype)
    {
        if (this->subtype != subtype)
        {
            this->Clear();

            switch (subtype)
            {
                case JType::ARR:
                {
                    new(this->val) std::vector<JVar>();
                    break;
                }

                case JType::STR:
                {
                    new(this->val) std::string();
                    break;
                }

                case JType::OBJ:
                {
                    new(this->val) std::map<std::string, JVar>();
                    break;
                }

                default: break;
            }

            this->subtype = subtype;
        }
    }

    void Set(const bool& value) override
    {
        *this = value;
    }
    void Set(const int64_t& value) override
    {
        *this = value;
    }
    void Set(const double& value) override
    {
        *this = value;
    }
    void Set(const std::string& value) override
    {
        *this = value;
    }

    bool    GetB() const override
    {
        return this->Bool();
    }
    int64_t GetI() const override
    {
        return this->Int();
    }
    double  GetN() const override
    {
        return this->Num();
    }
    const std::string& GetS() const override
    {
        return this->Str();
    }

protected:
    JType subtype;
    char  val[JO_MAX(sizeof(std::map<std::string, JVar>), JO_MAX(sizeof(std::string), sizeof(std::vector<JVar>)))];
};

class JParser
{
public:
    static void         Serialize(std::ostream& json, const JField& field);
    static void         Deserialize(std::istream& json, JField& field);

    static void         GetVal(std::istream& json, const std::string& name, JField* field);
    static void         GetArr(std::istream& json, const std::string& name, JField* arr);
    static void         GetObj(std::istream& json, JField* obj);
    static double       GetFlt(std::istream& json);
    static double       GetFlt(const std::string& num);
    static std::string  GetStr(std::istream& json);
    static std::string  GetNum(std::istream& json);
    static int64_t      GetInt(std::istream& json);
    static int64_t      GetInt(const std::string& num);
    static int64_t      GetInt(const std::string& json, std::string::size_type& off);
    static std::string  GetName(std::istream& json);
    static bool         GetBool(std::istream& json);
    static uint64_t     GetUint(std::istream& json);
    static uint64_t     GetUint(const std::string& json, std::string::size_type& off);
    static bool         IsFloat(const std::string& num);

    static void GetJson(const std::string& name, const JField& field, std::ostream& json);
    static void GetJson(const JVariant& var, std::ostream& json);
    static void GetJson(const JObject& obj, std::ostream& json);
    static void GetJson(const JArray& arr, std::ostream& json);
    static void GetJson(const std::string& str, std::ostream& json);
};

#ifdef JOBJECT_NS
} // namespace JOBJECT_NS
#endif