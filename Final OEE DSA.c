#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<dos.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

#define MAX 100
#define MAX_QUEUE 100
#define V_SIZE  100

#define STACKSIZE 6
#define TRUE 1
#define FALSE 0

#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=true;goto ExitJmp;

int currnodes=0;
int count=0;

int i,s;
int j,t;
int b,k;
int c,size;

int a[MAX];
int level[V_SIZE];

//Defining structure node

struct node
{
    char info[50];
    struct node *next;
    struct node *prev;
};
typedef struct node NODE;

int currnode = 0;

//Defining structure dqueue

struct dqueue
{
    int rear;
    int front;
    int data[MAX_QUEUE];

};

//Defining structure squeue

struct squeue
{
    int rear;
    int front;
    char ad[MAX_QUEUE][50];
};

typedef struct squeue QUEUES;

typedef struct dqueue QUEUED;

//Defining structure message

struct message
{
    char message_data[100];
    int hour[2];
};

//Defining stack

struct stack
{
    int top;
    int active;
    struct message items[STACKSIZE];
};

typedef struct stack STACK;

//Defining structure ad

struct ad
{
    char data[1000];
    struct ad *next;
};

typedef struct ad AD;

//Defining structure news_variables

struct news_variables
{
    int p;
    int v1;
    int v2;
};

typedef struct news_variables NV;

/*
 Function Name:Node*getnode
Input Params: Nothing
Return Type: Structure
Description:Creates a newnode and returns
 */

NODE * getnode()
{
    NODE * newnode;
    newnode = (NODE *)malloc(sizeof(NODE));
    if(newnode == NULL)
        printf("Memory Allocation Failed\n");
    return newnode;
}

/*
 Function Name:Void getdata
Input Params: NODE*newnode
Return Type: Void
Description:Takes data from user input into newnode
 */

void getdata(NODE * newnode)
{
    printf("Enter the ad information\n");
    getchar();
    scanf("%[^\n]s", newnode->info);
    newnode->next = NULL;
    newnode->prev = NULL;
}

/*
 Function Name:NODE * insert_at_front
Input Params: NODE*start
Return Type: Structure
Description:Insert newnode value into the linked list from front
 */

NODE * insert_at_front(NODE * start)
{
    NODE * newnode;
    newnode = getnode();
    if(newnode == NULL)
        return start;
    getdata(newnode);
    if(start == NULL)
        start = newnode;
    else
    {
        newnode->next= start;
        start->prev=newnode;
        start = newnode;
    }
    currnode++;
    printf("%s info is inserted at the start of the doubly linked list\n", newnode->info);
    return start;
}

/*
 Function Name:NODE * insert_at_end
Input Params: NODE*start
Return Type: Structure
Description:Insert newnode value into the linked list at the end
 */

NODE * insert_at_end(NODE * start)
{
    NODE * newnode, *tempnode;
    newnode = getnode();
    if(newnode == NULL)
        return start;
    getdata(newnode);
    if(start == NULL)
        start = newnode;
    else
    {
        tempnode = start;
        while(tempnode->next != NULL)
            tempnode = tempnode->next;
        tempnode->next = newnode;
        newnode->prev = tempnode;
    }
    currnode++;
    printf("%s is Inserted\n", newnode->info);
    return start;
}

/*
 Function Name:NODE * insert_at_position
Input Params: NODE*start
Return Type: Structure
Description:Insert newnode value into the linked list at required position
 */

NODE * insert_at_position(NODE * start)
{
    NODE *newnode, *tempnode;
    int position=0, i=0;
    printf("Enter insert position\n");
    scanf("%d", &position);
    if(position < 1 || position > currnodes+1 )
        printf("Invalid position\n");
    else
    {
        newnode = getnode();
        if(newnode == NULL)
            return start;
        getdata(newnode);
        if(start == NULL)
            start = newnode;
        else if(position == 1)
        {
            newnode->next= start;
            start->prev=newnode;
            start = newnode;
        }
        else if(position == currnodes+1)
        {
            tempnode = start;
            while(tempnode->next != NULL)
                tempnode = tempnode->next;
            tempnode->next = newnode;
            newnode->prev = tempnode;
        }
        else
        {
            tempnode = start;
            for(i=2;i<position;i++)
                tempnode = tempnode->next;
            newnode->next = tempnode->next;
            newnode->prev = tempnode;
            tempnode->next->prev = newnode;
            tempnode->next = newnode;
            }
            currnode++;
            printf("%s info is inserted at the %d position of the doubly linked list\n", newnode->info,position);
        }
        return start;
}

/*
 Function Name:NODE * delete_from_start
Input Params: NODE*start
Return Type: Structure
Description:Delete data from linked list from start
 */

NODE * delete_from_start(NODE * start)
{
    NODE * tempnode;
    if(start == NULL)
        printf("List is empty\n");
    else
    {
    if(currnodes == 1)
    {
        tempnode = start;
        start = NULL;
    }
    else
    {
        tempnode = start;
        start = start->next;
        start->prev = NULL;
    }
    printf("Node %s deleted from the start of the Doubly linked list\n", tempnode->info);
    free(tempnode);
    currnode--;
    }
    return start;
}

/*
 Function Name:NODE * delete_from_end
Input Params: NODE*start
Return Type: Structure
Description:Delete data from linked list from end
 */

