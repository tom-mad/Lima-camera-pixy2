///! 2017.10.05 09:40:33 CST
/// convert uint8_t array/pointer to cv::Mat

#include <opencv2/core.hpp>
#include <iostream>

int main(){        
    uint8_t uarr[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int rows = 2;
    int cols = 2;
    cv::Size sz(cols,rows);

    cv::Mat mat1(sz,CV_8UC3, uarr);
    cv::Mat mat2(rows, cols, CV_8UC3, uarr);
    uint8_t* uarr1;
    if (mat1.isContinuous())
    {
     std::cout<< "mat2: \n"<<mat1 << "\n\nmat2:\n" << mat2 << std::endl;
        uarr1 = mat1.ptr<uint8_t>(0);
     std::cout<< uarr1 << mat2 << std::endl;


    }
    cv::Mat mat3(sz,CV_8UC3, uarr1);
     std::cout<< "mat3: \n"<<mat3 << std::endl;

    for(int i=0;i<8;i++)
        std::cout<<uarr1[i];
    return 0;
}