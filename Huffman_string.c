#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct table
{
	char word[50];
	int freq;
	char code[10];
}TABLE;


typedef struct node
{
	char str[1000];
	int freq;
	struct node *left, *right,*next;
}NODE;

typedef struct PQueue
{
	NODE* head;
	int no_of_nodes;
}PQ;

typedef struct HuffTree
{
	NODE* root;
}H_TREE;

typedef NODE* ele_t;


//functions for table
void initTable(TABLE []);

//functions for priority queue
void initQ(PQ* q);
void createQueue (PQ *q, TABLE []);
void Enqueue(PQ* q,ele_t t);
NODE* smallestNode(PQ* q);
NODE* Dequeue(PQ* q);
void Print(PQ* q);

//functions for huffman tree
void initTree(H_TREE*);
NODE* constructHuffmanTree(PQ *q);

void initTree(H_TREE* t) //Initialises the root of the tree to NULL.
{
	t->root=NULL;
}

NODE* newNode() //Creates a new node and returns its address.
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->left = temp->right = NULL;
	return temp;
}

void initTable (TABLE t[]) //Initialises the frequencies of all table elements to zero.
{
	int i;
	for (i=0;i<257;i++)
	t[i].freq=0;
}
//j=0;
void CreateTable (char ipstr[],TABLE t[]) //Creates a character-frequency table from a string
{
	int i,j,chk;
	//for (i=0;ipstr[i]!='\0';i++)
	//{
		chk=0;
		//char x=ipstr[i];
		j=0;
		while (t[j].freq!=0)
		{
			if (strcmp(t[j].word,ipstr) ==0)   //if (t[j].c==x)
			{
				t[j].freq++;
				chk=1;
				break;
			}
			j++;
		}
		if (!chk)
		{
			strcpy(t[j].word, ipstr);
			t[j].freq++;
		}
	//}
}

/*void CreateTable2(TABLE t[])
{
	int chk=1, i=0,freq;
	char c;
	while (chk)
	{
		printf("Enter character and its frequency:\n");
		fflush(stdin);
		scanf("%c%d",&c,&freq);
		
		//scanf("%d",&freq);
		t[i].c = c;
		t[i].freq = freq;
		i++;
		printf("Enter 0 to stop, any other number to enter more entries: ");
		fflush(stdin);
		scanf("%d",&chk);
	}
} */
NODE* initNode(char str[], int f)
{
	NODE* node=(NODE*)malloc(sizeof(NODE));
	strcpy(node->str, str);
	node->freq = f;
	node->left = node->right = node->next=NULL;
	return node;
}
void createQueue (PQ *q, TABLE t[])
{
	NODE* node; char str[2];
	for (int i=0;i<257;i++)
	{
		if (t[i].freq!=0)
		{
			//printf("%c",i);
			//system("pause");
			//str[0] = t[i].c;
			//str[1] = '\0';
			//printf("%s",str);
			//a={t[i].c, t[i].freq, NULL, NULL, NULL}
			node = initNode(t[i].word, t[i].freq);
			Enqueue (q, node);
		}
	}
	
	//NODE a4={"D",1,NULL,NULL,NULL};
	//Enqueue (&q,&a1);
}

NODE* constructHuffmanTree(PQ *q)
{
	int i =0 ; char str1[257],str2[257],str3[257];
	NODE *t,*t1,*t2;
	//t = newNode();

	while (q->no_of_nodes>1)
	{		
		//Print(q);
		//system("pause");
		t=newNode();
		t1 = Dequeue(q);
		t2 = Dequeue(q);
		//printf("%s, %s\n",t1->str,t2->str);
		//system("pause");
		strcpy(str1,t1->str);
		str1[strlen(str1)]='\0';
		strcpy(str2,t2->str);
		str2[strlen(str2)]='\0';
		strcpy(str3,str1);
		strcat(str3,str2);
		str3[strlen(str3)]='\0';
		//printf("%s, %s, %s\n",str1,str2,str3);
		//system("pause");
		strcpy(t->str,str3);
		t->freq = t1->freq+t2->freq;
		t->right = t2;//has been interchanged
		t->left = t1;
		
		Enqueue(q,t);
	}
	
	return Dequeue(q);
		
	
}

void inorder(NODE* root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	printf("%d--%s ",root->freq,root->str);
	inorder(root->right);
}

void initQ(PQ* q)
{
	q->head = NULL;
	q->no_of_nodes = 0;
}

