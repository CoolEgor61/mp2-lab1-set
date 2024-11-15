// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

static const long long sizet = sizeof(TELEM); // Параметризация размера типа данных

TBitField::TBitField(int len)
{
    if (len > 0) {
        MemLen = ceil((double)len / ((double)sizet * 8.0));
        BitLen = len;
        pMem = new TELEM[MemLen]{ 0 };
        if (pMem == 0) throw overflow_error("Out of memory");
    }
    else throw length_error("Length must be positive");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen=bf.BitLen;
  MemLen=bf.MemLen;
  pMem=new TELEM[MemLen];
  if (pMem == 0) throw overflow_error("Out of memory"); else copy(bf.pMem,bf.pMem+bf.MemLen,pMem);

}

TBitField::~TBitField()
{
  delete[] pMem;
  pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/(sizet * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return ((TELEM)1) << (n % (sizet*8));
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
        if (MemLen == bf.MemLen) {
            copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
        }
        else {
            delete[] pMem;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
            if (pMem == 0) throw overflow_error("Out of memory"); else copy(bf.pMem, bf.pMem + bf.MemLen, pMem);
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
    return !(*this==bf);
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
    ans.pMem[MemLen-1] &= ~((~((TELEM)0)) << end);
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

// фикстуры

void TestTBitField::SetUp()
{
    bf = new TBitField(100);        // bf - for initialization

    bf1 = new TBitField(2);         // bf1 - bf3 - for assign operator
    bf2 = new TBitField(2);
    bf3 = new TBitField(5);

    bfa1 = new TBitField(4);        // bfa1 - bfa4 and expbf, expbf2 - for logical operators
    bfa2 = new TBitField(4);
    bfa3 = new TBitField(5);
    bfa4 = new TBitField(4);
    expbf = new TBitField(4);
    expbf2 = new TBitField(5);

    bfb1 = new TBitField(38);       // bfb1, bfb2, expbfb - for can_invert_large_bitfield
    bfb2 = new TBitField(38);
    expbfb = new TBitField(38);

    bfc1 = new TBitField(4);         // bfc1 - bfc4 - invert_plus_and_operator_on_different_size_bitfield
    bfc2 = new TBitField(4);
    bfc3 = new TBitField(8);         
    bfc4 = new TBitField(8);

}

void TestTBitField::SetUp2(int n)
{
    bf = new TBitField(n);
}

void TestTBitField::TearDown()
{
    delete bf;
    delete bf1;
    delete bf2;
    delete bf3;
    delete bfa1;
    delete bfa2;
    delete bfa3;
    delete expbf;
    delete expbf2;
    delete bfb1;
    delete bfb2;
    delete expbfb;
}
