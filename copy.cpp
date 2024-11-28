#include <fcntl.h>    // For open()
#include <unistd.h>   // For read(), write(), close()
#include <sys/stat.h> // For file permissions

#define BUFFER_SIZE 1024 // Size of the buffer for copying

int main(int argc, char *argv[])
{
    // Ensure the user has provided the correct arguments
    if (argc != 3)
    {
        write(2, "Usage: <program> <source_file> <destination_file>\n", 50);
        return 1;
    }

    const char *sourceFile = argv[1]; // Source file path
    const char *destFile = argv[2];   // Destination file path

    // Open the source file for reading
    int srcFd = open(sourceFile, O_RDONLY);
    if (srcFd == -1)
    {
        write(2, "Error opening source file\n", 26);
        return 1;
    }

    // Open/Create the destination file for writing
    // O_CREAT creates the file if it doesn't exist
    // O_TRUNC truncates it to zero length if it exists
    int destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (destFd == -1)
    {
        write(2, "Error opening destination file\n", 31);
        close(srcFd); // Close the source file before exiting
        return 1;
    }

    char buffer[BUFFER_SIZE]; // Buffer to hold data while copying
    ssize_t bytesRead, bytesWritten;

    // Read from the source and write to the destination
    while ((bytesRead = read(srcFd, buffer, BUFFER_SIZE)) > 0)
    {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten != bytesRead)
        {
            write(2, "Error writing to destination file\n", 34);
            close(srcFd);
            close(destFd);
            return 1;
        }
    }

    // Handle reading errors
    if (bytesRead == -1)
    {
        write(2, "Error reading from source file\n", 31);
    }

    // Close both the source and destination files
    close(srcFd);
    close(destFd);

    return 0;
}
