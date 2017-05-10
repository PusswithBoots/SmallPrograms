#include <iostream>      
#include <cv.h>      
#include <highgui.h>      
#include <fstream>
#include <tchar.h>
#include <sstream>
#include <string>
#include <cstring>
#include<stdlib.h>
using namespace std;

/*
@author:Äæ·çØ¼·ÉÏè

@time: 2017-02-17

@IDE: VS2013+OPENCV3.1
...
...
*/
void jpg2ppm(char* input, char* output)
{
	IplImage* jpg;
	jpg = cvLoadImage(input, -1);
	if (!jpg)
	{
		cout << "Can not open " << input << ",No Such File or Directory!" << endl;
		return;
	}
	uchar ptrBlue, ptrGreen, ptrRed;

	ofstream pppp;
	ofstream ppm(output, ios::app | ios::binary);
	ppm << "P6" << endl << jpg->width << " " << jpg->height << endl << 255 << endl;   //ppm header data

	for (int j = 0; j < jpg->height; j++)
	for (int i = 0; i < jpg->width; i++)
	{
		uchar* temp_ptr = &((uchar*)(jpg->imageData + jpg->widthStep*j))[i * 3];
		ptrBlue = temp_ptr[0];
		ptrGreen = temp_ptr[1];
		ptrRed = temp_ptr[2];

		ppm << ptrRed << ptrGreen << ptrBlue;
	}

	ppm.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	string rawImgPath = "D:\\dataset\\VOCdevkit\\VOC2012\\JPEGImages\\";   //your original image path
	string imgNameFile = "D:\\dataset\\VOCdevkit\\VOC2012\\JPEGImages\\fileName.txt"; //your original images name path dos:dir -b >fileName.txt
	string outPath = "D:\\dataset\\VOCdevkit\\VOC2012\\PPMImages\\";    //your ppm file output path
	string forma = ".ppm";
	//read fileName from fileName.txt

	ifstream fin(imgNameFile, ios::in);
	string anImgName;
	string tmpName;
	
	if (fin)
	while (getline(fin,anImgName))
	{
		char *input = (char*)malloc(sizeof(char)* 20);
		char *output = (char*)malloc(sizeof(char)* 20);
		memset(input, 0, sizeof(char)* 20);
		memset(output, 0, sizeof(char)* 20);  //CAUTION!!!! the function has a lost waste of memory,sugesst >8G memory run the program. And how to solve this drawbacks?
	    cout << "Processing file: " << anImgName << endl;
		strcpy(input, (rawImgPath + anImgName).c_str());   //c_str() function return const char tye,so do the strcpy.
		tmpName = anImgName.substr(0, anImgName.length()- 4);   //get the image name without last image format name
		strcpy(output, (outPath + tmpName+ forma).c_str());  //strcpy implement convert const char * to char *
		jpg2ppm(input, output); //processing function
		cout << "Done!" << endl;
		free(input);
		free(output);
	}
	else // no image name file
	{
		cout << "no such file" << endl;
	}
	fin.clear();
	fin.close();
	system("PAUSE");    //belong to <stdlib.h>
	return 0;
}
