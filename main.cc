#include "StreamMaker.h"

#include <sstream>
#include <iostream>
#include <cstdlib>

#include <TTree.h>
#include <TFile.h>

int main(int argc, char**argv)
{
    if(argv[1])
    {
        std::string daqFileName     = argv[1];
        StreamMaker *stream = new StreamMaker(daqFileName);
        stream->makeRawStream();
        //stream->makeDataStream();


        /**Create outputfile*/
        //Nasty string operations
        std::stringstream ss;
        std::string outFileName;
        const char* daqFileBaseName = basename(daqFileName.c_str());
        ss <<daqFileBaseName;
        ss >> outFileName;
        outFileName.erase(outFileName.find(".run"));
        outFileName = outFileName +"_raw.root";
        TFile* f = new TFile(outFileName.c_str(),"RECREATE");
        
        TTree* rawTree = stream->getStream();
        std::cout <<"Stream: "<<rawTree->GetName() <<std::endl;
        rawTree->Write();
        f->Close();
    }
    else
    {
        std::cout <<"Expected a run file" <<std::endl;
    }
}
