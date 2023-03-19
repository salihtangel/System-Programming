
#define _GNU_SOURCE
#define _POSIX_SOURCE
#include <fcntl.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#define FILEPATH 2

//remove braces
char * removeBraces(char * str)
{
	int i=0, j=0 ;
	char* str_no_spc= malloc(sizeof ( strlen(str)));
	

	//Iterating each character of string.
    while(str[i] != '\0')
    {
        if(str[i] != '[' &&  str[i] != ']')//Excluding brackets.
        {
            str_no_spc[j++] = str[i];
        }
        i++;
    }
    str_no_spc[j] = '\0';
    

	return str_no_spc;
}

int countBracesword(char *strd){

    char* strnew;
    strnew = malloc(2*sizeof ( strlen(strd)));

    strcpy(strnew,strd);
    int counter =0;

    while('\0' != *strnew ){

        if(']' == * strnew){
            return counter;
        }

        counter++;
        strnew++;

    }
    return -1;

}
// Function to replace a string with another
// string
char* replaceWord(const char* s, const char* oldW,
                  const char* newW, bool insensivitive)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;

    //if it is insensitive enter here
    if(insensivitive == true){
        while (*s) {
            // compare the substring with the result
            if (strcasestr(s, oldW) == s) {
                strcpy(&result[i], newW);
                i += newWlen;
                s += oldWlen;
            }
            else
                result[i++] = *s++;
        }


    }
    else if(insensivitive == false){
        while (*s) {
            // compare the substring with the result
            if (strstr(s, oldW) == s) {
                strcpy(&result[i], newW);
                i += newWlen;
                s += oldWlen;
            }
            else
                result[i++] = *s++;
        }
    }

    result[i] = '\0';
    return result;
}


int main(int argc, char *argv[]) {

    char recordToken[10][50];
    bool insensitive = false;
    const char *s = "/";
    int counter =0;
    int expression =0;

    int ret = 0, fd;
    char buf[1024] = {0};
    int i=0;
    size_t total_num_of_char;
    char * first;
    char * second;
    /* get the first token */
    //printf("%s\n",argv[1]);


                        /* l_type   l_whence  l_start  l_len  l_pid   */
    struct flock fl = { F_WRLCK, SEEK_SET, 0,       0,     0 };

   
    	
    
    	

    char *token = strtok(argv[1], s);



    /* walk through other tokens */
    while( token != NULL  ) {

        strcpy(recordToken[counter],token);

        //printf( "tokens:  %s\n", token );

        //printf("RT: %s \n",recordToken[counter-1]);

        if (  !strcmp (token,"i‘")  || !strcmp (token,"i;")) 
        {
            
            insensitive =true;
        }
        token = strtok(NULL, s);
        counter++;
    }

    
    //find the total number of char on the given files

    fl.l_pid = getpid();

    if (argc > 1) 
        fl.l_type = F_RDLCK;


    fd = open(argv[FILEPATH]   , O_RDWR );
    if (fd < 0) {
        perror("open() error");
        return ret;
    }
    

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("got lock\n");


    while ((ret = read(fd, buf, sizeof(buf)-1)) > 0) {
        i++;
        sleep(5);
    }

    //printf("\n");
    total_num_of_char = strlen(buf);
    printf("i=%d  - total number of char = strlen(buf)=%zu\n", i, total_num_of_char);


    char *lines = (char *) malloc(total_num_of_char * sizeof(char));
    memset(lines, 0, total_num_of_char * sizeof(char));
    lseek(fd, 0, SEEK_SET);
    i = 0;

    while ((ret = read(fd, buf, sizeof(buf)-1)) > 0)
    {
        // printf("ret: %d",ret);
        memcpy(lines + (1024 * i), buf, total_num_of_char);

        i++;
    }


    char* result =NULL;

    //if(recordToken[recordToken[3] == 'i'])

    if(recordToken[1][0] == '['){

            expression = 1;

            int wordlen = strlen(recordToken[1]);
            recordToken[1][wordlen] = '\0';
            char * a =NULL;
            a = removeBraces(recordToken[1]);


            first= malloc(sizeof ( strlen(a)));
            
            //str1 case
            *first = *a;
            a++;
            memcpy(++first,a,wordlen-2);
            //printf("HERE: %s\n",first);
    
           

            //ztr1 case
            a = removeBraces(recordToken[1]);
            second = malloc(sizeof(strlen(a)));
            char * temp =NULL;
            temp =second;
            *temp = *a;
            a++;
            a++;
            strcpy(++temp,a);
            
    }
    else if(recordToken[1][0] == '^'){
        for(int i = 0; i< 100; i++){
            if(buf[i] == '\n')
                printf("yeni satir %d",i);
        }
        char *temp = malloc(sizeof(recordToken[1]));

        //^ karakterini kaldirmak icin
        for(int i = 0; i < strlen(recordToken[1]) ;i++)
            temp[i]=recordToken[1][i+1];
        
        
        exit(1);
    }




    switch (expression)
    {
    case 1 :            //case[zstr] 
                result = replaceWord(lines,first,recordToken[2],insensitive);
                result = replaceWord(result,second,recordToken[2],insensitive);
        break;
    case 2 :            //case .
        break;      
    case 3 :
        break;
    case 4 :
        break;
    
    default:  
            result = replaceWord(lines,recordToken[1],recordToken[2],insensitive);
             //case a
        break;
    }

#if 0
    if(counter == 2){
        if(recordToken[0][0] == '['){

            //d) [zs]tr1 part
            int braceword = countBracesword(recordToken[0]) -1;

            printf("%s %d",removeBraces(recordToken[0]) , braceword);
            for(int i =0; i<braceword;i++){
                replaceWord(buf,recordToken[0],recordToken[1],false);
               // recordToken[0]*;
            }

        }
        //normal
        printf("%s",replaceWord(buf,recordToken[0],recordToken[1],insensitive));
    }
    else if( counter == 5){

        //if two times
        //send two times
        printf("insensivitive %d",insensitive);
        printf("%s",replaceWord(buf,recordToken[0],recordToken[3],insensitive));
        printf("%s",replaceWord(buf,recordToken[1],recordToken[4],insensitive));

    }

#endif

    lseek(fd, 0, SEEK_SET);
    memcpy(lines,result,strlen(result)+1);
    write(fd,lines, strlen(lines));
    //printf("%s\n",buf);
    printf("----------------------------\n");

    //printf("strlen(lines):%s ", lines);
    free(lines);
    //free(s);
    //free(token);


    fl.l_type = F_UNLCK;  /* set to unlock same region */
    
    	if (fcntl(fd, F_SETLK, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    
    	printf("Unlocked.\n");
    
    close(fd);
    //unlink("ls.output");
    return ret;
}
