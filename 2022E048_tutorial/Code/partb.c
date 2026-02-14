#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int numtasks, rank, dest, source, rc, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status Stat;

    MPI_Init(&argc, &argv); // Initializes the MPI environment [cite: 5, 90]
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // Gets total tasks [cite: 10, 91]
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Gets the unique rank of this process [cite: 15, 92]

    if (rank == 0) {
        dest = 1;
        source = 1;
        // Rank 0 sends 'x' to Rank 1 [cite: 96]
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        // Rank 0 waits to receive a message back from Rank 1 [cite: 97]
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        printf("Rank %d received message: %c from rank %d\n", rank, inmsg, source);
    } 
    else if (rank == 1) {
        dest = 0;
        source = 0;
        // Rank 1 waits to receive from Rank 0 [cite: 101]
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        // Rank 1 sends 'x' to Rank 0 [cite: 103]
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf("Rank %d received message: %c from rank %d\n", rank, inmsg, source);
    }

    MPI_Finalize(); // Terminates the MPI environment [cite: 47, 105]
    return 0;
}