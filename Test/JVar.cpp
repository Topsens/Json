#include "JObject.h"

struct JInner : public JObject
{
    JStr str;
    JOBJECT(JInner);
};
BEG_JFIELDS(JInner)
    JFIELD(str)
END_JFIELDS

struct JOuter : public JObject
{
    JNum num;
    JArr<JInt> ints;
    JInner inner;
    JOBJECT (JOuter);
};
BEG_JFIELDS(JOuter)
    JFIELD(num),
    JFIELD(ints),
    JFIELD(inner)
END_JFIELDS

bool Deserialize()
{
    JVar jvar;

    if (!jvar.Deserialize("") || !jvar.IsUndefined() || jvar.IsNull() || jvar.HasValue())
    {
        return false;
    }

    if (!jvar.Deserialize("null") || jvar.IsUndefined() || !jvar.IsNull() || JType::VAR != jvar.Subtype())
    {
        return false;
    }

    if (!jvar.Deserialize("123") || !jvar.HasValue() || JType::INT != jvar.Subtype() || 123 != jvar.Int())
    {
        return false;
    }

    if (!jvar.Deserialize("-123") || !jvar.HasValue() || JType::INT != jvar.Subtype() || -123 != jvar.Int())
    {
        return false;
    }

    if (!jvar.Deserialize("0X1AB") || !jvar.HasValue() || JType::INT != jvar.Subtype() || 0x1AB != jvar.Int())
    {
        return false;
    }

    if (!jvar.Deserialize("0x1ab") || !jvar.HasValue() || JType::INT != jvar.Subtype() || 0x1AB != jvar.Int())
    {
        return false;
    }

    if (jvar.Deserialize("1AB") || jvar.Deserialize("x1AB"))
    {
        return false;
    }

    if (!jvar.Deserialize("1.23") || !jvar.HasValue() || JType::NUM != jvar.Subtype() || 1.23 != jvar.Num())
    {
        return false;
    }

    if (!jvar.Deserialize("-1.23") || !jvar.HasValue() || JType::NUM != jvar.Subtype() || -1.23 != jvar.Num())
    {
        return false;
    }

    if (!jvar.Deserialize("123e4") || !jvar.HasValue() || JType::NUM != jvar.Subtype() || 1230000.0 != jvar.Num())
    {
        return false;
    }

    if (!jvar.Deserialize("-123e-4") || !jvar.HasValue() || JType::NUM != jvar.Subtype() || -0.0123 != jvar.Num())
    {
        return false;
    }

    if (!jvar.Deserialize("\"123\"") || !jvar.HasValue() || JType::STR != jvar.Subtype() || "123" != jvar.Str())
    {
        return false;
    }

    if (!jvar.Deserialize("true") || !jvar.HasValue() || JType::BOOL != jvar.Subtype() || !jvar.Bool())
    {
        return false;
    }

    if (!jvar.Deserialize("false") || !jvar.HasValue() || JType::BOOL != jvar.Subtype() || jvar.Bool())
    {
        return false;
    }

    if (!jvar.Deserialize("[]") || !jvar.IsUndefined() || jvar.HasValue() || JType::VAR != jvar.Subtype() || jvar.Length())
    {
        return false;
    }

    if (!jvar.Deserialize("[0, 1, 2]") || !jvar.HasValue() || JType::ARR != jvar.Subtype() || 3 != jvar.Length())
    {
        return false;
    }

    for (int64_t i = 0; i < 3; i++)
    {
        if (!jvar[i].HasValue() || JType::INT != jvar[i].Subtype() || i != jvar[i].Int())
        {
            return false;
        }
    }

    if (!jvar.Deserialize("{}") || !jvar.IsUndefined() || jvar.HasValue() || JType::VAR != jvar.Subtype() || 0 != jvar.Length())
    {
        return false;
    }

    if (!jvar.Deserialize(R"( {"one": 1, "null": null, "arr": [1, 2, 3]} )") || !jvar.HasValue() || JType::OBJ != jvar.Subtype() || 3 != jvar.Length())
    {
        return false;
    }

    if (!jvar["one"].HasValue() || JType::INT != jvar["one"].Subtype() || 1 != jvar["one"].Int())
    {
        return false;
    }

    if (jvar["null"].IsUndefined() || !jvar["null"].IsNull())
    {
        return false;
    }

    if (!jvar["arr"].HasValue() || JType::ARR != jvar["arr"].Subtype() || 3 != jvar["arr"].Length())
    {
        return false;
    }

    if (!jvar.Deserialize("{\"a.b\":1}") || !jvar.HasValue() || !jvar["a"].HasValue() || !jvar["a"]["b"].HasValue() || 1 != jvar["a"]["b"].Int())
    {
        return false;
    }

    return true;
}

