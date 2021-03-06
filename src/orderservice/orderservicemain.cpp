#include "../../include/orderservice/CServer.h"
#include "../../include/orderservice/orderserviceglobal.h"
#include "../../include/log/log.h"
#include "../../include/idservice/idhelper.h"
#include <signal.h>

void signal_crash_handler(int sig)
{
    LOG_WARN("signal_crash_handler");
    LOG_STOP();
    while (LOG_FINISH() == false)
    {
        sleep(2);
    }

    exit(-1);
}

void signal_exit_handler(int sig)
{
    LOG_WARN("signal_exit_handler");
    LOG_STOP();
    while (LOG_FINISH() == false)
    {
        sleep(2);
    }
    exit(0);
}

int main()
{
    signal(SIGTERM, signal_exit_handler);
    signal(SIGINT, signal_exit_handler);

    // ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    signal(SIGBUS, signal_crash_handler);  // 总线错误
    signal(SIGSEGV, signal_crash_handler); // SIGSEGV，非法内存访问
    signal(SIGFPE, signal_crash_handler);  // SIGFPE，数学相关的异常，如被0除，浮点溢出，等等
    signal(SIGABRT, signal_crash_handler); // SIGABRT，由调用abort函数产生，进程非正常退出
    srand((unsigned)getpid());
    
    LOG_INFO("Order Serivce Start...");
    globalServer.Init();
    globalServer.SetAcceptTcpHandler();
    globalServer.AeMain();
    LOG_INFO("Order Serivce Shutdown...");
    return 0;
}

/* int main()
{
    unsigned long id = getId(0);
    printf("id:%ld\n", id);
    return 0;
} */