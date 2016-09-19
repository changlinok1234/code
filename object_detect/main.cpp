#include <opencv/cv.h>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include  "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;using namespace cv;
using namespace std;
void pathAndLabeltrain(string dataName, vector<string>& dirname,vector<string>& outpath1,Mat& labels, vector<string>& imgName);
void roi(string roidataname,Mat& xmin, Mat& ymin,Mat& xmax,Mat& ymax);
int WriteData(string fileName, Mat& matData);


int main()
{
     string imgTrainDataName="/home/changlin/program/codeblocks/Computer_vision/assignment1/object_detect/set.txt";//生成训练集和测试集,这里没啥用，不用管
    string roidata="/home/changlin/program/codeblocks/Computer_vision/assignment1/object_detect/objectnum.txt";
    string trainobjectresult="/home/changlin/program/codeblocks/Computer_vision/assignment1/object_detect/reresult/train/";//生成训练集和测试集
    string str,str1;
    vector<string> trainImgName;
    vector<string> dir,outpath;//图片所在文件夹和图片名称的字符串矩阵
    Mat labelsTrain(0,1,CV_32FC1);
    Mat trainData;
    Mat outimage;
    Mat x1;
    Mat y1;
    Mat x2;
    Mat y2;
    int row,col;
    string classify1;
    pathAndLabeltrain(imgTrainDataName,dir,outpath,labelsTrain, trainImgName) ; //读取txt文档
    roi(roidata, x1, y1, x2, y2);                                           //目标坐标的提取
    for (int i=0; i != trainImgName.size(); i++) {
        Mat img=imread(trainImgName[i].c_str(),0);//c++中的类string使用C_STR()可以返回该字符的地址
      /*--------------- 提取感兴趣区域-------------------*/
     int x11=x1.at<int>(i);  //Mat格式数据每一行的提取方法
     int y11=y1.at<int>(i);
     int x22=x2.at<int>(i);
     int y22=y2.at<int>(i);

         row=y22-y11;
         col=x22-x11;
         cout<<row<<endl;
         cout<<col<<endl;
        cout<<x22<<endl;
        cout<<y22<<endl;
        cout<<i<<endl;
         Rect r1(x11,y11,col,row);
        outimage = img(r1);

    /*----------------------------对图像进行处理---------------  */


//outimage=img;


  //***************保存处理过的图像*********************/////////////////
       //*********查看文件夹是否已经存在,若不存在,则新建一个*******//
        str = trainobjectresult;  //一级文件夹
         str1 =str+dir[i]; //"二级文件夹";这里的str是最终输出的文件夹的路径
       const  char *str2 = str1.c_str();
        if ((access(str2 ,0)) != -1)
    {
        string str3= str2;
       string str4=str3+outpath[i];
      //  cout<<str3<<endl;
      // cout<<str4<<endl;
        imwrite(str4,outimage);
    }
      else
      {
       mkdir(str2, 0755);
       string str3= str2;
       string str4=str3+outpath[i];
      // cout<<str3<<endl;
       //cout<<str4<<endl;
        imwrite(str4,outimage);
      }
      }


  //   imwrite(trainobjectresult+classify1+trainImgName".jpg",trainImgName);
 //cout<<trainImgName<<endl;

  return 0;
}


void pathAndLabeltrain(string dataName, vector<string>& dirname,vector<string>& outpath1,Mat& labels, vector<string>& imgName)
{
    ifstream dataPath("/home/changlin/program/codeblocks/Computer_vision/assignment1/object_detect/image.txt");
    string buf;
    while( dataPath )//将训练样本文件依次读取进来
    {
        if( getline( dataPath, buf ) )
        {
            istringstream s(buf);
            string imgPath,classify,classifyLabel,dirnamestr,outpathstr;
            s >> imgPath >> classify >> classifyLabel;
            //cout<<imgPath<<endl;

            //*****提取图片所在的文件夹的名字****//
          string::size_type p1 = imgPath.find("/");
          string::size_type p2 = imgPath.find("/", p1 + 1);
          string::size_type p3 = imgPath.find("/", p2 + 1);
          string::size_type p4 = imgPath.find("/", p3 + 1);
          dirnamestr.assign(imgPath, p2 + 1, p3 - (p2 + 1));
          cout<<dirnamestr<<endl;

            outpathstr= imgPath.substr(dirnamestr.length()+9); //将图片名称提取出来
            cout<<outpathstr<<endl;

            int numLabel=atoi(classifyLabel.c_str());
            imgName.push_back( imgPath);//图像路径
            dirname.push_back( dirnamestr);//图片所在文件夹
            outpath1.push_back(outpathstr);//图片名称
            labels.push_back(numLabel);
        }
    }
    dataPath.close();
}


void roi(string roidataname,Mat& xmin, Mat& ymin,Mat& xmax,Mat& ymax)
{
 ifstream dataPathroi("/home/changlin/program/codeblocks/Computer_vision/assignment1/object_detect/objectnum.txt");
    string buf;
    while( dataPathroi )//将坐标依次读取进来
    {
        if( getline( dataPathroi, buf ) )
        {
            istringstream s(buf);
           int xleft,xright,ybelow,yup;
            s >> xleft >>ybelow >> xright>>yup;

            //*****提取坐标****//

            xmin.push_back( xleft );//图像路径
            ymin.push_back(ybelow);//图片所在文件夹
            xmax.push_back(xright);//图片名称
           ymax.push_back(yup);
        }
    }
    dataPathroi.close();

}
