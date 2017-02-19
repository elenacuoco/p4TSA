#include <tsaLog.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



namespace tsa {

    void LogInfo(const std::string &s, ...) {
    };

    void LogWarning(const std::string &s, ...) {
    };

    void LogSevere(const std::string &s, ...) {
    };

    void LogSevere(int lvl, const std::string &s, ...) {
    };

    void LogFatal(const std::string &s, ...) {
    };

    void LogDebug(int lvl, const std::string &s, ...) {
    };


#if 0

    FileDescriptor::FileDescriptor(char *filename) {
        mFd = open(filename, O_CREAT | O_TRUNC | O_WRONLY);
    }

    FileDescriptor::FileDescriptor(int fd) {
        mFd = fd;
    }

    FileDescriptor::~FileDescriptor() {
        if (mFd > 2) close(mFd);
    }

    int FileDescriptor::GetId() {
        return mFd;
    }

    LogStream::LogStream(unsigned int level)
    :
    FileDescriptor(STDERR_FILENO), rlog::StdioNode(STDERR_FILENO) {
        if (level & Log_Undef) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel(""));
        }
        if (level & Log_Critical) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("critical"));
        }
        if (level & Log_Error) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("error"));
        }
        if (level & Log_Warning) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("warning"));
        }
        if (level & Log_Notice) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("notice"));
        }
        if (level & Log_Info) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("info"));
        }
        if (level & Log_Debug) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("debug"));
        }
    }

    LogStream::LogStream(char *filename, unsigned int level)
    :
    FileDescriptor(filename), rlog::StdioNode(GetId()) {
        if (level & Log_Undef) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel(""));
        }
        if (level & Log_Critical) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("critical"));
        }
        if (level & Log_Error) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("error"));
        }
        if (level & Log_Warning) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("warning"));
        }
        if (level & Log_Notice) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("notice"));
        }
        if (level & Log_Info) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("info"));
        }
        if (level & Log_Debug) {
            subscribeTo((rlog::RLogNode*)rlog::GetGlobalChannel("debug"));
        }
    }

    LogStream::~LogStream() {

    }

#endif

}
