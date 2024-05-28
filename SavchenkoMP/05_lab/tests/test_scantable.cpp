#include <gtest.h>

#include "scantable.h"
#include <iostream>

using namespace std;

/*
TEST(ScanTable, TEST_NAME) {

}
*/


/// ���� ������������ �� ���������
TEST(ScanTable, DefaultConstructor) {
	ScanTable<int, std::string> table;
	EXPECT_EQ(table.get_size(), 0);
	EXPECT_EQ(table.get_max_size(), DEFAULT_SIZE);
	EXPECT_TRUE(table.empty());
	EXPECT_FALSE(table.full());
}

// ���� ������������ � ����������
TEST(ScanTable, ParameterizedConstructor) {
	int max_size = 20;
	ScanTable<int, std::string> table(max_size);
	EXPECT_EQ(table.get_size(), 0);
	EXPECT_EQ(table.get_max_size(), max_size);
	EXPECT_TRUE(table.empty());
	EXPECT_FALSE(table.full());
}

// ���� ������������ �����������
TEST(ScanTable, CopyConstructor) {
	ScanTable<int, std::string> original(10);
	std::string data1 = "data1";
	std::string data2 = "data2";
	original.insert(1, &data1);
	original.insert(2, &data2);

	ScanTable<int, std::string> copy(original);
	EXPECT_EQ(copy.get_size(), 2);
	EXPECT_EQ(*copy.find(1)->data, "data1");
	EXPECT_EQ(*copy.find(2)->data, "data2");
}

// ���� ������ insert
TEST(ScanTable, Insert) {
	ScanTable<int, std::string> table;
	std::string data = "test_data";

	table.insert(1, &data);
	EXPECT_EQ(table.get_size(), 1);
	EXPECT_FALSE(table.empty());
	EXPECT_EQ(*table.find(1)->data, "test_data");
}

// ���� ������ remove
TEST(ScanTable, Remove) {
	ScanTable<int, std::string> table;
	std::string data = "test_data";

	table.insert(1, &data);
	table.remove(1);
	EXPECT_EQ(table.get_size(), 0);
	EXPECT_TRUE(table.empty());
	EXPECT_EQ(table.find(1), nullptr);
}

// ���� ������ find
TEST(ScanTable, Find) {
	ScanTable<int, std::string> table;
	std::string data = "test_data";

	table.insert(1, &data);
	auto record = table.find(1);
	ASSERT_NE(record, nullptr);
	EXPECT_EQ(record->key, 1);
	EXPECT_EQ(*record->data, "test_data");

	EXPECT_EQ(table.find(2), nullptr);
}

// ���� ���������� ��������� []
TEST(ScanTable, BracketOperator) {
	ScanTable<int, std::string> table;
	std::string data = "test_data";

	table.insert(1, &data);
	auto record = table[1];
	ASSERT_NE(record, nullptr);
	EXPECT_EQ(record->key, 1);
	EXPECT_EQ(*record->data, "test_data");

	EXPECT_EQ(table[2], nullptr);
}


//////////////////////////////////////////////////////////


TEST(ScanTable, ParameterizedConstructorTest_IsFull) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(false, st.full());
}

TEST(ScanTable, ParameterizedConstructorTest_IsEmpty) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(true, st.empty());
}

TEST(ScanTable, ParameterizedConstructorTest_IsTabEnded) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(false, st.ended());
}

TEST(ScanTable, ParameterizedConstructorTest_Reset) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(false, st.reset());
}

TEST(ScanTable, ParameterizedConstructorTest_Next) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(false, st.next());
}

TEST(ScanTable, ParameterizedConstructorTest_GetDataCount) {
	int size = 3;
	ScanTable<int, string> st(3);


	EXPECT_EQ(0, st.get_size());
}

TEST(ScanTable, ParameterizedConstructorTest_GetMaxSize) {
	int size = 3;
	ScanTable<int, string> st(3);

	EXPECT_EQ(size, st.get_max_size());
}

// InsertTest
TEST(ScanTable, InsertTest_Empty) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";

	EXPECT_NO_THROW(st.insert(key, &data));
}

TEST(ScanTable, InsertTest_NotEmpty) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key1 = 1;
	int key2 = 2;
	string data1 = "a";
	string data2 = "b";
	st.insert(key1, &data1);

	EXPECT_NO_THROW(st.insert(key2, &data2));
}

TEST(ScanTable, InsertTest_Full) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key1 = 1;
	int key2 = 2;
	int key3 = 3;
	int key4 = 4;
	string data1 = "a";
	string data2 = "b";
	string data3 = "c";
	string data4 = "d";
	st.insert(key1, &data1);
	st.insert(key2, &data2);
	st.insert(key3, &data3);

	EXPECT_ANY_THROW(st.insert(key4, &data4));
}

// FindTest
TEST(ScanTable, FindTest) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key1 = 1;
	int key2 = 2;
	string data1 = "a";
	string data2 = "b";
	st.insert(key1, &data1);
	st.insert(key2, &data2);

	EXPECT_NO_THROW(st.find(1));
}

TEST(ScanTable, FindTest_Key) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";
	st.insert(key, &data);

	TabRecord<int, string>* find = st.find(1);

	EXPECT_EQ(key, find->key);
}

TEST(ScanTable, FindTest_Data) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";
	st.insert(key, &data);

	TabRecord<int, string>* find = st.find(1);

	EXPECT_EQ(data, *find->data);
}

TEST(ScanTable, FindTest_DataPointer) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";
	st.insert(key, &data);

	TabRecord<int, string>* find = st.find(1);

	EXPECT_NE(&data, find->data);
}

