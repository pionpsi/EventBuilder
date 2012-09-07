#include "StreamMaker.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <TTree.h>


StreamMaker::StreamMaker(std::string fileName):
    m_dataStream(0),
    m_rawStream(0),
    m_daqFileName(fileName)
{
    this->readDaqFile(fileName.c_str());
}

StreamMaker::~StreamMaker()
{}

void StreamMaker::printInfo()
{}


void StreamMaker::readDaqFile(const char* fileName)
{
    //First Read the File Header
    unsigned int nChannel;
    unsigned int lEvent;
    unsigned int runNo;
    std::string date;


    //Read the Header
    ifstream fileH (fileName);
	//Run-Number
    std::string temp;
	getline(fileH, temp);
    std::istringstream ss(temp);
	ss >> runNo;
	//Time-Stamp
	getline(fileH, date);
	//Number of channels
	getline(fileH, temp);
    std::istringstream ss2(temp);
	ss2 >> nChannel;
	//Eventlength	
	getline(fileH, temp);
    std::istringstream ss3(temp);
	ss3 >> lEvent;


    ///////////////////////////////////////////////////////
    // Read the binary data from the file
    FILE *file;
    file    = fopen(fileName,"rb");
    ///////////////////////////////////////////////////////
    //The Following buffers are used to read the binary data
    //

	short buffers           = 0;
	int buffer              = 0;
	unsigned long bufferL   = 0;
	unsigned int count      = 0;
	unsigned long eventNo   = 0;
	unsigned long TStamp    = 0;
    
    //Read the file up to 20 times 0xFF or a time out
    unsigned int fcount = 0;
    while(fcount <20)
    {
        fread(&buffers,1,1,file);
        if(buffers  == 0xFF)
        {
            ++fcount;
        }
        else
        {
            //Check this condition once again. 
            fcount = 0;
        }
        count++;

        if(count >1000)
        {
            std::cout << "Error: Corrupt Header, 10, x 0xFF is missing withing the first " <<count <<" bytes" <<std::endl;
            break;
        }
    }

    //Read the rest of the file
    while(fread(&bufferL,4,1,file))
    {
        //Test if each block starts with 0xCCCCCCC
        if(bufferL  == 0xCCCCCCCC)
        {
            //Read out the event header and check it against the file header values
			fread(&bufferL,4,1,file);
			if(bufferL != eventNo++ ) 
			{
                std::cout << "Error: Event number in event header doesn't match to the internal counter."<<std::endl;
                break;
			}
			fread(&TStamp,4,1,file);
			//cout << "Event: " << std::dec << eventNo-1 << "(" << TStamp << ")" << endl;

			fread(&bufferL,4,1,file);
			if(bufferL != (unsigned long)nChannel)
			{
                std::cout << "Error: File Size in Event-block and header don't match." << std::endl;;
				break;
			}

			fread(&bufferL,4,1,file);
			if(bufferL != (unsigned long)lEvent)
			{
                std::cout << "Error: File Size in Event-block and header don't match." << std::endl;
                break;
			}
			
			for (int i = 0; i < 7; ++i)
			{
				//vector<unsigned short> & channel = channels.at(i);
				//channel.clear();
				
				//Read the waveforms of the events
				for (unsigned int j = 0; j < lEvent; ++j)
				{
					fread(&buffer,2,1,file);
					if(buffer >= 16384) 
					{
                        std::cout << "Error: There is a value bigger then 2^14 in the data part."<<std::endl;
						break;
					}
					//channel.push_back(buffer);
				}
			}
		}
		else 
		{
            std::cout << "Error: Corrupt data structur" << std::endl;
        }
    }
}

void StreamMaker::makeRawStream()
{
    //trim the .run extension of the daqfilename and name the tree 
    std::string runNum  = m_daqFileName.erase(m_daqFileName.find(".run"));
    m_rawStream         = new TTree(runNum.c_str(),"rawfilename");
    std::cout << "Raw File Name: " << m_rawStream->GetName() <<std::endl;
}

void StreamMaker::makeDataStream()
{
}
