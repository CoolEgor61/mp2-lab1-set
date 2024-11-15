#include "tbitfield.h"

#include <gtest.h>

TEST_F(TestTBitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(this->SetUp2(100));
}

TEST_F(TestTBitField, can_get_length)
{
  EXPECT_EQ(100, bf->GetLength());
}

TEST_F(TestTBitField, new_bitfield_is_set_to_zero)
{
  int sum = 0;
  for (int i = 0; i < bf->GetLength(); i++)
  {
    sum += this->bf->GetBit(i);
  }

  EXPECT_EQ(0, sum);
}

TEST_F(TestTBitField, can_set_bit)
{

  EXPECT_EQ(0, bf->GetBit(3));

  this->bf->SetBit(3);
  EXPECT_NE(0, bf->GetBit(3));
}

TEST_F(TestTBitField, can_clear_bit)
{

  int bitIdx = 3;

  this->bf->SetBit(bitIdx);
  EXPECT_NE(0, bf->GetBit(bitIdx));

  this->bf->ClrBit(bitIdx);
  EXPECT_EQ(0, bf->GetBit(bitIdx));
}

TEST_F(TestTBitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(this->SetUp2(-3));
}

TEST_F(TestTBitField, throws_when_set_bit_with_negative_index)
{
  ASSERT_ANY_THROW(bf->SetBit(-3));
}

TEST_F(TestTBitField, throws_when_set_bit_with_too_large_index)
{
  ASSERT_ANY_THROW(bf->SetBit(110));
}

TEST_F(TestTBitField, throws_when_get_bit_with_negative_index)
{
  ASSERT_ANY_THROW(bf->GetBit(-3));
}

TEST_F(TestTBitField, throws_when_get_bit_with_too_large_index)
{
  ASSERT_ANY_THROW(bf->GetBit(110));
}

TEST_F(TestTBitField, throws_when_clear_bit_with_negative_index)
{
  ASSERT_ANY_THROW(bf->ClrBit(-3));
}

TEST_F(TestTBitField, throws_when_clear_bit_with_too_large_index)
{
  ASSERT_ANY_THROW(bf->ClrBit(110));
}

TEST_F(TestTBitField, can_assign_bitfields_of_equal_size)
{
  for (int i = 0; i < bf1->GetLength(); i++)
  {
      bf1->SetBit(i);
  }
  *(bf2) = *(bf1);

  EXPECT_NE(0, bf2->GetBit(0));
  EXPECT_NE(0, bf2->GetBit(1));
}

TEST_F(TestTBitField, assign_operator_changes_bitfield_size)
{
   // bf1 size = 2, bf3 size = 5
  for (int i = 0; i < bf1->GetLength(); i++)
  {
      bf1->SetBit(i);
  }
  *(bf3) = *(bf1);

  EXPECT_EQ(bf1->GetLength(), bf3->GetLength());
}

TEST_F(TestTBitField, can_assign_bitfields_of_non_equal_size)
{
    // bf1 size = 2, bf3 size = 5
  for (int i = 0; i < bf1->GetLength(); i++)
  {
      bf1->SetBit(i);
  }
  *(bf3) = *(bf1);

  EXPECT_NE(0, bf3->GetBit(0));
  EXPECT_NE(0, bf3->GetBit(1));
}

TEST_F(TestTBitField, compare_equal_bitfields_of_equal_size)
{
  for (int i = 0; i < bf1->GetLength(); i++)
  {
      bf1->SetBit(i);
  }
  *(bf2) = *(bf1);

  EXPECT_EQ(*(bf2), *(bf1));
}

TEST_F(TestTBitField, or_operator_applied_to_bitfields_of_equal_size)
{
  // bfa1 = 0011
  bfa1->SetBit(2);
  bfa1->SetBit(3);
  // bfa2 = 0101
  bfa2->SetBit(1);
  bfa2->SetBit(3);

  // expBf = 0111
  expbf->SetBit(1);
  expbf->SetBit(2);
  expbf->SetBit(3);

  EXPECT_EQ(*(expbf), (*bfa1) | *(bfa2));
}

TEST_F(TestTBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  // bfa1 = 0011
  bfa1->SetBit(2);
  bfa1->SetBit(3);
  // bfa3 = 01010
  bfa3->SetBit(1);
  bfa3->SetBit(3);

  // expbf2 = 01110
  expbf2->SetBit(1);
  expbf2->SetBit(2);
  expbf2->SetBit(3);

  EXPECT_EQ(*(expbf2), *(bfa1) | *(bfa3));
}

