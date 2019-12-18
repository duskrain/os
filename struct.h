/*
PCB结构
p_id  //进程的id
p_priority  //进程的优先级
p-type  //进程的状态
*parent  //进程的父进程
(*children)[10]  //进程的子进程
childcount  //子进程的计数器
p_source s[5]  //占用的资源
number[5]  //占用资源的计数器
*/
struct p_source
{
    char *name;//资源的名称
    int num;//资源的数量
};//定义资源结构

struct p_data
{
    char *p_id;//进程的名称
    int p_priority;//进程的优先级
    char *p_type;//进程的状态
    char *parent;//进程的父进程
    char *children[10];//进程的子进程
    int childcount;//进程的子进程数量
    struct p_source s[5];//进程占用的资源
    int number[5];
    char *block_name;//造成进程阻塞的资源名称
    int block_number;//造成进程阻塞的资源的数量
}; //定义一个进程的信息的结构

typedef struct list {
    struct p_data p;
    struct list *next;
} LinkList;//定义链表结构体




char N[10]={"NULL"};

struct p_data run =
        {
                .p_id =N,
                .p_priority = -1,
                .p_type = "run",
                .parent = N,
                .children = NULL,
                .childcount = 0,
                .s=NULL,
                .number = {0,0,0,0,0},
                .block_name = NULL,
                .block_number=0
        };//正在运行的进程;

struct p_source R1 = {.name = "R1",.num=1};
struct p_source R2 = {.name = "R2",.num=2};
struct p_source R3 = {.name = "R3",.num=3};
struct p_source R4 = {.name = "R4",.num=4};
//初始化资源

LinkList *head0, *end0;
LinkList *head1, *end1;
LinkList *head2, *end2;
//定义就绪队列的链表

LinkList *ready(){

    head0 = (LinkList*)malloc(sizeof(LinkList));
    end0 = head0;
    end0->next = NULL;//优先级为0的队列

    head1 = (LinkList*)malloc(sizeof(LinkList));
    end1 = head1;
    end1->next = NULL;//优先级为1的队列

    head2 = (LinkList*)malloc(sizeof(LinkList));
    end2 = head2;
    end2->next = NULL;//优先级为2的队列

}//初始化就绪队列

LinkList *head, *end;//定义阻塞队列的链表

LinkList *block() {
    head = (LinkList*)malloc(sizeof(LinkList));
    end = head;
    end->next = NULL;
}//初始化阻塞队列

/*
进程管理设计
void create()  //创建进程函数
void destory()  //销毁进程函数
void request()  //进程请求资源函数
void release()  //进程释放资源函数
void timeout()  //进程手动调度函数
void list_ready()  //列出就绪队列的进程
void list_block()  //列出阻塞队列的进程
void list_res()  //列出可用资源
void inf_process() //列出进程的信息
*/

void create(char *a,int b)
{

    if (run.p_id == N)
    {
        run.p_id = a;
        run.p_priority =b;
        run.p_type = "running" ;
        printf("进程%s已经创建,进程%s正在运行\n",run.p_id,run.p_id);
    }//如果没有进程在运行，那么创建的进程直接运行
    else
    {

        struct p_data process={
                .p_id = a,
                .p_priority = b,
                .p_type = "ready",
                .parent = run.p_id,
               .number={0,0,0,0,0,},
                .s=NULL
        };

        run.children[(run.childcount)] = process.p_id;
        run.childcount++;
        LinkList *new;
        new = (LinkList*)malloc(sizeof(LinkList));
        if (b == 0)
        {
            end0->next = new;
            end0 = new;
            new->p = process;
        }//如果优先级为0则插入到优先级为0的队列

        if (b == 1)
        {
            end1->next = new;
            end1 = new;
            new->p = process;
        }//如果优先级为1则插入到优先级为1的队列

        if (b == 2)
        {
            end2->next = new;
            end2 = new;
            new->p = process;
        }//如果优先级为2则插入到优先级为2的队列
        printf("进程%s正在运行，进程%s已经创建！\n", run.p_id, process.p_id);
    }
}//创建进程函数


