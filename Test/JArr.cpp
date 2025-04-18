#include "JObject.h"

int main()
{
    std::string e;
    size_t w;
    JArr<JInt> jarr;

    if (!jarr.Deserialize("", e, w) || !jarr.IsUndefined() || jarr.IsNull() || jarr.HasValue())
    {
        return -1;
    }

    if (!jarr.Deserialize("null", e, w) || jarr.IsUndefined() || !jarr.IsNull() || jarr.HasValue())
    {
        return -1;
    }

    if (!jarr.Deserialize("[]", e, w) || !jarr.IsUndefined() || jarr.IsNull() || jarr.HasValue() || 0 != jarr().size())
    {
        return -1;
    }

    if (!jarr.Deserialize("[0, 1, 2]", e, w) || 0 != jarr[0] || 1 != jarr[1] || 2 != jarr[2])
    {
        return -1;
    }

    JArr<JArr<JInt>> jarrarr;
    if (!jarrarr.Deserialize("[[0, 1], [2, 3]]", e, w) || 0 != jarrarr[0][0] || 1 != jarrarr[0][1] || 2 != jarrarr[1][0] || 3 != jarrarr[1][1])
    {
        return -1;
    }

    jarr = nullptr;
    if (jarr.IsUndefined() || !jarr.IsNull())
    {
        return -1;
    }

    jarr.Clear();
    if (!jarr.IsUndefined())
    {
        return -1;
    }

    jarr.Push(0);
    if (0 != jarr[0])
    {
        return -1;
    }

    jarr.Unshift(1);
    if (1 != jarr[0])
    {
        return -1;
    }

    jarr.Insert(2, 1);
    if (2 != jarr[1])
    {
        return -1;
    }

    JArr<JInt> jsub;
    jsub.Push(3);
    jsub.Push(4);

    jarr.Insert(jsub, 1);
    if (3 != jarr[1] || 4 != jarr[2])
    {
        return -1;
    }

    jarr.Insert({ 5, 6 }, 1);
    if (5 != jarr[1] || 6 != jarr[2])
    {
        return -1;
    }

    jarr = { 0, 1, 2 };
    if (0 != jarr[0] || 1 != jarr[1] || 2 != jarr[2])
    {
        return -1;
    }

    jarr = { 0, 1, 2, 3 };
    jarr.RemoveAt(0);
    if (3 != jarr.Length() || 1 != jarr[0])
    {
        return -1;
    }

    jarr.RemoveIf([](size_t index, const JInt& value)
    {
        return 1 == index && 2 == value;
    });
    if (2 != jarr.Length() || 3 != jarr[1])
    {
        return -1;
    }

    return 0;
}