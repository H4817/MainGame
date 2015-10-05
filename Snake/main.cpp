#include <SFML/Graphics.hpp>
#include <time.h>

#include <iostream>

using namespace sf;
using namespace std;

int N=30,M=30;
int Scale=16;
bool pause = false;
char zaxodit[8] = "zaxodit";
int w = Scale*N;
int h = Scale*M;

int dir,num=4;
float timer=0;

struct PieceOfSnake 
{ int x,y;}  s[100];

struct Fruct
{ int x,y;} f;

 void Tick()
 {
    for (int i=num;i>0;--i)
	 {s[i].x=s[i-1].x;
	 s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;      
    if (dir==1) s[0].x-=1;        
    if (dir==2) s[0].x+=1;         
    if (dir==3) s[0].y-=1;         
 
    if ((s[0].x==f.x) && (s[0].y==f.y)) 
      { num++; 
    	f.x=rand() % N;
        f.y=rand() % M;}
 
    if (s[0].x>N-1) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M-1) s[0].y=0;  if (s[0].y<0) s[0].y=M;
 
    for (int i=1;i<num;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
 }

void Pause()
{
  cout << zaxodit << endl;  
}

int main()
{  
	srand(time(0));

    RenderWindow window(VideoMode(w, h), "SFML works!");

	Texture tile1,tile2,tile3;
	tile1.loadFromFile("green1116.png");
	tile2.loadFromFile("red16.png");
    tile3.loadFromFile("pause.jpg");
	Sprite sprite1, sprite2, sprite3;
	sprite1.setTexture(tile1);
	sprite2.setTexture(tile2);
    sprite3.setTexture(tile3);

	Clock clock;

	f.x=10;
    f.y=10; 

    while (window.isOpen())
    { 
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)      
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Space){ // сюда заходим один раз
                pause = !pause;
                
                //while (pause){
                
                
                //window.clear();
                //window.draw(sprite3);
                //window.display();
                //if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                //pause = !pause;}
                
                //}
                
                //Pause();
                //while (pause){   тут зависает
                
                //sprite3.setPosition(100,200);
                
                //while(pause){ 
                    
                    //if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Space){break;}
                    
                //}
                
                //}
                }
        

            
                
		}
        
        
        if (!pause){
        
           if (dir == 1){
	       if (Keyboard::isKeyPressed(Keyboard::Left))  dir=1;    
	       if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
		   if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;
        }   
        
          else  if (dir == 2){
                if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;    
                if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
                if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;
                         } 
               
         
          else  if (dir == 3){
                if (Keyboard::isKeyPressed(Keyboard::Right))  dir=2;    
                if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
                if (Keyboard::isKeyPressed(Keyboard::Up)) dir=3;
                         }  
             
        
           else if (dir == 0){
                if (Keyboard::isKeyPressed(Keyboard::Right)) dir=2;    
                if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;
                if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
                         }  
            
 
		timer+=time; 
		if (timer>0.1) {timer=0; Tick();}	}

   ////// draw  ///////
    window.clear();

    for (int i=0; i<w; i+=Scale) 
		  for (int j=0; j<h; j+=Scale) 
		    { sprite1.setPosition(i,j);  window.draw(sprite1); }
 
    for (int i=0;i<num;i++)
	        { sprite2.setPosition(s[i].x*Scale, s[i].y*Scale);  window.draw(sprite2); }
   
	sprite2.setPosition( f.x*Scale,  f.y*Scale);  window.draw(sprite2);	

	window.display();
	}

    return 0;
}





















































