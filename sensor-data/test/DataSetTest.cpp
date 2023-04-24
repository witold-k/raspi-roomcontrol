#include <gtest/gtest.h>
#include "../src/DataSet.hpp"


using namespace sensor_data;


//static float delta(float f1, float f2) {
//    return f1 < f2 ? f2 - f1 : f1 - f2;
//}


TEST(DataSetTest, serialize) {
    char buffer[50];
    size_t s1, s2;
    DataSet<8> set1(10.0f, 20.0f);
    s1 = set1.serialize(buffer, sizeof(buffer));
    DataSet<8> set2;
    s2 = set2.deserialize(buffer, sizeof(buffer));
    EXPECT_EQ(set1, set2);
    EXPECT_EQ(s1, s2);
}
