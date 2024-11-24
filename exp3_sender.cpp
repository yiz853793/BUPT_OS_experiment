#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234   // 消息队列的关键字

struct msg_buf {
    long mtype;           // 消息类型
    char mtext[100];      // 消息内容
};

int main() {
    key_t key = MSG_KEY;
    int msgid;
    struct msg_buf message;
    int i = 0;

    // 创建消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // 发送消息
    while (i < 5) {
        message.mtype = 1;  // 设置消息类型
        snprintf(message.mtext, sizeof(message.mtext), "Message %d from sender", i + 1);
        
        if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }
        
        printf("Sender: Sent message: %s\n", message.mtext);
        i++;
        sleep(1);  // 模拟发送消息的延迟
    }

    return 0;
}
