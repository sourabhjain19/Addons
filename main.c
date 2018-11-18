#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<dos.h>
#include<time.h>
#include<stdbool.h>
#define MAX 100

#define STACKSIZE 6
#define TRUE 1
#define FALSE 0

#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=true;goto ExitJmp;

int currnodes=0,count=0;
int i,s ,j,t,b,k,c,size;
int a[MAX];

struct message
{
    char message_data[100];
    int hour[2];
};

struct stack
{
    int top;
    int active;
    struct message items[STACKSIZE];
};

typedef struct stack STACK;

struct ad
{
    char data[1000];
    struct add *next;
};

typedef struct ad AD;

struct news_variables
{
    int p;
    int v1;
    int v2;
};

typedef struct news_variables NV;

void initialize_stacks(STACK *ps1, STACK *ps2)
{
    ps1->top = -1;
    ps2->top = -1;

    ps1->active = 1;
    ps2->active = 0;

    int i,j,size;
    char ad[100];
    int h1,h2;
    printf("enter the number of ads\n");
    scanf("%d",&size);
    getchar();
    for(i=0;i<size;i++)
    {

        printf("\nenter the advertisment you want to broadcast\n");
        scanf("%[^\n]s",ad);
        getchar();
        printf("enter the timings when your ad should be displayed\n*****Note:An ad can be broadcasted twice a day*****\n");
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

int empty(STACK *ps)
{
    if(ps->top == -1)
        return TRUE;
    else
        return FALSE;
}

struct message pop(STACK *ps)
{
    struct message s;
    strcpy(s.message_data,ps->items[ps->top].message_data);
    s.hour[0] = ps->items[ps->top].hour[1];
    s.hour[1] = ps->items[ps->top].hour[0];
    ps->top --;
    return s;
}


void view_current_message(STACK *ps1, STACK *ps2)
{
    if(ps1->active == 1)
        peek(ps1);
    else
        peek(ps2);
}

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

void push(STACK * ps, struct message s)
{

    ps->top++;
    strcpy(ps->items[ps->top].message_data,s.message_data);
    ps->items[ps->top].hour[0] = s.hour[0];
    ps->items[ps->top].hour[1] = s.hour[1];
    return;
}


void peek( STACK *ps)
{
    printf("%s", ps->items[ps->top].message_data);
    printf("%s%d", "\ntiming is ", ps->items[ps->top].hour[0]);
    printf("\n\n\n");
    return;
}


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

void centerstring(char *s)
{
    int i;
    int l=strlen(s);
    int pos=(int)((80-l)/2);
    for(i=0;i<pos;i++)
        printf(" ");
    printf("%s\n",s);
}

struct queue
{
    int front;
    int rear;
    char items[MAX][1000];
};

typedef struct queue QUEUE;

int empty1(QUEUE *q)
{
    if(q->front>q->rear)
        return TRUE;
    else
        return FALSE;
}

int full1(QUEUE *q)
{
    if(q->rear==MAX-1)
        return TRUE;
    else
        return FALSE;
}

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

void delay(int sec)
{
    int ms=1000*sec;
    clock_t start_time=clock();
    while(clock() < start_time+ ms)
        ;
}
int main()
{
try
{
    FILE *fp1,*fp2,*fp3;

    QUEUE q1,q2,q3,q4,q5,q6,q7,q8,q9,q10;

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
        a[i]=0;

    AD *start=NULL;
    AD *paper=NULL;
    AD *paper1=NULL;

    NV news1,news2;

for(i=1;i<=MAX;i++)
        start=InsertNth(start,"Currently No Ad",i);

for(i=1;i<=26;i++)
        paper=InsertNth(paper,"Currently No Ad",i);

for(i=1;i<=16;i++)
        paper1=InsertNth(paper1,"Currently No Ad",i);

    news1.p=2;
    news2.p=2;
    news1.v1=0;
    news2.v1=0;
    news1.v2=0;
    news2.v2=0;

    while(1)
    {
        printf("*******************************\n");
        printf("Enter the Choice :\n1.Add an Advertisement in TV\n2.Add an Advertisement in Times of India Newspaper\n3.Add an advertisement in Hindu Newspaper\n4.Display ads in Times of India\n5.Display ads in Hindu Newspaper\n6.Delete all the contents in the files\n");
        scanf("%d",&c);
        printf("*******************************\n");
        switch(c)
        {
        case 1:
                    {
                        if(count==MAX)
                        {
                                printf("No more adds can be displayed today....\n");
                                break;
                        }
                        printf("The Charges for displaying an add 10 minutes a day is 1 lakh. Assuming an add is of 1 minute .\n");

                        printf("Enter the advertisement : ");
                        getchar();
                        scanf("%[^\n]s",addata);

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
        case 2:
                     {
                         printf("Welcome to TIMES OF INDIA ad section\n");
                         printf("**********************************\n");

                         printf("We follow the following ad categories\n");
                         printf("1.Matrimony:- \t1.Inner Page=735/sq.cm\t2.Front Page=800/sq.cm\t3.Back Page=760/sq.cm\n2.Retail:- \t1.Inner Page=500/sq.cm\t2.Front Page=600/sq.cm\t3.Back Page=550/sq.cm\n3.Services:-\t1.Inner Page=132/sq.cm\t2.Front Page=149/sq.cm\t3.Back Page=140/sq.cm\n4.Education:-\t1.Inner Page=800/sq.cm\t2.Front Page: 850/sq.cm\t3.Back Page=820/sq.cm\n5.Others:-\t1.Inner Page=120/sq.cm\t2.Front Page=200/sq.cm\t3.Back Page=185/sq.cm\n");
                         printf("Please select your category\n");
                         scanf("%d",&c);
                         switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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
                                                                printf("Failed to publish your add\n");
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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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
                        switch(c)
                        {
                        case 1:
                                    {
                                        printf("Enter the Advertisement : ");
                                        getchar();
                                        scanf("%[^\n]s",addata);

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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

                                        printf("Please Enter the page you want to select : \n1.Inner Page \n2.Front Page \n3.Back Page\n");
                                        printf("Please enter the choice : ");
                                        scanf("%d",&w);

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
                    break;
                }

          case 4:
                    {
                       fp1= fopen("Data_stored_TimesOfIndia.txt","a+");

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
          case 5:
                    {
                        fp2=fopen("Data_stored_Hindu.txt","a+");

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
        case 7:
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
        case 8:
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

        case 6:
                    {
                        printf("Deleted all the previous data in the files.\n");

                        fp1=fopen("Data_stored_Hindu.txt","w");
                        fp2=fopen("Data_stored_TV.txt","w");
                        fp3=fopen("Data_stored_TimesOfIndia.txt","w");

                        fclose(fp1);
                        fclose(fp2);
                        fclose(fp3);
                    }
                    break;

        case 10:
                    {
                        fp3=fopen("Data_stored_TV.txt","a+");

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

        case 11:
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

        }
    }
}
catch(. . .)
{
     printf("Invalid Input");
}
    return 0;
}
