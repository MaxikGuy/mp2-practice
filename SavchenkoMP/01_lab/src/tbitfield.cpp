// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len > 0) {
        BitLen = len;
        MemLen = ((len + bitsInElem - 1) >> shiftSize);
        pMem = new TELEM[MemLen];
        memset(pMem, 0, MemLen * sizeof(TELEM));
    }
    else if(len == 0) {
        BitLen = 0;
        MemLen = 0;
        pMem = nullptr;
    }
    else {
        throw "error: BitFiels size < 0";
    }
}
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (MemLen) {
        pMem = new TELEM[MemLen];
        memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    }
    else {
        pMem = nullptr;
    }
}
TBitField::~TBitField()
{
    if (MemLen > 0)
        delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const noexcept // индекс Мем для бита n
{
    return n >> shiftSize;
}
TELEM TBitField::GetMemMask(const int n) const noexcept // битовая маска для бита n
{
    return 1 << (n & (bitsInElem - 1));
}

// доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}
void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0) throw "error: index out of range";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}
void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0) throw "error: index out of range";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}
int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0) throw "error: index out of range";
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) >> (n & (bitsInElem - 1)));
}

// битовые операции
const TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (MemLen != bf.MemLen)
        if (MemLen > 0)
            delete[] pMem;

    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return (*this);
}
bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return false;
    bool flag = true;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) {
            flag = false;
            break;
        }
    return flag;
}
bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !((*this) == bf);
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;

    TBitField res(len);
    for (int i = 0; i < res.MemLen; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];
    return res;
}
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;

    TBitField res(len);
    for (int i = 0; i < res.MemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}
TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (!GetBit(i)) res.SetBit(i);
    return res;
}

// ввод/вывод
istream& operator>>(istream& in, TBitField& bf) // ввод
{
    string ans;
    bool flag_size = true;
    bool flag_values = true;
    
    in >> ans;
    if (ans.size() > bf.BitLen) {
        flag_size = false;
        throw "error: wrong input size";
    }

    for (int i = 0; i < ans.size(); i++)
        if (ans[i] != '1' && ans[i] != '0') {
            flag_values = false;
            break;
        }
    if (!flag_values) throw "error: wrong input values";

    if (flag_size && flag_values)
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == '0') bf.ClrBit(i);
            if (ans[i] == '1') bf.SetBit(i);
        }

    return in;
}
ostream& operator<<(ostream& out, const TBitField& bf) // вывод
{
    int len = bf.BitLen;
    int bitsInElem = bf.bitsInElem;
    for (int i = 0; i < len; i++) {
        if (bf.GetBit(i))
            out << '1';
        else
            out << '0';
    }
    return out;
}