TEST_F(TestTBitField, and_operator_applied_to_bitfields_of_equal_size)
{
  // bfa1 = 0011
  bfa1->SetBit(2);
  bfa1->SetBit(3);
  // bfa2 = 0101
  bfa2->SetBit(1);
  bfa2->SetBit(3);

  // expBf = 0001
  expbf->SetBit(3);

  EXPECT_EQ(*(expbf), *(bfa1) & *(bfa2));
}

TEST_F(TestTBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  // bfa1 = 0011
  bfa1->SetBit(2);
  bfa1->SetBit(3);
  // bfa3 = 01010
  bfa3->SetBit(1);
  bfa3->SetBit(3);

  // expbf2 = 00010
  expbf2->SetBit(3);

  EXPECT_EQ(*(expbf2), *(bfa1) & *(bfa3));
}

TEST_F(TestTBitField, can_invert_bitfield)
{
  // bfa1 = 0100
  bfa1->SetBit(1);
  *(bfa2) = ~(*(bfa1));

  // expbf = 1011
  expbf->SetBit(0);
  expbf->SetBit(2);
  expbf->SetBit(3);

  EXPECT_EQ(*(expbf), *(bfa2));
}

TEST_F(TestTBitField, can_invert_large_bitfield)
{
  bfb1->SetBit(35);
  *(bfb2) = ~(*(bfb1));

  for(int i = 0; i < bfb1->GetLength(); i++)
    expbfb->SetBit(i);
  expbfb->ClrBit(35);

  EXPECT_EQ(*(expbfb), *(bfb2));
}

TEST_F(TestTBitField, invert_plus_and_operator_on_different_size_bitfield)
{
  // bfc1 = 0001
  bfc1->SetBit(0);
  *(bfc2)= ~(*bfc1);
  // bfc2 = 1110

  // bfc3 = 00011000
  bfc3->SetBit(3);
  bfc3->SetBit(4);

  // bfc4 = 00001000
  bfc4->SetBit(3);

  EXPECT_EQ(*(bfc3) & *(bfc2), *(bfc4));
}

TEST_F(TestTBitField, can_invert_many_random_bits_bitfield)
{

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bfb1->SetBit(bits[i]);

  *(bfb2) = ~(*(bfb1));

  for(int i = 0; i < expbfb->GetLength(); i++)
    expbfb->SetBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
      expbfb->ClrBit(bits[i]);

  EXPECT_EQ(*(expbfb), *(bfb2));
}

TEST_F(TestTBitField, bitfields_with_different_bits_are_not_equal)
{
  bfa1->SetBit(1);
  bfa1->SetBit(3);

  bfa2->SetBit(1);
  bfa2->SetBit(2);

  EXPECT_NE(*(bfa1), *(bfa2));
}

TEST_F(TestTBitField, bitfield_stay_clear_after_two_clears)
{
    int bitIdx = 3;

    bf->SetBit(bitIdx);

    bf->ClrBit(bitIdx);

    bf->ClrBit(bitIdx);
    EXPECT_EQ(0, bf->GetBit(bitIdx));
}

TEST_F(TestTBitField, or_operator_applied_to_three_bitfields)
{
    // bfa1 = 0011
    bfa1->SetBit(2);
    bfa1->SetBit(3);
    // bfa2 = 1100
    bfa2->SetBit(0);
    bfa2->SetBit(1);
    // bfa4 = 0000

    // expbf = 1111
    expbf->SetBit(0);
    expbf->SetBit(1);
    expbf->SetBit(2);
    expbf->SetBit(3);

    EXPECT_EQ(*(expbf), *(bfa1) | *(bfa2) | *(bfa4));
}

TEST_F(TestTBitField, and_operator_applied_to_three_bitfields)
{
    // bfa1 = 0011
    bfa1->SetBit(2);
    bfa1->SetBit(3);
    // bfa2 = 1100
    bfa2->SetBit(0);
    bfa2->SetBit(1);
    // bfa4 = 0000

    // expbf = 0000

    EXPECT_EQ(*(expbf), *(bfa1) & *(bfa2) & *(bfa4));
}