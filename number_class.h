// number_class.h
#ifndef NUMBER_CLASS_H // include guard
#define NUMBER_CLASS_H

#include <string>
#include <ostream>
#include <sstream>

#define ALPHABET_SIZE 36

typedef unsigned long long ull;

const char alphabet[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

namespace N
{

    int search_binary(const char arr[], int left, int right, char key)
    {
        int middle = 0;
        while (1)
        {
            middle = (left + right) / 2;

            if (key < arr[middle])
                right = middle - 1;
            else if (key > arr[middle])
                left = middle + 1;
            else
                return middle;

            if (left > right)
                return -1;
        }
    }

    int pos(char key) { return search_binary(alphabet, 0, ALPHABET_SIZE, key); }

    class number
    {
    private:
        std::string value;
        int base;
    public:
        number();
        number(std::string, int);
        ull to_decimal();
        std::string to_base(int);
        void convert(int);

        friend std::ostream& operator <<(std::ostream&, const number&);
        friend bool operator ==(const number&, const number&);
        friend bool operator !=(const number&, const number&);
        friend bool operator <(const number&, const number&);
        friend bool operator >(const number&, const number&);
        friend bool operator <=(const number&, const number&);
        friend bool operator >=(const number&, const number&);

        friend const number operator +(number, const number&);
        number& operator +=(const number&);
        friend const number operator -(number, const number&);
        number& operator -=(const number&);
        friend const number operator *(const number&, const number&);
        number& operator *=(const number&);
        friend const number operator /(const number&, const number&);
        number& operator /=(const number&);

        ~number();
    };
    
    number::number(std::string v, int b)
    {
        if ((b < 2) || (b > 36))
        {
            throw "Invalid base (" + std::to_string(b) + ")";
        }
        for (int i = 0; i < v.size(); i++)
        {
            if (pos(v[i]) > b)
            {
                throw "Invalid char " + v[i];
            }
        }
        value = v;
        base = b;
    }

    number::number()
    {
        value = "0";
        base = 10;
    }

    ull number::to_decimal()
    {
        ull result = 0, q = 1;
        for (int i = 0; i < value.size(); i++)
        {
            result += q * pos(value[i]);
            q *= base;
        }
        return result;
    }

    std::string number::to_base(int b)
    {
        if ((b < 2) || (b > 36))
        {
            throw "Invalid base (" + std::to_string(b) + ")";
        }
        std::string result = "";
        ull a = to_decimal();
        while (a > 0)
        {
            result += alphabet[a % b];
            a /= b;
        }
        return result;
    }

    void number::convert(int b)
    {
        if ((b < 2) || (b > 36))
        {
            throw "Invalid base (" + std::to_string(b) + ")";
        }
        if (b == 10)
        {
            value = std::to_string(to_decimal());
            base = 10;
            return;
        }
        else
        {
            value = to_base(b);
            base = b;
            return;
        }
    }

    std::ostream& operator <<(std::ostream& os, const number& n)
    {
        os << n.value + " (" + std::to_string(n.base) + ")";
        return os;
    }

    bool operator ==(const number& a, const number& b)
    {
        if (a.base != b.base)
        {
            throw "Various bases (" + std::to_string(a.base) + ") (" + std::to_string(b.base) + ")";
        }

        if (a.value.size() != b.value.size())
            return 0;
        bool f = 1;
        for (int i = 0; ((i < a.value.size()) && (f)); i++)
            f = (a.value[i] == b.value[i]);
        return f;
    }

    bool operator !=(const number& a, const number& b)
    {
        return !(a == b);
    }

    bool operator <(const number& a, const number& b)
    {
        if (a.base != b.base)
        {
            throw "Various bases (" + std::to_string(a.base) + ") (" + std::to_string(b.base) + ")";
        }

        if (a.value.size() < b.value.size())
            return 1;
        bool f = 1;
        for (int i = 0; ((i < a.value.size()) && (f)); i++)
            f = (a.value[i] < b.value[i]);
        return f;
    }

    bool operator >(const number& a, const number& b)
    {
        if (a.base != b.base)
        {
            throw "Various bases (" + std::to_string(a.base) + ") (" + std::to_string(b.base) + ")";
        }

        if (a.value.size() > b.value.size())
            return 1;
        bool f = 1;
        for (int i = 0; ((i < a.value.size()) && (f)); i++)
            f = (a.value[i] > b.value[i]);
        return f;
    }

    bool operator <=(const number& a, const number& b)
    {
        return !(a > b);
    }

    bool operator >=(const number& a, const number& b)
    {
        return !(a < b);
    }

    const number operator +(number l, const number& r)
    {
        if (l.base != r.base)
        {
            throw "Various bases (" + std::to_string(l.base) + ") (" + std::to_string(r.base) + ")";
        }

        number a, b, result("", a.base);
        if (l < r)
        {
            a = r;
            b = l;
        }
        else
        {
            a = l;
            b = r;
        }

        while (a.value.size() > b.value.size())
            b.value = '0' + b.value;

        int q = 0;
        for (int i = a.value.size() - 1; i >= 0; i--)
        {
            int t = pos(a.value[i]) + pos(b.value[i]) + q;
            result.value = alphabet[t % result.base] + result.value;
            q = t / result.base;
        }

        if (q != 0)
            result.value = alphabet[q] + result.value;

        return result;
    }

    number& number::operator +=(const number& a)
    {
        return *this = (*this + a);
    }

    const number operator -(number l, const number& r)
    {
        if (l.base != r.base)
        {
            throw "Various bases (" + std::to_string(l.base) + ") (" + std::to_string(r.base) + ")";
        }

        number a, b, result("", a.base);
        if (l < r)
        {
            a = r;
            b = l;
        }
        else if (l == r)
        {
            return number("0", result.base);
        }
        else
        {
            a = l;
            b = r;
        }

        while (a.value.size() > b.value.size())
            b.value = '0' + b.value;

        int q = 0;
        for (int i = a.value.size() - 1; i >= 0; i--)
        {
            int t = pos(a.value[i]) - pos(b.value[i]) - q;
            result.value = alphabet[(t < 0 ? result.base - 1 : t)] + result.value;
            q = (t < 0 ? 1 : 0);
        }

        while ((result.value[0] == '0') && (result.value.size() > 1))
            result.value = result.value.substr(1, result.value.size() - 1);
        
        return result;
    }

    number& number::operator -=(const number& a)
    {
        return *this = (*this - a);
    }

    const number operator *(const number& l, const number& r)
    {
        if (l.base != r.base)
        {
            throw "Various bases (" + std::to_string(l.base) + ") (" + std::to_string(r.base) + ")";
        }

        number a, b, result("", a.base);
        if (l < r)
        {
            a = r;
            b = l;
        }
        else if ((l.value == "0") || (r.value == "0"))
        {
            return number("0", result.base);
        }
        else
        {
            a = l;
            b = r;
        }

        for (ull i = 0; i < b.to_decimal(); i++)
            result += a;

        return result;
    }

    number& number::operator *=(const number& a)
    {
        return *this = (*this * a);
    }

    const number operator /(const number& l, const number& r)
    {
        if (l.base != r.base)
        {
            throw "Various bases (" + std::to_string(l.base) + ") (" + std::to_string(r.base) + ")";
        }
        if (r.value == "0")
        {
            throw "Divide by zero";
        }

        number a, b, result("", a.base);
        if (l < r)
        {
            a = r;
            b = l;
        }
        else if ((l.value == "0") || (r.value == "0"))
        {
            return number("0", result.base);
        }
        else
        {
            a = l;
            b = r;
        }

        while (a > b)
        {
            a -= b;
            result += number("1", result.base);
        }
        return result;
    }

    number& number::operator /=(const number& a)
    {
        return *this = (*this / a);
    }

    number::~number()
    {
    }

}

#endif /* NUMBER_CLASS_H */
