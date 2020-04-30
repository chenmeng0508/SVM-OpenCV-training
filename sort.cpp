#include <stdio.h>  
#include <time.h>  
#include <opencv2/opencv.hpp>  
#include <opencv/cv.h>  
#include <iostream> 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <io.h>

using namespace std;
using namespace cv;

void getFiles( string path, vector<string>& files );

int main()
{
    int result = 0;
    char * filePath = "D:\\coding_for_c++\\opencv2.4.9_demo\\x64\\Debug\\data\\test_image\\0"; 
    vector<string> files;  
    getFiles(filePath, files );  
    int number = files.size();  

	//输出需要判断的文件的数量
    cout<<number<<endl;

    CvSVM svm;
    svm.clear();

	//载入训练好的图像特征
    string modelpath = "svm.xml";
    FileStorage svm_fs(modelpath,FileStorage::READ);
    if(svm_fs.isOpened())
    {
        svm.load(modelpath.c_str());
    }
    for (int i = 0;i < number;i++)  
    {  
        Mat inMat = imread(files[i].c_str());
        Mat p = inMat.reshape(1, 1);
        p.convertTo(p, CV_32FC1);
        int response = (int)svm.predict(p);
        if (response == 0)
        {
            result++;
        }
    }

	//输出符合训练特征的图片的数量
    cout<<result<<endl;
    getchar();
    return  0;
}
void getFiles( string path, vector<string>& files )  
{  
    long   hFile   =   0;  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
            }  
            else  
            {       files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
} 