#include <iostream>
#include "clientone.h"
#include "serverone.h"
#include "servertow.h"
#include "clienttwo.h"

using namespace std;

int main(int argc, char* argv)
{
//    ServerOne one;
//    one.init();

//    ClientOne one;
//    one.init();
//    one.Connect();
//    cout<<"end"<<endl;

//    ServerTow two;
//    two.init();

    ClientTwo two;
    two.init();
    two.Connect();
}






