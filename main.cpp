#include <iostream>
#include "clientone.h"
#include "serverone.h"
#include "servertow.h"
#include "clienttwo.h"
#include "serverthree.h"

#include "configs/Configs.h"
#include "third-party/pugixml.hpp"

using namespace std;

int main(int argc, char* argv)
{
    pugi::xml_document doc;
    if(doc.load_file("net_config.xml",pugi::parse_default,pugi::encoding_utf8)!=pugi::status_ok)
    {
        std::cout<<"xml load failed!"<<std::endl;
    }
    pugi::xml_node ser_config = doc.child("root");
    ServerConfigs::getInstance()->getMsgFromXmlNode(ser_config.child("server"));
    ClientConfigs::getInstance()->getMsgFromXmlNode(ser_config.child("client"));

//    ServerOne one;
//    one.init();

//    ClientOne one;
//    one.init();
//    one.Connect();
//    cout<<"end"<<endl;

//    ServerTow two;
//    two.init();

//    ClientTwo two;
//    two.init();
//    two.Connect();

    ServerThree three;
    three.init();
}






