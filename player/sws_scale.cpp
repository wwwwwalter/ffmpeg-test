#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
}

int main_sws(void)
{



	AVCodec *codec = nullptr;
	av_register_all();

	codec = av_codec_next(nullptr);
	
	codec = codec->next;
	codec = codec->next;
	
	cout << codec->supported_framerates->den << endl;
	cout << codec->supported_framerates->num << endl;













	return 0;
}