NODE * delete_from_end( NODE * start)
{
    NODE * tempnode, *prevnode;
    if(start == NULL)
        printf("List is empty\n");
    else
    {
    if(currnodes == 1)
    {
        tempnode = start;
        start = NULL;
    }
    else
    {
        tempnode = start;
        while(tempnode->next != NULL)
            tempnode = tempnode->next;
        prevnode = tempnode;
        prevnode = prevnode->prev;
        prevnode->next = NULL;
    }
    printf("Node %s deleted from the end of the Doubly linked list\n", tempnode->info);
    free(tempnode);
    currnode--;
    }
    return start;
}

/*
 Function Name:NODE * delete_from_position
Input Params: NODE*start
Return Type: Structure
Description:Delete data from linked list from required position
 */

NODE * delete_from_position(NODE * start)
{
    NODE * tempnode, *prevnode;
    int position=0, i=0;
    if(start == NULL)
        printf("List is empty\n");
    else
    {
    printf("Enter delete position\n");
    scanf("%d", &position);
    if(position < 1 || position > currnode )
        printf("Invalid position\n");
    else
    {
    if(currnode == 1)
    {
        tempnode = start;
        start = NULL;
    }
    else if(position == 1)
    {
        tempnode = start;
        start = start->next;
        start->prev = NULL;
    }
    else if(position == currnode)
    {
    tempnode = start;
    while(tempnode->next != NULL)
        tempnode = tempnode->next;
    prevnode = tempnode;
    prevnode = prevnode->prev;
    prevnode->next = NULL;
    }
    else
    {
        prevnode = NULL;
        tempnode = start;
        i = 2;
    while(i<=position)
    {
        prevnode = tempnode;
        tempnode = tempnode->next;
        i++;
    }
        prevnode->next = tempnode->next;
        tempnode->next->prev = prevnode;
    }
        printf("Node %s deleted from the %d position from the Doubly linked list\n", tempnode->info, position);
        free(tempnode);
        currnode--;
    }
    }
    return start;
}

/*
 Function Name:Display_list
Input Params: NODE*start
Return Type: Void
Description:Display the content of list
 */

void display_list(NODE * start)
{
    NODE * tempnode;
    int x;
    tempnode = start;
    printf("%s\n",tempnode->info);
    while(1)
    {
    printf("Enter 1 to Move Forward and 2 to go Back and 0 to Exit\n");
    scanf("%d",&x);
    if(currnodes == 0)
        printf("List Empty\n");
    else
    {


        if(x==1)
        {
            tempnode=tempnode->next;
            printf("%s\n",tempnode->info);
        }
        else if(x==2)
        {
            tempnode=tempnode->prev;
            printf("%s\n",tempnode->info);
        }
        else if(x==0)
            break;

    }
    }
}

/*
 Function Name:Initialize_stacks
Input Params:STACK *ps1, STACK *ps2
Return Type: Void
Description:Intializes the queue through initialising it's components
 */

void initialize_stacks(STACK *ps1, STACK *ps2)
{
    ps1->top = -1;
    ps2->top = -1;

    ps1->active = 1;
    ps2->active = 0;

    int i,j,size;
    char ad[100];
    int h1,h2;
    printf("Enter the Number of Ads :");
    scanf("%d",&size);
    for(i=0;i<size;i++)
    {

        printf("Enter the Advertisement you want to broadcast\n");
        getchar();
        scanf("%[^\n]s",ad);

        printf("Enter the timings when your ad should be displayed\n*****Note:An ad can be broad-casted twice a day*****\n");
        scanf("%d",&h1);
        scanf("%d",&h2);

        ps1->top++;
        strcpy(ps1->items[i].message_data,ad);
        ps1->items[i].hour[0] = h1;
        ps1->items[i].hour[1] = h2;
        printf("Ad created\n");
        getchar();

    }

}
/*
 Function Name:empty
Input Params:STACK *ps
Return Type: Int
Description:Return the value if stack is empty
 */

int empty(STACK *ps)
{
    if(ps->top == -1)
        return TRUE;
    else
        return FALSE;
}

/*
 Function Name:Message pop
Input Params: Stack pointer *ps
Return Type: Structure s
Description:Does pop function
 */

struct message pop(STACK *ps)
{
    struct message s;
    strcpy(s.message_data,ps->items[ps->top].message_data);
    s.hour[0] = ps->items[ps->top].hour[1];
    s.hour[1] = ps->items[ps->top].hour[0];
    ps->top --;
    return s;
}
/*
 Function Name: View_current_message
Input Params: Stack pointer *ps1,stack pointer *ps2
Return Type: Void
Description:Views current message in the stack
 */


void view_current_message(STACK *ps1, STACK *ps2)
{

    if(ps1->active == 1)
        peek(ps1);

    else
        peek(ps2);

}
/*
 Function Name: Update hour
Input Params: Stack pointer *ps1 and *ps2
Return Type: Void
Description: Updates time
 */

void update_hour(STACK *ps1, STACK *ps2)

{

    struct message s;

    if(ps1->active == 1)
    {
        s= pop(ps1);
        push(ps2,s);

        if(empty(ps1))
        {
            ps1->active = 0;
            ps2->active = 1;

        }
    }

    else

    {
        s = pop(ps2);
        push(ps1, s);

        if(empty(ps2))
        {
            ps2->active = 0;
            ps1->active = 1;

        }

    }

}
/*
 Function Name: Push
Input Params: Stack pointer *ps and structure variable message s
Return Type: Void
Description: It does push function
 */
void push(STACK * ps, struct message s)

{

    ps->top++;

    strcpy(ps->items[ps->top].message_data,s.message_data);
    ps->items[ps->top].hour[0] = s.hour[0];
    ps->items[ps->top].hour[1] = s.hour[1];

    return;

}

