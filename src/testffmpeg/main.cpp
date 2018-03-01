
//cpp������Ҫ��
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/mem.h>
#include <libavutil/fifo.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

//Ԥ����ָ��
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"swresample.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")
#pragma comment(lib,"avutil.lib")

#include <stdio.h>

extern "C"
{
#include "SDL.h"
};
/*
* http://blog.csdn.net/leixiaohua1020/article/details/38868499
*/


const int bpp = 12;

int screen_w = 640, screen_h = 360;
const int pixel_w = 640, pixel_h = 360;

unsigned char buffer[pixel_w*pixel_h*bpp / 8];

int main(int argc, char* argv[])
{
	//��ʼ��SDLϵͳ
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window *screen;
	//SDL 2.0 Support for multiple windows
	//��������SDL_Window
	screen = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_w, screen_h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);//������Ļ�Ŀ�߶�
	if (!screen) {
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}
	//������Ⱦ��SDL_Renderer
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);

	Uint32 pixformat = 0;
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	pixformat = SDL_PIXELFORMAT_IYUV;
	
	//��������SDL_Texture,�൱��SDL1.x��SDL_CreateYUVOverlay()
	SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer, pixformat, SDL_TEXTUREACCESS_STREAMING, pixel_w, pixel_h);

	FILE *fp = NULL;
	fp = fopen("../sintel_640_360.yuv", "rb+");//ֻ��(r)д(+)��ʽ����һ���������ļ�(b)

	if (fp == NULL) {
		printf("cannot open this file\n");
		return -1;
	}

	SDL_Rect sdlRect;//���νṹ�������ڴ����е���ʾλ��

	while (1) {
		if (fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp) != pixel_w*pixel_h*bpp / 8) {
			// Loop
			fseek(fp, 0, SEEK_SET);
			fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp);
		}
		//�������������
		SDL_UpdateTexture(sdlTexture, NULL, buffer, pixel_w);

		sdlRect.x = 0;
		sdlRect.y = 0;
		sdlRect.w = screen_w;
		sdlRect.h = screen_h;

		SDL_RenderClear(sdlRenderer);//��ʾ֮ǰһ����Ҫ��������ѡ��
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &sdlRect);//����������ݿ�������Ⱦ��
		SDL_RenderPresent(sdlRenderer);//��ʾ����
		
		SDL_Delay(40);//��ʱ40ms

	}
	SDL_Quit();//�˳�SDLϵͳ
	return 0;
}