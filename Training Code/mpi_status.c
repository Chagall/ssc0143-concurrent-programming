#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main (int argc, char *argv[]){

	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;
	MPI_Status status;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else {
		printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
		for(int i = 1; i < comm_sz; i++){
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			printf("Message received from:");
			printf(" %d ", status.MPI_SOURCE);
			printf(", with tag: %d ", status.MPI_TAG);
			printf(", and error: %d\n", status.MPI_ERROR);
		}
	}

	MPI_Finalize();
	return 0;
}