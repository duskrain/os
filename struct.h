/*
PCB�ṹ
p_id  //���̵�id
p_priority  //���̵����ȼ�
p-type  //���̵�״̬
*parent  //���̵ĸ�����
(*children)[10]  //���̵��ӽ���
childcount  //�ӽ��̵ļ�����
p_source s[5]  //ռ�õ���Դ
number[5]  //ռ����Դ�ļ�����
*/
struct p_source
{
    char *name;//��Դ������
    int num;//��Դ������
};//������Դ�ṹ

struct p_data
{
    char *p_id;//���̵�����
    int p_priority;//���̵����ȼ�
    char *p_type;//���̵�״̬
    char *parent;//���̵ĸ�����
    char *children[10];//���̵��ӽ���
    int childcount;//���̵��ӽ�������
    struct p_source s[5];//����ռ�õ���Դ
    int number[5];
    char *block_name;//��ɽ�����������Դ����
    int block_number;//��ɽ�����������Դ������
}; //����һ�����̵���Ϣ�Ľṹ

typedef struct list {
    struct p_data p;
    struct list *next;
} LinkList;//��������ṹ��




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
        };//�������еĽ���;

struct p_source R1 = {.name = "R1",.num=1};
struct p_source R2 = {.name = "R2",.num=2};
struct p_source R3 = {.name = "R3",.num=3};
struct p_source R4 = {.name = "R4",.num=4};
//��ʼ����Դ

LinkList *head0, *end0;
LinkList *head1, *end1;
LinkList *head2, *end2;
//����������е�����

LinkList *ready(){

    head0 = (LinkList*)malloc(sizeof(LinkList));
    end0 = head0;
    end0->next = NULL;//���ȼ�Ϊ0�Ķ���

    head1 = (LinkList*)malloc(sizeof(LinkList));
    end1 = head1;
    end1->next = NULL;//���ȼ�Ϊ1�Ķ���

    head2 = (LinkList*)malloc(sizeof(LinkList));
    end2 = head2;
    end2->next = NULL;//���ȼ�Ϊ2�Ķ���

}//��ʼ����������

LinkList *head, *end;//�����������е�����

LinkList *block() {
    head = (LinkList*)malloc(sizeof(LinkList));
    end = head;
    end->next = NULL;
}//��ʼ����������

/*
���̹������
void create()  //�������̺���
void destory()  //���ٽ��̺���
void request()  //����������Դ����
void release()  //�����ͷ���Դ����
void timeout()  //�����ֶ����Ⱥ���
void list_ready()  //�г��������еĽ���
void list_block()  //�г��������еĽ���
void list_res()  //�г�������Դ
void inf_process() //�г����̵���Ϣ
*/

void create(char *a,int b)
{

    if (run.p_id == N)
    {
        run.p_id = a;
        run.p_priority =b;
        run.p_type = "running" ;
        printf("����%s�Ѿ�����,����%s��������\n",run.p_id,run.p_id);
    }//���û�н��������У���ô�����Ľ���ֱ������
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
        }//������ȼ�Ϊ0����뵽���ȼ�Ϊ0�Ķ���

        if (b == 1)
        {
            end1->next = new;
            end1 = new;
            new->p = process;
        }//������ȼ�Ϊ1����뵽���ȼ�Ϊ1�Ķ���

        if (b == 2)
        {
            end2->next = new;
            end2 = new;
            new->p = process;
        }//������ȼ�Ϊ2����뵽���ȼ�Ϊ2�Ķ���
        printf("����%s�������У�����%s�Ѿ�������\n", run.p_id, process.p_id);
    }
}//�������̺���


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
        printf("�����л���ɽ���%s��������\n", run.p_id);
        return 0;
    }
    else if ((head1 != end1) && head1->next != NULL)
    {

        run = head1->next->p;
        run.p_type = "running";
        ptr = head1;
        head1 = ptr->next;
        free(ptr);
        printf("�����л���ɽ���%s��������\n", run.p_id);
        return 0;
    }
    else if ((head2 != end1) && head2->next != NULL)
    {
        run = head2->next->p;
        run.p_type = "running";
        ptr = head2;
        head2 = ptr->next;
        free(ptr);
        printf("�����л���ɽ���%s��������\n", run.p_id);
        return 0;
    }
    else
    {
        printf("��������Ϊ�գ�����%s��������\n", run.p_id);
    }
}//������ת����

int request(char *source,int num)
{
    if (strcmp(source,R1.name)==0&&R1.num >= num)
    {
        R1.num = (R1.num - num);
        run.s[1] = R1;
        run.number[1] = num+ run.number[1];
        printf("%s������ԴR1�ɹ�\n", run.p_id);
    }
    else if (strcmp(source,R2.name)==0&&R2.num >= num)
    {
        R2.num = (R2.num - num);
        run.s[2] = R2;
        run.number[2] = num + run.number[2];
        printf("%s������ԴR2�ɹ�\n", run.p_id);
        return 0;
    }
    else if (strcmp(source,R3.name)==0&&R3.num >= num)
    {
        R3.num = (R3.num - num);
        run.s[3] = R3;
        run.number[3] = num + run.number[3];
        printf("%s������ԴR3�ɹ�\n", run.p_id);
    }
    else if (strcmp(source,R4.name)==0&&R4.num >= num)
    {
        R4.num = (R4.num - num);
        run.s[3] = R4;
        run.number[3] = num + run.number[3];
        printf("%s������ԴR4�ɹ�\n", run.p_id);
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
        blocktemp->p.block_number = num;//��������ˣ���running�Ľ��̵����������У�

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

            printf("������Դʧ�ܣ��޽��̾���\n", run.p_id);
            return 0;
        }
        printf("����%s������������%s�������С�\n", blocktemp->p.p_id,run.p_id);

    }
}//������Դ����

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
}//back���������ڽ��������еĽ��̵��ؾ������С�



