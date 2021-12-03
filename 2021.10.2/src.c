/*
 * @Author: StarNight
 * @Date: 2021-12-03 05:52:04
 * @LastEditors: StarNight
 * @LastEditTime: 2021-12-03 07:20:05
 * @Description:Main
 */

#include <bits/types/FILE.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *string;

// string[] gAllText
// 用来保存用户输入
string *gAllText = NULL;
// 是否自动提醒保存?
// 0 为 no ,1 为 yes
short Is_save = 0;
// 一次读取的行数, 默认100
const int Lines = 100;

inline void save_file(string file_name, string mode); // 保存文件
inline void show_contents();                          // 显示目录
inline void edit();                                   // 进入编辑
inline string *scanf_str(string *allText, int lines, int *is_exit); //读取输入
inline void save();
inline void check_save(int is_save);

/**
 * @description: 保存输入到文件
 * @param {string} fileName
 * @param {string} mode
 */
inline void save_file(string file_name, string mode) {
  FILE *file_ptr = fopen(file_name, mode);
  if (gAllText != NULL) {
    for (int i = 0; (gAllText + i) != NULL; ++i) {
      fprintf(file_ptr, "%s", gAllText[i]);
    }
  }
  fclose(file_ptr);
}

/**
 * @description: 显示菜单
 */
inline void show_contents() {
  printf("请输入你的选择:\n");
  printf("1.进入编辑");
  printf("2.保存文件");
  printf("3.退出");
}

/**
 * @description:
 * 读取times行到传入的string[]中,并返回指向读取完后string的下一个元素的指针;
 * 如果读取到"cmd:quit" 则设置 is_exit 表示返回
 * @param {string} *allText
 * @param {int} lines
 * @param {int} *is_exit
 */
inline string *scanf_str(string *allText, int lines, int *is_exit) {
  for (int i = 0; i < lines; ++i) {
    scanf("%s", allText[i]);
    if (strcmp(allText[i], "cmd:quit") == 0) {
      *is_exit = 1;
    }
  }
  return allText + lines + 1;
}

/**
 * @description: 保存文件总流程
 */
inline void save() {
  for (;;) {
    printf("请输入保存的文件名:");
    string file_name = NULL;
    scanf("%s", file_name);
    printf("请输入操作方式:\n");
    printf("W:覆盖写入\n");
    printf("a:追加写入\n");
    string mode = NULL;
    scanf("%s", mode);
    if ((strcmp(mode, "W") == 0) || (strcmp(mode, "a")) == 0) {
      save_file(file_name, mode);
      Is_save = 0;
      break;
    }
    printf("输入不正确(可能是大小写不符?)\n请重新输入:\n\n\n");
  }
}

/**
 * @description: 进入编辑
 */
inline void edit() {
  printf("请在下方输入(tip:输入\"cmd:quit\"退出哦):\n");
  for (int is_exit = 0; is_exit != 1; scanf_str(gAllText, Lines, &is_exit)) {
    ;
  }
  Is_save = 1;
}

inline void check_save(int is_save) {
  if (is_save == 1) {
    printf("检测到你还没有保存,是否保存?(n 表示否,输入其他保存)");
    char choice = 0;
    scanf("%c", &choice);
    if (choice != 'n') {
      save();
    }
  }
}

int main() {
  for (;;) {
    show_contents();
    char choice = 0;
    scanf("%c", &choice);
    switch (choice) {
    case '1':
      edit();
      break;
    case '2':
      save();
      break;
    case '3':
      check_save(Is_save);
      return 0;
    case 0:
      printf("请重新输入\n");
      break;
    default:
      printf("输入无效,请重新输入\n");
    }
    system("clear");
  }
  return 0;
}