bool Serialize()
{
    JVar jvar;

    if (!jvar.Deserialize(R"(
        [
            123,
            123.,
            "123",
            false,
            {
                "var": "a\\b\"c"
            },
            null
        ]
    )"))
    {
        return false;
    }

    const std::string json = "[123,123,\"123\",false,{\"var\":\"a\\\\b\\\"c\"},null]";
    if (json != jvar.Serialize())
    {
        return false;
    }

    jvar.Unshift(JVar());
    if (json != jvar.Serialize())
    {
        return false;
    }

    jvar.Push(JVar());
    if (json != jvar.Serialize())
    {
        return false;
    }

    if (8 != jvar.Length())
    {
        return false;
    }

    return true;
}

bool ToArr()
{
    JVar jvar;

    if(!jvar.Deserialize("[0, 1, 2]"))
    {
        return false;
    }

    JArr<JInt> ints;
    if (!jvar.ToArr(ints))
    {
        return false;
    }

    if (!ints.HasValue() || 3 != ints.Length())
    {
        return false;
    }

    if (jvar.Serialize() != jvar.ToArr<JInt>().Serialize())
    {
        return false;
    }

    for (int64_t i = 0; i < 3; i++)
    {
        if (i != ints[i])
        {
            return false;
        }
    }

    JArr<JNum> nums;
    if (!jvar.ToArr(nums))
    {
        return false;
    }

    if (!nums.HasValue() || 3 != nums.Length())
    {
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        if ((double)i != nums[i])
        {
            return false;
        }
    }

    return true;
}

bool ToObj()
{
    JVar jvar;

    if (!jvar.Deserialize(R"(
        {
            "num": 1.0,
            "ints": [
                1,
                2,
                null
            ],
            "inner": {
                "str": "123"
            }
        }
    )"))
    {
        return false;
    }

    JOuter jouter;
    if (!jvar.ToObj(jouter))
    {
        return false;
    }

    if (!jouter.HasValue() || !jouter.num.HasValue() || !jouter.ints.HasValue() || !jouter.inner.HasValue())
    {
        return false;
    }

    if (1.0 != jouter.num)
    {
        return false;
    }

    auto& ints = jouter.ints;
    if (3 != ints.Length() || 1 != ints[0] || 2 != ints[1] || !ints[2].IsNull())
    {
        return false;
    }

    auto& inner = jouter.inner;
    if (!inner.str.HasValue() || "123" != inner.str())
    {
        return false;
    }

    if (jvar.Serialize() != jvar.ToObj<JOuter>().Serialize())
    {
        return false;
    }

    return true;
}

bool Array()
{
    JVar jvar;

    jvar.Push(0);
    if (!jvar.HasValue() || JType::ARR != jvar.Subtype() || 1 != jvar.Length() || 0 != jvar[0].Int())
    {
        return false;
    }

    jvar.Unshift(1.0);
    if (2 != jvar.Length() || 1.0 != jvar[0].Num())
    {
        return false;
    }

    jvar.Insert("hello", 1);
    if (3 != jvar.Length() || "hello" != jvar[1].Str())
    {
        return false;
    }

    jvar.RemoveAt(0);
    if (2 != jvar.Length() || "hello" != jvar[0].Str())
    {
        return false;
    }

    jvar.RemoveIf([](size_t index, const JVar& item)
    {
        return 0 == index && JType::STR == item.Subtype();
    });
    if (1 != jvar.Length() || 0 != jvar[0].Int())
    {
        return false;
    }

    return true;
}

bool Asign()
{
    JVar jvar;

    jvar = nullptr;
    if (jvar.IsUndefined() || !jvar.IsNull())
    {
        return false;
    }

    jvar = true;
    if (!jvar.HasValue() || !jvar.Bool())
    {
        return false;
    }

    jvar = 0;
    if (jvar.IsNull())
    {
        return false;
    }

    jvar = nullptr;
    if (!jvar.IsNull() || JType::VAR != jvar.Subtype())
    {
        return false;
    }

    jvar = 123;
    if (!jvar.HasValue() || JType::INT != jvar.Subtype() || 123 != jvar.Int())
    {
        return false;
    }

    JArr<JInt> jarr;
    if (!jarr.Deserialize("[0, 1, 2]"))
    {
        return false;
    }

    jvar = jarr;
    if (!jvar.HasValue() || JType::ARR != jvar.Subtype() || 3 != jvar.Length())
    {
        return false;
    }

    for (int64_t i = 0; i < 3; i++)
    {
        if (JType::INT != jvar[i].Subtype() || i != jvar[i].Int())
        {
            return false;
        }
    }

    JOuter jouter;
    if (!jouter.Deserialize(R"(
        {
            "num": 0,
            "ints": [0, 1],
            "inner": {
                "str": "123"
            }
        }
    )"))
    {
        return false;
    }

    jvar = jouter;
    if (!jvar.HasValue() || JType::OBJ != jvar.Subtype())
    {
        return false;
    }

    if (!jvar["num"].HasValue() || !jvar["ints"].HasValue() || !jvar["inner"].HasValue())
    {
        return false;
    }

    if (JType::NUM != jvar["num"].Subtype() || 0 != jvar["num"].Num())
    {
        return false;
    }

    if (JType::ARR != jvar["ints"].Subtype() || 2 != jvar["ints"].Length())
    {
        return false;
    }

    for (int64_t i = 0; i < 2; i++)
    {
        if (!jvar["ints"][i].HasValue() || JType::INT != jvar["ints"][i].Subtype() || i != jvar["ints"][i].Int())
        {
            return false;
        }
    }

    if (!jvar.Deserialize("{\"int\":1,\"arr\":[1,2,3]}"))
    {
        return false;
    }

    JVar copy;
    copy = jvar;
    if (!copy.HasValue() || JType::OBJ != copy.Subtype())
    {
        return false;
    }

    auto& vint = copy["int"];
    if (JType::INT != vint.Subtype() || !vint.HasValue() || 1 != vint.Int())
    {
        return false;
    }

    auto& varr = copy["arr"];
    if (JType::ARR != varr.Subtype() || !varr.HasValue() || 3 != varr.Length())
    {
        return false;
    }

    if (JType::INT != varr[0].Subtype() || !varr[0].HasValue() || 1 != varr[0].Int() ||
        JType::INT != varr[1].Subtype() || !varr[1].HasValue() || 2 != varr[1].Int() ||
        JType::INT != varr[2].Subtype() || !varr[2].HasValue() || 3 != varr[2].Int())
    {
        return false;
    }

    return true;
}

bool Compose()
{
    JVar jvar;
    jvar["int"] = 123;
    jvar["num"] = 1.23;
    jvar["obj"]["str"] = "123";

    if (JType::OBJ != jvar.Subtype())
    {
        return false;
    }

    if (JType::INT != jvar["int"].Subtype() || JType::NUM != jvar["num"].Subtype() || JType::OBJ != jvar["obj"].Subtype())
    {
        return false;
    }

    if (123 != jvar["int"].Int() || 1.23 != jvar["num"].Num())
    {
        return false;
    }

    if (JType::STR != jvar["obj"]["str"].Subtype() || "123" != jvar["obj"]["str"].Str())
    {
        return false;
    }

    auto& und = ((const JVar&)jvar)["undefined"];
    if (!und.IsUndefined())
    {
        return false;
    }

    return true;
}

bool Default()
{
    JVar jvar;

    if (123 != jvar.Int(123))
    {
        return false;
    }

    if (1.23 != jvar.Num(1.23))
    {
        return false;
    }

    if (jvar.Bool(false))
    {
        return false;
    }

    if ("hello" != jvar.Str("hello"))
    {
        return false;
    }

    jvar.Deserialize("123");
    if (123 != jvar.Int(1234))
    {
        return false;
    }

    return true;
}

int main()
{
    if (!Deserialize())
    {
        return -1;
    }

    if (!Serialize())
    {
        return -1;
    }

    if (!ToArr())
    {
        return -1;
    }

    if (!ToObj())
    {
        return -1;
    }

    if (!Array())
    {
        return -1;
    }

    if (!Asign())
    {
        return -1;
    }

    if (!Compose())
    {
        return -1;
    }

    if (!Default())
    {
        return -1;
    }

    return 0;
}