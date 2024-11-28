// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <string.h>
// int main() {
//     int fd = 0;

//     fd = open("./file.txt", O_RDWR);
//     if(-1 == fd) {
//         printf("open fail\n");
//         return 1;
//     }else {
//         printf("open ok\n");
//     }

//     char buf[] = "Steve Yu, today is nice";
//     write(fd, (void *)buf, strlen(buf));

//     lseek(fd, SEEK_SET, 0);

//     char buf2[30] = {0};
//     read(fd, buf2, sizeof(buf));

//     puts(buf2);

//     close(fd);
//     return 0;
// }

