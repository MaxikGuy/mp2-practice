#include <gtest.h>

#include <iostream>
#include "tabrecord.h"

using namespace std;

/*
TEST(TabRecord, TEST_NAME) {

}
*/

// ���� ������������ �� ���������
TEST(TabRecord, DefaultConstructor) {
	TabRecord<int, std::string> record;
	EXPECT_EQ(record.key, int());
	EXPECT_EQ(record.data, nullptr);
}

// ���� ������������ � �����������
TEST(TabRecord, ParameterizedConstructor) {
	std::string data = "test_data";
	TabRecord<int, std::string> record(1, &data);
	EXPECT_EQ(record.key, 1);
	EXPECT_EQ(*record.data, "test_data");
}

// ���� ������������ �����������
TEST(TabRecord, CopyConstructor) {
	std::string data = "test_data";
	TabRecord<int, std::string> original(1, &data);
	TabRecord<int, std::string> copy(original);
	EXPECT_EQ(copy.key, 1);
	EXPECT_EQ(*copy.data, "test_data");
}

// ���� ��������� ������������
TEST(TabRecord, AssignmentOperator) {
	std::string data1 = "test_data1";
	std::string data2 = "test_data2";
	TabRecord<int, std::string> record1(1, &data1);
	TabRecord<int, std::string> record2(2, &data2);

	record2 = record1;
	EXPECT_EQ(record2.key, 1);
	EXPECT_EQ(*record2.data, "test_data1");
}

// ���� �����������
TEST(TabRecord, Destructor) {
    int key = 5;
    double data = 3.14;
    {
        TabRecord<int, double> record(key, &data);
    }
    // �������� ���������� ������ ������ ��� ������ ��� ����������� �������
    EXPECT_TRUE(true);
}