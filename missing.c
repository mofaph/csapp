/*
 * 给出还没有完成的家庭作业
 *
 * mofaph@gmail.com
 * 2013-5-12
 *
 * 基本的想法就是，将所有的题目看作一个题目组成的集合。在初始化的时候，将所有的题
 * 目都设置为没有完成的标志，如果一道题目已经完成了，就设置一个完成的标志。
 *
 * 因为我将所有完成的题目都放在 exercise/ 这个目录下，并且以同一种风格命名：ex章
 * 节号-题目号。因此，扫描这个目录下的所有文件，得到章节号和题目号，然后映射到所
 * 有题目的集合中。
 *
 * 当需要输出结果的时候，只需要扫描题目集合，收集所有的标记为未完成的题目号。然后，
 * 将这些题目号映射为章节号和题目号就大功告成了。
 *
 * unix> cc missing.c -o missing
 * unix> ./missing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <regex.h>
#include <dirent.h>

struct homework {
        int beg;                /* 起始题号 */
        int end;                /* 结束题号 */
};

#define MAX_CHAPTER 13
struct homework homework_topic[MAX_CHAPTER] = {
        /*
         * 由于计算题目的个数是用 end-beg+1 的方式，所以为了确保没有题目的章节的
         * 题目数是零。因此，人为地设置起始题号是 1，结束题号是 0，就可以统一使用
         * end-beg+1 的方式计算题目数
         */
        { 1,  0},                               /* 0 */
        { 1,  0}, {55, 90}, {54, 70}, {43, 58}, /* 1-4 */
        {15, 22}, {23, 47}, { 6, 15}, { 9, 26}, /* 5-8 */
        {11, 20}, { 6, 10}, { 6, 13}, {16, 39}, /* 9-12 */
};

int total_topic[1024] = {0};

int init_total_topic(void)
{
        memset(total_topic, 0, sizeof(total_topic));

        int i, all;
        for (i = 0, all = 0; i < MAX_CHAPTER; i++)
                all += homework_topic[i].end - homework_topic[i].beg + 1;
        total_topic[all] = -1;
        return all;
}

/* 根据章节号和题号，给出总题号 */
int index_total(int chapter_num, int topic_num)
{
        if (chapter_num < 0 || chapter_num > MAX_CHAPTER)
                return -1;
        if (topic_num < homework_topic[chapter_num].beg ||
            topic_num > homework_topic[chapter_num].end)
                return -1;

        int i, index = 0;
        for (i = 0; i < chapter_num; i++)
                index += homework_topic[i].end-homework_topic[i].beg+1;
        index += topic_num-homework_topic[chapter_num].beg;
        return index;
}

/* 根据总题号，给出章节号和题号 */
void get_chapter_topic_from_index(int index, int *chapter_num, int *topic_num)
{
        int i, n;
        n = index;
        for (i = 0; i < MAX_CHAPTER; i++) {
                int all = homework_topic[i].end - homework_topic[i].beg + 1;
                if (n < all) {
                        *chapter_num = i;
                        *topic_num = homework_topic[i].beg + n;
                        break;
                } else {
                        n -= all;
                }
        }
}

/* 从文件名中，获取章节号和题号 */
void get_chapter_topic_from_filename(char *filename, int *chapter_num, int *topic_num)
{
        int ret;

        regex_t preg;
        char *regex = "^ex([0-9]+)-([0-9]+)";
        ret = regcomp(&preg, regex, REG_EXTENDED);
        if (ret != 0) {
                perror("regcomp");
                return;
        }

        regmatch_t pmatch[3];
        ret = regexec(&preg, filename, 3, pmatch, 0);
        if (ret == REG_NOMATCH) {
                regfree(&preg);
                return;
        }

        char buf[10];

        memset(buf, 0, sizeof(buf));
        memcpy(buf, filename+pmatch[1].rm_so, pmatch[1].rm_eo-pmatch[1].rm_so);
        *chapter_num = atoi(buf);

        memset(buf, 0, sizeof(buf));
        memcpy(buf, filename+pmatch[2].rm_so, pmatch[2].rm_eo-pmatch[2].rm_so);
        *topic_num = atoi(buf);

        regfree(&preg);
}

/* 如果题目已经完成了，就在题目集合中设置完成标志 */
void set_total_topic(char *dirname)
{
        DIR *dp = opendir(dirname);
        if (dp == NULL) {
                perror("opendir");
                return;
        }

        for (;;) {
                struct dirent *dirp;
                dirp = readdir(dp);
                if (dirp == NULL)
                        break;
                char *filename = dirp->d_name;
                int chapter, topic, index;
                get_chapter_topic_from_filename(filename, &chapter, &topic);
                index = index_total(chapter, topic);
                if (index >= 0)
                        total_topic[index] = 1;
        }

        closedir(dp);
}

int main(void)
{
        int len = init_total_topic();
        set_total_topic("exercise");

        int i;
        int old_chapter = 0, new_chapter = 0, topic;
        int unfinish = 0;
        for (i = 0; i < len; i++) {
                if (total_topic[i] == -1)
                        break;
                if (total_topic[i] == 0) {
                        unfinish += 1;
                        get_chapter_topic_from_index(i, &new_chapter, &topic);
                        static int count = 0;
                        if (old_chapter != new_chapter) {
                                if (old_chapter != 0)
                                        printf("\n");
                                old_chapter = new_chapter;
                                count = 0;
                        } else {
                                count += 1;
                                if (count % 8 == 0)
                                        printf("\n    ");
                        }
                        printf(" %d.%d", new_chapter, topic);
                }
        }
        printf("\n\n");

        int finish = len - unfinish;
        printf("total: %d, finish: %d(%.2f%%), unfinish: %d(%.2f%%)\n",
               len,
               finish, (double)finish/len*100,
               unfinish, (double)unfinish/len*100);

        return 0;
}
