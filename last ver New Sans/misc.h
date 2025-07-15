void downbone(bone &x){
	if(x.y>=353.0)
		x.destroy=1;
	else
		x.y+=2;
}
void upbone(bone &x){
	if(x.y<=206.0)
		x.destroy=1;
	else
		x.y-=2;
}
void left(bone &x){
	if(x.x<=245)
		x.destroy=1;
	else
		x.x-=2.5;
}
void leftf(bone &x){
	if(x.x<=245)
		x.destroy=1;
	else
		x.x-=5;
}
void lefts(bone &x){
	if(x.x<=245)
		x.destroy=1;
	else
		x.x-=1;
}
void leftbone(bone &x){
	if(x.x<=243)
		x.destroy=1;
	else
		x.x-=2;
}
void rightbone(bone &x){
	if(x.x>=390)
		x.destroy=1;
	else
		x.x+=2;
}
void apbone(bone &x){
	if(sec%3!=2||t>=10)
		x.destroy=1;
}
bool once_a_second(){
	return !t;
}
bool once_a_second_half(){
	return t==15;
}
bool a_second_two(){
	return sec%2==0&&t==0;
}
bool a_second_two_half(){
	return sec%2==1&&t==0;
}
bool three_times_a_second(){
	return t%10==0;
}
bool many_times_a_second(){
	return t%5==0;
}
bool three_second(){
	return sec%3==0&&t==0;
}
bool three_second_two(){
	return sec%3==2&&t==0;
}
bool four_second(){
	return sec%4==0&&t==0;
}
bool four_second_two(){
	return sec%4==2&&t==0;
}
void gen(){
	bones.push(bone(388,205,8,155,1,1,random(2)+2,left));
}
void genf(){
	bones.push(bone(388,205,8,155,1,1,random(2)+2,leftf));
}
void sbu(){
	bones.push(bone(358.75,351,38.75,7.5,2,1,1,upbone));
}
void sbuu(){
	bones.push(bone(397.5-min(60.0,(sec*15.0+t/2.0)),351,min(60.0,(sec*15.0+t/2.0)),7.5,10,1,4,upbone));
}
void sbd(){
	bones.push(bone(243.5,205,38.75,7.5,10,1,4,downbone));
}
void sbdd(){
	bones.push(bone(242.5,205,min(60.0,(sec*15.0+t/2.0)),7.5,10,1,4,downbone));
}
void sbl(){
	bones.push(bone(390,205,7.5,min(60.0,(sec*15.0+t/2.0)),10,1,4,leftbone));
}
void sbr(){
	bones.push(bone(242,360-min(60.0,(sec*15.0+t/2.0)),7.5,min(60.0,(sec*15.0+t/2.0)),10,1,4,rightbone));
}
void gbgen(){
	point pp={random(640),random(480)};
	gbs.push(gb(pp.x,pp.y,look(pp),100,10,10,10,30,30,1));
}
void apg(){
	p={320,282.5};
	jp=0;
	g=0;
	grav=random(4)+1;
}
void apb(){
	if(grav==1)
		bones.push(bone(242.5,205,155,75,5,1,1,apbone));
	if(grav==2)
		bones.push(bone(242.5,285,155,75,5,1,1,apbone));
	if(grav==3)
		bones.push(bone(242.5,205,75,155,5,1,1,apbone));
	if(grav==4)
		bones.push(bone(322.5,205,75,155,5,1,1,apbone));
}
void l4b1(){
	bones.push(bone(388,205,8,116.25,1,1,1,lefts));
}
void l4b2(){
	bones.push(bone(388,243.75,8,116.5,1,1,1,lefts));
}
void l5b1(){
	bones.push(bone(388,205,8,116.25,1,1,1,leftbone));
}
void l5b2(){
	bones.push(bone(388,243.75,8,116.5,1,1,1,leftbone));
}