/*
 Function Name: Peek
Input Params: Stack pointer *ps
Return Type: Void
Description:Prints peek value of the stack
 */
void peek( STACK *ps)
{

    printf("%s", ps->items[ps->top].message_data);
    printf("%s%d", "\ntiming is ", ps->items[ps->top].hour[0]);
    printf("\n\n\n");

    return;
}
/*
 Function Name:Print
Input Params: Stack pointer *ps1 and *ps2
Return Type: Void
Description: Elements of stack are being printed
 */

void print( STACK *ps1, STACK *ps2)
{
    int i = 0, j = 0;

    if(ps1->active == 1)
        printf("%s", "Stack1 is Active\n");

    else
        printf("%s", "Stack2 is Active\n");

    if(empty(ps1))
    {
        printf("%s", "Stack1 is empty\n");
    }
    else
    {

        printf("%s", "\nThe stack elements of first stack are listed below:\n");
        for(i = ps1->top ; i >= 0 ; i--)
        {

            printf("%s\n", ps1->items[i].message_data);

        }
    }

    if(empty(ps2))
    {

        printf("%s", "\n\nStack2 is empty\n");

    }

    else
    {

        printf("%s", "\nThe stack elements of second stack are listed below:\n");
        for(j = ps2->top ; j >= 0 ; j--)
        {

            printf("%s\n", ps2->items[j].message_data);

        }

    }
}
/*
 Function Name: AD*append
Input Params: AD * start,char data[],int position
Return Type: Structure pointer
Description:Appends data into the structure
 */


AD *append(AD * start,char data[],int position)
{

   AD * temp=start;
   int i=0;

   while(i<position - 1)
   {
       temp=temp->next;
       i++;
   }

   strcpy(temp->data,data);

   return start;
}
/*
 Function Name:AD *displayNTimes
Input Params: AD * start,int n,char content[]
Return Type: Structure pointer
Description: Displaying function
 */
AD *displayNTimes(AD * start,int n,char content[])
{

    int l;
     for(l=0;l<n;l++)
    {
        t=rand()%MAX;

        while(1)
        {
            if(a[t]==0)
            {
                start=append(start,content,t+1);
                a[t]=1;
                break;
            }
            else
                t=rand()%MAX;
        }
    }
    return start;
}
/*
 Function Name: AD * InsertNth
Input Params: AD * start,char data[],int position
Return Type: Structure
Description:Does newly created  node insertion function
 */
 AD * InsertNth(AD * start,char data[],int position)
 {

    AD * newnode, *nextnode;
    k=0;

    if(position < 1 || position > currnodes+1)
        printf("Invalid Position!\n");
    else
    {
        newnode = (AD *) malloc(sizeof(AD));

        if(newnode == NULL)
            return start;

        strcpy(newnode->data,data);
        newnode->next=NULL;

        if(position == 1)
        {
            newnode->next= start;
            start= newnode;
        }
        else if(position == currnodes + 1)
            {
                nextnode=start;

                while(nextnode->next!=NULL)
                    nextnode = nextnode->next;

                nextnode->next = newnode;
            }
        else
            {
                nextnode = start;
                k = 1;

                while(k < position-1)
                {
                    nextnode =nextnode->next;
                    k++;
                }

                newnode->next =nextnode->next;
                nextnode->next =newnode;
            }
        currnodes++;
    }
    return start;
}
/*
 Function Name: Centerstring
Input Params: Character pointer *s
Return Type: Void
Description: Prints string at the center
 */
void centerstring(char *s)
{

    int i;
    int l=strlen(s);
    int pos=(int)((80-l)/2);
    for(i=0;i<pos;i++)
        printf(" ");
    printf("%s\n",s);

}
/*
 Defining structure queue
 */
struct queue
{

    int front;
    int rear;
    char items[MAX][1000];

};

typedef struct queue QUEUE;
/*
 Function Name: Empty1
Input Params: Queue pointer *q
Return Type: Integer
Description: Checks queue is empty or not
 */
int empty1(QUEUE *q)
{
    if(q->front>q->rear)
        return TRUE;
    else
        return FALSE;
}
/*
 Function Name: Full1
Input Params: Queue pointer q
Return Type: Integer
Description:Checks queue is full or not
 */
int full1(QUEUE *q)
{

    if(q->rear==MAX-1)
        return TRUE;
    else
        return FALSE;

}
/*
 Function Name:Enqueue
Input Params: Queue pointer,input items
Return Type: Void
Description:Adds elements to the queue
 */
void enqueue(QUEUE *q,char item[1000])
{

    if(full1(q))
    {
        printf("Queue Full\n");
        return;
    }
    q->rear++;
    strcpy(q->items[q->rear],item);
    printf("Enqueue Sucessfull\n");
    return;

}
/*
 Function Name: Delay
Input Params: Time in sec
Return Type: Void
Description: Time starts for a diplaying perticuler message
 */
void delay(int sec)
{

    int ms=1000*sec;
    clock_t start_time=clock();
    while(clock() < start_time+ ms)
        ;
}
/*
 Function Name:isEmptyd
Input Params: Queue pointer *pq
Return Type: Integer
Description: Check empty or not
 */
int isEmptyd(QUEUED *pq)
{
    return (pq->front>pq->rear);
}

/*
 Function Name:isEmptys
Input Params: Queue pointer *pq
Return Type: Integer
Description: Check empty or not
 */
int isEmptys(QUEUES *pq)
{
    return (pq->front>pq->rear);
}
/*
 Function Name: Isfulld
Input Params: Queue pointer *pq
Return Type: Integer
Description:Check queue is full or not
 */