int timeout()
{

    LinkList *temp;
    temp = (LinkList*)malloc(sizeof(LinkList));
    if (run.p_priority == 0)
    {
        end1->next = temp;
        end1 = temp;
        temp->p = run;
        temp->p.p_type = "ready";
        temp->p.p_priority = 1;
    }
    else if (run.p_priority == 2 || run.p_priority == 1)
    {
        end2->next = temp;
        end2 = temp;
        temp->p = run;
        temp->p.p_type = "ready";
        temp->p.p_priority = 2;

    }
    LinkList *ptr;
    //ptr = (LinkList*)malloc(sizeof(LinkList));
    if ((head0 != end0) && head0->next != NULL)
    {
        run = head0->next->p;
        run.p_type = "running";
        ptr = head0;
        head0 = ptr->next;
        free(ptr);
        printf("进程切换完成进程%s正在运行\n", run.p_id);
        return 0;
    }
    else if ((head1 != end1) && head1->next != NULL)
    {

        run = head1->next->p;
        run.p_type = "running";
        ptr = head1;
        head1 = ptr->next;
        free(ptr);
        printf("进程切换完成进程%s正在运行\n", run.p_id);
        return 0;
    }
    else if ((head2 != end1) && head2->next != NULL)
    {
        run = head2->next->p;
        run.p_type = "running";
        ptr = head2;
        head2 = ptr->next;
        free(ptr);
        printf("进程切换完成进程%s正在运行\n", run.p_id);
        return 0;
    }
    else
    {
        printf("就绪队列为空，进程%s正在运行\n", run.p_id);
    }
}//进程轮转函数

int request(char *source,int num)
{
    if (strcmp(source,R1.name)==0&&R1.num >= num)
    {
        R1.num = (R1.num - num);
        run.s[1] = R1;
        run.number[1] = num+ run.number[1];
        printf("%s请求资源R1成功\n", run.p_id);
    }
    else if (strcmp(source,R2.name)==0&&R2.num >= num)
    {
        R2.num = (R2.num - num);
        run.s[2] = R2;
        run.number[2] = num + run.number[2];
        printf("%s请求资源R2成功\n", run.p_id);
        return 0;
    }
    else if (strcmp(source,R3.name)==0&&R3.num >= num)
    {
        R3.num = (R3.num - num);
        run.s[3] = R3;
        run.number[3] = num + run.number[3];
        printf("%s请求资源R3成功\n", run.p_id);
    }
    else if (strcmp(source,R4.name)==0&&R4.num >= num)
    {
        R4.num = (R4.num - num);
        run.s[3] = R4;
        run.number[3] = num + run.number[3];
        printf("%s请求资源R4成功\n", run.p_id);
    }
    else
    {
        LinkList *blocktemp;
        blocktemp = (LinkList*)malloc(sizeof(LinkList));
        end->next = blocktemp;
        end = blocktemp;
        blocktemp->p = run;
        blocktemp->p.p_type = "block";
        blocktemp->p.block_name = source;
        blocktemp->p.block_number = num;//如果阻塞了，则将running的进程调入阻塞队列；

        LinkList *ptr;
        //ptr = (LinkList*)malloc(sizeof(LinkList));
        if ((head0 != end0) && head0->next != NULL)
        {
            run = head0->next->p;
            run.p_type = "running";
            ptr = head0;
            head0 = ptr->next;
            free(ptr);
        }
        else if ((head1 != end1) && head1->next != NULL)
        {
            run = head1->next->p;
            run.p_type = "running";
            ptr = head1;
            head1 = ptr->next;
            free(ptr);
        }
        else if ((head2 != end1) && head2->next != NULL)
        {
            run = head2->next->p;
            run.p_type = "running";
            ptr = head2;
            head2 = ptr->next;
            free(ptr);
        }
        else
        {

            printf("请求资源失败，无进程就绪\n", run.p_id);
            return 0;
        }
        printf("进程%s阻塞，，进程%s正在运行。\n", blocktemp->p.p_id,run.p_id);

    }
}//请求资源函数

