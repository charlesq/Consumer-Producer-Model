#include <iostream>
#include <cstring>
#include "../inc/ThreadModelOne.h"
#include "../inc/ThreadModelDeadlock.h"

static void usage(void)
{
    /* will switch to getOption() later */
    std::cout << "Please specify ThreadModel followed by other required arguments " << std::endl;
    std::cout << "  In the case of (ThreadModelOne 2 Consumers, 3 Producers, 5 BufferItems Per BufferQueue): "<< std::endl;
    std::cout << "              ./cp ThreadModelOne 2 3 5" << std::endl;
    std::cout << "  In the case of (ThreadModelDeadlock 2 superworkers, 2 BufferItems Per BufferQueue):" <<  std::endl; 
    std::cout << "              ./cp ThreadModelDeadlock 2 2" << std::endl;
}

void handleThreadModelOne(int argc, char *argv[])
{
    if (argc < 5)
    {
        usage();
        exit(1);
    }
    int numCon, numPro, numBuf;
    numCon = atoi(argv[2]);
    numPro = atoi(argv[3]);
    numBuf = atoi(argv[4]);
    ThreadModelOne tm1(numCon, numPro, numBuf);
    tm1.run();
}

void handleThreadModelDeadlock(int argc, char *argv[])
{
    int numSuper, numBuf;
    if (argc < 4)
    {
        usage();
        exit(1);
    }
    numSuper = atoi(argv[2]);
    numBuf = atoi(argv[3]);
    ThreadModelDeadlock tmd(numSuper, numBuf);
    tmd.run();
}

int main(int argc, char *argv[])
{
   
    if (argc < 2)
    {
        usage();
        exit(1);
    }
    if (strcmp(argv[1], "ThreadModelOne") == 0)
        handleThreadModelOne(argc, argv);
    else if (strcmp(argv[1], "ThreadModelDeadlock") == 0)
       handleThreadModelDeadlock(argc,argv);
    else
       std::cout << "Other model not ready yet" << std::endl;

    return 0;
}

