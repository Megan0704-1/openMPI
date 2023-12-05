#include <iostream>
#include <mpi.h>

using namespace std;

int main(int arg, char *argv[]){
    int rank;
    int size;
    char name[80];

    int length;

    MPI_Init(&arg, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(name, &length);

    cout << "Rank: " << rank << " size: " << size << " on " << name << endl;

    MPI_Finalize();

    return 0;
}
