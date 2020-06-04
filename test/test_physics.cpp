#include <gtest/gtest.h>

#include <cmath>

#include "../common/physics/include/vector.h"
#include "../common/physics/include/aabb.h"

TEST(Physics, Vec2_Addition)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const neko::physics::Vec2 b{1.0f, 4.0f};

    //Test operator +
    neko::physics::Vec2 c = a + b;
    ASSERT_EQ(c.x, a.x + b.x);
    ASSERT_EQ(c.y, a.y + b.y);

    //Test operator +=
    const neko::physics::Vec2 d{3.0f, 4.0f};
    neko::physics::Vec2 e = d;
    e += a;
    ASSERT_EQ(e.x, d.x + a.x);
    ASSERT_EQ(e.y, d.y + a.y);
}

TEST(Physics, Vec2_Substraction)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const neko::physics::Vec2 b{1.0f, 4.0f};

    //Test operator -
    neko::physics::Vec2 c = a - b;
    ASSERT_EQ(c.x, a.x - b.x);
    ASSERT_EQ(c.y, a.y - b.y);

    //Test operator -=
    const neko::physics::Vec2 d{3.0f, 4.0f};
    neko::physics::Vec2 e = d;
    e += a;
    ASSERT_EQ(e.x, d.x - a.x);
    ASSERT_EQ(e.y, d.y - a.y);
}

TEST(Physics, Vec2_MultiplicationByScalar)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const float b = 4.0f;

    //Test operator *
    neko::physics::Vec2 c = a * b;
    ASSERT_EQ(c.x, a.x * b);
    ASSERT_EQ(c.y, a.y * b);

    //Test operator *=
    const neko::physics::Vec2 d{3.0f, 4.0f};
    neko::physics::Vec2 e = d;
    e *= b;
    ASSERT_EQ(e.x, d.x * b);
    ASSERT_EQ(e.y, d.y * b);
}

TEST(Physics, Vec2_DivisionByScalar)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const float b = 4.0f;

    //Test operator /
    neko::physics::Vec2 c = a / b;
    ASSERT_EQ(c.x, a.x / b);
    ASSERT_EQ(c.y, a.y / b);

    //Test operator /=
    const neko::physics::Vec2 d{3.0f, 4.0f};
    neko::physics::Vec2 e = d;
    e /= b;
    ASSERT_EQ(e.x, d.x / b);
    ASSERT_EQ(e.y, d.y / b);
}

TEST(Physics, Vec2_Magnitude)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const float b = 4;

    //Test .SqrMagnitude()
    ASSERT_EQ(a.Magnitude(), sqrt((a.x * a.x) + (a.y * a.y)));
}

TEST(Physics, Vec2_SqrMagnitude)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const float b = 4;

    //Test .SqrMagnitude()
    ASSERT_EQ(a.SqrMagnitude(), (a.x * a.x) + (a.y * a.y));
}

TEST(Physics, Vec2_Normalize)
{
    const neko::physics::Vec2 a{0.0f, 3.0f};
    const neko::physics::Vec2 b = a.Normalized();

    //Test .Normalized()
    ASSERT_EQ(b.Magnitude(), 1.0f);

    //Test .Normalize()
    neko::physics::Vec2 c= a;
    c.Normalize();
    ASSERT_EQ(c.Magnitude(), 1.0f);
}

TEST(Physics, Vec2_DotProduct)
{
    const neko::physics::Vec2 a{0.0f, 3.0f};
    const neko::physics::Vec2 b{1.0f, 0.0f};

    //Test .Dot()
    ASSERT_EQ(a.Dot(b), 0.0f);

    //Test static Dot()
    ASSERT_EQ(neko::physics::Vec2::Dot(a, b), 0.0f);


    const neko::physics::Vec2 c{2.0f, 3.0f};
    const neko::physics::Vec2 d{1.0f, 1.0f};

    //Test .Dot()
    ASSERT_EQ(c.Dot(d), c.x * d.x + c.y * d.y);

    //Test static Dot()
    ASSERT_EQ(neko::physics::Vec2::Dot(c, d), c.x * d.x + c.y * d.y);
}

