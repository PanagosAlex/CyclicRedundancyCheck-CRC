/*
* ΑΕΜ: 3782
* Ονοματεπώνυμο: Αλέξανδρος Πανάγος
*/

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string.h>

using namespace std;

int main() {
	int i,j,k=0,l,m=0,keylen,msglen,ran[20];
	char input[100], key[30],temp[30],quot[100],rem[30],key1[30],x_or[30],key2[30],rem1[30], *message;
	float sum,sum1,sum2;

	srand(time(0));
// input of the key
	cout<<("Enter Key: ");
	cin>>key;  
	strcpy(key2,key);
	for(l=0;l<100000;l++){ 
// the number of sequences that will be created
	strcpy(key,key2);
	for (i=0;i<10;i++) { 
// randon number generator for the 10 1s and 0s of the sequence
		if(rand()%2)
			input[i]='1';
		else
			input[i]='0';
	}
	keylen=strlen(key);
	msglen=10;
	strcpy(key1,key);
// Calculation of the FCS 
	for (i=0;i<keylen-1;i++) {
		input[msglen+i]='0';
	}
	for (i=0;i<keylen;i++)
	 temp[i]=input[i];
	for (i=0;i<msglen;i++) {
		quot[i]=temp[0];
		if(quot[i]=='0')
		 for (j=0;j<keylen;j++)
		 key[j]='0'; else
		 for (j=0;j<keylen;j++)
		 key[j]=key1[j];
		for (j=keylen-1;j>0;j--) {
			if(temp[j]==key[j])
			 rem[j-1]='0'; else
			 rem[j-1]='1';
		}
		rem[keylen-1]=input[i+keylen];
		strcpy(temp,rem);
	}
	strcpy(rem,temp);
// rinal sequence that arrives on the reciever
  cout<<"\nFinal data is: ";
	message = new char(msglen + keylen + 1);
    strcpy(message,input);
	for (i=0;i<5;i++)
    {
        message[i+10]=rem[i];
    }
	for (i=0;i<15;i++)
    {
        printf("%c",message[i]);
    }
    printf("\n");
// applying the BER equel to 0.001
    for( i = 0 ; i < 15 ; i++ )
    {
      ran[i]=rand()%1000; 
    }

    for( i = 0 ; i < 15 ; i++ ) {
      	if(ran[i]==1)
      	{
	        if(message[i]=='1')
	            message[i]='0';
	        else
	            message[i]='1';
        	m++;
    	}
    }
// calculating whether the sequence arrived accurately or inaccurately
	for( i = 0; i < 6 ; i++ )
    {
        x_or[i]=message[i];
    }
    for( i = 0; i < 6 ; i++ )
    {
        if(x_or[i]==key2[i])
            x_or[i]='0';
        else
            x_or[i]='1';
    }
    j=6;
    while(j < 16)
    {
        if(x_or[0]=='0')
        {
            // 1 digit rotation towards the left after the deletion of the first
            for(i=0;i<5;i++) 
            {
                x_or[i] = x_or[i+1];
            }
            x_or[5]=message[j++];
            continue;
        }
        for( i = 0; i < 6 ; i++ )
        {
            if(x_or[i]==key2[i])
                x_or[i]='0';
            else
                x_or[i]='1';
        }
    }
    j=0;
    for( i = 0; i < 5 ; i++ )
        if(x_or[i]=='0')
            j++;
        if(j==5)
            printf("The sequence arrived accuretely\n");
        else
        {
            printf("The sequence arrived inaccurately\n");
            k++;
        }
        }
// printing the final statistics of the algorithm
    sum=(float)(k);
    sum1=(float)(l);
    sum2=(float)(m);
	  cout<<"\nThe percentage which arrives with an error on the reciever is: "<<sum2/sum1*100<<"%"<<endl;
    cout<<"The percentage which the CRC spots an error occured is: "<<sum/sum1*100<<"%"<<endl;
    cout<<"The percentage which arrives with an error and CRC does not spot is: "<<(sum2-sum)/sum1*100<<"%"<<endl;
	return 0;
}