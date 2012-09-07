#include "StreamMaker.h"

#include <TTree.h>


StreamMaker::StreamMaker()
{
    
    m_dataStream    =   new TTree("dataTree","Data Trees");
    m_rawStream     =   new TTree("rawTree","Raw Trees");
}

StreamMaker::~StreamMaker()
{}

void StreamMaker::printInfo()
{}

void makeRawStream()
{
}

void makeDataStream()
{
}
