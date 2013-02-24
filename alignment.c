#include<stdio.h>
#include<string.h>


#define ALIGNMENT_LENGTH 20
#define TRUE 1
#define FALSE 0

int main(){
	char filename[]="temp.c";
	FILE *fp=fopen(filename , "r" );
	int t=ALIGNMENT_LENGTH+1;
	char aligned_line[t];
	char broken_word[ALIGNMENT_LENGTH];
	int i=0 , j;
	 
	int EOF_flag=FALSE;


	//while( EOF_flag==FALSE ){
	for(j=0 ; j<5 ; j++ ) {
		for( ; i<t && ( *(aligned_line+i)=(char)fgetc(fp) )  != EOF ; i++ );

		char *temp=aligned_line+(i-1);
		if( *temp==EOF )EOF_flag=TRUE;

		if( *temp==' ' || *temp=='\t' ){
			broken_word[0]=*temp;
			*temp='\0';
		}
		else{
			for(i=0 ; !isspace(*temp) ; i++ ){
				*(broken_word+i)=*temp;
				temp--;
			}
			//*(broken_word+i)='\0';
			*(temp+1)='\0' ;
		}

		printf("%s$$", aligned_line );

		/*now fill the aligned_line, by broken_word, but in reverse order */
		int k=0;
		while(i>-1){
			*(aligned_line+k)=*(broken_word+i);
			k++;
			i--;
		}
		i=k+1;

	}
	//}



return 0;

}

