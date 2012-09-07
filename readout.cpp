//Test we do:
//- Check the 20 x 0xFF
//- Check for 0xCCCCCCCC in front of each event
//- Check that the event counter is working properly
//- Check that the file header corresponds to the event headers
//- Check that there are no additional bytes in an event
//- Check that there is no data point above 16384 (14bit)s

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<stdlib.h>
#include<string>
#include<vector>

using namespace std;

void readout ()
{

//Define the Headvariables
char fileName[] = "run_0191.run";

FILE * file;
unsigned int nChannel;
unsigned int lEvent;
unsigned int runNo;
string date;


//Read the Header
ifstream fileH (fileName);
	//Run-Number
	string temp;
	getline(fileH, temp);
	istringstream ss(temp);
	ss >> runNo;
	//Time-Stamp
	getline(fileH, date);
	//Number of channels
	getline(fileH, temp);
	istringstream ss2(temp);
	ss2 >> nChannel;
	//Eventlength	
	getline(fileH, temp);
	istringstream ss3(temp);
	ss3 >> lEvent;
//Display header
cout << "run number: " << runNo << endl << "date: " << date << endl << "number of channels: " << nChannel << endl << "event length: " << lEvent << endl;;

fileH.close();

//Create a root file and tree

TFile * f = new TFile("out.root","RECREATE");
TTree * tree = new TTree("myTree","rawData");

//Define the required branches
unsigned long bEventNo;
unsigned long bTStamp;

vector<unsigned short> channel0;
vector<unsigned short> channel1;
vector<unsigned short> channel2;
vector<unsigned short> channel3;
vector<unsigned short> channel4;
vector<unsigned short> channel5;
vector<unsigned short> channel6;

tree->Branch("eventNo/l",&bEventNo);
tree->Branch("TStamp/l",&bTStamp);

tree->Branch("channel0",&channel0);
tree->Branch("channel1",&channel1);
tree->Branch("channel2",&channel2);
tree->Branch("channel3",&channel3);
tree->Branch("channel4",&channel4);
tree->Branch("channel5",&channel5);
tree->Branch("channel6",&channel6);


	//Read binary
	file = fopen(fileName,"rb");

	//The following buffer are used to read the binary data into
	short buffers = 0;
	int buffer = 0;
	long bufferl = 0;
	unsigned int count = 0;
	unsigned long eventNo = 0;
	unsigned long TStamp = 0;


	
	//Read the file up to 20 times 0xFF or an time out
	unsigned int fcount = 0;
	while(fcount<20) 
	{
		fread(&buffers,1,1,file);
		if(buffers == 0xFF) 
		{
			fcount++;
		}
		else 
		{
			fcount = 0;
		}
		count++;
		//output the data in hex and char.
		//cout << std::dec << count << "\t" <<std::hex << *buffer << "\t" << char(*buffer) << endl;

		//error, if can't find the 40 F within the first 1000 bytes.
		if(count > 1000)
		{
			cout << "Error: Corrupt Header, 10 x 0xFFFF is missing within the first 1000 bytes." << endl;
			return 1;
		}
	}




	//Reads the rest of the file
	while(fread(&bufferl,4,1,file)) 
	{
		//Test, if each data block starts with 0xCCCCCCCC
		if(bufferl == 0xCCCCCCCC) 
		{
		//Read out the event header and check it against the file header values
			fread(&bufferl,4,1,file);
			if(bufferl != eventNo++ ) 
			{
			cout << "Error: Event number in event header doesn't match to the internal counter.";
			break;
			}
			fread(&TStamp,4,1,file);
			//cout << "Event: " << std::dec << eventNo-1 << "(" << TStamp << ")" << endl;

			fread(&bufferl,4,1,file);
			if(bufferl != (unsigned long)nChannel)
			{
				cout << "Error: File Size in Event-block and header don't match." << endl;;
				break;
			}

			fread(&bufferl,4,1,file);
			if(bufferl != (unsigned long)lEvent)
			{
			cout << "Error: File Size in Event-block and header don't match." << endl;;
			break;
			}
		
			//Root header data
			bEventNo = eventNo;
			bTStamp = TStamp;		
			
			channel0.clear();
			channel1.clear();
			channel2.clear();
			channel3.clear();
			channel4.clear();
			channel5.clear();
			channel6.clear();

			//Read the waveforms of the events
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel0.push_back(buffer);
			}
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel1.push_back(buffer);
			}
			
			
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel2.push_back(buffer);		
			}
			
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel3.push_back(buffer);		
			}
			
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel4.push_back(buffer);		
			}
		
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel5.push_back(buffer);		
			}
			
			for(int i=0;i<(lEvent);i++)
			{
				fread(&buffer,2,1,file);
				if(buffer >= 16384) 
				{
					cout << "Error: There is a value bigger then 2^14 in the data part.";
					break;
				}
				channel6.push_back(buffer);
			}

	
			//Fill root tree	
			tree->Fill();
		}
		else 
		{
			cout << "Error: Corrupt data structur" << endl;		
		}
		
	}
	cout << "number of events: " << eventNo - 1 << endl;
	//Write tree and close files.

	fclose(file);
	tree->Write();
	tree->Scan();
	f->Close();
	
}

