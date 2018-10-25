#include <gtest/gtest.h>
#include <algorithm>
#include "network.h"
#include "random.h"
#include <iostream>

RandomNumbers RNG(101);
Network net;

TEST(networkTest, initialize) {
    net.resize(100);
    EXPECT_EQ(net.size(), 100);
    std::vector<double> vals = net.sorted_values();
    EXPECT_TRUE(std::is_sorted(vals.begin(), vals.end(), std::greater<double>()));
    double var = 0;
    for (auto I : vals) var += I*I;
    EXPECT_GT(var, 10);
}

TEST(networkTest, connect) {
    bool trylink = net.add_link(0,0);
   // std::cout << "1" << std::endl;
    EXPECT_FALSE(trylink);
    trylink = net.add_link(0,100);
   // std::cout << "2" << std::endl;
    EXPECT_FALSE(trylink);
    trylink = net.add_link(9,10);
   // std::cout << "3" << std::endl;
    EXPECT_TRUE(trylink);
  //  std::cout << "4" << std::endl;
    EXPECT_EQ(net.degree(9)+net.degree(10), 2); 
  //  std::cout << "4" << std::endl;   
    trylink = net.add_link(9,8);
   // std::cout << "4" << std::endl;
    trylink = net.add_link(1,9);
  //  std::cout << "5" << std::endl;
    std::vector<size_t> ngb = net.neighbors(9);
   // std::cout << "6" << std::endl;
    EXPECT_EQ(ngb.size(), 3);
    EXPECT_TRUE(ngb[0]==10 && ngb[1]==8 && ngb[2]==1);
    size_t numlink = net.random_connect(2);
   // std::cout << "7" << std::endl;
    EXPECT_NEAR(numlink, 200, 5);
}

TEST(networkTest, values) {
    std::vector<double> vals{1.0, 10.0, -0.4, .2, -21.8, 11.0};
    //std::cout << "1" << std::endl;
    size_t numv = net.set_values(vals);
    //std::cout << "2" << std::endl;
    EXPECT_EQ(numv, 6);
   // std::cout << "3" << std::endl;
    double checksum = 0;
  //  std::cout << "4" << std::endl;
    for (size_t n=0; n<6; n++) checksum += net.value(n);
   // std::cout << "5" << std::endl;
    EXPECT_NEAR(checksum, 0.0, 0.01);
    //std::cout << "6" << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
