#include<stdio.h>
#include<ctype.h>
int main(){
	int key;
	char pt[30];
	char ct[30];
	int a[30];
	printf("enter the plain text\n");
	scanf("%s",pt);
	printf("enter the key  .....\n");
	scanf("%d",&key);
	printf("\nTHE PLAIN TEXT : \n%s",pt);
	char r[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for(int i=0;pt[i]!='\0';i++){
		a[i]=tolower(pt[i]);
		int n1;
		int v=0;
		for(int j=0;r[j]!=a[i];j++){
			v++;
		}
		n1=v+key;
		if(n1>=0&&n1<=25){
			ct[i]=r[n1];
		}else if(n1>25){
			ct[i]=r[n1%25];
		}
		
	}
	printf("\n CIPHER TEXT : ......\n %s",ct);
	
}