int isFulld(QUEUED *pq)
{
    return (pq->rear==MAX_QUEUE);
}

/*
 Function Name: Isfulls
Input Params: Queue pointer *pq
Return Type: Integer
Description:Check queue is full or not
 */


int isFulls(QUEUES *pq)
{
    return (pq->rear==MAX_QUEUE);
}
/*
 Function Name: Enqueued
Input Params: Queue pointer *pq,int data
Return Type: Void
Description:Elements are stored into the queue
 */

void enqueued(QUEUED *pq,int data)
{

    if(isFulld(pq))
    {
        printf("Fatal!Cannot enqueue more elements");
    }
    else
    {
        pq->rear++;
        pq->data[pq->rear]=data;

    }
}
/*
 Function Name:Enqueues
Input Params:Queue pointer *pq
Return Type: Void
Description: Element will be added into the queue
 */
void enqueues(QUEUES *pq)
{
        int str[50];

    if(isFulls(pq))
    {
        printf("Fatal!Cannot enqueue more elements");
    }
    else
    {
        pq->rear++;

        printf("Enter the advertisment\n");
        getchar();
        scanf("%[^\n]s",str);
        strcpy(pq->ad[pq->rear],str);
        printf("Advertisement has been added successfully\n");

    }
}

/*
 Function Name:Dequeued
Input Params: Queue pointer *pq
Return Type: Int
Description: Element dequeued from the queue
 */
int dequeued(QUEUED *pq)
{

    if(isEmptyd(pq))
    {

        printf("************End of BFS************");
        return -1;

    }
    else{

        int x = pq->data[pq->front];
        pq->front++;
        return x;

    }
}

/*
 Function Name:Dequeues
Input Params: Queue pointer *pq
Return Type: Void
Description: Element dequeued from the queue
 */
void dequeues(QUEUES *pq)
{

    if(isEmptys(pq))
    {
        printf("NO ads");
        return -1;
    }
    else{
        pq->front++;
        printf("Ad updated");

    }
}
/*
 Function Name:Seeks
Input Params: Queue pointer *pq
Return Type: Void
Description: Gives seek value of  the queue
 */
void seeks(QUEUES *pq)
{

    if(isEmptys(pq))
    {
        printf("no ads");
        return;
    }
    else
    {
        printf("%s",pq->ad[pq->front]);
    }

}
/*
 Function Name:BFS
Input Params: Int s,int v,int adj[][V_SIZE]
Return Type: Void
Description: BFS operations are done here
 */
void BFS(int s,int v,int adj[][V_SIZE])
{
    int vis[V_SIZE],p[V_SIZE];
    //initialising visited array
    for (int i=0;i<v;i++)
    {
        vis[i]=0;
        p[i]=0;
        level[i]=0;
    }

    QUEUED q;
    q.rear=-1;
    q.front=0;
    enqueued(&q,s);
    vis[s]=1;
    level[s]=0;
    //printf("%d",isEmpty(&q));

    while(!isEmptyd(&q))
    {
        int curr=dequeued(&q);
        printf("%d",curr+1);

        for(int i=0;i<v;i++)
        {
            if(adj[curr][i]==1 && !vis[i])
            {
                level[i]=level[curr]+1;
                enqueued(&q,i);
                vis[i]=1;
                p[i]=curr;
            }
        }
    }
    for(int i=0;i<v;i++)
     {
         printf("%d\n",level[i]);
     }
}