void back(struct p_data a, int b)
{
    LinkList *temp;
    temp = (LinkList*)malloc(sizeof(LinkList));
    if (b == 0)
    {
        end1->next = temp;
        end1 = temp;
        temp->p = a;
        temp->p.p_type = "ready";
    }
    else if (b == 1)
    {
        end1->next = temp;
        end1 = temp;
        temp->p = a;
        temp->p.p_type = "ready";
    }
    else if (b == 2)
    {
        end2->next = temp;
        end2 = temp;
        temp->p = a;
        temp->p.p_type = "ready";
    }
}//back函数，用于将阻塞队列的进程调回就绪队列。



int release(char *a,int b)
{
    /*
    R1.num = (R1.num - num);
    R1.arry[R1.count] = run.p_id;
    R1.count++;
    run.s[1] = R1;
    run.number[1] = num + run.number[1];
    printf("%s请求资源成功\n", run.p_id);
    return 0;
    */
    LinkList *p_mov = head;
    if (strcmp(a,"R1")==0)
    {
        R1.num = R1.num + b;
        run.number[1] = 0;
        printf("资源R1已经释放，释放数量为%d",b);
        while ((p_mov != end))//条件为当前节点，遍历时主要显示当前节点
        {
            if (strcmp(p_mov->next->p.block_name,a)==0 && p_mov->next->p.block_number <= R1.num) {
                back(p_mov->next->p, p_mov->next->p.p_priority);
                if (p_mov->next == end) {
                    LinkList *temp;
                    temp = p_mov->next;
                    head = end;
                    free(temp);
                    return 0;
                } else {
                    LinkList *temp;
                    temp = p_mov->next;
                    p_mov->next = temp->next;
                    p_mov = p_mov->next;
                    free(temp);
                }
            }
        }
    }
    else if (strcmp(a,"R2")==0)
    {
        R2.num = R2.num + b;
        run.number[2] = 0;
        printf("资源R2已经释放，释放数量为%d",b);
        while ((p_mov != end))//条件为当前节点，遍历时主要显示当前节点
        {
            if (strcmp(p_mov->next->p.block_name,a)==0 && p_mov->next->p.block_number <= R2.num)
            {
                back(p_mov->next->p, p_mov->next->p.p_priority);
                if (p_mov->next == end)
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    head = end;
                    free(temp);
                    return 0;
                }
                else
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    p_mov->next = temp->next;
                    p_mov = p_mov->next;
                    free(temp);
                }
            }
        }
    }
    else if (strcmp(a,"R3")==0)
    {
        R3.num = R3.num + b;
        run.number[3] = 0;
        printf("资源R3已经释放，释放数量为%d",b);
        while ((p_mov != end))//条件为当前节点，遍历时主要显示当前节点
        {
            if (strcmp(p_mov->next->p.block_name,a)==0 && p_mov->next->p.block_number <= R3.num)
            {
                back(p_mov->next->p, p_mov->next->p.p_priority);
                if (p_mov->next == end)
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    head = end;
                    free(temp);
                    return 0;
                }
                else
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    p_mov->next = temp->next;
                    p_mov = p_mov->next;
                    free(temp);
                }
            }
        }
    }
    else if (strcmp(a,"R4")==0)
    {
        R4.num = R4.num + b;
        run.number[4] = 0;
        printf("资源R4已经释放，释放数量为%d",b);
        while ((p_mov != end))//条件为当前节点，遍历时主要显示当前节点
        {
            if (strcmp(p_mov->next->p.block_name,a)==0  && p_mov->next->p.block_number <= R4.num)
            {
                back(p_mov->next->p, p_mov->next->p.p_priority);
                if (p_mov->next == end)
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    head = end;
                    free(temp);
                    return 0;
                }
                else
                {
                    LinkList *temp;
                    temp = p_mov->next;
                    p_mov->next = temp->next;
                    p_mov = p_mov->next;
                    free(temp);
                }
            }
        }
    }
}//释放资源函数

