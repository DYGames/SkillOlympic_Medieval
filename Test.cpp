#include "DXUT.h"
#include "Test.h"

void Test::init()
{

}

void Test::update()
{
	Node::update();


}

void Test::exit()
{
	for (auto it : _children)
		removeChild(it);
}