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
struct bone{
	double x,y,h,w,atk,fpsatk;
	int type,destroy,lasthit;
	void (*move)(bone&);
};
struct gb{
	double x,y,dir,w,atk,fpsatk;
	int round,spin,wait,keep,type,now,lasthit;
};
queue<bone>bones;
queue<gb>gbs;
int pr,heartmode=1,sansim,chsans,lmpr,moving,t,sec;
double jp,g,hp=92,kr;
PIMAGE soul[10],sans[16],box,ui,backword,wd[13],wl,pd[13],pl,wgb,bgb,ogb;
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
	ui=newimage();
	getimage(ui,"PNG","ui");
	backword=newimage();
	getimage(backword,"PNG","backword");
	for(int i=0;i<=9;i++){
		wd[i]=newimage();
		sprintf(temps,"w%d",i);
		getimage(wd[i],"PNG",temps);
	}
	wl=newimage();
	getimage(wl,"PNG","wline");
	for(int i=0;i<=9;i++){
		pd[i]=newimage();
		sprintf(temps,"p%d",i);
		getimage(pd[i],"PNG",temps);
	}
	pl=newimage();
	getimage(pl,"PNG","pline");
	wgb=newimage();
	getimage(wgb,"PNG","wgb");
	bgb=newimage();
	getimage(bgb,"PNG","bgb");
	ogb=newimage();
	getimage(ogb,"PNG","ogb");
	srand(time(0));
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
	if(keystate(key_esc))
		exit(0);
	if(keystate(key_enter)){
		hp=92;
		kr=0;
	}
}
void move(int pr){
	point n=p;
	switch(heartmode){
		case 1:
		case 2:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
			break;
		case 3:
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
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
				jp=4;
			}
			break;
		case 4:
			if(pr&4)
				n.x-=4;
			if(pr&8)
				n.x+=4;
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
				jp=4;
			}
			break;
		case 5:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
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
				jp=4;
			}
			break;
		case 6:
			if(pr&1)
				n.y-=4;
			if(pr&2)
				n.y+=4;
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
				jp=4;
			}
			break;
	}
	n.x=max(min(n.x,388.5),251.5);
	n.y=max(min(n.y,351.0),214.0);
	if(p.x==n.x&&p.y==n.y)
		moving=0;
	else
		moving=1;
	p.x=n.x;
	p.y=n.y;
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
	putimage(33,406,ui);
	putimage(33,379,backword);
	setfillcolor(EGERGB(191,0,0));
	bar(257,374,367,395);
	setfillcolor(EGERGB(255,0,255));
	bar(257,374,257+(hp+kr)*110.0/92,395);
	setfillcolor(EGERGB(255,255,0));
	bar(257,374,257+hp*110.0/92,395);
	int allhp=hp+kr;
	if(kr){
		putimage(418,377,pd[allhp/10]);
		putimage(433,377,pd[allhp%10]);
		putimage(457,377,pl);
		putimage(481,377,pd[9]);
		putimage(496,377,pd[2]);
	}
	else{
		putimage(418,377,wd[allhp/10]);
		putimage(433,377,wd[allhp%10]);
		putimage(457,377,wl);
		putimage(481,377,wd[9]);
		putimage(496,377,wd[2]);
	}
	int bs=bones.size();
	while(bs--){
		bone x=bones.front();
		bones.pop();
		switch(x.type){
			case 1:
				setfillcolor(WHITE);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 2:
				setfillcolor(0x14A9FF);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 3:
				setfillcolor(0xFFA040);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
			case 4:
				setfillcolor(0xFF0000);
				bar(x.x,x.y,x.x+x.h,x.y+x.w);
				break;
		}
		x.move(x);
		bones.push(x);
	}
}
void addbone(double x,double y,double w,double h,double atk,double fpsatk,int type,void (*move)(bone&)){
	bones.push({x,y,w,h,atk,fpsatk,type,0,0,move});
}
void addgb(double x,double y,double dir,double w,double atk,double fpsatk,int spin,int wait,int keep,int type){
	int round=rand()%4;
	gbs.push({x,y,dir,w,atk,fpsatk,round,spin,wait,keep,type,0,0});
}
void dropkr(){
	if(kr>=40){
		kr--;
		return;
	}
	if(kr>=30){
		if(t%2==0)
			kr--;
		return;
	}
	if(kr>=20){
		if(t%5==0)
			kr--;
		return;
	}
	if(kr>=10){
		if(t%15==0)
			kr--;
		return;
	}
	if(kr)
		if(t%30==0)
			kr--;
	return;
}
void hurt(double x){
	if(kr==0&&hp==1)
		exit(0);
	if(hp>x){
		hp-=x;
		kr+=x;
	}
	else{
		kr+=hp-1;
		hp=1;
	}
}
void check(bone &x){
	if(x.type==2&&moving==0)
		return;
	if(x.type==3&&moving==1)
		return;
	if(p.x+2>=x.x&&p.x-2<=x.x+x.h&&p.y+2>=x.y&&p.y-2<=x.y+x.w)
		if(x.lasthit)
			hurt(x.fpsatk);
		else{
			hurt(x.atk);
			x.lasthit=1;
		}
	else
		x.lasthit=0;
}
void check(gb &x){
	if(x.type==2&&moving==0)
		return;
	if(x.type==3&&moving==1)
		return;
}
void hit(){
	int bs=bones.size();
	while(bs--){
		bone x=bones.front();
		bones.pop();
		check(x);
		x.move(x);
		if(!x.destroy)
			bones.push(x);
	}
	int gs=gbs.size();
	while(gs--){
		gb x=gbs.front();
		gbs.pop();
		x.now++;
		if(x.now<=x.spin+x.wait+x.keep){
			if(x.now>x.spin+x.wait)
				check(x);
			gbs.push(x);
		}
	}
}
void downbone(bone &x){
	if(x.y>=351.0)
		x.destroy=1;
	else
		x.y+=2;
}
void left(bone &x){
	if(x.x<=214.0)
		x.destroy=1;
	else
		x.x-=5;
}
void leftf(bone &x){
	if(x.x<=214.0)
		x.destroy=1;
	else
		x.x-=2.5;
}
void downbonef(bone &x){
	if(x.y>=351.0)
		x.destroy=1;
	else
		x.y+=3;
}
void upbone(bone &x){
	if(x.y<=214.0)
		x.destroy=1;
	else
		x.y-=2;
}
void apbone(bone &x){
	x.destroy=1;
}
int main(){
	hc();
	init();
	for(;;delay_fps(30)){
		t++;
		t%=30;
		if(!t)
			sec++;
		addbone(282.25,351,77.5,7.5,10,10,4,apbone);
		if(t%15==0){
			if(!t){
				addbone(388,210,8,155,1,1,rand()%2+2,leftf);
				addbone(359.75,351,38.75,7.5,5,1,1,upbone);
			}
			else{
				addbone(388,210,8,155,1,1,rand()%2+2,left);
				addbone(243.5,214,38.75,7.5,5,1,1,downbone);
				}
		}
		show();
		hit();
		dropkr();
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