int main()
{
try
{
    FILE *fp1,*fp2,*fp3;

    FILE *details;


    FILE *details1;


    FILE *details2;


    char producer[100],director[100],ba[100];

    QUEUE q1,q2,q3,q4,q5;

    QUEUE q6,q7,q8,q9,q10;

    q1.front=0;
    q1.rear=-1;

    q2.front=0;
    q2.rear=-1;

    q3.front=0;
    q3.rear=-1;

    q4.front=0;
    q4.rear=-1;

    q5.front=0;
    q5.rear=-1;

    q6.front=0;
    q6.rear=-1;

    q7.front=0;
    q7.rear=-1;

    q8.front=0;
    q8.rear=-1;

    q9.front=0;
    q9.rear=-1;

    q10.front=0;
    q10.rear=-1;

    AD *temp=NULL;
    int i,c,w,n;
    char addata[1000];

    for(i=0;i<MAX;i++)
     {
         a[i]=0;
     }

    AD *start=NULL;
    AD *paper=NULL;
    AD *paper1=NULL;

    NV news1,news2;

for(i=1;i<=MAX;i++)
       {
           start=InsertNth(start,"Currently No Ad",i);
       }

for(i=1;i<=26;i++)
      {
          paper=InsertNth(paper,"Currently No Ad",i);
      }

for(i=1;i<=16;i++)
        {
            paper1=InsertNth(paper1,"Currently No Ad",i);
        }

    news1.p=2;
    news2.p=2;
    news1.v1=0;
    news2.v1=0;
    news1.v2=0;
    news2.v2=0;

    while(1)
    {
        int c1;
        printf("*******************************\n");
        printf("Enter the Choice :\n");
        printf("1.Add an Advertisement in TV\n");
        printf("2.Add an Advertisement in Times of India Newspaper\n");
        printf("3.Add an Advertisement in Hindu Newspaper\n");
        printf("4.Add an Advertisement in Banners of the shopping malls time to time\n");
        printf("5.Add an Advertisement in Social Media\n");
        printf("6.Add an Advertisement through messages in the nearer locality\n");
        printf("7.Display Advertisement in TV\n");
        printf("8.Display Advertisement in Times of India Newspaper\n");
        printf("9.Display Advertisement in Hindu Newspaper\n");
        printf("10.Display Advertisement in Banners of Shopping Mall\n");
        printf("11.Display Advertisement in Social Media of various users\n");
        printf("12.Navigate through Advertisements\n");
        printf("13.Delete the information stored in all the files\n");
        printf("14.Report any Advertisements\n");

        scanf("%d",&c);

        if(c<0 || c>14)
        {
            printf("Invalid");
            break;
        }


        printf("*******************************\n");
        switch(c)
        {
            /*
Description: Recursively visits the tree in the order of Left, Right, Root
 */
        case 1:
                    {
                        if(count==MAX)
                        {
                                printf("No more adds can be displayed today....\n");
                                break;
                        }

                        details=fopen("Tv ads.txt","a+");

                        printf("The Charges for displaying an add 10 minutes a day is 1 lakh. Assuming an add is of 1 minute .\n");

                        printf("Enter the advertisement : ");
                        getchar();
                        scanf("%[^\n]s",addata);

                        fprintf(details,"AD is %s\n",addata);

                        printf("Enter the Producer of ad : ");
                        scanf("%s",producer);

                        fprintf(details,"Producer = %s\n",producer );

                        printf("Enter the Director of ad : ");
                        scanf("%s",director);

                        fprintf(details,"Director = %s\n",director);

                        printf("Enter the Brand Ambassador : ");
                        scanf("%s",ba);
                        fprintf(details,"Brand Ambassador = %s\n",ba );

                        fprintf(details,"***********************\n");

                        fclose(details);

                        printf("How many minutes you want your add to display in a day:");
                        scanf("%d",&n);

                        printf("Therefore your charges will be %f Lakhs\n",n/10.0);
                        printf("Are you ready to pay the charges : \n 1.Yes\n0.No\n");
                        scanf("%d",&w);

                        if(w==1)
                        {
                            count=count+n;

                            if(count>MAX)
                            {
                                    printf("The no of minutes are greater than 100. So now you can only display an add for %d minutes",n-count+MAX);
                                    printf("The charges will be %f\n",(n-count+MAX)/10.0);
                                    printf("Is that ok.\n1.Yes\n0.No\n");
                                    scanf("%d",&w);

                                    if(w==1)
                                    {
                                        n=n-count+MAX;
                                        count=MAX;
                                    }
                            }

                            start=displayNTimes(start,n,addata);


                            printf("Your Add will be displayed for %d minutes today.\n",n);
                            break;
                        }
                    }
                    /*
Description: Recursively visits the tree in the order of Left, Right, Root
 */
        case 2:
                     {
                         printf("Welcome to TIMES OF INDIA ad section\n");
                         printf("**********************************\n");

                         printf("We follow the following ad categories\n");
                         printf("1.Matrimony:- \t1.Inner Page=735/sq.cm\t2.Front Page=800/sq.cm\t3.Back Page=760/sq.cm\n2.Retail:- \t1.Inner Page=500/sq.cm\t2.Front Page=600/sq.cm\t3.Back Page=550/sq.cm\n3.Services:-\t1.Inner Page=132/sq.cm\t2.Front Page=149/sq.cm\t3.Back Page=140/sq.cm\n4.Education:-\t1.Inner Page=800/sq.cm\t2.Front Page: 850/sq.cm\t3.Back Page=820/sq.cm\n5.Others:-\t1.Inner Page=120/sq.cm\t2.Front Page=200/sq.cm\t3.Back Page=185/sq.cm\n");
                         printf("Please select your category\n");
                         scanf("%d",&c);

          if(c<0 || c>5)
        {
            printf("Invalid");
            break;
        }

          details1=fopen("Times of India ads.txt","a+");
             if(details1==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                         switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details1,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details1,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details1,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details1,"Address = %s\n",ba );

                                        fprintf(details1,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Matrimonial for Inner page is %d rupees\n",size*735);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                               {
                                                                   printf("Failed to publish your add\n");
                                                               }
                                                        }
                                                        break;
                                             case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Matrimonial for Front page is %d rupees\n",size*800);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Matrimonial for Back page is %d rupees\n",size*760);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }
                                                        }
                                                        else
                                                            printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }

                           case 2:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        fprintf(details1,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details1,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details1,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details1,"Address = %s\n",ba );

                                        fprintf(details1,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Retail for Inner page is %d rupees\n",size*500);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Retail for Front page is %d rupees\n",size*600);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Retail for Back page is %d rupees\n",size*550);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }
                                                        }

                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                     case 3:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details1,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details1,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details1,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details1,"Address = %s\n",ba );

                                        fprintf(details1,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Services for Inner page is %d rupees\n",size*132);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Services for Front page is %d rupees\n",size*149);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Services for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 4:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details1,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details1,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details1,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details1,"Address = %s\n",ba );

                                        fprintf(details1,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Education for Inner page is %d rupees\n",size*800);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Education for Front page is %d rupees\n",size*820);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Education for Back page is %d rupees\n",size*820);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 5:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details1,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");
                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news1.p==26)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Inner page is %d rupees\n",size*120);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,news1.p);
                                                                news1.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");

                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news1.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Front page is %d rupees\n",size*200);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,1);
                                                                news1.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news1.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Back page is %d rupees\n",size*185);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper=append(paper,addata,26);
                                                                news1.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    } break;
                                        }

                                    }
                                    break;
                    }
                    fclose(details1);
                    break;


                     }
        case 3:
                    {
                        printf("Welcome to THE HINDU NEWSPAPER\n");
                        printf("*******************************\n");

                        printf("There are different ad category below:\n");
                        printf("The Tariff rates in Rupees per Sq.cm for different category are : \n");
                        printf("1.Property    : - \t1.Inner Page = 70\t2.Front Page = 125\t3.Back Page = 95\n2.Empower     : - \t1.Inner Page = 75\t2.Front Page = 350\t3.Back Page = 175\n3.Tenders     : - \t1.Inner Page = 70\t2.Front Page = 125\t3.Back Page = 95\n4.Automobile  : - \t1.Inner Page = 125\t2.Front Page = 160\t3.Back Page = 150\n5.Others      : - \t1.Inner Page = 120\t2.Front Page = 200\t3.Back Page = 185\n");
                        printf("Please select your category : ");
                        scanf("%d",&c);

          if(c<0 || c>5)
        {
            printf("Invalid");
            break;
        }

        details2=fopen("The Hindu ads.txt","a+");
           if(details2==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                        switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details2,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in property for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in property for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                 paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {

                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in property for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }
                                                        }
                                                        else
                                                            printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                        case 2:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details2,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Empower for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);
                                                            printf("The charges of ad in Empower for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                        printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Empower for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }
                                                        }

                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                     case 3:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details2,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Tender for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Tender for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Tender for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 4:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details2,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Automobile for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");
                                                        }

                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Automobile for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad in Automobile for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    case 5:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);
                                        fprintf(details2,"AD is %s\n",addata);

                                        printf("Enter the name of advertiser : ");
                                        scanf("%s",producer);
                                        fprintf(details2,"Name = %s\n",producer );

                                        printf("Enter the  phone no : ");
                                        scanf("%s",director);
                                        fprintf(details2,"Phone no = %s\n",director);

                                        printf("Enter the Address : ");
                                        getchar();
                                        scanf("%[^\n]s",ba);
                                        fprintf(details2,"Address = %s\n",ba );

                                        fprintf(details2,"***********************\n");

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

          if(w<0 || w>3)
        {
            printf("Invalid");
            break;
        }
                                        switch(w)
                                        {
                                            case 1:
                                                        {
                                                            if(news2.p==16)
                                                            {
                                                                printf("All the Inner Pages are full.\n");
                                                                break;
                                                            }
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Inner page is %d rupees\n",size*70);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);
                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                               paper1=append(paper1,addata,news2.p);
                                                                news2.p++;
                                                            }
                                                            else
                                                                printf("Failed to publish your add\n");

                                                        }
                                                        break;
                                            case 2:
                                                    {
                                                        if(news2.v1==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Front page is %d rupees\n",size*125);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,1);
                                                                news2.v1=1;
                                                            }
                                                            else
                                                            {
                                                                printf("Failed to publish your add\n");
                                                            }
                                                        }
                                                        else
                                                            printf("Front page has an add already.\n");
                                                    }
                                                    break;
                                            case 3:
                                                    {
                                                        if(news2.v2==0)
                                                        {
                                                            printf("Enter the size of ad in sq cms :");
                                                            scanf("%d",&size);

                                                            printf("The charges of ad for Back page is %d rupees\n",size*95);
                                                            printf("Are you ready to pay the charges :\n1.Yes\n0.No\n");
                                                            scanf("%d",&i);

                                                            if(i==1)
                                                            {
                                                                printf("Your ad is published.\n");
                                                                paper1=append(paper1,addata,16);
                                                                news2.v2=1;
                                                            }

                                                        }
                                                        else
                                                        printf("Back page has an add already.\n");
                                                    }
                                        }
                                        break;
                                    }
                    }
                    fclose(details2);
                    break;
                }

          case 8:
                    {
                       fp1= fopen("Data_stored_TimesOfIndia.txt","a+");

                        if(fp1==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                        i=1;
                        AD *tmp=paper;
                        while(tmp->next!=NULL)
                        {
                            printf("%s\n",tmp->data);

                            tmp=tmp->next;
                            i++;
                        }
                        printf("%s\n",tmp->data);

                        fclose(fp1);
                    }
                    break;
          case 9:
                    {
                        fp2=fopen("Data_stored_Hindu.txt","a+");

                    if(fp2==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                    {
                        i=1;
                        AD *tmp=paper1;
                        while(tmp->next!=NULL)
                        {
                            printf("%s\n",tmp->data);

                            tmp=tmp->next;
                            i++;
                        }
                        printf("%s\n",tmp->data);
                    }
                        fclose(fp2);
                        break;
                    }
        case 5:
                     {
                         FILE *f;
                         char word[1000];
                         char category[100];
                         char producer[100];
                         char dir[100];
                         char emb[100];
                         char admes[1000];

                        printf("Enter the Ad message");
                        getchar();
                        scanf("%[^\n]s",admes);

                        printf("Enter the category of product");
                        scanf("%s",category);

                        printf("Enter the producer of the ad");
                        scanf("%s",producer);

                        printf("Enter the brand embassedor of ad");
                        scanf("%s",emb);

                        printf("Enter the director of ad");
                        scanf("%s",dir);

                            f=fopen("U1.txt","r");
                                                if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q1,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U2.txt","r");
                                                     if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }
                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q2,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U3.txt","r");
                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }
                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q3,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U4.txt","r");

                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q4,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U5.txt","r");

                                if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q5,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U6.txt","r");

                             if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q6,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U7.txt","r");
                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q7,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U8.txt","r");

                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q8,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U9.txt","r");

                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q9,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);

                             f=fopen("U10.txt","r");

                                  if(f==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                            while(!feof(f))
                            {
                                fscanf(f,"%s",word);
                                if(!strcmp(word,category))
                                {
                                    enqueue(&q10,admes);
                                    printf("Add is sent\n");
                                    break;
                                }
                            }
                            fclose(f);
                     }
                     break;
        case 11:
                {
                    int choice;
                    printf("Enter the user name whose add is to be displayed :\n");
                    printf("User 1\n");
                    printf("User 2\n");
                    printf("User 3\n");
                    printf("User 4\n");
                    printf("User 5\n");
                    printf("User 6\n");
                    printf("User 7\n");
                    printf("User 8\n");
                    printf("User 9\n");
                    printf("User 10\n");

                    scanf("%d",&choice);

      if(choice<0 || choice>300)
        {
            printf("Invalid");
            break;
        }
                    switch(choice)
                    {
                        case 1:
                                    {
                                         printf("The ad's displayed to user 1 is \n");
                                        for(i=q1.front;i<=q1.rear;i++)
                                        {
                                            printf("%s\n",q1.items[i]);
                                        }
                                    }
                                    break;

                        case 2:
                                    {
                                         printf("The ad's displayed to user 2 is \n");
                                        for(i=q2.front;i<=q2.rear;i++)
                                        {
                                            printf("%s\n",q2.items[i]);
                                        }
                                    }
                                    break;

                        case 3:
                                    {
                                         printf("The ad's displayed to user 3 is \n");
                                        for(i=q3.front;i<=q3.rear;i++)
                                        {
                                            printf("%s\n",q3.items[i]);
                                        }
                                    }
                                    break;

                         case 4:
                                    {
                                         printf("The ad's displayed to user 4 is \n");
                                        for(i=q4.front;i<=q4.rear;i++)
                                        {
                                            printf("%s\n",q4.items[i]);
                                        }
                                    }
                                    break;

                            case 5:
                                    {
                                         printf("The ad's displayed to user 5 is \n");
                                        for(i=q5.front;i<=q5.rear;i++)
                                        {
                                            printf("%s\n",q5.items[i]);
                                        }
                                    }
                                    break;

                            case 6:
                                    {
                                         printf("The ad's displayed to user 6 is \n");
                                        for(i=q6.front;i<=q6.rear;i++)
                                        {
                                            printf("%s\n",q6.items[i]);
                                        }
                                    }
                                    break;

                            case 7:
                                    {
                                         printf("The ad's displayed to user 7 is \n");
                                        for(i=q7.front;i<=q7.rear;i++)
                                        {
                                            printf("%s\n",q7.items[i]);
                                        }
                                    }
                                    break;

                            case 8:
                                    {
                                         printf("The ad's displayed to user 8 is \n");
                                        for(i=q8.front;i<=q8.rear;i++)
                                        {
                                            printf("%s\n",q8.items[i]);
                                        }
                                    }
                                    break;

                            case 9:
                                    {
                                         printf("The ad's displayed to user 9 is \n");
                                        for(i=q9.front;i<=q9.rear;i++)
                                        {
                                            printf("%s\n",q9.items[i]);
                                        }
                                    }
                                    break;

                            case 10:
                                    {
                                         printf("The ad's displayed to user 10 is \n");
                                        for(i=q10.front;i<=q10.rear;i++)
                                        {
                                            printf("%s\n",q10.items[i]);
                                        }
                                    }
                    }
                }
                break;

        case 0:     exit(0);

        case 13:
                    {
                        printf("Deleted all the previous data in the files.\n");

                        fp1=fopen("Data_stored_Hindu.txt","w");
                             if(fp1==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                        fp2=fopen("Data_stored_TV.txt","w");
                             if(fp2==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }
                        fp3=fopen("Data_stored_TimesOfIndia.txt","w");
                             if(fp3==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                        fclose(fp1);
                        fclose(fp2);
                        fclose(fp3);
                    }
                    break;

        case 7:
                    {
                        fp3=fopen("Data_stored_TV.txt","a+");
                             if(fp3==NULL)
                        {
                            printf("Can't open file\n");
                            break;
                        }

                        fprintf(fp3,"\n%s\n\n", "Today's ads in Television are : ");

                        i=1;
                        AD *tmp=start;

                        while(tmp->next!=NULL)
                        {
                            centerstring(tmp->data);
                            fprintf(fp3,"%s %d %s %s\n","Add in",i,"th minute is ",tmp->data);
                            tmp=tmp->next;
                            i++;
                        }

                        printf("%s\n",tmp->data);
                        fprintf(fp3,"%s %d %s %s\n","Add in",i,"th minute is ",tmp->data);

                        fclose(fp3);
                    }

                    break;

        case 4:
                {
                     STACK s1, s2;
                     int choice = 0,flag;

                    printf("Enter the advertisments according to the timings\n");
                    initialize_stacks(&s1, &s2);

                    while(1)
                    {

                        printf("\n******** MENU ********\n");
                        printf("1-Broadcast the Advertisment\n");
                        printf("2-Update the ad\n");
                        printf("3-Exit\n");
                        printf("***********************\n");

                        scanf("%d", &choice);

          if(choice<0 || choice>300)
        {
            printf("Invalid");
            break;
        }
                        switch(choice)
                        {
                            case 1: printf("\nWelcome to urban oasis mall..\n We are very glad to have you here\n");
                                    view_current_message(&s1, &s2);
                                    printf("*****The message is broadcasted*****\n");
                                    break;

                            case 2: update_hour(&s1, &s2);
                                    printf("The message ad is updated\n");
                                    printf("***********************************\n");
                                    break;

                            case 3: exit(0);
                                    break;
                       }

                    }
                }

                break;

        case 6:
                 {
                     int adj[V_SIZE][V_SIZE]={0},u,v,choice,range;
                        //number of vertices
                        int nv;
                        //number of edges
                        int e;
                        int x;
                        int adsize;

                        printf("\nEnter the number of people in the area:");
                        scanf("%d",&nv);

                        printf("Enter the number of connections between people:");
                        scanf("%d",&e);

                        printf("Enter the connected edges\n");

                        for (int i=0;i<e;i++)
                        {
                            scanf("%d%d",&u,&v);
                            adj[--u][--v]=1;
                            adj[v][u]=1;
                        }

                        printf("Enter the source for bfs:");
                        int s;
                        scanf("%d",&s);
                        BFS(--s,nv,adj);

                        QUEUES ads;
                        ads.front=0;
                        ads.rear=-1;

                        printf("\nEnter the number of ads\n");
                        scanf("%d",&adsize);

                        for(int i=0;i<adsize;i++)
                            enqueues(&ads);

                        printf("\nEnter the range for broadcasting the ads\n");
                        scanf("%d",&range);
                        while(1)
                        {
                            printf("Menu\n1.Broadcast the message to the users in within the given range\n2.Update the advertisment\n");
                            printf("3.Change the range\n4.Add Advertisements\n5.Exit\n");

                            printf("Enter the choice\n");
                            scanf("%d",&choice);

                            int j;

    if(choice<0 || choice>300)
        {
            printf("Invalid");
            break;
        }
                            switch(choice)
                            {
                                case 1: for(j=0;j<v&&level[j]<=range;j++)
                                        {
                                           printf("Ad displayed to the user %d is  ",j+1);
                                           seeks(&ads);
                                           printf("\n");
                                        }

                                        break;

                                case 2: dequeues(&ads);
                                        break;

                                case 3: printf("Enter the range for broadcasting the ads\n");
                                        scanf("%d",&range);
                                        break;

                                case 4: printf("Enter the number of ads\n");
                                        scanf("%d",&adsize);
                                        for(int i=0;i<adsize;i++)
                                            enqueues(&ads);

                                case 5: exit(0);

                            }

                        }
                 }
                 break;

         case 14:
                 {
                     int cu;
                     char adname[50],report[100];

                     FILE *file1,*file2,*file3;

                     printf("Welcome to the report section of the Advertisement\n");

                     while(1)
                     {
                         printf("Menu\n1.Report for the ad in newspaper\n2.Report for the ad displayed on television\n");

                         printf("3.Report for the ad in display boards\n4.exit\n");

                         printf("Enter the choice\n");
                         scanf("%d",&cu);

          if(cu<0 || cu>300)
        {
            printf("Invalid");
            break;
        }
                         switch(cu)
                         {
                             case 1:
                                 {
                                     file1=fopen("Newspaper.txt","a");
                                     if(file1==NULL)
                                     {
                                         printf("File error\n");
                                         return;
                                     }
                                     printf("Enter the ad for which you want to report\n");
                                     getchar();
                                     scanf("%[^\n]s",adname);

                                     fprintf(file1,"%s\n",adname);
                                     printf("Enter the report\n");
                                     getchar();
                                     scanf("%[^\n]s",report);

                                     fprintf(file1,"%s\n",report);
                                     printf("Thank you for your valuable feedback\n");

                                     fprintf(file1,"**********************\n");

                                    fclose(file1);
                                    break;
                                 }
                            case 2:
                                 {
                                     file2=fopen("TV.txt","a");
                                     if(file2==NULL)
                                     {
                                         printf("File error\n");
                                         return;
                                     }
                                     printf("Enter the ad for which you want to report\n");
                                     getchar();
                                     scanf("%[^\n]s",adname);

                                     fprintf(file2,"%s\n",adname);
                                     printf("Enter the report\n");
                                     getchar();
                                     scanf("%[^\n]s",report);

                                     fprintf(file2,"%s\n",report);

                                     printf("Thank you for your valuable feedback\n");

                                     fprintf(file2,"**********************\n");

                                    fclose(file2);
                                    break;
                                 }
                             case 3:
                                 {
                                     file3=fopen("Display Boards.txt","a");
                                     if(file3==NULL)
                                     {
                                         printf("File error\n");
                                         return;
                                     }
                                     printf("Enter the ad for which you want to report\n");
                                     getchar();
                                     scanf("%[^\n]s",adname);

                                     fprintf(file3,"%s\n",adname);
                                     printf("Enter the report\n");
                                     getchar();
                                     scanf("%[^\n]s",report);

                                     fprintf(file3,"%s\n",report);
                                     printf("Thank you for your valuable feedback\n\n");

                                     fprintf(file3,"**********************\n");

                                    fclose(file3);
                                    break;
                                 }
                           case 4: exit(0);

                         }
                     }

                }

                 break;

          case 12:
                {
                    NODE * start;
                    start = NULL;
                    int rule,iter;
                    char content[50];
                    printf("Enter the number of ads\n");
                    scanf("%d",&rule);
                    for(iter=0;iter<rule;iter++)
                    {
                        start=insert_at_end(start);
                    }
                    display_list(start);
                    break;
                }


        }
    }
}

catch(. . .)
{
     printf("Invalid Input");
}
    return 0;
}

