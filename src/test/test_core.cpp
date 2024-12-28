#include <gtest/gtest.h>  
#include "../modules/core/core.hpp"
#include "../modules/core/loadsave.cpp"   

namespace ev {  

class EVFileTest : public ::testing::Test {  
protected:  
    EVFile file;  

    EVFileTest() : file("test.txt") {   
        file.fileContent.clear();  
    }  

    void SetUp() override {  
        file.insertChar(0, 0, 'H');  
        file.insertChar(0, 1, 'e');  
        file.insertChar(0, 2, 'l');  
        file.insertChar(0, 3, 'l');  
        file.insertChar(0, 4, 'o');  
        file.insertChar(1, 0, 'W');  
        file.insertChar(1, 1, 'o');  
        file.insertChar(1, 2, 'r');  
        file.insertChar(1, 3, 'l');  
        file.insertChar(1, 4, 'd');  
    }  

    void TearDown() override {  
        remove("test.txt"); 
    }  
};  

TEST_F(EVFileTest, InsertChar) {  
    EXPECT_EQ(file.insertChar(0, 4, '!'), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent[0], "Hello!");  
}  

TEST_F(EVFileTest, CoverChar) {  
    EXPECT_EQ(file.coverChar(0, 0, 'h'), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent[0], "hello");  
}  

TEST_F(EVFileTest, DeleteCharFront) {  
    EXPECT_EQ(file.deleteChar(0, 4, true), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent[0], "Hell"); 
}  

TEST_F(EVFileTest, DeleteCharBack) {  
    EXPECT_EQ(file.deleteChar(0, 0, false), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent[0], "ell"); 
}

TEST_F(EVFileTest, DeleteLine) {  
    EXPECT_EQ(file.deleteLine(0, 0, 1, 0), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent.size(), 0); 
}

TEST_F(EVFileTest, CopyLine) {  
    EXPECT_EQ(file.copyLine(0, 0, 1, 0), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.copiedFile.size(), 2); 
    EXPECT_EQ(file.copiedFile[0], "Hello");  
}

TEST_F(EVFileTest, PasteLine) {  
    file.copyLine(0, 0, 1, 0); 
    EXPECT_EQ(file.pasteLine(1, 0), EVFile::EVFileStatus::EVFILE_OK);  
    EXPECT_EQ(file.fileContent.size(), 4); 
    EXPECT_EQ(file.fileContent[2], "Hello"); 
}

TEST_F(EVFileTest, InsertCharOutOfBounds) {  
    EXPECT_EQ(file.insertChar(2, 0, 'A'), EVFile::EVFileStatus::EVFILE_OUT_OF_BOUND); 
    EXPECT_EQ(file.insertChar(0, 10, 'A'), EVFile::EVFileStatus::EVFILE_OUT_OF_BOUND); 
}  

} // namespace ev  

