#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* replace(const char* in, const char* s, const char* r);

int main(){
	char in[100];
	char s[100];
	char r[100];
	
	scanf("%s%s%s",in,s,r);
	char* out=replace(in, s, r);
	printf("%s",out);
	free(out);
	return 0;
}


char* replace(const char* in, const char* s, const char* r){
	int in_size = strlen(in);
	int s_size = strlen(s);//size of substring to be replaced
	int r_size = strlen(r);//size of substring to replace with
	char* ptr;
	ptr = malloc((strlen(in)+0)*sizeof(char));//make ptr have same size of in
	int i=0;
	
	while(*(in + i)!='\0'){//make ptr equivalent to in
		*(ptr+i) = *(in+i);
		i++;
	}
	*(ptr+i)='\0';
	
	if(strstr(in,s)==NULL){//if s is never found in in, just return in unchanged
		return ptr;
	}else{
		i=0;
		char* tmp = strstr(ptr,s);//find where 1st instance of s is
		char* newptr = malloc((in_size-s_size+r_size+0)*sizeof(char));//allocate size of in plus size of r
		
		while((ptr+i)<tmp){//copy until we reach s
			*(newptr + i) = *(ptr + i);
			i++;
		}
		
		int j = i+s_size;
		int k = 0;
		while(k < r_size){//put r in where s was
			*(newptr + i) = *(r+k);
			//printf("%c \n",*(r+k));//debugging
			i++;
			k++;
			
		}
		
		while(j<in_size){//resume copying where we left off, skipping over s
			*(newptr + i) = *(ptr + j);
			//printf("%c ",*(newptr + i));//debugging
			//printf("%c \n",*(ptr + j));//debugging
			i++;
			j++;
		}
		*(newptr+i)='\0';
		free(ptr);//avoid memory leaks
		//return newptr;//debugging
		return replace(newptr, s, r);//recursive function to find any other/new instances of s
	}
		
}