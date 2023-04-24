#include <gtest/gtest.h>
#include "../src/Fixed.hpp"


using namespace sensor_data;


static float delta(float f1, float f2) {
    return f1 < f2 ? f2 - f1 : f1 - f2;
}


TEST(FixedTest, set) {
    Fixed<8> i1 = 8.0f;
    EXPECT_LE(delta((float)i1, 8.0f), 0.01);

    i1 = 8.5f;
    EXPECT_LE(delta((float)i1, 8.5f), 0.01);

    Fixed<3> i2 = 8.0f;
    EXPECT_LE(delta((float)i2, 8.0f), 0.01);

    i2 = 8.5f;
    EXPECT_LE(delta((float)i2, 8.5f), 0.01);

    Fixed<11> i3 = 8.0f;
    EXPECT_LE(delta((float)i3, 8.0f), 0.01);

    i3 = 8.5f;
    EXPECT_LE(delta((float)i3, 8.5f), 0.01);
}


TEST(FixedTest, serialize1) {
    Fixed<11> i11((uint16_t)701);
    SerializedFixed sf = i11.serialize();
    Fixed<11> i12(sf);
    EXPECT_EQ(i11, i12);

    Fixed<3> i21((uint16_t)701);
    sf = i21.serialize();
    Fixed<3> i22(sf);
    EXPECT_EQ(i21, i22);

    Fixed<0> i31((uint16_t)701);
    sf = i31.serialize();
    Fixed<0> i32(sf);
    EXPECT_EQ(i31, i32);
}


TEST(FixedTest, serialize2) {
    size_t s;
    char buffer[2];

    Fixed<11> i11((uint16_t)701);
    s = i11.serialize(buffer, sizeof(buffer));
    EXPECT_EQ(s, 2);
    Fixed<11> i12((uint16_t)0);
    s = i12.deserialize(buffer, sizeof(buffer));
    EXPECT_EQ(s, 2);
    EXPECT_EQ(i11, i12);

    Fixed<3> i21((uint16_t)701);
    s = i21.serialize(buffer, sizeof(buffer));
    EXPECT_EQ(s, 2);
    Fixed<3> i22((uint16_t)0);
    s = i22.deserialize(buffer, sizeof(buffer));
    EXPECT_EQ(s, 2);
    EXPECT_EQ(i21, i22);
}


TEST(FixedTest, round) {
    Fixed<8> f(2.3f);
    float r = f.round(1);
    float d = delta(r, 2.3);
    EXPECT_LE(d, 0.0001f);
}
