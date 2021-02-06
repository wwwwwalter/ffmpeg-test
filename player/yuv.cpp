#include <iostream>
#include <cstdlib>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
typedef unsigned char uchar;


int simplest_yuv420_split(const char *filename, int w, int h, int num) {
	FILE *fp = fopen(filename, "rb+");

	FILE *fp_Y = fopen("output_yuv420p_Y", "wb+");
	FILE *fp_U = fopen("output_yuv420p_U", "wb+");
	FILE *fp_V = fopen("output_yuv420p_V", "wb+");


	uchar *frame = new uchar[w*h * 3 / 2];

	for (int i = 0; i < num; ++i) {
		cout << fread(frame, 1, w*h * 3 / 2, fp) << endl;
		fwrite(frame, 1, w*h, fp_Y);
		fwrite(frame+w*h, 1, w*h / 4, fp_U);
		fwrite(frame+w*h*5/4, 1, w*h / 4, fp_V);
	}

	delete frame;
	fclose(fp);
	fclose(fp_Y);
	fclose(fp_U);
	fclose(fp_V);
	return 0;
}


int simplest_yuv420_gray(const char *filename, int w, int h, int num) {
	FILE *fp = fopen(filename, "rb+");
	FILE *fp1 = fopen("output_gray.yuv","wb+");
	FILE *fp2 = fopen("output_gray_U.U","wb+");
	uchar *frame = new uchar[w*h*3/2];

	for (int i = 1; i <= num; ++i) {
		fread(frame, 1, w*h * 3 / 2, fp);
		memset(frame + w * h, 128, w*h / 2);
		fwrite(frame, 1, w*h * 3 / 2, fp1);
		fwrite(frame + w * h, 1, w*h / 4, fp2);
	}

	delete(frame);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);


	return 0;
}


int simplest_rgb24_split(const char *url, int w, int h, int num) {
	FILE *fp = fopen(url, "rb+");
	FILE *fp1 = fopen("output_r.y", "wb+");
	FILE *fp2 = fopen("output_g.y", "wb+");
	FILE *fp3 = fopen("output_b.y", "wb+");
	FILE *fp4 = fopen("output_rgb.y", "wb+");

	unsigned char *pic = (unsigned char *)malloc(w*h * 3);

	for (int i = 0; i < num; i++) {

		fread(pic, 1, w*h * 3, fp);

		for (int j = 0; j < w*h * 3; j = j + 3) {
			//R
			fwrite(pic + j, 1, 1, fp1);
			//G
			fwrite(pic + j + 1, 1, 1, fp2);
			//B
			fwrite(pic + j + 2, 1, 1, fp3);
		}

		char temp[1] = { 0 };
		for (int j = 0; j < w*h*3; j = j + 3) {
			fwrite(pic + j, 1, 1, fp4);
			fwrite(temp, 1, 1, fp4);
			fwrite(temp, 1, 1, fp4);
		}
	}

	free(pic);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

	return 0;
}




int main_yuv(void) {

#if 0
	const char *filename = "C:\\Users\\admin\\Downloads\\stefan_cif\\stefan_cif.yuv";
	int w = 352;
	int h = 288;
	//simplest_yuv420_split(filename,w ,h , 90);
	//simplest_yuv420_gray(filename, w, h, 90);

#endif

	FILE *fpr = fopen("walter_rgb_r","wb+");
	FILE *fpg = fopen("walter_rgb_g", "wb+");
	FILE *fpb = fopen("walter_rgb_b", "wb+");
	FILE *fprgb = fopen("walter_rgb_rgb", "wb+");


	char temp[1] = { 0 };

	//c->val[0]:b
	//c->val[1]:g
	//c->val[2]:r

	Mat mat = imread("E:\\player\\player\\fmt.png");

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec3b *c = mat.ptr<Vec3b>(i, j);

			fwrite(&c->val[2], 1, 1, fpr);//r
			fwrite(temp, 1, 1, fpr);   //g
			fwrite(temp, 1, 1, fpr);   //b			
		}
	}

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec3b *c = mat.ptr<Vec3b>(i, j);
			
			fwrite(temp, 1, 1, fpg);   //r
			fwrite(&c->val[1], 1, 1, fpg);//g
			fwrite(temp, 1, 1, fpg);   //b
			
		}
	}

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec3b *c = mat.ptr<Vec3b>(i, j);

			fwrite(temp, 1, 1, fpb);   //r
			fwrite(temp, 1, 1, fpb);   //g
			fwrite(&c->val[0], 1, 1, fpb);//b
		}
	}

	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec3b *c = mat.ptr<Vec3b>(i, j);

			fwrite(&c->val[2], 1, 1, fprgb);   //r
			fwrite(&c->val[1], 1, 1, fprgb);   //g
			fwrite(&c->val[0], 1, 1, fprgb);   //b			
		}
	}

	fclose(fpr);
	fclose(fpg);
	fclose(fpb);
	fclose(fprgb);

	

	//const char *filename = "E:\\player\\player\\fmt.png";
	//simplest_rgb24_split(filename, 302, 340, 1);



	return 0;
}