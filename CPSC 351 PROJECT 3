#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

using namespace std;


int main(int argc, char** argv)
{
	/* Make sure the command line is correct */
	if (argc < 3)
	{
		cout << "FILE NAME missing\n";

		exit(1);
	}

	/* Open the specified file */
	int fd = open(argv[1], O_RDWR);


	if (fd < 0)
	{
		cout << "\n" << "input file cannot be opened" << "\n";
		exit(1);
	}

	int outputFD = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);

	if (outputFD < 0)
	{
		cout << "\n" << "Output file cannot be opened" << "\n";
		exit(1);
	}

	struct stat stats;
	if (stat(argv[1], &stats) == 0)
		cout << endl << "file size " << stats.st_size;
	else
		cout << "Unable to get file properties.\n";

	/* Get the page size  */
	int pagesize = getpagesize();
	cout << endl << "page size is " << pagesize << "\n";

	//Get total iterations to perform
	int iterations = stats.st_size / pagesize;
	//Last chunk
	if ( stats.st_size % pagesize != 0 )
	{
		iterations += 1;
	}
	//Setting the size of outputFile to inputFile
	ftruncate(outputFD, stats.st_size);
	char *data;
	for ( int i = 0 ; i < iterations ; i++ )
	{
		/* map the file into memory */
		data = (char*)mmap(NULL, pagesize, PROT_READ, MAP_SHARED, fd, i * pagesize );

		/* Did the mapping succeed ? */
		if (!data)
		{
			cout << "\n" << "mapping did not succeed" << "\n";
			exit(1);
		}

		char* outputData = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, outputFD, i * pagesize);
		/* Did the mapping succeed ? */
		if (!outputData)
		{
			cout << "\n" << "Mapping output file did not succeed" << "\n";
			exit(1);
		}
		
		/*Copy data from input file memory to output fle memory*/
		memcpy(outputData,data,pagesize);
		/* Unmap the shared memory region */
		munmap(data, pagesize);
		munmap(outputData, pagesize);

		//cout << "Total Iterations : " << iterations << " ,Current Iteration : " << i << endl;
	}
	
	/* Close the file */
	close(fd);
	close(outputFD);

	return 0;
}
