#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <fstream>

using namespace std;

class Cargame :public olc::PixelGameEngine
{
public:
	string b;
	class Car {
	public:
		float x = 60;
		float y = 130;
		float cwidth = 20;
		float clength = 40;
		float speed = 80;
		int health = 3;

	};
	class AICar {
	public:
		float x = rand() % 100;
		float y = -10 - rand() % 200;
		float cwidth = 20;
		float clength = 40;
		float speed = 140 + rand() % 40;
		float color = 200;
	};

	Cargame() {

	}
	bool OnUserCreate() override {
		heartsprite = new olc::Sprite("heart1.png");
		carsprite = new olc::Sprite("red.png");
		aisprite = new olc::Sprite("blue.png");
		myfile.open("data.txt");
		myfile >> b;
		return true;
		

	}
	bool OnUserDestroy()override {
		myfile << score << endl;
		return true;
	}
	bool OnUserUpdate(float felapsedTime)override {

		Clear(olc::Pixel(0, 0, 0));
		// player car and car controller
		DrawSprite(d.x, d.y, carsprite);
		

		//FillRect(d.x, d.y, d.cwidth, d.clength, olc::Pixel(255, 0, 0));
		
		if (GetKey(olc::A).bHeld){
			d.x -= d.speed * felapsedTime;
			}
		if (GetKey(olc::D).bHeld) {
			d.x += d.speed * felapsedTime;
		}
		
		// making the ai cars
		for (int j = 0; j < 3; j++) {
			//FillRect(c[j].x, c[j].y, c[j].cwidth, c[j].clength, olc::Pixel(0, 0, c[j].color));
			DrawSprite(c[j].x, c[j].y, aisprite);
			c[j].y += c[j].speed * felapsedTime;
			if (c[j].y >= 180) {
				c[j].y = -10 - rand() % 200;
				c[j].x = rand() % 100;
				c[j].speed = 140 + rand() % 40;
				c[j].color = 200;
			}
			//hit detection
			if (c[j].x < d.x + d.cwidth && c[j].x + c[j].cwidth > d.x &&
				c[j].y < d.y + d.clength && c[j].y + c[j].clength > d.y) {
					c[j].color = 100;
					d.health -= 1;
					c[j].y = -30;
					c[j].x = rand() % 100;
					c[j].speed = 140 + rand() % 40;
					c[j].color = 200;
			}
	
		}
		
		score += felapsedTime * 100;
		DrawString(20, 20, to_string(d.health));
		DrawString(70, 169, to_string(score));
		
		DrawString(50, 20, b);
		DrawSprite(10, 18, heartsprite);
		if (d.health < 0) {
			return false;
		}

		return true;
	}
	private:
		fstream myfile;
		Car d;
		AICar c[3];
		float dlocation = 0;
		float alocation = 0;
		bool hit = false;
		olc::Sprite* carsprite;
		olc::Sprite* aisprite;
		olc::Sprite* heartsprite;
		double score = 0;
};
int main() {
	
	srand(time(NULL));
	Cargame c;
	if (c.Construct(120, 180, 4, 4))
		c.Start();
	return 0;
}
