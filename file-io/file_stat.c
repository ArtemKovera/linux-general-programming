/*
    Program demonstrating how to examine the file's attributes
    (the file's path name is given to the program as a command line argument)
*/
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>
#include<sys/sysmacros.h>


int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_path_name>\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    struct stat sb;                                                   //stat buffer

    if(stat(argv[1], &sb) != 0)
    {
        perror("stat()");
        exit(EXIT_FAILURE);
    }

    int flag = 1;
    
    printf("ID of containing device:  [%lx,%lx]\n", (long) major(sb.st_dev), (long) minor(sb.st_dev));
    printf("Inode number: %u\n", sb.st_ino);
    printf("File type: ");    
    switch (sb.st_mode & S_IFMT) 
    {
        case S_IFBLK:  printf("block device\n");                  break;
        case S_IFCHR:  printf("character device\n");              break;
        case S_IFDIR:  printf("directory\n");        flag = 0;    break;         
        case S_IFIFO:  printf("FIFO/pipe\n");                     break;
        case S_IFLNK:  printf("symlink\n");                       break;
        case S_IFREG:  printf("regular file\n");                  break;
        case S_IFSOCK: printf("socket\n");                        break;
        default:       printf("unknown?\n");                      break;
    }

    if(flag)
        printf("Number of hard linkes: %u\n", sb.st_nlink);

    printf("User ID of owner: %u\n", sb.st_uid);
    printf("Group ID of owner: %u\n", sb.st_gid);
    printf("Total size, in bytes: %ld\n", sb.st_size);
    printf("Block size for filesystem I/O: %ld\n", sb.st_blksize);
    printf("Number of 512B blocks allocated: %ld\n", sb.st_blocks);
    printf("last accessed: %s", ctime(&sb.st_atim));
    printf("last modified: %s", ctime(&sb.st_mtim));
    printf("last changed:  %s", ctime(&sb.st_ctim));
    
    printf("Permissions: %c%c%c%c%c%c%c%c%c\n",
           (sb.st_mode & S_IRUSR) ? 'r' : '-',
           (sb.st_mode & S_IWUSR) ? 'w' : '-',
           (sb.st_mode & S_IXUSR) ? 'x' : '-',
           (sb.st_mode & S_IRGRP) ? 'r' : '-',
           (sb.st_mode & S_IWGRP) ? 'w' : '-',
           (sb.st_mode & S_IXGRP) ? 'x' : '-',
           (sb.st_mode & S_IROTH) ? 'r' : '-',
           (sb.st_mode & S_IWOTH) ? 'w' : '-',
           (sb.st_mode & S_IXOTH) ? 'x' : '-'
          );
    
    
    return 0;
}