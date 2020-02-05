#pragma once

typedef uint32_t codeword_type;

template <typename Symbol, typename Weight>
struct weighted_symbol {
    weighted_symbol() {}
    weighted_symbol(Symbol s, Weight w) : s(s), w(w) {}
    Symbol s;
    Weight w;
};

struct codeword {
    codeword() : m_pos(0), m_bits(0) {}

    size_t length() const {
        return m_pos;
    }

    codeword_type get() const {
        return m_bits;
    }

    void append(bool bit) {
        m_bits |= codeword_type(bit) << m_pos++;
    }

    codeword operator+(bool bit) {
        codeword x = *this;
        x.append(bit);
        return x;
    }

    codeword operator=(codeword const& rhs) {
        codeword x;
        x.m_pos = rhs.m_pos;
        x.m_bits = rhs.m_bits;
        return x;
    }

    friend std::ostream& operator<<(std::ostream& os, codeword const& c) {
        codeword_type b = c.m_bits;
        for (uint32_t p = 0; p != c.m_pos; ++p) {
            os << (b & 1);
            b >>= 1;
        }
        return os;
    }

private:
    uint32_t m_pos;
    codeword_type m_bits;
};
