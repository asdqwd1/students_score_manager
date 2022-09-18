#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STUDENT_NUM 100
#define COURSE_NUM 6

/* ѧ����Ϣ */
struct student {
    char StuNo[16];     // ѧ��
    char StuName[64];   // ����
    char prof[32];      // רҵ
    double scores[COURSE_NUM];         // 6�ſγɼ�
    double zhongjidian;       // �ܼ���
};

int student_count = 0;

struct course_st {
    char CourNo[16];    // �γ̺�
    char CourName[64];  // �γ�����
    int xuefen;      // ѧ��
};

/* ���100��ѧ����Ϣ */
struct student stu[STUDENT_NUM];

/* �γ���Ϣ */
struct course_st course[COURSE_NUM];

/* ������˵� */
int main_menus()
{
    int choice;
    printf("*********** ���˵� ***********\n"
        "1. ѧ����Ϣ��ѯ\n"
        "2. ����ѧ����Ϣ\n"
        "3. �޸ĳɼ�\n"
        "4. ����\n"
        "5. ��ӡ\n"
        "6. �ɼ���ӡ\n"
        "0. �˳�\n"
        "***************************\n");

    printf("������Ҫִ�еĲ���: ");
    scanf("%d", &choice);
    getchar();

    return choice;
}

/* ��ӡ�����γ���Ϣ */
void show_one(struct student* c)
{
    printf("%s %s %s", c->StuNo, c->StuName, c->prof);
    for (int i = 0; i < COURSE_NUM; i++) {
        printf(" %.2lf", c->scores[i]);
    }
    printf(" %.2lf\n", c->zhongjidian);
}

/* ��ʾ����ѧ����Ϣ */
void show_all()
{
    int i = 0;
    for (int i = 0; i < student_count; i++) {
        show_one(&stu[i]);
    }
}

/* ���������� */
int find()
{
    char search[64] = { 0 };

    printf("������Ҫ���ҵ�ѧ�Ż�������: ");
    scanf("%s", search);
    getchar();

    int i = 0;
    for (i = 0; i < student_count; i++) {
        if (strcmp(stu[i].StuNo, search) == 0
            || strcmp(stu[i].StuName, search) == 0) {
            show_one(&stu[i]);
            break;
        }
    }

    if (i == student_count) {
        printf("δ�ҵ���ѧ�Ż�������.\n");
        return -1;
    }

    return i;
}

/* ���㼨�� �ܼ���=��ѧ��*�γ̳ɼ�/(��ѧ��) */
int cal(struct student* c)
{
    double scores = 0.0;
    int all_xuefen = 0;
    for (int i = 0; i < COURSE_NUM; i++) {
        scores += c->scores[i] * course[i].xuefen;
        all_xuefen += course[i].xuefen;
    }
    c->zhongjidian = scores / all_xuefen;

    return 0;
}

/* ����ѧ����Ϣ */
int add()
{
    printf("��˳��ֱ���������,ѧ��,רҵ,ÿ�ſγɼ�(�����������,Ӣ��, ����, ��ͼ, ����, ����): ");
    scanf("%s %s %s %lf %lf %lf %lf %lf %lf", stu[student_count].StuNo,
        stu[student_count].StuName, stu[student_count].prof,
        &stu[student_count].scores[0], &stu[student_count].scores[1],
        &stu[student_count].scores[2], &stu[student_count].scores[3],
        &stu[student_count].scores[4], &stu[student_count].scores[5]);
    getchar();

    cal(&stu[student_count]);
    student_count++;

    return 0;
}

/* ����޸Ĳ˵� */
int modify_menus()
{
    int choice;
    printf("*********** �޸Ĳ˵� ***********\n");
    for (int i = 0; i < COURSE_NUM; i++) {
        printf("%d. %s\n", i + 1, course[i].CourName);
    }
    printf("***************************\n");

    printf("������Ҫ�޸ĵĿγ�: ");
    scanf("%d", &choice);
    getchar();

    return choice - 1;
}
/* �޸ĳɼ� */
int modify()
{
    int i = find();
    printf("modify_menus: %d\n", i);
    if (i < 0) {
        printf("return\n");
        return i;
    }

    int choice = modify_menus();

    printf("������Ҫ�޸ĵĳɼ�: ");
    scanf("%lf", &stu[i].scores[choice]);
    getchar();

    return 0;
}

