#pragma once

#include <algorithm>
#include <cassert>
#include <codecvt>
#include <cstdint>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <map>
#include <stdexcept>
#include <sstream>
#include <type_traits>
#include <vector>

#if defined(_MSC_VER) && _MSC_VER < 1900
    #define noexcept
#endif

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

inline std::string to_string(JType type)
{
    switch (type)
    {
        case JType::BOOL:
            return "JType::BOOL";

        case JType::INT:
            return "JType::INT";

        case JType::NUM:
            return "JType::NUM";

        case JType::STR:
            return "JType::STR";

        case JType::OBJ:
            return "JType::OBJ";

        case JType::ARR:
            return "JType::ARR";

        case JType::VAR:
            return "JType::VAR";

        default:
            return "Unknown type";
    }
}

inline std::ostream& operator<<(std::ostream& stream, JType type)
{
    stream << to_string(type);
    return stream;
}

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
    JStr(const JStr& other) = default;
    JStr(JStr&& other) noexcept { *this = std::move(other); }

    JStr& operator=(const JStr& other) = default;
    JStr& operator=(JStr&& other) noexcept
    {
        this->nul = other.nul;
        this->und = other.und;
        this->Value = std::move(other.Value);
        other.Clear();
        return *this;
    }

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
    static bool ToTime(const std::string& value, time_t& time)
    {
        if (0 == value.find("/Date("))
        {
            std::string::size_type pos = 6;
            time = GetInt(value, pos);

            if ('+' == value[pos] || '-' == value[pos])
            {
                auto zone = GetInt(value, pos);
                auto hours = zone / 100;
                auto minites = zone - hours * 100;

                time -= hours * 60 * 60;
                time -= minites * 60;
            }

            return true;
        }
        else
        {
            tm tm = { 0 };
            std::string::size_type pos = 0;

            tm.tm_year = (int)GetUint(value, pos) - 1900;
            if ('-' != value[pos])
            {
                return false;
            }

            tm.tm_mon = (int)GetUint(value, ++pos) - 1;
            if ('-' != value[pos])
            {
                return false;
            }

            tm.tm_mday = (int)GetUint(value, ++pos);
            if ('T' != value[pos])
            {
                return false;
            }

            tm.tm_hour = (int)GetUint(value, ++pos);
            if (':' != value[pos])
            {
                return false;
            }

            tm.tm_min = (int)GetUint(value, ++pos);
            if (':' != value[pos])
            {
                return false;
            }

            tm.tm_sec = (int)GetUint(value, ++pos);

            if ('.' == value[pos])
            {
                GetUint(value, ++pos);
            }

            time = mktime(&tm);
            if (-1 == time)
            {
                return false;
            }

            if ('z' != tolower(value[pos]))
            {
                auto zone = GetInt(value, pos);
                auto hours = zone / 100;
                auto minites = zone - hours * 100;

                time -= hours * 60 * 60;
                time -= minites * 60;
            }

            return true;
        }
    }

    static std::string ToString(time_t time)
    {
        tm tm;

        #if defined(WIN32) || defined(_WIN32)
        localtime_s(&tm, &time);
        #else
        tm = *localtime(&time);
        #endif

        std::ostringstream json;
        json << '\"' << std::to_string(tm.tm_year + 1900) << '-'
            << std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << '-'
            << std::setfill('0') << std::setw(2) << tm.tm_mday << 'T'
            << std::setfill('0') << std::setw(2) << tm.tm_hour << ':'
            << std::setfill('0') << std::setw(2) << tm.tm_min  << ':'
            << std::setfill('0') << std::setw(2) << tm.tm_sec  << "Z\"";
        return json.str();
    }

    static int64_t GetInt(const std::string& json, std::string::size_type& off)
    {
        char* end;
        int64_t value;

        if (json.length() > off + 2 && '0' == json[off] && ('x' == json[off + 1] || 'X' == json[off + 1]))
        {
            value = strtoll(json.c_str() + off, &end, 16);
        }
        else
        {
            value = strtoll(json.c_str() + off, &end, 10);
        }

        if (end == json.c_str() + off)
        {
            throw std::runtime_error("Failed to parse int");
        }

        off = end - json.c_str();

        return value;
    }

    static uint64_t GetUint(const std::string& json, std::string::size_type& off)
    {
        char* end;
        uint64_t value;

        if (json.length() > off + 2 && '0' == json[off] && ('x' == json[off + 1] || 'X' == json[off + 1]))
        {
            value = std::strtoull(json.c_str() + off, &end, 16);
        }
        else
        {
            value = std::strtoull(json.c_str() + off, &end, 10);
        }

        if (end == json.c_str() + off)
        {
            throw std::runtime_error("Failed to parse uint");
        }

        off = end - json.c_str();

        return value;
    }

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
    JArr(const JArr& other) = default;
    JArr(JArr&& other) noexcept { *this = std::move(other); }
    JArr(const std::initializer_list<T>& list) : Value(list)
    {
        this->nul = false;
        this->und = false;
    }

    JArr& operator=(const JArr& other) = default;

    JArr& operator=(JArr&& other) noexcept
    {
        this->nul = other.nul;
        this->und = other.und;
        this->Value = std::move(other.Value);
        other.Clear();
        return *this;
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
        *this = other;
    }
    JVar(JVar&& other) noexcept : JVar()
    {
        *this = std::move(other);
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

    JVar& operator=(const JVar& other)
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
        return *this;
    }

    JVar& operator=(JVar&& other) noexcept
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
        other.Clear();
        return *this;
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

    bool ToArr(JArray& arr, std::string& err) const override
    {
        arr.Clear();

        if (this->IsUndefined())
        {
            return true;
        }

        if (this->IsNull())
        {
            (JField&)arr = nullptr;
            return true;
        }

        if (JType::ARR != this->subtype)
        {
            err = "This is not an array";
            return false;
        }

        try
        {
            this->ForEachItem([&arr, &err](const JVar& var)
            {
                if (var.IsUndefined())
                {
                    return false;
                }

                auto item = arr.NewItem();

                if (var.IsNull())
                {
                    *item = nullptr;
                    return false;
                }

                if (JType::VAR == item->Type())
                {
                    *(JVar*)item = var;
                }
                else if (item->Type() == var.Subtype())
                {
                    switch (item->Type())
                    {
                        case JType::INT:
                        {
                            ((JBase*)item)->Set(var.Int());
                            break;
                        }

                        case JType::NUM:
                        {
                            ((JBase*)item)->Set(var.Num());
                            break;
                        }

                        case JType::STR:
                        {
                            ((JBase*)item)->Set(var.Str());
                            break;
                        }

                        case JType::ARR:
                        {
                            if (!var.ToArr(*(JArray*)item, err))
                            {
                                throw std::runtime_error(err);
                            }
                            break;
                        }

                        case JType::OBJ:
                        {
                            if (!var.ToObj(*(JObject*)item, err))
                            {
                                throw std::runtime_error(err);
                            }
                            break;
                        }

                        default: break;
                    }
                }
                else if (JType::NUM == item->Type() && JType::INT == var.Subtype())
                {
                    ((JBase*)item)->Set((double)var.Int());
                }
                else
                {
                    throw std::runtime_error("Type mismatch. Expecting: " + to_string(item->Type()) + ". Actual: " + to_string(var.Subtype()));
                }

                return false;
            });
        } catch (const std::exception& e)
        {
            err = e.what();
            return false;
        }

        return true;
    }
    bool ToObj(JObject& obj, std::string& err) const override
    {
        obj.Clear();

        if (this->IsUndefined())
        {
            return true;
        }

        if (this->IsNull())
        {
            (JField&)obj = nullptr;
            return true;
        }

        if (JType::OBJ != this->subtype)
        {
            err = "This is not an object";
            return false;
        }

        try
        {
            this->ForEachField([&obj, &err](const std::string& name, const JVar& var)
            {
                if (var.IsUndefined())
                {
                    return false;
                }

                auto field = obj.GetField(name);
                if (!field)
                {
                    return false;
                }

                if (var.IsNull())
                {
                    *field = nullptr;
                    return false;
                }

                if (JType::VAR == field->Type())
                {
                    *(JVar*)field = var;
                }
                else if (field->Type() == var.Subtype())
                {
                    switch (field->Type())
                    {
                        case JType::INT:
                        {
                            ((JBase*)field)->Set(var.Int());
                            break;
                        }

                        case JType::NUM:
                        {
                            ((JBase*)field)->Set(var.Num());
                            break;
                        }

                        case JType::STR:
                        {
                            ((JBase*)field)->Set(var.Str());
                            break;
                        }

                        case JType::ARR:
                        {
                            if (!var.ToArr(*(JArray*)field, err))
                            {
                                throw std::runtime_error(err);
                            }
                            break;
                        }

                        case JType::OBJ:
                        {
                            if (!var.ToObj(*(JObject*)field, err))
                            {
                                throw std::runtime_error(err);
                            }
                            break;
                        }

                        default: break;
                    }
                }
                else if (JType::NUM == field->Type() && JType::INT == var.Subtype())
                {
                    ((JBase*)field)->Set((double)var.Int());
                }
                else
                {
                    throw std::runtime_error("Type mismatch: " + name + ". Expecting: " + to_string(field->Type()) + ". Actual: " + to_string(var.Subtype()));
                }

                return false;
            });
        } catch (const std::exception& e)
        {
            err = e.what();
            return false;
        }

        return true;
    }
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

    template<typename T>
    JArr<T> ToArr() const
    {
        JArr<T> arr;
        if (!this->ToArr(arr))
        {
            arr.Clear();
        }
        return arr;
    }
    template<typename T>
    T ToObj() const
    {
        T obj;
        if (!this->ToObj(obj))
        {
            obj.Clear();
        }
        return obj;
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
            throw std::runtime_error("Is not an array");
        }

        return (*(jvec*)this->val)[index];
    }
    const JVar& operator[](std::size_t index) const
    {
        if (JType::ARR != this->subtype)
        {
            throw std::runtime_error("Is not an array");
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

    JVar& operator=(const JField& field)
    {
        this->Clear();

        if (field.IsUndefined())
        {
            return *this;
        }

        if (field.IsNull())
        {
            *this = nullptr;
            return *this;
        }

        switch (field.Type())
        {
            case JType::INT:
            {
                *this = ((JBase&)field).GetI();
                break;
            }

            case JType::NUM:
            {
                *this = ((JBase&)field).GetN();
                break;
            }

            case JType::STR:
            {
                *this = ((JBase&)field).GetS();
                break;
            }

            case JType::BOOL:
            {
                *this =((JBase&)field).GetB();
                break;
            }

            case JType::ARR:
            {
                ((JArray&)field).ForEach([this](const JField& field)
                {
                    auto item = this->NewItem();
                    *item = field;
                    return false;
                });

                break;
            }

            case JType::OBJ:
            {
                ((JObject&)field).ForEach([this](const std::string& name, const JField& field)
                {
                    auto f = this->GetField(name);
                    *f = field;
                    return false;
                });

                break;
            }

            case JType::VAR:
            {
                auto& var = (JVariant&)field;
                switch (var.Subtype())
                {
                    case JType::BOOL:
                    {
                        *this = ((JBase&)var).GetB();
                        break;
                    }

                    case JType::INT:
                    {
                        *this = ((JBase&)var).GetI();
                        break;
                    }

                    case JType::NUM:
                    {
                        *this = ((JBase&)var).GetN();
                        break;
                    }

                    case JType::STR:
                    {
                        *this = ((JBase&)var).GetS();
                        break;
                    }

                    case JType::ARR:
                    {
                        std::function<void(const JVariant&)> foreach = [this](const JVariant& var)
                        {
                            (*this->NewItem()) = var;
                        };
                        var.ForEach(foreach);
                        break;
                    }

                    case JType::OBJ:
                    {
                        std::function<void(const std::string&, const JVariant&)> foreach = [this](const std::string& name, const JVariant& var)
                        {
                            (*this->GetField(name)) = var;
                        };
                        var.ForEach(foreach);
                        break;
                    }

                    default: break; // ignore JType::VAR
                }
                break;
            }

            default: break;
        }

        return *this;
    }

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
    static void Serialize(std::ostream& json, const JField& field)
    {
        GetJson("", field, json);
    }

    static void Deserialize(std::istream& json, JField& field)
    {
        field.Clear();

        char c;
        do
        {
            json.read(&c, 1);
            if (json.eof())
            {
                return;
            }
        } while (' ' == c || '\r' == c || '\n' == c || '\t' == c);

        json.seekg(-1, std::ios::cur);

        GetVal(json, "", &field);

        json.read(&c, 1);

        while (!json.eof())
        {
            if ('\t' != c && '\r' != c && '\n' != c && ' ' != c)
            {
                json.seekg(-1, std::ios::cur);
                throw Unexpected();
            }

            json.read(&c, 1);
        }
    }

private:
    static std::runtime_error ExpectMore()
    {
        return std::runtime_error("Expecting more charactors");
    }

    static std::runtime_error TypeMismatch(const std::string& name, JType expected, JType actual)
    {
        return std::runtime_error(("Type mismatch: " + name + ". Expecting: " + to_string(expected) + ". Actual: " + to_string(actual)).c_str());
    }

    static std::runtime_error Unexpected()
    {
        return std::runtime_error("Unexpected charactor");
    }

    static bool IsNumber(char c)
    {
        return c >= '+' && c <= '9' && c != ',' && c != '/';
    }

    static char GetChar(std::istream& json)
    {
        char c;
        json.read(&c, 1);

        if (json.eof())
        {
            throw ExpectMore();
        }

        return c;
    }

    static char FirstNotSpace(std::istream& json)
    {
        char c;

        do
        {
            c = GetChar(json);

        } while (' ' == c || '\r' == c || '\n' == c || '\t' == c);

        return c;
    }

    static JField* GetField(JField* f, const std::string& n)
    {
        return (JType::OBJ == f->Type() ? ((JObject*)f)->GetField(n) : ((JVariant*)f)->GetField(n));
    }

    static JField* NewItem(JField* f)
    {
        return (JType::ARR == f->Type() ? ((JArray*)f)->NewItem() : ((JVariant*)f)->NewItem());
    }

    static void GetVal(std::istream& json, const std::string& name, JField* field)
    {
        auto c = FirstNotSpace(json);
        switch (c)
        {
            case '{':
            {
                if (field && JType::OBJ != field->Type() && JType::VAR != field->Type())
                {
                    json.seekg(-1, std::ios::cur);
                    throw TypeMismatch(name, field->Type(), JType::OBJ);
                }
                GetObj(json, (JObject*)field);
                break;
            }

            case '[':
            {
                if (field && JType::ARR != field->Type() && JType::VAR != field->Type())
                {
                    json.seekg(-1, std::ios::cur);
                    throw TypeMismatch(name, field->Type(), JType::ARR);
                }
                GetArr(json, name, field);
                break;
            }

            case '\"':
            {
                if (field)
                {
                    if (JType::STR == field->Type() || JType::VAR == field->Type())
                    {
                        ((JBase*)field)->Set(GetStr(json));
                    }
                    else
                    {
                        json.seekg(-1, std::ios::cur);
                        throw TypeMismatch(name, field->Type(), JType::STR);
                    }
                }
                else
                {
                    GetStr(json);
                }
                break;
            }

            default:
            {
                json.seekg(-1, std::ios::cur);

                switch (c)
                {
                    case 't':
                    case 'f':
                    {
                        if (field)
                        {
                            if (JType::BOOL == field->Type() || JType::VAR == field->Type())
                            {
                                ((JBase*)field)->Set(GetBool(json));
                            }
                            else
                            {
                                throw TypeMismatch(name, field->Type(), JType::BOOL);
                            }
                        }
                        else
                        {
                            GetBool(json);
                        }
                        break;
                    }

                    case 'n':
                    {
                        if ('n' == GetChar(json) &&
                            'u' == GetChar(json) &&
                            'l' == GetChar(json) &&
                            'l' == GetChar(json))
                        {
                            if (field)
                            {
                                *field = nullptr;
                            }
                        }
                        else
                        {
                            json.seekg(-1, std::ios::cur);
                            throw Unexpected();
                        }
                        break;
                    }

                    default:
                    {
                        if (IsNumber(c))
                        {
                            if (field)
                            {
                                switch (field->Type())
                                {
                                    case JType::INT:
                                    {
                                        ((JBase*)field)->Set(GetInt(json));
                                        break;
                                    }

                                    case JType::NUM:
                                    {
                                        ((JBase*)field)->Set(GetFlt(json));
                                        break;
                                    }

                                    case JType::VAR:
                                    {
                                        auto num = GetNum(json);
                                        if (IsFloat(num))
                                        {
                                            ((JBase*)field)->Set(GetFlt(num));
                                        }
                                        else
                                        {
                                            ((JBase*)field)->Set(GetInt(num));
                                        }
                                        break;
                                    }

                                    default:
                                    {
                                        throw TypeMismatch(name, field->Type(), JType::NUM);
                                    }
                                }
                            }
                            else
                            {
                                GetFlt(json);
                            }
                        }
                        else
                        {
                            throw Unexpected();
                        }
                        break;
                    }
                }

                break;
            }
        }
    }

    static void GetArr(std::istream& json, const std::string& name, JField* arr)
    {
        auto c = FirstNotSpace(json);
        if (']' == c)
        {
            return;
        }

        json.seekg(-1, std::ios::cur);

        do
        {
            GetVal(json, name, arr ? NewItem(arr) : nullptr);

        } while ([&]
        {
            switch (FirstNotSpace(json))
            {
                case ',': return true;

                case ']': return false;

                default:
                {
                    json.seekg(-1, std::ios::cur);
                    throw Unexpected();
                }
            }
        }());
    }
    static void GetObj(std::istream& json, JField* obj)
    {
        auto c = FirstNotSpace(json);
        if ('}' == c)
        {
            return;
        }

        do
        {
            if ('\"' != c)
            {
                json.seekg(-1, std::ios::cur);
                throw Unexpected();
            }

            auto n = GetName(json);
            auto f = obj ? GetField(obj, n) : nullptr;

            c = GetChar(json);
            while ('.' == c)
            {
                if (f)
                {
                    switch (f->Type())
                    {
                        case JType::OBJ:
                        case JType::VAR:
                        {
                            break;
                        }

                        default:
                        {
                            json.seekg(-1, std::ios::cur);
                            throw TypeMismatch(n, f->Type(), JType::OBJ);
                        }
                    }
                }

                n = GetName(json);
                f = f ? GetField(f, n) : nullptr;

                c = GetChar(json);
            }
            assert('\"' == c);

            c = FirstNotSpace(json);

            if (':' != c)
            {
                json.seekg(-1, std::ios::cur);
                throw Unexpected();
            }

            GetVal(json, n, f);

        } while ([&]
        {
            switch (FirstNotSpace(json))
            {
                case ',':
                {
                    c = FirstNotSpace(json);
                    return true;
                }

                case '}':
                {
                    return false;
                }

                default:
                {
                    json.seekg(-1, std::ios::cur);
                    throw Unexpected();
                }
            }
        }());
    }

    static double GetFlt(std::istream& json)
    {
        double v;
        json >> v;
        return v;
    }

    static double GetFlt(const std::string& num)
    {
        char* end;
        double v = strtod(num.c_str(), &end);

        if (num.c_str() == end)
        {
            throw std::runtime_error("Failed to parse double");
        }

        return v;
    }

    static std::string GetStr(std::istream& json)
    {
        std::ostringstream oss;

        char c = 0;
        char p;
        do
        {
            p = c;
            c = GetChar(json);

        } while ([&]
        {
            switch (c)
            {
                case '\\':
                {
                    if ('\\' == p)
                    {
                        oss << c;
                        c = 0;
                    }
                    break;
                }

                case '\"':
                {
                    if ('\\' != p)
                    {
                        return false;
                    }

                    oss << c;
                    break;
                }

                case '/':
                {
                    // \/ equals /
                    oss << c;
                    break;
                }

                case 'n':
                {
                    oss << ('\\' == p ? '\n' : 'n');
                    break;
                }

                case 'r':
                {
                    oss << ('\\' == p ? '\r' : 'r');
                    break;
                }

                case 't':
                {
                    oss << ('\\' == p ? '\t' : 't');
                    break;
                }

                case 'u':
                {
                    if ('\\' == p)
                    {
                        char buf[5];
                        for (int i = 0; i < 4; i++)
                        {
                            c = tolower(GetChar(json));
                            if (('0' <= c && '9' >= c) ||
                                ('a' <= c && 'f' >= c))
                            {
                                buf[i] = c;
                                continue;
                            }

                            json.seekg(-1, std::ios::cur);
                            throw Unexpected();
                        }
                        buf[4] = '\0';
                        oss << utf8().to_bytes((wchar_t)strtol(buf, nullptr, 16));
                    }
                    else
                    {
                        oss << c;
                    }
                    break;
                }

                default:
                {
                    if ('\\' == p)
                    {
                        json.seekg(-1, std::ios::cur);
                        throw Unexpected();
                    }
                    oss << c;
                    break;
                }
            }

            return true;
        }());

        return oss.str();
    }

    static std::string GetNum(std::istream& json)
    {
        std::ostringstream oss;

        bool digit = false;
        bool sign  = false;
        bool hex   = false;
        bool exp   = false;

        auto c = GetChar(json);
        auto p = json.peek();

        if ('0' == c && ('x' == p || 'X' == p))
        {
            oss << c << GetChar(json);

            c = GetChar(json);

            digit = true;
            sign  = true;
            hex   = true;
        }

        const auto isnum = [hex](char c)
        {
            if (c >= '0' && c <= '9')
            {
                return true;
            }

            if (hex && ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
            {
                return true;
            }

            return false;
        };

        if ('+' != c && '-' != c && '.' != c && !isnum(c))
        {
            throw Unexpected();
        }

        do
        {
            if ('+' == c || '-' == c)
            {
                if (sign)
                {
                    throw Unexpected();
                }

                sign = true;
            }
            else if ('E' == c || 'e' == c)
            {
                if (exp)
                {
                    throw Unexpected();
                }

                exp  = true;
                sign = false;
            }
            else if ('.' == c)
            {
                if (digit)
                {
                    throw Unexpected();
                }

                digit = true;
            }

            oss << c;

        } while ([&json, &c, &isnum]
        {
            auto p = json.peek();

            if ('.' == p || '+' == p || '-' == p || 'e' == p || 'E' == p || isnum(p))
            {
                c = GetChar(json);
                return true;
            }

            return false;
        }());

        return oss.str();
    }

    static int64_t GetInt(std::istream& json)
    {
        int64_t v;

        auto c = GetChar(json);
        auto p = json.peek();
        if ('0' == c && ('x' == p || 'X' == p))
        {
            json.seekg(1, std::ios::cur);
            json >> std::hex >> v;
        }
        else
        {
            if (json.eof())
            {
                json.clear();
                json.seekg(-1, std::ios::end);
            }
            else
            {
                json.seekg(-1, std::ios::cur);
            }

            json >> std::dec >> v;
        }

        return v;
    }

    static int64_t GetInt(const std::string& num)
    {
        int64_t v;
        char* end;

        if (num.length() > 2 && '0' == num[0] && ('x' == num[1] || 'X' == num[1]))
        {
            v = strtoll(num.c_str(), &end, 16);
        }
        else
        {
            v = strtoll(num.c_str(), &end, 10);
        }

        if (num.c_str() == end)
        {
            throw std::runtime_error("Failed to parse int");
        }

        return v;
    }

    static int64_t GetInt(const std::string& json, std::string::size_type& off)
    {
        char* end;
        int64_t value;

        if (json.length() > off + 2 && '0' == json[off] && ('x' == json[off + 1] || 'X' == json[off + 1]))
        {
            value = strtoll(json.c_str() + off, &end, 16);
        }
        else
        {
            value = strtoll(json.c_str() + off, &end, 10);
        }

        if (end == json.c_str() + off)
        {
            throw std::runtime_error("Failed to parse int");
        }

        off = end - json.c_str();

        return value;
    }

    static std::string GetName(std::istream& json)
    {
        std::ostringstream oss;

        char c = 0;
        char p;
        do
        {
            p = c;
            c = GetChar(json);

        } while ([&]
        {
            switch (c)
            {
                case '\\':
                {
                    if ('\\' == p)
                    {
                        oss << c;
                        c = 0;
                    }
                    break;
                }

                case '\"':
                {
                    if ('\\' != p)
                    {
                        json.seekg(-1, std::ios::cur);
                        return false;
                    }

                    oss << c;
                    break;
                }

                default:
                {
                    if ('\\' == p)
                    {
                        json.seekg(-1, std::ios::cur);
                        throw Unexpected();
                    }

                    if ('.' == c)
                    {
                        json.seekg(-1, std::ios::cur);
                        return false;
                    }

                    oss << c;
                    break;
                }
            }

            return true;
        }());

        return oss.str();
    }

    static bool GetBool(std::istream& json)
    {
        switch (GetChar(json))
        {
            case 't':
            {
                if ('r' == GetChar(json) &&
                    'u' == GetChar(json) &&
                    'e' == GetChar(json))
                {
                    return true;
                }

                break;
            }

            case 'f':
            {
                if ('a' == GetChar(json) &&
                    'l' == GetChar(json) &&
                    's' == GetChar(json) &&
                    'e' == GetChar(json))
                {
                    return false;
                }

                break;
            }

            default: break;
        }

        json.seekg(-1, std::ios::cur);
        throw Unexpected();
    }

    static uint64_t GetUint(std::istream& json)
    {
        uint64_t v;

        auto c = GetChar(json);
        if ('0' == c && 'x' == json.peek())
        {
            json.seekg(1, std::ios::cur);
            json >> std::hex >> v;
        }
        else
        {
            json.seekg(-1, std::ios::cur);
            json >> std::dec >> v;
        }

        return v;
    }

    static uint64_t GetUint(const std::string& json, std::string::size_type& off)
    {
        char* end;
        uint64_t value;

        if (json.length() > off + 2 && '0' == json[off] && ('x' == json[off + 1] || 'X' == json[off + 1]))
        {
            value = std::strtoull(json.c_str() + off, &end, 16);
        }
        else
        {
            value = std::strtoull(json.c_str() + off, &end, 10);
        }

        if (end == json.c_str() + off)
        {
            throw std::runtime_error("Failed to parse uint");
        }

        off = end - json.c_str();

        return value;
    }

    static bool IsFloat(const std::string& num)
    {
        if (num.length() >= 2 && '0' == num[0] && ('x' == num[1] || 'X' == num[1]))
        {
            return false;
        }

        for (auto c : num)
        {
            if ('.' == c || 'e' == c || 'E' == c)
            {
                return true;
            }
        }

        return false;
    }

    static void GetJson(const std::string& name, const JField& field, std::ostream& json)
    {
        if (field.IsUndefined())
        {
            return;
        }

        if (!name.empty())
        {
            json << '\"' << name << "\":" ;
        }

        if (field.IsNull())
        {
            json << "null";
            return;
        }

        switch (field.Type())
        {
            case JType::INT:
            {
                json << ((JBase&)field).GetI();
                break;
            }

            case JType::NUM:
            {
                json << std::setprecision(std::numeric_limits<double>::digits10 + 1) << ((JBase&)field).GetN();
                break;
            }

            case JType::BOOL:
            {
                json << (((JBase&)field).GetB() ? "true" : "false");
                break;
            }

            case JType::STR:
            {
                GetJson(((JBase&)field).GetS(), json);
                break;
            }

            case JType::OBJ:
            {
                GetJson((JObject&)field, json);
                break;
            }

            case JType::ARR:
            {
                GetJson((JArray&)field, json);
                break;
            }

            case JType::VAR:
            {
                GetJson((JVariant&)field, json);
                break;
            }

            default:
            {
                throw std::runtime_error(name + ": unknown json type");
            }
        }
    }

    static void GetJson(const JVariant& var, std::ostream& json)
    {
        switch (var.Subtype())
        {
            case JType::BOOL:
            {
                json << (((JBase&)var).GetB() ? "true" : "false");
                break;
            }

            case JType::INT:
            {
                json << ((JBase&)var).GetI();
                break;
            }

            case JType::NUM:
            {
                json << std::setprecision(std::numeric_limits<double>::digits10 + 1) << ((JBase&)var).GetN();
                break;
            }

            case JType::STR:
            {
                json << '\"';

                for (auto c : ((JBase&)var).GetS())
                {
                    switch (c)
                    {
                        case '\\':
                        {
                            json << "\\\\";
                            break;
                        }

                        case '"':
                        {
                            json << "\\\"";
                            break;
                        }

                        default:
                        {
                            json << c;
                            break;
                        }
                    }
                }

                json << '\"';
                break;
            }

            case JType::OBJ:
            {
                json << '{';

                bool first = true;
                auto foreach = (std::function<void(const std::string&, const JVariant&)>)[&first, &json](const std::string& name, const JVariant& var)
                {
                    if (var.IsUndefined())
                    {
                        return;
                    }

                    if (!first)
                    {
                        json << ',';
                    }
                    first = false;

                    GetJson(name, var, json);
                };
                var.ForEach(foreach);

                json << '}';
                break;
            }

            case JType::ARR:
            {
                json << '[';

                bool first = true;
                auto foreach = (std::function<void(const JVariant&)>)[&first, &json](const JVariant& var)
                {
                    if (var.IsUndefined())
                    {
                        return;
                    }

                    if (!first)
                    {
                        json << ',';
                    }
                    first = false;

                    GetJson("", var, json);
                };
                var.ForEach(foreach);

                json << ']';
                break;
            }

            default: break;
        }
    }

    static void GetJson(const JObject& obj, std::ostream& json)
    {
        json << '{';

        bool first = true;
        obj.ForEach([&](const std::string& name, const JField& field)
        {
            if (field.IsUndefined())
            {
                return false;
            }

            if (!first)
            {
                json << ',';
            }
            first = false;

            GetJson(name, field, json);

            return false;
        });

        json << '}';
    }

    static void GetJson(const JArray& arr, std::ostream& json)
    {
        json << '[';

        bool first = true;
        arr.ForEach([&](const JField& field)
        {
            if (!first)
            {
                json << ',';
            }
            first = false;

            GetJson("", field, json);

            return false;
        });

        json << ']';
    }

    static void GetJson(const std::string& str, std::ostream& json)
    {
        json << '\"';

        for (auto c : str)
        {
            switch (c)
            {
                case '\\':
                {
                    json << "\\\\";
                    break;
                }

                case '"':
                {
                    json << "\\\"";
                    break;
                }

                default:
                {
                    json << c;
                    break;
                }
            }
        }

        json << '\"';
    }

    static std::wstring_convert<std::codecvt_utf8<wchar_t>>& utf8()
    {
        // TODO: no multi-threading safe. Make it local thread storage?
        static std::wstring_convert<std::codecvt_utf8<wchar_t>> u8;
        return u8;
    }
};

inline std::string JField::Serialize() const
{
    std::ostringstream json;
    this->Serialize(json);
    return json.str();
}

inline bool JField::Serialize(std::ostream& json) const
{
    JParser::Serialize(json, *this);
    return !!json;
}

inline bool JField::Serialize(std::ostream&& json) const
{
    return this->Serialize((std::ostream&)json);
}

inline bool JField::Deserialize(std::istream& json)
{
    try
    {
        JParser::Deserialize(json, *this);
        return true;

    } catch(const std::exception&)
    {
        this->Clear();
        return false;
    }
}

inline bool JField::Deserialize(std::istream&& json)
{
    return this->Deserialize((std::istream&)json);
}

inline bool JField::Deserialize(std::istream& json, std::string& error, size_t& where)
{
    try
    {
        where = -1;
        error.clear();
        JParser::Deserialize(json, *this);
        return true;

    } catch(const std::exception& e)
    {
        if (!json)
        {
            json.clear();
            json.seekg(0, std::ios::end);
        }
        where = json.tellg();
        error = e.what();
        this->Clear();
        return false;
    }
}

inline bool JField::Deserialize(std::istream&& json, std::string& error, size_t& where)
{
    return this->Deserialize((std::istream&)json, error, where);
}

inline bool JField::Deserialize(const std::string& json)
{
    auto stream = std::istringstream(json);

    try
    {
        JParser::Deserialize(stream, *this);
        return true;

    } catch(const std::exception&)
    {
        this->Clear();
        return false;
    }
}

inline bool JField::Deserialize(std::string&& json)
{
    return this->Deserialize((const std::string&)json);
}

inline bool JField::Deserialize(const std::string& json, std::string& error, size_t& where)
{
    return this->Deserialize(std::istringstream(json), error, where);
}

inline bool JField::Deserialize(std::string&& json, std::string& error, size_t& where)
{
    return this->Deserialize(std::istringstream(json), error, where);
}

#ifdef JOBJECT_NS
} // namespace JOBJECT_NS
#endif