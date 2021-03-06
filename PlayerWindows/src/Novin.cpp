#include <Engine.h>
#include <iostream>

int main(int argc, char *argv[])
{
    printf("%s\n", argv[0]);
    if (argc < 2)
    {
        printf("ERROR - The Engine Requires a Path to a Project Directory!\n");
        return 1;
    }
    if (argc > 2)
    {
        printf("WARNING - The engine was started with to many Command line arguments!\n");
    }

    NV::Core::Engine instance;

    instance.Init(argv[1]);
    instance.Run();
    instance.Teardown();

    return 0;
}