#include "gtest/gtest.h"
#include "../modules/config.hpp"
#include <algorithm>


TEST(TestSuite, TestEncrypt_md5) {
    std::string a = "1234567";
    std::string a_md5 = ev::md5(a);

    std::string b = "fdashjgfhjeasgeqfugrehjfgasdkjh";
    std::string b_md5 = ev::md5(b);

    std::string c = "fjkash^&*^(&*%^$^&dfsahj1234675GHJGHJ%^ED^ew7q6r8473xcgfwqe6t34)";
    std::string c_md5 = ev::md5(c);

    std::string aa = "OP{};/lk']p\\[|+;l'IN&^#@%&&(%)}+]";
    std::string aa_md5 = ev::md5(aa);

    std::string ba = "123476518905743561546301754567";
    std::string ba_md5 = ev::md5(ba);

    std::string ca = "```easyVim真是牛逼zsnb···```";
    std::string ca_md5 = ev::md5(ca);

    std::string spec1 = "";
    std::string spec1_md5 = "D41D8CD98F00B204E9800998ECF8427E";
    std::transform(spec1_md5.begin(),spec1_md5.end(),spec1_md5.begin(),::tolower);

    EXPECT_EQ(ev::md5(a), a_md5);
    EXPECT_EQ(ev::md5(b), b_md5);
    EXPECT_EQ(ev::md5(c), c_md5);
    EXPECT_EQ(ev::md5(aa), aa_md5);
    EXPECT_EQ(ev::md5(ba), ba_md5);
    EXPECT_EQ(ev::md5(ca), ca_md5);

    EXPECT_EQ(ev::md5(spec1), spec1_md5);
}


TEST(TestSuite, TestEncrypt_aes) {
    std::vector<std::string> passage = {"12345671569732486354785107127", 
                                        "gftyryujgkhjhhgvjgmjuyh", 
                                        "1234675", 
                                        "中文", 
                                        "123476518905743561546301754567", 
                                        "1543214143312"};
    std::vector<std::string> enc = std::vector<std::string>();
    std::vector<std::string> dec = std::vector<std::string>();
    std::string key = "uaYBHtznvMU45n4f";
    ev::aes_encrypt(&passage, &enc, key);
    ev::aes_decrypt(&enc, &dec, key);
    for (size_t i = 0; i < passage.size(); i++) {
        EXPECT_NE(passage[i], enc[i]);
        EXPECT_NE("", enc[i]);
        EXPECT_EQ(passage[i], dec[i]);
    }
}

TEST(TestSuite, TestEncrypt_aes2) {
    std::vector<std::string> passage = {"12345671569732486354785107127", 
                                        "gftyryujgkhjhhgvjgmjuyh", 
                                        "1234675", 
                                        "中文", 
                                        "123476518905743561546301754567", 
                                        "1543214143312"};
    std::vector<std::string> enc = std::vector<std::string>();
    std::vector<std::string> dec = std::vector<std::string>();
    std::string key = "uaYBHt";
    ev::aes_encrypt(&passage, &enc, key);
    ev::aes_decrypt(&enc, &dec, key);
    for (size_t i = 0; i < passage.size(); i++) {
        EXPECT_NE(passage[i], enc[i]);
        EXPECT_NE("", enc[i]);
        EXPECT_EQ(passage[i], dec[i]);
    }
}