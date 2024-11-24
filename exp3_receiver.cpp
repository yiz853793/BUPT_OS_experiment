#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_KEY 1234   // 消息队列的键值

// 这里不需要重新定义 msgbuf，直接使用系统中的定义

struct msg_buf {
    long mtype;       // 消息类型
    char mtext[200];  // 消息内容
};

int main() {
    key_t key = MSG_KEY; // 消息队列的键值
    int msgid = msgget(key, 0666 | IPC_CREAT); // 创建消息队列
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    struct msg_buf message;

    // 从消息队列接收消息
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Receiver: Received message: %s\n", message.mtext); // 打印接收到的消息

    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