int destory(char *a)
{
    //判断销毁的进程是不是正在运行的进程，如果是，则要调用新的进程
    if (strcmp(run.p_id,a)==0)
    {
        R1.num = R1.num + run.number[1];
        R2.num = R2.num + run.number[2];
        R3.num = R3.num + run.number[3];
        R4.num = R4.num + run.number[4];
        LinkList *ptr;
        //ptr = (LinkList*)malloc(sizeof(LinkList));
        if ((head0 != end0) && head0->next != NULL)
        {
            run = head0->next->p;
            run.p_type = "running";
            ptr = head0;
            head0 = ptr->next;
            free(ptr);
            return 0;
        }
        else if ((head1 != end1) && head1->next != NULL)
        {

            run = head1->next->p;
            run.p_type = "running";
            ptr = head1;
            head1 = ptr->next;
            free(ptr);
            return 0;
        }
        else if ((head2 != end1) && head2->next != NULL)
        {
            run = head2->next->p;
            run.p_type = "running";
            ptr = head2;
            head2 = ptr->next;
            free(ptr);
            return 0;
        }
        else
        {
            printf("就绪队列为空，没有进程可运行。\n");
        }
        printf("%s进程已经销毁",a);
    }
    //如果不是running进程，则执行普通的销毁代码
    else
    {
        LinkList *temp;
        LinkList *p_mov0 = head0;
        while ((p_mov0 != end0) && p_mov0->next != NULL)
        {
            if (strcmp(p_mov0->next->p.p_id, a)==0)
            {
                R1.num = R1.num + p_mov0->next->p.number[1];
                R2.num = R2.num + p_mov0->next->p.number[2];
                R3.num = R3.num + p_mov0->next->p.number[3];
                R4.num = R4.num + p_mov0->next->p.number[4];
                if (p_mov0->next != end0)
                {
                    temp = p_mov0->next;
                    p_mov0->next = temp->next;
                    free(temp);
                    return 0;
                }
                else
                {
                    temp = p_mov0->next;
                    end0 = p_mov0;
                    free(temp);
                    return 0;
                }
            }
            else
            {
                p_mov0 = p_mov0->next;
            }
        }
        LinkList *p_mov1 = head1;
        while ((p_mov1 != end1) && p_mov1->next != NULL )
        {
            if (strcmp(p_mov1->next->p.p_id, a)==0)
            {
                R1.num = R1.num + p_mov1->next->p.number[1];
                R2.num = R2.num + p_mov1->next->p.number[2];
                R3.num = R3.num + p_mov1->next->p.number[3];
                R4.num = R4.num + p_mov1->next->p.number[4];
                if (p_mov1->next != end1)
                {
                    temp = p_mov1->next;
                    p_mov1->next = temp->next;
                    free(temp);
                    return 0;
                }
                else
                {
                    temp = p_mov1->next;
                    end1 = p_mov1;
                    free(temp);
                    return 0;
                }
            }
            else
            {
                p_mov1 = p_mov1->next;
            }
        }
        LinkList *p_mov2 = head2;
        while ((p_mov2 != end2) && p_mov2->next != NULL)
        {
            if (strcmp(p_mov2->next->p.p_id, a)==0)
            {
                R1.num = R1.num + p_mov2->next->p.number[1];
                R2.num = R2.num + p_mov2->next->p.number[2];
                R3.num = R3.num + p_mov2->next->p.number[3];
                R4.num = R4.num + p_mov2->next->p.number[4];
                if (p_mov2->next != end2)
                {
                    temp = p_mov2->next;
                    p_mov2->next = temp->next;
                    free(temp);
                    return 0;
                }
                else
                {
                    temp = p_mov2->next;
                    end2 = p_mov2;
                    free(temp);
                }
            }
            else
            {
                p_mov2 = p_mov2->next;
            }
        }

        LinkList *p_mov = head;
        while ((p_mov != end) && p_mov->next != NULL)
        {
            if (strcmp(p_mov->next->p.p_id, a)==0)
            {
                R1.num = R1.num + p_mov->next->p.number[1];
                R2.num = R2.num + p_mov->next->p.number[2];
                R3.num = R3.num + p_mov->next->p.number[3];
                R4.num = R4.num + p_mov->next->p.number[4];
                if (p_mov->next != end)
                {
                    temp = p_mov->next;
                    p_mov->next = temp->next;
                    free(temp);
                    return 0;
                }
                else
                {
                    temp = p_mov->next;
                    end = p_mov;
                    free(temp);
                }
            }
            else
            {
                p_mov = p_mov->next;
            }
        }
        printf("%s进程已经销毁",a);
    }
}//销毁进程函数

