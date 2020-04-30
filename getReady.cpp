#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//���¶���to_string
namespace std
{
	template<typename T>
	  typename enable_if<is_convertible<T, _Longlong>::value, string>::type     to_string(T rhs)
	{
		return to_string(static_cast<_Longlong>(rhs));
	}
}  

int main()
{
   char ad[128]={0};
   int  filename = 0,filenum=0;
   Mat img = imread("D:\\coding_for_c++\\opencv2.4.9_demo\\x64\\Debug\\digits.png");

       string outpath = "D:\\coding_for_c++\\opencv2.4.9_demo\\x64\\Debug\\data\\";
       int b = 20;
       int m = img.cols /b;    //m*n���и����ͼ��ĸ���
       int n = img.rows /b;    
       Vector<Mat> ceil_img;  //������ceil_img�洢��ͼ��


       Vector<int> name;     //������name�洢��ͼ������֣���0��m*n-1
       for (int t = 0; t < m*n; t++){
               name.push_back(t);
               }

       Mat image_cut, roi_img, tim_img;
       //�и�ͼƬ
       for (int j = 0; j <n; j++)
       {
               for (int i = 0; i < m; i++)
               {
                       //Rect��������
                       Rect rect(i * 20, j * 20, 20, 20);
                       image_cut = Mat(img, rect);
                       roi_img = image_cut.clone();
                       ceil_img.push_back(roi_img);
               }
       }

               //�����ļ�
       for (int t=0; t < m*n;t++){
           imwrite(outpath +to_string(name[t])+".png", ceil_img[t]);
       }


       return 0;
}