/* ����˵� */
int sort_menus()
{
    int choice;
    printf("*********** ����˵� ***********\n");
    for (int i = 0; i < COURSE_NUM; i++) {
        printf("%d. %s\n", i + 1, course[i].CourName);
    }
    printf("%d. %s\n", COURSE_NUM + 1, "�ܼ���");
    printf("***************************\n");

    printf("������Ҫ����Ŀγ�: ");
    scanf("%d", &choice);
    getchar();

    return choice - 1;
}

/* �ȽϺ���
 * ���� 1 ��Ҫ����
 * s == A ���� */
int cmp(struct student* l, struct student* r, int choice, char s)
{
    int ret = 0;
    if (choice >= 0 && choice < 6) {
        if (s == 'A') {
            ret = l->scores[choice] > r->scores[choice] ? 1 : -1;
        }
        else {
            ret = l->scores[choice] < r->scores[choice] ? 1 : -1;
        }
    }
    else if (choice == 6) {
        if (s == 'A') {
            ret = l->zhongjidian > r->zhongjidian ? 1 : -1;
        }
        else {
            ret = l->zhongjidian < r->zhongjidian ? 1 : -1;
        }
    }

    return ret;
}

/* ���� */
int sort()
{
    int choice = sort_menus();
    char s;
    printf("������Ҫ����(A)���ǽ���(D): ");
    scanf("%c", &s);
    s = s == 'a' ? 'A' : s;

    getchar();

    struct student tmp;
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (cmp(&stu[j], &stu[j + 1], choice, s) == 1) {
                tmp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = tmp;
            }
        }
    }

    return 0;
}

int statist_menu()
{
    int choice;
    printf("*********** ͳ�Ʋ˵� ***********\n");
    for (int i = 0; i < COURSE_NUM; i++) {
        printf("%d. %s\n", i + 1, course[i].CourName);
    }
    printf("***************************\n");

    printf("������Ҫͳ�ƵĿγ�: ");
    scanf("%d", &choice);
    getchar();

    return choice - 1;
}

int statist()
{
#define GRADE_NUM 5
    struct st_statist {
        int grade[GRADE_NUM];   /* ���ȼ����� */
    };

    char* grade_names[] = { "90-100", "80-90 ", "70-80 ", "60-70 ", "<60   " };

    struct st_statist s;
    memset(&s, 0, sizeof(s));

    int choice = statist_menu();

    double score = 0.0;
    double sum = 0.0;
    for (int i = 0; i < student_count; i++) {
        score = stu[i].scores[choice];
        sum += score;
        if (score >= 90) {
            s.grade[0]++;
        }
        else if (score >= 80) {
            s.grade[1]++;
        }
        else if (score >= 70) {
            s.grade[2]++;
        }
        else if (score >= 60) {
            s.grade[3]++;
        }
        else {
            s.grade[4]++;
        }
    }

    printf("ƽ��ֵ: %0.2f\n", sum / student_count);
    for (int i = 0; i < GRADE_NUM; i++) {
        printf("%s ռ��: %0.2f\n", grade_names[i], 100 * s.grade[i] / (double)student_count);
    }
}

int load()
{
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "open file student.txt error: %s\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < STUDENT_NUM; i++) {
        if (fscanf(fp, "%s %s %s %lf %lf %lf %lf %lf %lf %lf",
            stu[i].StuNo, stu[i].StuName, stu[i].prof,
            &stu[i].scores[0], &stu[i].scores[1], &stu[i].scores[2],
            &stu[i].scores[3], &stu[i].scores[4], &stu[i].scores[5],
            &stu[i].zhongjidian) != EOF) {
            student_count++;
        }
        else {
            break;
        }
    }

    fclose(fp);

    fp = fopen("course.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "open file course.txt error: %s\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < COURSE_NUM; i++) {
        if (fscanf(fp, "%s %s %d", course[i].CourNo, course[i].CourName,
            &course[i].xuefen) != EOF) {
        }
        else {
            break;
        }
    }

    fclose(fp);

    return 0;
}

int main(int argc, char** argv)
{
    load();

    while (1) {
        switch (main_menus()) {
        case 1:
            find();
            break;
        case 2:
            add();
            break;
        case 3:
            modify();
            break;
        case 4:
            sort();
            break;
        case 5:
            show_all();
            break;
        case 6:
            statist();
            break;
        case 0:
            exit(0);
        }
    }

    return 0;
}