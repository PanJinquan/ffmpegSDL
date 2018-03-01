
//cpp代码中要加
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/mem.h>
#include <libavutil/fifo.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

//预编译指令
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
	//初始化SDL系统
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}

	SDL_Window *screen;
	//SDL 2.0 Support for multiple windows
	//创建窗口SDL_Window
	screen = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_w, screen_h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);//创建屏幕的宽高度
	if (!screen) {
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}
	//创建渲染器SDL_Renderer
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);

	Uint32 pixformat = 0;
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	pixformat = SDL_PIXELFORMAT_IYUV;
	
	//创建纹理SDL_Texture,相当于SDL1.x的SDL_CreateYUVOverlay()
	SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer, pixformat, SDL_TEXTUREACCESS_STREAMING, pixel_w, pixel_h);

	FILE *fp = NULL;
	fp = fopen("../sintel_640_360.yuv", "rb+");//只读(r)写(+)方式，打开一个二进制文件(b)

	if (fp == NULL) {
		printf("cannot open this file\n");
		return -1;
	}

	SDL_Rect sdlRect;//矩形结构：内容在窗口中的显示位置

	while (1) {
		if (fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp) != pixel_w*pixel_h*bpp / 8) {
			// Loop
			fseek(fp, 0, SEEK_SET);
			fread(buffer, 1, pixel_w*pixel_h*bpp / 8, fp);
		}
		//设置纹理的数据
		SDL_UpdateTexture(sdlTexture, NULL, buffer, pixel_w);

		sdlRect.x = 0;
		sdlRect.y = 0;
		sdlRect.w = screen_w;
		sdlRect.h = screen_h;

		SDL_RenderClear(sdlRenderer);//显示之前一般需要清屏（可选）
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &sdlRect);//将纹理的数据拷贝给渲染器
		SDL_RenderPresent(sdlRenderer);//显示内容
		
		SDL_Delay(40);//延时40ms

	}
	SDL_Quit();//退出SDL系统
	return 0;
}