
// char * removebraces(char * str)
// {
// 	int i=0, j=0 ;
// 	char* str_no_spc= malloc(sizeof ( strlen(strd)));
	

// 	//Iterating each character of string.
//     while(str[i] != '\0')
//     {
//         if(str[i] != '[' &&  str[i] != ']')//Excluding brackets.
//         {
//             str_no_spc[j++] = str[i];
//         }
//         i++;
//     }
//     str_no_spc[j] = '\0';
    

// 	return str_no_spc;
// }



#include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <unistd.h>
	#include <string.h>
    
    int main(int argc, char *argv[])
    {
		#if 0
    	                 /* l_type   l_whence  l_start  l_len  l_pid   */
    	struct flock fl = { F_WRLCK, SEEK_SET, 0,       0,     0 };
    	int fd;
    
        fl.l_pid = getpid();
    
    	if (argc > 1) 
    		fl.l_type = F_RDLCK;
    

    	if ((fd = open("inputFilePath", O_RDWR)) == -1) {
    		perror("open");
    		exit(1);
    	}
    
    	
    	printf("Trying to get lock...");
    
    	if (fcntl(fd, F_SETLKW, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    
    	printf("got lock\n");
    	
    
    	fl.l_type = F_UNLCK;  /* set to unlock same region */
    
    	if (fcntl(fd, F_SETLK, &fl) == -1) {
    		perror("fcntl");
    		exit(1);
    	}
    
    	printf("Unlocked.\n");
    
    	close(fd);


		#endif

		 char ali[12] = "salih tangel";
         char * temp2 = malloc(11*sizeof(char)); // salih tangel  ali tangel

			
            memcpy(temp2, &ali[1],strlen(ali)-1 );
			temp2[strchr(temp2,'h')] = '\0';
			temp2
            printf("temp2: %s \n ",temp2);
    }
	