void Enqueue(PQ* q,NODE* t)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode=t;
	//strcpy(newNode->str,STR);
	newNode->next = NULL;

	if(q->head == NULL)
	{
		q->head = newNode;
		q->no_of_nodes++;
		return;
	}

	NODE* temp = q->head;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next = newNode;
	q->no_of_nodes++;
}

NODE* smallestNode(PQ* q)
{
	NODE* smallest = q->head;//if u set to NULL then if largest is the first element then NULL
	// is returned which is wrong!!
	//printf("Worked till here!!\n");
	NODE* current = q->head;

	if(q->head == NULL)
		return NULL;

	int minfreq = q->head->freq;
	while(current!=NULL)
	{
		if(current->freq<minfreq)
		{
			minfreq = current->freq;
			smallest = current;
		}


		current = current->next;
	}

	return smallest;

}

void Print(PQ* q)
{
	if(q->head == NULL)
		{
			printf("Queue is empty\n");
			return;
		}
	NODE* temp = q->head;
	while(temp!=NULL)
	{
		printf("%d--%s ",temp->freq,temp->str);
		temp = temp->next;
	}
	printf("\n");
}

NODE* Dequeue(PQ* q)
{
	if(q->head == NULL)
		return NULL;

	NODE* smallest = smallestNode(q);
	NODE* curr  = q->head;
	NODE* prev = NULL;
	
	//if only one node is present then it is the largest node
	if(q->head->freq == smallest->freq && q->head->next == NULL)
	{
		NODE* temp = q->head;
		//free(q->head);
		q->no_of_nodes--;
		q->head = NULL;
		return temp;
	}

	//if first node is smallest node and it is not the only node
	if (q->head->freq==smallest->freq)
	{
		NODE* temp=q->head;
		q->head=q->head->next;
		q->no_of_nodes--;
		return temp;
	}
	while(curr->freq!=smallest->freq && curr!=NULL)
	{
		prev=curr;
		curr = curr->next;
	}

	prev->next = curr->next;
	NODE* temp = curr;
	//free(curr);
	q->no_of_nodes--;
	return temp;
}
int getPos(TABLE table[], char c[])
{
	int i,k;
	for (i=0;i<257;i++)
	{
		if (strcmp(table[i].word,c)==0)//if (table[i].c ==c)
		{
			k=i;
			break;
		}
	}
	return k;
}
void assignCodes(NODE* root,TABLE table[],char arr[],int top)
{
	char c[1000];
	if(root == NULL)
		return;

	if(root->left!=NULL)
	{
		arr[top] = '0';
		assignCodes(root->left,table,arr,top+1);
	}

	if(root->right!=NULL)
	{
		arr[top] = '1';
		assignCodes(root->right,table,arr,top+1);
	}

	if(root->left == NULL && root->right == NULL)
	{
		arr[top] = '\0';
		strcpy(c,root->str);
		int pos = getPos(table,c);
		strcpy(table[pos].code,arr); 
	}

}

void printCode(TABLE table[])
{
	int i;
	printf("\nCharacter -- Frequency -- Code\n");
	for(i=0;i<257;i++)
	{
		if(table[i].freq!=0)
		{
			printf("%s -- %d -- %s\n",table[i].word,table[i].freq,table[i].code);
		}
	}
}

char codeMatch(TABLE tab[], char tempstr[])
{
	int i;
	int c=-1;
	for (i=0;tab[i].freq!=0;i++)
	{
		if (strcmp(tempstr,tab[i].code) ==0)
		{
			c = i;
			break;
		}
	}
	return c;
}

void decodeCodes (TABLE tab[],char decodstr[])
{
	int i,j=0;
	int k=0;
	
	char tempstr[1000];
	char outputstr[100];
	strcpy(outputstr,"");
	for (i=0;decodstr[i]!='\0';i++)
	{
		tempstr[j] = decodstr[i];
		j++;
		tempstr[j] = '\0';
		int x = codeMatch(tab,tempstr);
		if (x>=0)
		{
			strcat(outputstr,tab[x].word);  //Append the string in xth index of the table.
			strcat(outputstr," ");
			//k++;
			j=0;
		}
	}
	if (strlen(outputstr)>0)
	printf("Output string is: %s\n",outputstr);
	else
	printf("You did not enter a valid bitstring.\n");
}

