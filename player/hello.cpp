#include <iostream>
#include <stdio.h>

using namespace std;

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
}


struct URLProtocol;

char *urlprotocolinfo() {
	char *info = (char *)malloc(40000);
	memset(info, 0, 40000);

	av_register_all();

	struct URLProtocol *pup = NULL;
	//Input
	struct URLProtocol **p_temp = &pup;
	cout << avio_enum_protocols((void **)p_temp, 0) << endl;
	while ((*p_temp) != NULL) {
		sprintf_s(info, sizeof(info),"%s[In ][%10s]\n", info, avio_enum_protocols((void **)p_temp, 0));
	}
	pup = NULL;
	//Output
	avio_enum_protocols((void **)p_temp, 1);
	while ((*p_temp) != NULL) {
		sprintf_s(info, sizeof(info),"%s[Out][%10s]\n", info, avio_enum_protocols((void **)p_temp, 1));
	}

	return info;
}


int main_hello(int argc, char* argv[]) {

	char *infostr = nullptr;
	infostr = urlprotocolinfo();


	return 0;
}