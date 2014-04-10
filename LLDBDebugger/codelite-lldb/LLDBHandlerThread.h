#ifndef LLDBHANDLERTHREAD_H
#define LLDBHANDLERTHREAD_H

#include <wx/thread.h>
#include <lldb/API/SBListener.h>
#include <lldb/API/SBProcess.h>

/**
 * @class LLDBHandlerThread
 * @author eran
 * @brief Wait for the process events and report any changes to the application
 */
class CodeLiteLLDBApp;
class LLDBHandlerThread : public wxThread
{
    CodeLiteLLDBApp* m_app;
    lldb::SBProcess  m_process;
    lldb::SBListener m_listener;
    
public:
    LLDBHandlerThread(CodeLiteLLDBApp* app, lldb::SBListener listener, lldb::SBProcess process);
    virtual ~LLDBHandlerThread();
    
    void Start() {
        Create();
        Run();
    }

protected:
    virtual void* Entry();
};

#endif // LLDBHANDLERTHREAD_H
