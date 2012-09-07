#ifndef STREAMMAKER
#define STREAMMAKER

#include <fstream>
#include <string>
#include <vector>

class TTree;
class TFile;

class StreamMaker
{
    public:
        /**
         * Pass the run file name to build ntuples(TTree)
         */
        StreamMaker(std::string daqFileName);
        ~StreamMaker();

    public:
        /**
         * Make Event Building verbose
         */
        void printInfo();

        /**
         * Make the raw stream
         */
        void makeRawStream();

        /**
         * Make the data stream
         */
        void makeDataStream();

        /**
         * save tree in a file
         */
        void writeTree(std::string rootFileName);

        /**
         * Return the TTree
         */
        TTree* getStream();

    private:
        /**
         * Fill the Trees
         */
        void fillTree();


        /**
         * get the Run Number from the daq file extension
         */
        std::string getRunNumber();

    private:       
        TTree* m_tree;
        std::string m_daqFileName;

        const static unsigned int NCHANNEL = 7;

        bool isDataStream;
        bool isRawStream;

        std::vector<std::vector<unsigned short> > m_channels;
};

#endif