TEST(ScanTable, FindTest_NotFound) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";
	st.insert(key, &data);

	EXPECT_NO_THROW(st.find(2));
}

TEST(ScanTable, FindTest_NotFound_Pointer) {
	int size = 3;
	ScanTable<int, string> st(3);

	int key = 1;
	string data = "a";
	st.insert(key, &data);

	TabRecord<int, string>* find = st.find(3);

	EXPECT_EQ(nullptr, find);
}


///////////////////////////////////////////////////////


TEST(ScanTable, copy_constructor_test)
{
	ScanTable<int, string> st(3);
	st.insert(1, &string("abc"));

	ScanTable<int, string> copiedSt(st);

	EXPECT_EQ(st.find(1)->key, copiedSt.find(1)->key);
}
// insert Test
TEST(ScanTable, insert_test_empty)
{
	ScanTable<int, string> st(3);

	string data = "Data1";

	EXPECT_NO_THROW(st.insert(5, &data));
}

TEST(ScanTable, insert_test_not_empty)
{
	ScanTable<int, string> st(3);

	string data1 = "Data1";
	string data2 = "Data2";
	st.insert(5, &data1);

	EXPECT_NO_THROW(st.insert(10, &data2));
}

TEST(ScanTable, insert_test_full)
{
	ScanTable<int, string> st(3);

	string data1 = "Data1";
	string data2 = "Data2";
	string data3 = "Data3";
	string data4 = "Data4";
	st.insert(2, &data1);
	st.insert(3, &data2);
	st.insert(5, &data3);

	EXPECT_ANY_THROW(st.insert(10, &data4));
}
// remove Test
TEST(ScanTable, remove_test)
{
	ScanTable<int, string> st(3);

	string data1 = "Data1";
	string  data2 = "Data2";
	st.insert(5, &data1);
	st.insert(10, &data2);

	st.remove(5);

	EXPECT_EQ(st.get_size(), 1);
}
TEST(ScanTable, remove_test_empty)
{
	ScanTable<int, string> st(5);

	ASSERT_ANY_THROW(st.remove(1));
}
TEST(ScanTable, remove_non_existent_test)
{
	ScanTable<int, string> table(5);
	string data1 = "Data1";
	string data2 = "Data2";
	table.insert(5, &data1);
	table.insert(10, &data2);
	ASSERT_ANY_THROW(table.remove(3));
}
// find Test
TEST(ScanTable, find_test)
{

	ScanTable<int, string> st(5);

	string data1 = "Data1";
	string data2 = "Data2";
	st.insert(5, &data1);
	st.insert(10, &data2);

	EXPECT_NO_THROW(st.find(1));
}

TEST(ScanTable, find_test_key)
{
	ScanTable<int, string> st(5);

	string data = "Data1";
	st.insert(5, &data);

	TabRecord<int, string>* find = st.find(5);

	EXPECT_EQ(find->key, 5);
}

TEST(ScanTable, find_test_data)
{
	ScanTable<int, string> st(5);

	string data = "Data1";
	st.insert(5, &data);

	TabRecord<int, string>* find = st.find(5);

	EXPECT_EQ(data, *find->data);
}

TEST(ScanTable, test_not_find)
{
	ScanTable<int, string> st(3);

	string data = "Data1";
	st.insert(5, &data);

	EXPECT_EQ(st.find(2), nullptr);
}
// get_curr Test
TEST(ScanTable, get_key_test)
{
	ScanTable<int, string> st(3);

	string data = "Data1";
	st.insert(5, &data);
	st.reset();
	
	TabRecord<int, string>* tab = st.get_curr();

	EXPECT_EQ(tab->key, 5);
	EXPECT_EQ(*tab->data, data);
}
//Is Full
TEST(ScanTable, is_full_test_false)
{
	ScanTable<int, string> st(3);

	ASSERT_FALSE(st.full());
}

TEST(ScanTable, is_full_test_false_with_elements)
{
	ScanTable<int, string> st(3);
	string data1 = "Data1";
	st.insert(5, &data1);
	ASSERT_FALSE(st.full());
}

TEST(ScanTable, is_full_test_true)
{
	ScanTable<int, string> st(1);

	string data = "Data1";
	st.insert(5, &data);
	ASSERT_TRUE(st.full());
}
//Is Empty
TEST(ScanTable, is_empty_test_false)
{
	ScanTable<int, string> st(3);

	string data = "Data1";
	st.insert(5, &data);
	ASSERT_FALSE(st.empty());
}

TEST(ScanTable, is_empty_test_true)
{
	ScanTable<int, string> st(3);

	ASSERT_TRUE(st.empty());
}
//Count
TEST(ScanTable, get_count_test)
{
	ScanTable<int, string> st(3);

	string data = "Data1";
	st.insert(5, &data);
	EXPECT_EQ(st.get_size(), 1);
}
//Is tab Ended
TEST(ScanTable, is_tab_ended_test)
{
	ScanTable<int, string> st(3);

	ASSERT_FALSE(st.ended());
}
TEST(ScanTable, is_tab_ended_true_test)
{
	ScanTable<int, string> st(1);
	string data = "Data1";
	st.insert(5, &data);
	st.reset();
	st.next();

	ASSERT_TRUE(st.ended());
}
// reset
TEST(ScanTable, reset_test)
{
	ScanTable<int, string> st(3);

	ASSERT_FALSE(st.reset());
}
//next
TEST(ScanTable, next_test)
{
	ScanTable<int, string> st(3);

	ASSERT_FALSE(st.next());
}
TEST(ScanTable, next_test_true)
{
	ScanTable<int, string> st(1);
	string data = "Data1";
	st.insert(5, &data);
	st.reset();
	st.next();
	ASSERT_TRUE(st.next());
}
