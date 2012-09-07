#ifndef STREAMMAKER
#define STREAMMAKER

#include <fstream>
#include <string>

class TTree;
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

    private:
        /**
         * read the daqFile
         */
        void readDaqFile(const char* fileName);

    private:       
        TTree* m_dataStream;
        TTree* m_rawStream;
        std::string m_daqFileName;

        bool isDataStream;
        bool isRawStream;
};

#endif
