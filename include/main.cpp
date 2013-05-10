#include <gCore.h>


#define ARROW_WEIGHT	3
#define ARROW_SPEED		1
#define ARROW_SPEED_MAX 10
#define ARROW_COEF_EASY 0.75


class Arrow : public Sprite
{
public:

	vector2 len;
	vector2 lenavel;


	Arrow(	char	*src =		NULL,
			Surface *parent =	NULL,
			double	 posx =		0,
			double	 posy =		0,
			double	 lenx =		0,
			double	 leny =		0) : Sprite(src,parent,posx,posy)
	{
		len = vector2(lenx,leny);

		addListener([this](){Arrow_display();});
	}

	virtual ~Arrow(){ /* Nothing. Deal with it */ };


private:

	void Arrow_display()
	{
		len = len+lenavel*Main::speedFactor();
		scale2d(sqrt(pow(len.x,2)+pow(len.y,2)),ARROW_WEIGHT);
		rotation = atan2f(len.y,len.x)*180/PI;
	}
};


int main(int argc,char *argv[])
{
	Main *window = new Main(800,600,60,false,"Cross product");
	Resource::cache("../res/pack01.pak");

	Screen *scr = new Screen(NULL,0,0,800,600);


		// MENU
	Surface *textBG = new Surface(scr);
		Text *mainText = new Text("Produto cruzado",textBG,12,12,24,255,255,255,0,"LiberationMono-Bold.ttf");
		Text *tipText =  new Text("[TAB] seleciona vetor para alteração",textBG,12,48,24,255,255,255,0,"LiberationMono-Regular.ttf");
		Text *tipText2 = new Text("[SETA] altera seu comprimento nos eixos X e Y",textBG,12,84,24,255,255,255,0,"LiberationMono-Regular.ttf");
		Text *tipText3 = new Text("[ESC] fecha o programa",textBG,12,120,24,255,255,255,0,"LiberationMono-Regular.ttf");
		textBG->pos.x = 512;
		textBG->addListener([textBG]()
		{
			textBG->pos.x -= textBG->pos.x*0.2;
		});


		// ARROWS

	Surface *graphGB = new Surface(scr);
		vector2 origin(Main::width()/2.0f,Main::height()/2.0f);
		Arrow *arrowR = new Arrow("red.bmp",graphGB,origin.x,origin.y,100,10);
		Arrow *arrowG = new Arrow("green.bmp",graphGB,origin.x,origin.y,10,100);
		Arrow *arrowB = new Arrow("blue.bmp",graphGB,origin.x,origin.y,0,0);
		Arrow *arrowSelected = arrowR;
		graphGB->alpha = 0;
		graphGB->addListener([graphGB]()
		{
			graphGB->alpha += (1-graphGB->alpha)*0.02;
		});



		// COMMANDS

	Object *obj = new Object();
		obj->addListener([	arrowR,
							arrowG,
							arrowB,
							&arrowSelected]()
		{
			if(Event::keyDown(SDLK_TAB))
				if(arrowSelected->id() == arrowR->id()) arrowSelected = arrowG;
				else									arrowSelected = arrowR;

			if(Event::keyDown(SDLK_LEFT)	||
				Event::keyDown(SDLK_RIGHT)	||
				Event::keyDown(SDLK_UP)		||
				Event::keyDown(SDLK_DOWN)	)
			{

				if(Event::keyDown(SDLK_LEFT))
					arrowSelected->lenavel.x--;

				if(Event::keyDown(SDLK_RIGHT))
					arrowSelected->lenavel.x++;

				if(Event::keyDown(SDLK_UP))
					arrowSelected->lenavel.y--;

				if(Event::keyDown(SDLK_DOWN))
					arrowSelected->lenavel.y++;

				if(abs(arrowSelected->lenavel.x) > ARROW_SPEED_MAX)
					if(arrowSelected->lenavel.x > 0)	arrowSelected->lenavel.x =  ARROW_SPEED_MAX;
					else								arrowSelected->lenavel.x = -ARROW_SPEED_MAX;

				if(abs(arrowSelected->lenavel.y) > ARROW_SPEED_MAX)
					if(arrowSelected->lenavel.y > 0)	arrowSelected->lenavel.y =  ARROW_SPEED_MAX;
					else								arrowSelected->lenavel.y = -ARROW_SPEED_MAX;
			}else{
				arrowR->lenavel = arrowR->lenavel*vector2(ARROW_COEF_EASY,ARROW_COEF_EASY);
				arrowG->lenavel = arrowG->lenavel*vector2(ARROW_COEF_EASY,ARROW_COEF_EASY);
			}

			if(Event::keyDown(SDLK_ESCAPE))
				Main::RUNNING = false;


				// THE ACTUAL CODE

			arrowB->len.x = (arrowR->len.x - arrowG->len.x)*sin((arrowR->rotation - arrowG->rotation)*PI/180);
			arrowB->len.y = (arrowR->len.y - arrowG->len.y)*cos((arrowR->rotation - arrowG->rotation)*PI/180);



		});

	Text *textFPS = new Text("FPS::99",scr,18,Main::height()-18,9,255,0,0,0,"LiberationMono-Regular.ttf");
	textFPS->addListener([textFPS]()
	{
		textFPS->text("FPS= "+toStringi(Main::fps()));
	});
		
	window->display();
	return EXIT_SUCCESS;
}