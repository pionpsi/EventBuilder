#include "StreamMaker.h"
#include <iostream>

#include <TTree.h>
#include <TFile.h>
int main()
{

    StreamMaker *stream = new StreamMaker("run_0191.run");
    stream->makeRawStream();

    TFile* f = new TFile("output.root","RECREATE");
    TTree* rawTree = stream->getStream();
    rawTree->Write();
    f->Close();
    
    //stream->makeDataStream();
}
