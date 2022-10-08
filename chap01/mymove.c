#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 9999

void error_handling(char *message);

/* 조건
1. open(), read(), write() 함수 사용
2. Command line에서 source file 및 destination file 이름을 직접 입력 -> 미입력시 에러
3. 원본파일의 크기와 이동된 파일의 크기는 동일해야 됨
*/

int main(int argc, char *argv[]){
    if(argc<3){
        error_handling("[Error] mymove Usage: ./mymove src_file dest_file");
    }

    // 변수 선언
    int f1, f2;
    int f1_size, f2_size;
    char buf[BUF_SIZE]; 

    // source file 읽기
    f1 = open(argv[1], O_RDONLY);
    if(f1 == -1){
        error_handling("source file open() error!");
    }
    f1_size = read(f1, buf, sizeof(buf));
    // printf("%d - %s", f1_size, buf);
    close(f1);

    // destination file 생성 및 쓰기
    f2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (f2 == -1)
        error_handling("destination file open() error!");
    f2_size = write(f2, buf, f1_size);
    // printf("%d - %s", f2_size, buf);
    close(f2);

    // 원본파일의 크기와 이동된 파일의 크기는 동일한지 확인
    if(f1_size == f2_size){
        printf("move from %s to %s (bytes: %d) finished.\n", argv[1], argv[2], f2_size);
        remove(argv[1]);
    }
    else{
        error_handling("write() error!");
    }
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}