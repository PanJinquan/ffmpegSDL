/**
 * ��򵥵�SDL2������Ƶ�����ӣ�SDL2����RGB/YUV��
 * Simplest Video Play SDL2 (SDL2 play RGB/YUV) 
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * ������ʹ��SDL2����RGB/YUV��Ƶ�������ݡ�SDLʵ�����ǶԵײ��ͼ
 * API��Direct3D��OpenGL���ķ�װ��ʹ���������Լ���ֱ�ӵ��õײ�
 * API��
 *
 * This software plays RGB/YUV raw video data using SDL2.
 * SDL is a wrapper of low-level API (Direct3D, OpenGL).
 * Use SDL is much easier than directly call these low-level API.  
 */

#include <stdio.h>

extern "C"
{
#include "SDL.h"
};

const int bpp=12;

//int screen_w=500,screen_h=500;
//const int pixel_w=680,pixel_h=180;
int screen_w = 640, screen_h = 360;
const int pixel_w = 640, pixel_h = 360;//���������ԭ��Ƶ�Ŀ������ƥ��

unsigned char buffer[pixel_w*pixel_h*bpp/8];

//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)
//Break
#define BREAK_EVENT  (SDL_USEREVENT + 2)

int thread_exit=0;

int refresh_video(void *opaque){
	thread_exit=0;
	while (thread_exit==0) {
		SDL_Event event;
		event.type = REFRESH_EVENT;//�Զ�����¼�
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}
	thread_exit=0;
	//Break
	SDL_Event event;
	event.type = BREAK_EVENT;//�Զ�����¼�
	SDL_PushEvent(&event);
	return 0;
}

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)) {  
		printf( "Could not initialize SDL - %s\n", SDL_GetError()); 
		return -1;
	} 

	SDL_Window *screen; 
	//SDL 2.0 Support for multiple windows
	screen = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_w, screen_h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	if(!screen) {  
		printf("SDL: could not create window - exiting:%s\n",SDL_GetError());  
		return -1;
	}
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);  

	Uint32 pixformat=0;
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	pixformat= SDL_PIXELFORMAT_IYUV;  

	SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,pixformat, SDL_TEXTUREACCESS_STREAMING,pixel_w,pixel_h);

	FILE *fp=NULL;
	//fp=fopen("test_yuv420p_320x180.yuv","rb+");
	fp = fopen("../sintel_640_360.yuv", "rb+");//ֻ��(r)д(+)��ʽ����һ���������ļ�(b)

	if(fp==NULL){
		printf("cannot open this file\n");
		return -1;
	}

	SDL_Rect sdlRect;  

	SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video,NULL,NULL);
	SDL_Event event; 
	int player_state = 1;//0:��ʾ�ݶ���1��ʾ��������
	while(1){
		//Wait
		SDL_WaitEvent(&event);
		if(event.type==REFRESH_EVENT&&player_state==1){
			if (fread(buffer, 1, pixel_w*pixel_h*bpp/8, fp) != pixel_w*pixel_h*bpp/8){
				// Loop
				fseek(fp, 0, SEEK_SET);
				fread(buffer, 1, pixel_w*pixel_h*bpp/8, fp);
			}

			SDL_UpdateTexture( sdlTexture, NULL, buffer, pixel_w);  

			//FIX: If window is resize
			sdlRect.x = 0;  
			sdlRect.y = 0;  
			sdlRect.w = screen_w;  
			sdlRect.h = screen_h;  
			
			SDL_RenderClear( sdlRenderer );   
			SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, &sdlRect);  
			SDL_RenderPresent( sdlRenderer );  
			
		}else if(event.type==SDL_WINDOWEVENT){
			//��ô�������仯�¼�
			SDL_GetWindowSize(screen,&screen_w,&screen_h);//��ô��ڿ�͸�
		}else if(event.type==SDL_QUIT){
			thread_exit=1;
		}else if(event.type==BREAK_EVENT){
			break;
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE&&event.key.state == SDL_PRESSED)//���ո������ͣ���߲���
		{
			SDL_Delay(40);
			player_state = (player_state == 1) ? 0 : 1;
			printf("player_state=%d\n", player_state);
		}
		else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE&&event.key.state == SDL_PRESSED)//��Esc�����˳�����
		{
			SDL_Delay(40);
			break;
			//SDL_Quit();
		}
		//printf("event.key.keysym.scancode=%d\n", event.key.keysym.scancode);

	}
	SDL_Quit();
	return 0;
}
