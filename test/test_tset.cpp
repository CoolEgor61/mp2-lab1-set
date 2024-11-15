#include "tset.h"

#include <gtest.h>

TEST_F(TestTSet, can_get_max_power_set)
{
  EXPECT_EQ(5, s->GetMaxPower());
}

TEST_F(TestTSet, can_insert_non_existing_element)
{
  const int k = 3;
  s->InsElem(k);

  EXPECT_NE(s->IsMember(k), 0);
}

TEST_F(TestTSet, can_insert_existing_element)
{
  const int k = 3;
  s->InsElem(k);
  s->InsElem(k);

  EXPECT_NE(s->IsMember(k), 0);
}

TEST_F(TestTSet, can_delete_non_existing_element)
{
  const int k = 3;
  s->DelElem(k);

  EXPECT_EQ(s->IsMember(k), 0);
}

TEST_F(TestTSet, can_delete_existing_element)
{
  const int k = 3;

  s->InsElem(k);
  EXPECT_GT(s->IsMember(k), 0);

  s->DelElem(k);
  EXPECT_EQ(s->IsMember(k), 0);
}

TEST_F(TestTSet, compare_two_sets_of_non_equal_sizes)
{
  EXPECT_EQ(1, *s1 != *s2);
}

TEST_F(TestTSet, compare_two_equal_sets)
{
  // s = s0 = {1, 3}
  s->InsElem(1);
  s->InsElem(3);
  s0->InsElem(1);
  s0->InsElem(3);

  EXPECT_EQ(*s, *s0);
}

TEST_F(TestTSet, compare_two_non_equal_sets)
{
  // s = {1, 3}
  s->InsElem(1);
  s->InsElem(3);
  // s0 = {1, 2}
  s0->InsElem(1);
  s0->InsElem(2);

  EXPECT_EQ(1, *s != *s0);
}

TEST_F(TestTSet, can_assign_set_of_equal_size)
{
  // s = {1, 3}
  s->InsElem(1);
  s->InsElem(3);
  *s0 = *s;

  EXPECT_EQ(*s, *s0);
}

TEST_F(TestTSet, can_assign_set_of_greater_size)
{
  // s1 = {1, 3}
  s1->InsElem(1);
  s1->InsElem(3);
  *s2 = *s1;

  EXPECT_EQ(*s2, *s1);
}

TEST_F(TestTSet, can_assign_set_of_less_size)
{
  // s2 = {1, 3}
  s2->InsElem(1);
  s2->InsElem(3);
  *s1 = *s2;

  EXPECT_EQ(*s2, *s1);
}

TEST_F(TestTSet, can_insert_non_existing_element_using_plus_operator)
{
  const int k = 3;
  s1->InsElem(0);
  s1->InsElem(2);
  *s3 = *s1 + k;

  EXPECT_NE(0, s3->IsMember(k));
}

TEST_F(TestTSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  const int k = 6;
  s1->InsElem(0);
  s1->InsElem(2);

  ASSERT_ANY_THROW(*s3 = *s1 + k);
}

TEST_F(TestTSet, can_insert_existing_element_using_plus_operator)
{
  const int k = 3;
  s1->InsElem(0);
  s1->InsElem(k);
  *s3 = *s1 + k;

  EXPECT_NE(0, s1->IsMember(k));
}

TEST_F(TestTSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  // s = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // s0 = {0, 1, 2}
  s0->InsElem(0);
  s0->InsElem(1);
  s0->InsElem(2);
  *s4 = *s + *s0;

  EXPECT_EQ(5, s4->GetMaxPower());
}

TEST_F(TestTSet, can_combine_two_sets_of_equal_size)
{
  // s = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // s0 = {0, 1, 2}
  s0->InsElem(0);
  s0->InsElem(1);
  s0->InsElem(2);
  *s4 = *s + *s0;
  // s5 = {0, 1, 2, 4}
  s5->InsElem(0);
  s5->InsElem(1);
  s5->InsElem(2);
  s5->InsElem(4);

  EXPECT_EQ(*s5, *s4);
}

TEST_F(TestTSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  // s = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // set2 = {0, 1, 2}
  s6->InsElem(0);
  s6->InsElem(1);
  s6->InsElem(2);
  *s0 = *s + *s6;

  EXPECT_EQ(7, s0->GetMaxPower());
}

TEST_F(TestTSet, can_combine_two_sets_of_non_equal_size)
{
  // s = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // set2 = {0, 1, 2, 6}
  s6->InsElem(0);
  s6->InsElem(1);
  s6->InsElem(2);
  s6->InsElem(6);
  *s0 = *s + *s6;
  // s7 = {0, 1, 2, 4, 6}
  s7->InsElem(0);
  s7->InsElem(1);
  s7->InsElem(2);
  s7->InsElem(4);
  s7->InsElem(6);

  EXPECT_EQ(*s7, *s0);
}

TEST_F(TestTSet, can_intersect_two_sets_of_equal_size)
{
  // s = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // s0 = {0, 1, 2}
  s0->InsElem(0);
  s0->InsElem(1);
  s0->InsElem(2);
  *s4 = (*s) * (*s0);
  // expSet = {1, 2}
  s5->InsElem(1);
  s5->InsElem(2);

  EXPECT_EQ(*s4, *s5);
}

TEST_F(TestTSet, can_intersect_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  s->InsElem(1);
  s->InsElem(2);
  s->InsElem(4);
  // set2 = {0, 1, 2, 4, 6}
  s6->InsElem(0);
  s6->InsElem(1);
  s6->InsElem(2);
  s6->InsElem(4);
  s6->InsElem(6);
  *s0 = (*s) * (*s6);
  // s7 = {1, 2, 4}
  s7->InsElem(1);
  s7->InsElem(2);
  s7->InsElem(4);

  EXPECT_EQ(*s7, *s0);
}

TEST_F(TestTSet, check_negation_operator)
{
  // s = {1, 3}
  s->InsElem(1);
  s->InsElem(3);
  *s0 = ~(*s);
  // s4 = {0, 2}
  s4->InsElem(0);
  s4->InsElem(2);
  s4->InsElem(4);

  EXPECT_EQ(*s0, *s4);
}

TEST_F(TestTSet, can_combine_three_sets_of_equal_size)
{
	// set1 = {1, 2, 4}
	s15->InsElem(1);
	s15->InsElem(2);
	s15->InsElem(4);
	// set2 = {0, 1, 2}
	s25->InsElem(0);
	s25->InsElem(1);
	s25->InsElem(2);
	//set3 = {4, 8, 16}
	s35->InsElem(4);
	s35->InsElem(8);
	s35->InsElem(16);
	*s45 = (*s15) + (*s25) + (*s35);
	// expSet = {0, 1, 2, 4, 8, 16}
	s55->InsElem(0);
	s55->InsElem(1);
	s55->InsElem(2);
	s55->InsElem(4);
	s55->InsElem(8);
	s55->InsElem(16);

	EXPECT_EQ(*s55, *s45);
}