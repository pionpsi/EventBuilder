#include "StreamMaker.h"
#include <iostream>

#include <TTree.h>
#include <TFile.h>

int main(int argc, char**argv)
{
    if(argv[1])
    {
        std::string daqFileName     = argv[1];
        StreamMaker *stream = new StreamMaker(daqFileName);
        stream->makeRawStream();

        TFile* f = new TFile("output.root","RECREATE");
        TTree* rawTree = stream->getStream();
        rawTree->Write();
        f->Close();
        
        //stream->makeDataStream();
    }
    else
    {
        std::cout <<"Expected a run file" <<std::endl;
    }
}
