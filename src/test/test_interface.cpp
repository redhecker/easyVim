#include "../include.hpp"
#include "gtest/gtest.h"


/*********************************
            Tests for 
    Encryption and Decryption
          Super@redhecker
**********************************/
TEST(TestSuite, test_aes){
    std::vector<std::string> passage = {"easyVim",
                                        "is so good",
                                        "123456",
                                        "中文",
                                        "!@#$%^&*()"};
    std::string password = "e@syVim_Passw0rd";
    std::string fake1    = "e@syVim_Password";
    std::string fake2    = "123456";

    std::vector<std::string> enc = std::vector<std::string>();
    std::vector<std::string> dec = std::vector<std::string>();

    ev::EVencrypt(&passage, &enc, password);

    EXPECT_EQ(ev::EVdecrypt(&enc, &dec, password), true);
    for (size_t i = 0; i < passage.size(); i++) {
        EXPECT_EQ(passage[i], dec[i]);
    }

    // test if the password is wrong
    dec.clear();
    EXPECT_EQ(ev::EVdecrypt(&enc, &dec, fake1), false);
    EXPECT_EQ(ev::EVdecrypt(&enc, &dec, fake2), false);

    enc.clear();
    dec.clear();
    EXPECT_EQ(ev::EVencrypt(&passage, &enc, password, ev::EV_ENCRYPT_TYPE::EV_ENCRYPT_AES_NBEGIN), true);
    EXPECT_EQ(ev::EVdecrypt(&enc, &dec, fake1, ev::EV_DECRYPT_TYPE::EV_DECRYPT_AES_NBEGIN), true);
    for (size_t i = 0; i < passage.size(); i++) {
        EXPECT_NE(passage[i], dec[i]);
    }
}
