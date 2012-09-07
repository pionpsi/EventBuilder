#include "StreamMaker.h"
#include <iostream>

int main()
{
    StreamMaker *stream = new StreamMaker("run_0191.run");
    stream->makeRawStream();
}
