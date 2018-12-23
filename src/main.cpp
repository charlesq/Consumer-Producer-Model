#include <iostream>
#include "../inc/ThreadModelOne.h"

static void usage(void)
{
    std::cout << "please specify number of consumers and number of producers and number of bufferItems on commandline" << std::endl;
    std::cout << "  example:  the case of (2 consumers, 3 producers, 5 bufferItesm): "<< std::endl;
    std::cout << "              ./cp 2 3 5" << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        usage();
        exit(1);
    }
    int numCon, numPro, numBuf;
    numCon = atoi(argv[1]);
    numPro = atoi(argv[2]);
    numBuf = atoi(argv[3]);
    ThreadModelOne tm1(numCon, numPro, numBuf);
    tm1.run();
    std::cout << "print data" << std::endl;
    return 0;
}

