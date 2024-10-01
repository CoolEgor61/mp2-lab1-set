// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>
#include <exception>

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

static const int sizet = sizeof(TELEM); // Параметризация размера типа данных

TBitField::TBitField(int len)
{
    if (len > 0) {
        MemLen = ceil((double)len / ((double)sizet * 8.0));
        BitLen = len;
        pMem = new TELEM[MemLen]{ 0 };
    }
    else throw length_error("Length must be positive");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen=bf.BitLen;
  MemLen=bf.MemLen;
  pMem=new TELEM[MemLen];
  copy(bf.pMem,bf.pMem+bf.MemLen,pMem);

}

TBitField::~TBitField()
{
  delete[] pMem;
  pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/(sizet * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % (sizet*8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > -1 && n<BitLen) {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else throw range_error("Out of range");
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > -1 && n < BitLen) {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
    else throw range_error("Out of range");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
        if (n > -1 && n < BitLen) return (pMem[GetMemIndex(n)] & GetMemMask(n));
        else throw range_error("Out of range");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;
    else {
        BitLen = bf.BitLen;
        if (MemLen = bf.MemLen) {
            copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
        }
        else {
            ~(*this);
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
            copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) return 0;
        }
        return 1;
    }
    else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen){
        return !(*this==bf);
    }
    else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField ans(max(BitLen, bf.BitLen));
    int end = min(MemLen, bf.MemLen);
    for (int i = 0; i < end; i++) ans.pMem[i] = pMem[i] | bf.pMem[i];
    for (int i = end; i < ans.MemLen; i++) if (BitLen > bf.BitLen) ans.pMem[i] = pMem[i]; else ans.pMem[i] = bf.pMem[i];
    return ans;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField ans(max(BitLen,bf.BitLen));
    int end = min(MemLen, bf.MemLen);
    for (int i = 0; i < end; i++) ans.pMem[i] = pMem[i] & bf.pMem[i];
    return ans;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField ans(BitLen);
    for (int i = 0; i < MemLen; i++) ans.pMem[i]=~pMem[i];
    int end = BitLen - MemLen * sizet * 8;
    ans.pMem[MemLen - 1] &= ~((~((TELEM)0)) << end);
    return ans;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string input;
    istr >> input;
    if (input.size() > bf.BitLen) throw length_error("Wrong input length"); else for (int i = 0; i < input.size(); i++) if (input[i] == '1') bf.SetBit(i); else if (input[i] == 0); else throw logic_error("Wrong input");
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i) != 0) ostr << 1; else ostr << 0;
    }
    return ostr;
}