int release(char *a,int b)
{
    /*
    R1.num = (R1.num - num);
    R1.arry[R1.count] = run.p_id;
    R1.count++;
    run.s[1] = R1;
    run.number[1] = num + run.number[1];
    printf("%s������Դ�ɹ�\n", run.p_id);
    return 0;
    */
    LinkList *p_mov = head;
    if (strcmp(a,"R1")==0)
    {
        R1.num = R1.num + b;
        run.number[1] = 0;
        printf("��ԴR1�Ѿ��ͷţ��ͷ�����Ϊ%d",b);
        while ((p_mov != end))//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
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
        printf("��ԴR2�Ѿ��ͷţ��ͷ�����Ϊ%d",b);
        while ((p_mov != end))//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
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
        printf("��ԴR3�Ѿ��ͷţ��ͷ�����Ϊ%d",b);
        while ((p_mov != end))//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
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
        printf("��ԴR4�Ѿ��ͷţ��ͷ�����Ϊ%d",b);
        while ((p_mov != end))//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
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
}//�ͷ���Դ����

int destory(char *a)
{
    //�ж����ٵĽ����ǲ����������еĽ��̣�����ǣ���Ҫ�����µĽ���
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
            printf("��������Ϊ�գ�û�н��̿����С�\n");
        }
        printf("%s�����Ѿ�����",a);
    }
    //�������running���̣���ִ����ͨ�����ٴ���
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
        printf("%s�����Ѿ�����",a);
    }
}//���ٽ��̺���

void list_ready()
{
    LinkList *p_mov0 = head0;
    printf("���ȼ�Ϊ0�Ķ���Ϊ: ");
    while ((p_mov0!= end0)&& p_mov0->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
    {
        printf("%s ", p_mov0->next->p.p_id);
        p_mov0 = p_mov0->next;
    }
    printf("\n");
    LinkList *p_mov1 = head1;
    printf("���ȼ�Ϊ1�Ķ���Ϊ: ");
    while ((p_mov1 != end1) && p_mov1->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
    {
        printf("%s ", p_mov1->next->p.p_id);
        p_mov1 = p_mov1->next;
    }
    printf("\n");
    LinkList *p_mov2 = head2;
    printf("���ȼ�Ϊ2�Ķ���Ϊ: ");
    while (p_mov2!=end2&& p_mov2->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
    {
        printf("%s ", p_mov2->next->p.p_id);
        p_mov2 = p_mov2->next;
    }
    printf("\n");
}//�г���ͬ���ȼ��ľ�������

void list_block()
{
    LinkList *p_mov = head;

    printf("��������Ϊ: ");
    while ((p_mov != end) && p_mov->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
    {
        printf("%s ", p_mov->next->p.p_id);
        p_mov = p_mov->next;
    }
}//�г���������

void print(struct p_data a)
{
    printf("���̵���Ϣ����:\n");
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
        while ((p_mov0 != end0) && p_mov0->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
        {
            if ((strcmp(p_mov0->next->p.p_id,a)==0))
            {
                print(p_mov0->next->p);
                return 0;
            }
            p_mov0 = p_mov0->next;
        }

        LinkList *p_mov1 = head1;
        while ((p_mov1 != end1) && p_mov1->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
        {
            if ((strcmp(p_mov1->next->p.p_id,a)==0))
            {
                print(p_mov1->next->p);
                return 0;
            }
            p_mov0 = p_mov0->next;
        }

        LinkList *p_mov2 = head2;
        while ((p_mov2 != end2) && p_mov2->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
        {
            if ((strcmp(p_mov2->next->p.p_id,a)==0))
            {
                print(p_mov2->next->p);
                return 0;
            }
            p_mov2 = p_mov2->next;
        }

        LinkList *p_mov = head;
        while ((p_mov != end) && p_mov->next != NULL)//����Ϊ��ǰ�ڵ㣬����ʱ��Ҫ��ʾ��ǰ�ڵ�
        {
            if ((strcmp(p_mov->next->p.p_id,a)==0))
            {
                print(p_mov->next->p);
                return 0;
            }
            p_mov = p_mov->next;
        }

        printf("���ҵ����̲�����");
    }
}//�г����̵���Ϣ

void list_res()
{
    printf("R1:%d\n", R1.num);
    printf("R2:%d\n", R2.num);
    printf("R3:%d\n", R3.num);
    printf("R4:%d\n", R4.num);
}//�г�������Դ

