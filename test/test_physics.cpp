#include <gtest/gtest.h>

#include "../common/physics/include/vector.h"

TEST(Physics, Vector)
{
    std::cout << "Start testing Vec2\n";

    const neko::physics::Vec2 a{ 2, 3};
    const neko::physics::Vec2 b{ 1, 4};
    neko::physics::Vec2 c ;

    //Test operator +
    std::cout << "  Test operator + => ";
    c = a + b;

    ASSERT_EQ(c.x, a.x + b.x);
    ASSERT_EQ(c.y, a.y + b.y);

    std::cout << "Success\n";

    //Test operator -
    std::cout << "  Test operator - => ";
    c = a - b;
    ASSERT_EQ(c.x, a.x - b.x);
    ASSERT_EQ(c.y, a.y - b.y);
    std::cout << "Success\n";

    //Test operator +=
    std::cout << "  Test operator += => ";
    neko::physics::Vec2 d;
    d += a;
    ASSERT_EQ(d.x, a.x);
    ASSERT_EQ(d.y, a.y);
    std::cout << "Success\n";
}

TEST(Physics, Matrix){

}
