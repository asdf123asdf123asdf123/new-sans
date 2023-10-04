#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
#include"exege.h"
using namespace std;
void hc(){
	HWND h=GetForegroundWindow();
	ShowWindow(h,SW_HIDE);
}
struct point{
	double x,y;
}p;
int pr,heartmode=1,sansim,chsans,lmpr;
double jp,g;
PIMAGE soul[10],box,sans[16];
void init(){
	char temps[255];
	initgraph(640,480,INIT_RENDERMANUAL);
	setcaption("New Sans");
	setbkcolor(BLACK);
	ege_enable_aa(true);
    p={320,282.5};
    for(int i=1;i<=6;i++){
		soul[i]=newimage();
		sprintf(temps,"soul%d",i);
		getimage(soul[i],"PNG",temps);
	}
	for(int i=1;i<=13;i++){
		sans[i]=newimage();
		sprintf(temps,"sans%d",i);
		getimage(sans[i],"PNG",temps);
	}
	box=newimage();
    getimage(box,"PNG","fightbox");
}
void press(){
	pr=0;
	if(keystate(key_up))
		pr|=1;
	if(keystate(key_down))
		pr|=2;
	if(keystate(key_left))
		pr|=4;
	if(keystate(key_right))
		pr|=8;
}
//bool check(point x){
//	if(x.x>=251.5&&x.x<=388.5&&x.y>=214&&x.y<=351)
//		return true;
//	return false;
//}
void move(int pr){
	point n=p;
	switch(heartmode){
		case 1:
		case 2:
			if(pr&1)
				n.y-=6;
			if(pr&2)
				n.y+=6;
			if(pr&4)
				n.x-=6;
			if(pr&8)
				n.x+=6;
			break;
		case 3:
			if(pr&4)
				n.x-=6;
			if(pr&8)
				n.x+=6;
			if((pr&2)&&jp){
				n.y+=jp;
				jp-=0.25;
			}
			else{
				jp=0;
				n.y-=g;
				g+=0.25;
			}
			if(n.y<=214.0){
				g=0;
				jp=6;
			}
			break;
		case 4:
			if(pr&4)
				n.x-=6;
			if(pr&8)
				n.x+=6;
			if((pr&1)&&jp){
				n.y-=jp;
				jp-=0.25;
			}
			else{
				jp=0;
				n.y+=g;
				g+=0.25;
			}
			if(n.y>=351.0){
				g=0;
				jp=6;
			}
			break;
		case 5:
			if(pr&1)
				n.y-=6;
			if(pr&2)
				n.y+=6;
			if((pr&8)&&jp){
				n.x+=jp;
				jp-=0.25;
			}
			else{
				jp=0;
				n.x-=g;
				g+=0.25;
			}
			if(n.x<=251.5){
				g=0;
				jp=6;
			}
			break;
		case 6:
			if(pr&1)
				n.y-=6;
			if(pr&2)
				n.y+=6;
			if((pr&4)&&jp){
				n.x-=jp;
				jp-=0.25;
			}
			else{
				jp=0;
				n.x+=g;
				g+=0.25;
			}
			if(n.x>=388.5){
				g=0;
				jp=6;
			}
			break;
	}
	p.x=max(min(n.x,388.5),251.5);
	p.y=max(min(n.y,351.0),214.0);
}
void show(){
	cleardevice();
	putimage(p.x-8,p.y-8,soul[heartmode]);
	if(!chsans){
		sansim%=13;
		sansim++;
	}
	chsans=(chsans+1)%3;
	putimage(261,25,sans[sansim]);
	putimage_withalpha(NULL,box,237.5,200);
}
int main(){
	hc();
	init();
	int x=0;
	for(;;delay_fps(30)){
		x++;
		x%=120;
		if(!x){
			heartmode%=6;
			heartmode+=1;
		}
		show();
		press();
		move(pr);
		if(pr)
			lmpr=pr;
		else
			if(heartmode==2)
				move(lmpr);
	}
	closegraph();
	return 0;
}
