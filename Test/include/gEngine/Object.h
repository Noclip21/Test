#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <functional>

#include "Utils.h"


#include "prologue.h"
class G_DECLSPEC Object
{
	
	public:
		
		static vector<Object*> objects;


		static bool alive(Object *obj);


		Object();
		virtual ~Object();


		void addListener(function<void ()> f);
		void display();
		void kill();

	private:
		vector<function<void ()>> listeners;

		bool markedToDeath;

};
#include "epilogue.h"

#endif