void list_ready()
{
    LinkList *p_mov0 = head0;
    printf("优先级为0的队列为: ");
    while ((p_mov0!= end0)&& p_mov0->next != NULL)//条件为当前节点，遍历时主要显示当前节点
    {
        printf("%s ", p_mov0->next->p.p_id);
        p_mov0 = p_mov0->next;
    }
    printf("\n");
    LinkList *p_mov1 = head1;
    printf("优先级为1的队列为: ");
    while ((p_mov1 != end1) && p_mov1->next != NULL)//条件为当前节点，遍历时主要显示当前节点
    {
        printf("%s ", p_mov1->next->p.p_id);
        p_mov1 = p_mov1->next;
    }
    printf("\n");
    LinkList *p_mov2 = head2;
    printf("优先级为2的队列为: ");
    while (p_mov2!=end2&& p_mov2->next != NULL)//条件为当前节点，遍历时主要显示当前节点
    {
        printf("%s ", p_mov2->next->p.p_id);
        p_mov2 = p_mov2->next;
    }
    printf("\n");
}//列出不同优先级的就绪队列

void list_block()
{
    LinkList *p_mov = head;

    printf("阻塞队列为: ");
    while ((p_mov != end) && p_mov->next != NULL)//条件为当前节点，遍历时主要显示当前节点
    {
        printf("%s ", p_mov->next->p.p_id);
        p_mov = p_mov->next;
    }
}//列出阻塞队列

void print(struct p_data a)
{
    printf("进程的信息如下:\n");
    printf("p_id:%s\n", a.p_id);
    printf("p_priority:%d\n", a.p_priority);
    printf("p_type:%s\n", a.p_type);
    printf("parent:%s\n", a.parent);
    printf("children:");
    for (int i = a.childcount; i >= 1; i--)
        printf("%s ", a.children[i - 1]);
    printf("\n");
    printf("p_source:");
    for (int t = 1; t <= 4; t++)
    {
        if (a.number[t] != 0)
        {
            printf("%s", a.s[t].name);
            printf("(%d) ", a.number[t]);
        }
    }
}

int inf_process(char *a)
{
    if (strcmp(run.p_id,a)==0)
    {
        print(run);
    }
    else
    {
        LinkList *p_mov0 = head0;
        while ((p_mov0 != end0) && p_mov0->next != NULL)//条件为当前节点，遍历时主要显示当前节点
        {
            if ((strcmp(p_mov0->next->p.p_id,a)==0))
            {
                print(p_mov0->next->p);
                return 0;
            }
            p_mov0 = p_mov0->next;
        }

        LinkList *p_mov1 = head1;
        while ((p_mov1 != end1) && p_mov1->next != NULL)//条件为当前节点，遍历时主要显示当前节点
        {
            if ((strcmp(p_mov1->next->p.p_id,a)==0))
            {
                print(p_mov1->next->p);
                return 0;
            }
            p_mov0 = p_mov0->next;
        }

        LinkList *p_mov2 = head2;
        while ((p_mov2 != end2) && p_mov2->next != NULL)//条件为当前节点，遍历时主要显示当前节点
        {
            if ((strcmp(p_mov2->next->p.p_id,a)==0))
            {
                print(p_mov2->next->p);
                return 0;
            }
            p_mov2 = p_mov2->next;
        }

        LinkList *p_mov = head;
        while ((p_mov != end) && p_mov->next != NULL)//条件为当前节点，遍历时主要显示当前节点
        {
            if ((strcmp(p_mov->next->p.p_id,a)==0))
            {
                print(p_mov->next->p);
                return 0;
            }
            p_mov = p_mov->next;
        }

        printf("查找到进程不存在");
    }
}//列出进程的信息

void list_res()
{
    printf("R1:%d\n", R1.num);
    printf("R2:%d\n", R2.num);
    printf("R3:%d\n", R3.num);
    printf("R4:%d\n", R4.num);
}//列出可用资源