/*void CompareHuffmanASCII(char ipstr[], char finaloutput[])  //Compares the size (in bytes) between Huffman and ASCII Representation of the input string.
{
	int ascii_final = strlen(ipstr)*7;
	int huffman_final = strlen(finaloutput);

	if(ascii_final > huffman_final)
	{
		printf("Number of bytes used for ASCII representation is %d\nNumber of bytes used by Huffman Coding is %d\n",ascii_final,huffman_final);
		printf("The compression percentage is: %f\n", (((ascii_final-huffman_final)*1.0/ascii_final)*100.0) );
		printf("Huffman is therefore Superior to ASCII representation\n");
	}
	else
	{
		printf("Number of bytes used for ASCII representation is %d\nNumber of bytes used by Huffman Coding is %d\n",ascii_final,huffman_final);
		printf("ASCII is therefore Superior to Huffman representation\n");
	}
}*/


void printHuffCode(TABLE tab[],char ipstr[][50],char ipstr2[])  //Prints the huffman code for the input string.
{
	int i;
	char finaloutput[1000];
	strcpy(finaloutput,"");
	for (i=0;i<10000;i++)
	{
		//printf("%d",&i);
		int x = getPos(tab,ipstr[i]);
		strcat(finaloutput,tab[x].code);
	}
	printf("\nThe huffman code for %s is: %s\n",ipstr2,finaloutput);
	//Place compare function here.
	//CompareHuffmanASCII(ipstr, finaloutput);
	printf("After decoding, ");
	decodeCodes (tab,finaloutput);
}

int main()
{
	int ch,i,j=0;
	char ipstr[1000]; 
	char ipstr_lc[1000];
	char decodstr[1000];
	char tempstr[50];
	char arr[10];
	char divwords[10000][50];
	int wordindex;
	TABLE tab[257];
	printf("Enter 1 for input through string\nEnter 2 for input through file: ");
	scanf("%d",&ch);
	int ipstr_index=0;
	if (ch==2)
	{
		FILE *fp;
		char fname[500];
		printf("Enter name of the file including extension: ");
		fflush(stdin);
		gets(fname);
		fp = fopen (fname,"r");
		if (!(fp))
		{
			printf("You did not enter a valid file name");
			return 0;
		}
		char c;
		while((c = fgetc(fp))!=EOF)
		{
			ipstr[ipstr_index++] = c;
		}
		ipstr[ipstr_index] = '\0';
		fclose(fp);
	}
	else
	{
		fflush(stdin);
		
		printf("Enter the input string: ");
		gets(ipstr);    //Say, input is "the weather today is the best in the world" */
	}
		
		strcpy (ipstr_lc, strlwr(ipstr));
		initTable(tab);
		for (i=0;ipstr_lc[i]!='\0';i++)
		{
			wordindex = 0;
			char temp = ipstr_lc[i];
			if (isalnum(temp) || temp=='-')
			{
				tempstr[j] = temp;
				j++;
			}
			else
			{
				tempstr[j] = '\0';
				//tempstr contains a word
				
				if (strlen(tempstr)!=0)
				{
				
					CreateTable (tempstr,tab);
					j=0;
					strcpy(divwords[wordindex],tempstr);
					wordindex++;
				}
			}
		}
		tempstr[j] = '\0';
		if (strlen(tempstr)!=0)
				{
				
					CreateTable (tempstr,tab);
					j=0;
					strcpy(divwords[wordindex],tempstr);
					wordindex++;
				}
		//CreateTable(ipstr,tab);
	
	/*else
	{
		printf("Sorry!!!");
		return 0;
		//initTable(tab);
		//CreateTable2(tab);
	}*/
	PQ q;
	initQ(&q);
		
	H_TREE t;
	initTree(&t);
	
	createQueue(&q, tab);
	


	//Print(&q);
	//system("pause");
	t.root = constructHuffmanTree(&q);
	printf("\nInorder Output\n");
	
	inorder(t.root);

	assignCodes(t.root,tab,arr,0);

	printCode(tab);
	system("pause");
	
	/*for (i=0;i<100000;i++)
	{
		char tmp[70];
		strcpy(tmp,wordindex[i]);
		
	}*/
	printHuffCode (tab,divwords,ipstr);
	//Now for the reverse process.
	int uch = 0;
	printf("Do you want to perform decoding or not? (0-No, Any other-Yes): ");
	scanf("%d",&uch);
	if (uch)
	{
	printf("Now for the decoding process\n");
	printf("Enter a valid codestring: ");
	scanf("%s",decodstr);
	decodeCodes (tab,decodstr);
	}

	return 0; 
}
