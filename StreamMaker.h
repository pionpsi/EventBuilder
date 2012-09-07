#ifndef STREAMMAKER
#define STREAMMAKER


class TTree;
class StreamMaker()
{
    public:
        StreamMaker();
        ~StreamMaker();

    public:
        void printInfo();

    private:
        void makeRawStream();
        void makeDataStream();

    private:       
        TTree* m_dataStream;
        TTree* m_rawStream;

        bool isDataStream;
        bool isRawStream;
}

#endif