TEST(Physics, Vec2_AngleBetween)
{
    const neko::physics::Vec2 a{0.0f, 3.0f};
    const neko::physics::Vec2 b{1.0f, 0.0f};

    //Test .AngleBetween()
    ASSERT_EQ(neko::physics::Vec2::AngleBetween(a, b), acos(a.Dot(b) / (a.Magnitude() * b.Magnitude())));

    //Test static AngleBetween()
    ASSERT_EQ(neko::physics::Vec2::AngleBetween(a, b), acos(neko::physics::Vec2::Dot(a, b) / (a.Magnitude() * b.Magnitude())));
}

TEST(Physics, Vec2_CrossProduct)
{
    const neko::physics::Vec2 a{2.0f, 3.0f};
    const neko::physics::Vec2 b{1.0f, -3.0f};

//    //Test .Dot()
//    ASSERT_EQ(a.Cross(b).x, 0);
//    ASSERT_EQ(a.Cross(b).y, 0);
//    ASSERT_EQ(a.Cross(b).z, a.x * b.y - a.y * b.x);
//
//    //Test static Dot()
//    ASSERT_EQ(neko::physics::Vec2::Cross(a, b).x, 0);
//    ASSERT_EQ(neko::physics::Vec2::Cross(a, b).y, 0);
//    ASSERT_EQ(neko::physics::Vec2::Cross(a, b).z, a.x * b.y - a.y * b.x);
}

TEST(Physics, Matrix){

}

TEST(Physics, AABB_GetCenter){
    neko::physics::Vec2 bottomLeft{0.0f, 0.0f};
    neko::physics::Vec2 topRight{2.0f, 2.0f};
    neko::physics::AABB aabb{bottomLeft, topRight};

    neko::physics::Vec2 center = aabb.GetCenter();

    ASSERT_EQ(center.x, (topRight.x + bottomLeft.x) / 2.0f);
    ASSERT_EQ(center.y, (topRight.y + bottomLeft.y) / 2.0f);
}

TEST(Physics, AABB_GetExtent){
    neko::physics::Vec2 bottomLeft{0.0f, 0.0f};
    neko::physics::Vec2 topRight{2.0f, 2.0f};
    neko::physics::AABB aabb{bottomLeft, topRight};

    neko::physics::Vec2 extent = aabb.GetExtent();

    ASSERT_EQ(extent.x, (topRight.x - bottomLeft.x) / 2.0f);
    ASSERT_EQ(extent.y, (topRight.y - bottomLeft.y) / 2.0f);
}

TEST(Physics, AABB_Overlap){
    //base aabb
    neko::physics::Vec2 bottomLeft{0.0f, 0.0f};
    neko::physics::Vec2 topRight{2.0f, 2.0f};
    neko::physics::AABB aabb{bottomLeft, topRight};

    //Self overlapping
    ASSERT_TRUE(aabb.Overlap(aabb));

    //non overlapping aabb
    neko::physics::Vec2 bottomLeft1{10.0f, 10.0f};
    neko::physics::Vec2 topRight1{20.0f, 20.0f};
    neko::physics::AABB aabb1{bottomLeft1, topRight1};

    ASSERT_FALSE(aabb.Overlap(aabb1));
    ASSERT_FALSE(aabb1.Overlap(aabb));

    //overlapping aabb
    neko::physics::Vec2 bottomLeft2{1.0f, 1.0f};
    neko::physics::Vec2 topRight2{20.0f, 20.0f};
    neko::physics::AABB aabb2{bottomLeft2, topRight2};

    ASSERT_TRUE(aabb.Overlap(aabb2));
    ASSERT_TRUE(aabb2.Overlap(aabb));

    //Contained aabb
    neko::physics::Vec2 bottomLeft3{-1.0f, -1.0f};
    neko::physics::Vec2 topRight3{3.0f, 3.0f};
    neko::physics::AABB aabb3{bottomLeft3, topRight3};

    ASSERT_TRUE(aabb.Overlap(aabb3));
    ASSERT_TRUE(aabb3.Overlap(aabb));

    //Contained aabb
    neko::physics::Vec2 bottomLeft4{2.0f, 2.0f};
    neko::physics::Vec2 topRight4{3.0f, 3.0f};
    neko::physics::AABB aabb4{bottomLeft4, topRight4};

    ASSERT_TRUE(aabb.Overlap(aabb4));
    ASSERT_TRUE(aabb4.Overlap(aabb));
}
