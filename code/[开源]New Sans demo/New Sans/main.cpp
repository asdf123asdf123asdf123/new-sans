#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
#include"exege.h"
using namespace std;
void hc(){
	HWND h=GetForegroundWindow();
	ShowWindow(h,SW_HIDE);
}
int main(){
	hc();
	int x=100,y=100,sansim=0,chsans=1;
	initgraph(640,480,INIT_RENDERMANUAL);
	setcaption("New Sans");
	setbkcolor(BLACK);
	ege_enable_aa(true);
	PIMAGE rs=newimage(),sans[16],box=newimage();
	char temps[255];
    getimage(rs,"PNG","redsoul");
	for(int i=1;i<=13;i++){
		sans[i]=newimage();
		sprintf(temps,"sans%d",i);
		cout<<temps<<endl;
		getimage(sans[i],"PNG",temps);
	}
    getimage(box,"PNG","fightbox");
	for(;;delay_fps(30)){
		cleardevice();
		putimage(x,y,rs);
		if(chsans){
			sansim%=13;
			sansim++;
		}
		putimage(100,100,sans[sansim]);
		chsans=!chsans;
		putimage_withalpha(NULL,box,237.5,200);
		if(keystate(key_up))
			y-=6;
		if(keystate(key_down))
			y+=6;
		if(keystate(key_left))
			x-=6;
		if(keystate(key_right))
			x+=6;
	}
	closegraph();
	return 0;
}
