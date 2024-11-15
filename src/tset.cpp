// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s) return *this;
    else {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (BitField != s.BitField) return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet ans(BitField | s.BitField);
    return ans;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet ans = *this;
    ans.BitField.SetBit(Elem);
    return ans;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet ans = *this;
    ans.BitField.ClrBit(Elem);
    return ans;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet ans(this->BitField & s.BitField);
    return ans;
}

TSet TSet::operator~(void) // дополнение
{
    TSet ans(~(this->BitField));
    return ans;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}

// фикстуры

void TestTSet::SetUp()
{
    s = new TSet(5);        // s - for initialization

    s0 = new TSet(5);
    s1 = new TSet(4);
    s2 = new TSet(6);
    s3 = new TSet(4);
    s4 = new TSet(5);
    s5 = new TSet(5);
    s6 = new TSet(7);
    s7 = new TSet(7);

    s15 = new TSet(18);
    s25 = new TSet(18);
    s35 = new TSet(18);
    s45 = new TSet(18);
    s55 = new TSet(18);
}

void TestTSet::SetUp2(int n)
{
    s = new TSet(n);
}

void TestTSet::TearDown()
{
    delete s;
    delete s0;
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    delete s6;
    delete s7;
    delete s15;
    delete s25;
    delete s35;
    delete s45;
    delete s55;
}
